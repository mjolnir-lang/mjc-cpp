#pragma once

#include <core/StringView.hpp>
#include <vector>
#include <cstring>

#include <cstdio>
#include <chrono>
#include <thread>


/// A Robin Hood hash set with indexed element access.
///
/// - Order preserving
/// - High load factor
/// - Indexable
/// - Open addressing
/// - Fibonacci hashing
/// - FNV-1a hashing
/// - 255 character string max
/// - 65535 element max
/// - 
class MjStringSet {
private:

    struct StringRef {
        u8 size;
        u8 chunk;
        u16 offset;

        constexpr
        StringRef(u8 size, u16 offset) noexcept : size(size), offset(offset) {}
    };

    struct Bucket {
        u16 string_id;   // The string ID (index into `_string_refs`)
        u16 string_hash; // The hash of the string.
        u8 string_size;  // The duplicated string size for efficient bucket comparisons on hash collisions
        u8 psl;          // The Probe Sequence Length of the bucket
    };

    Bucket *_buckets;
    StringRef *_string_refs; // indexed from token stream. do not re-order
    std::vector<u8> _string_data; // append only bump allocator. indicies stored in `_ids`
    f32 _max_load_factor;
    u16 _grow_threshold;
    u16 _capacity; // The allocated size of `_buckets`
    u16 _size; // The current size of both `_string_refs` and _buckets`
    u8 _log2_capacity;
public:


    MjStringSet(u16 initial_capacity = 8, f32 max_load_factor = 0.75) noexcept :
        _max_load_factor(max_load_factor),
        _capacity(1),
        _log2_capacity(0)
    {
        // Calculate the minimum capacity we need to be able to store without growing.
        while (_capacity < initial_capacity / _max_load_factor) {
            _capacity <<= 1;
            _log2_capacity += 1;
        }

        _grow_threshold = _capacity * _max_load_factor;
        _string_refs = reinterpret_cast<StringRef *>(malloc(_grow_threshold * sizeof(StringRef)));
        _buckets = reinterpret_cast<Bucket *>(malloc(_capacity * sizeof(Bucket)));
        clear();
    }


    ~MjStringSet() {
        free(_string_refs);
        free(_buckets);
    }


    ///
    /// Operators
    ///


    StringView operator[](u16 id) const noexcept {
        return string(id);
    }


    ///
    /// Properties
    ///


    bool is_empty() const noexcept {
        return _size == 0;
    }


    u16 size() const noexcept {
        return _size;
    }


    u16 capacity() const noexcept {
        return _grow_threshold;
    }


    u16 real_capacity() const noexcept {
        return _capacity;
    }


    u16 space() const noexcept {
        return _grow_threshold - _size;
    }


    u16 real_space() const noexcept {
        return _capacity - _size;
    }


    f32 load_factor() const noexcept {
        return f32(_size) / _capacity;
    }


    StringView string(u16 id) const noexcept {
        return {string_data(id), string_size(id)};
    }


    const u8 *string_data(u16 id) const noexcept {
        return &_string_data[_string_refs[id].offset];
    }


    u8 string_size(u16 id) const noexcept {
        return _string_refs[id].size;
    }


    StringView string_or_null(u16 id) const noexcept {
        return has_string_id(id) ? string(id) : nullptr;
    }


    bool has_string_id(u16 id) const noexcept {
        return id < _size;
    }


    bool has_string(StringView string) const noexcept {
        return has_string_id(id_of(string));
    }


    u16 id_of(StringView string) const noexcept {
        return search(string);
    }


    ///
    /// Methods
    ///


    void set_max_load_factor(f32 max_load_factor) noexcept {
        u16 old_grow_threshold = _grow_threshold;
        _max_load_factor = max_load_factor;
        _grow_threshold = _capacity * _max_load_factor;

        // If we lower the grow threshold enough, we may have to grow more than once on the next insert.
        // Resize now instead.
        if (_size >= _grow_threshold) {
            reserve(_size - _grow_threshold);
        } else if (_grow_threshold > old_grow_threshold) {

            // We still have to make sure we have enough string reference slots.
            _string_refs = reinterpret_cast<StringRef *>(realloc(_string_refs, _grow_threshold * sizeof(StringRef)));
        }
    }


    void clear() noexcept {
        _size = 0;

        for (u32 i = 0; i < _capacity; ++i) {
            _buckets[i].psl = 0;
        }
    }


    u16 search(StringView string) const noexcept {
        u16 string_hash = hash(string);
        u16 bucket_index = index_from_hash(string_hash, _log2_capacity);
        Bucket *bucket = &_buckets[bucket_index];
        u8 psl = 1;

        while (psl <= bucket->psl) {
            if (
                string_hash == bucket->string_hash &&
                string.size() == bucket->string_size &&
                !std::memcmp(string.data(), string_data(bucket->string_id), bucket->string_size)
            ) {
                return bucket->string_id;
            }

            psl += 1;
            bucket_index = (bucket_index + 1) & (_capacity - 1);
            bucket = &_buckets[bucket_index];
        }

        return _size;
    }


    void insert(Slice<const StringView> strings) noexcept {

        // TODO: If there are enough duplicates, then we might resize more than necessary.
        reserve(strings.size());

        for (StringView string : strings) {
            insert(string);
        }
    }


    void insert(const StringView *strings, u32 size) noexcept {
        insert({strings, size});
    }


    u16 insert2(StringView string) noexcept {
        u16 string_id = search(string);

        if (string_id == _size) {
            insert_unique(string);
        }

        return string_id;
    }


    u16 insert(StringView string) noexcept {
        Bucket probe{_size, hash(string), u8(string.size()), 1};
        u16 bucket_index = index_from_hash(probe.string_hash, _log2_capacity);
        Bucket *bucket = &_buckets[bucket_index];

        while (probe.psl <= bucket->psl) {
            if (
                probe.string_hash == bucket->string_hash &&
                probe.string_size == bucket->string_size &&
                !std::memcmp(string.data(), string_data(bucket->string_id), bucket->string_size)
            ) {
                return bucket->string_id;
            }

            probe.psl += 1;
            bucket_index = (bucket_index + 1) & (_capacity - 1);
            bucket = &_buckets[bucket_index];
        }

        if (_size >= _grow_threshold) {
            grow();

            // Reset the probe, because growing the container invalidated it.
            probe.psl = 1;
            bucket_index = index_from_hash(probe.string_hash, _log2_capacity);
            bucket = &_buckets[bucket_index];
        }

        while (bucket->psl > 0) {
            if (bucket->psl < probe.psl) {
                std::swap(*bucket, probe);
            }

            probe.psl += 1;
            bucket_index = (bucket_index + 1) & (_capacity - 1);
            bucket = &_buckets[bucket_index];
        }

        *bucket = probe;
        _string_refs[_size] = {u8(string.size()), u16(_string_data.size())};
        _string_data.insert(_string_data.end(), string.begin(), string.end());
        return _size++;
    }


    u16 insert_unique(StringView string) noexcept {
        if (_size >= _grow_threshold) {
            grow();
        }

        return insert_unique_no_grow(string);
    }


    void insert_unique(Slice<const StringView> strings) noexcept {
        reserve(strings.size());

        for (StringView string : strings) {
            insert_unique_no_grow(string);
        }
    }


    void insert_unique(const StringView *strings, u32 size) noexcept {
        insert_unique({strings, size});
    }


    u16 insert_unique_no_grow(StringView string) noexcept {
        rehash_bucket({_size, hash(string), u8(string.size()), 1});
        _string_refs[_size] = {u8(string.size()), u16(_string_data.size())};
        _string_data.insert(_string_data.end(), string.begin(), string.end());
        return _size++;
    }


    void insert_unique_no_grow(Slice<const StringView> strings) noexcept {
        for (StringView string : strings) {
            insert_unique_no_grow(string);
        }
    }


    void insert_unique_no_grow(const StringView *strings, u32 size) noexcept {
        insert_unique_no_grow({strings, size});
    }


    void reserve(u32 count) {

        // Calculate the maximum capacity we need to be able to store without growing.
        u16 required_capacity = (_size + count) / _max_load_factor;

        // Do nothing if we already have enough space.
        if (required_capacity < _capacity) {
            return;
        }

        // Calculate the number of times to grow.
        u32 new_log2_capacity = _log2_capacity;

        do {
            new_log2_capacity += 1;
        } while ((1 << new_log2_capacity) < required_capacity);

        grow(new_log2_capacity - _log2_capacity);
    }


    void debug() const noexcept {
        printf("Load: (%u/%u) (grow: %u), %4.2f%% (max: %4.2f%%)\n", _size, _capacity, _grow_threshold, 100 * load_factor(), 100 * _max_load_factor);

        for (u32 bucket_index = 0; bucket_index < _capacity; ++bucket_index) {
            const Bucket &bucket = _buckets[bucket_index];

            if (bucket.psl == 0) {
                continue;
            }

            StringView string = this->string(bucket.string_id);
            printf("[%4u] [%2u, %04X] %4u: '%.*s'\n", bucket_index, bucket.psl - 1, bucket.string_hash, bucket.string_id, string.size(), string.data());
        }

        //printf("Data: [%u] '%.*s'\n", u32(_string_data.size()), u32(_string_data.size()), _string_data.data());
        //printf("Refs:\n");

        //for (u32 string_id = 0; string_id < _size; ++string_id) {
        //    StringView string = this->string(string_id);
        //    printf("[%4u] '%.*s'\n", string_id, string.size(), string.data());
        //}
    }


private:


    void grow(u32 n = 1) {

        // Use the old bucket array as the set of probes for rehashing.
        Slice<Bucket> probes{_buckets, _capacity};

        // Resize the container.
        _capacity <<= n;
        _log2_capacity += n;
        _grow_threshold = _capacity * _max_load_factor;

        // Allocate the new bucket array and initialize them to empty.
        _buckets = reinterpret_cast<Bucket *>(malloc(_capacity * sizeof(Bucket)));

        for (u32 i = 0; i < _capacity; ++i) {
            _buckets[i].psl = 0;
        }

        // Reserve more space for the string references.
        _string_refs = reinterpret_cast<StringRef *>(realloc(_string_refs, _grow_threshold * sizeof(StringRef)));

        // Iterate over the old buckets and insert them into the new array.
        for (Bucket &probe : probes) {
            if (probe.psl == 0) {
                continue;
            }

            // Reset the PSL of the probe, because growing the container invalidated it.
            probe.psl = 1;
            rehash_bucket(probe);
        }

        free(probes.data());
    }


    void rehash_bucket(Bucket probe) noexcept {

        // Initialize the probe with the string metadata.
        u16 bucket_index = index_from_hash(probe.string_hash, _log2_capacity);
        Bucket *bucket = &_buckets[bucket_index];

        // Look for the next open bucket.
        while (bucket->psl > 0) {
            if (bucket->psl < probe.psl) {
                std::swap(*bucket, probe);
            }

            probe.psl += 1;
            bucket_index = (bucket_index + 1) & (_capacity - 1);
            bucket = &_buckets[bucket_index];
        }

        // Assign to the open bucket and return the string ID.
        *bucket = probe;
    }


    /// Map the given hash to a bucket index using the desired index bit width.
    static
    constexpr
    u16 index_from_hash(u16 hash, u32 index_bit_width) {

        // Apply a fibonacci hash to the given hash to fit the hash in the given number of bits.
        // This becomes the index into the bucket collection whose size is a power of 2.
        return (hash * 11400714819323198485llu) >> (64 - index_bit_width);
    }


    /// Return the hash of the given string.
    static
    constexpr
    u16 hash(StringView string) noexcept {

        // Calculate the 32 bit FNV-1a hash of the given string.
        u32 hash = 0x811C9DC5u;

        for (u8 ch : string) {
            hash = (hash ^ ch) * 0x01000193u;
        }

        // Apply a fibonacci hash to the result to fit the hash in 16 bits.
        return (hash * 11400714819323198485llu) >> 48;
    }
};
