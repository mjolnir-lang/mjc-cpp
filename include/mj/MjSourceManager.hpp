#pragma once

#include <mj/ast/MjTemplate.hpp>
#include <mj/ast/MjTokenSpan.hpp>
#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjSourceFile.hpp>
#include <mj/ast/MjSourceLocation.hpp>

#include <container/Vector.hpp>


class MjSourceManager {
protected:
    Vector<const MjSourceFile *> _sources;


    ///
    /// Constructors
    ///


    constexpr
    MjSourceManager() noexcept {}


    MjSourceManager(const MjSourceManager &) = delete;


public:


    ///
    /// Operators
    ///


    MjSourceManager &operator=(const MjSourceManager &) = delete;


    ///
    /// Properties
    ///


    constexpr
    Vector<const MjSourceFile *> sources() const noexcept {
        return _sources;
    }


    ///
    /// Source Query Methods
    ///


    /// Return the source ID of the item info.
    u32 source_id_of(MjItemInfo item_info) const noexcept {
        return (item_info.data() >> 50) & 0xFFFFu;
    }


    /// Return the source ID of the item.
    u32 source_id_of(const MjItem *item) const noexcept {
        return source_id_of(item->item_info());
    }


    /// Return the source of the item info.
    const MjSourceFile *source_of(MjItemInfo item_info) const noexcept {
        return _sources[source_id_of(item_info)];
    }


    /// Return the source of the item.
    const MjSourceFile *source_of(const MjItem *item) const noexcept {
        return source_of(item->item_info());
    }


    u32 start_token_offset_of(MjItemInfo item_info) const noexcept {
        return 0;
    }


    u32 end_token_offset_of(MjItemInfo item_info) const noexcept {
        return 0;
    }


    constexpr
    MjToken token_of(u32 source_id, u32 token_offset) const noexcept {
        return source_of(source_id)->token_at(token_offset);
    }


    constexpr
    MjTokenSpan tokens_of(u32 source_id, u32 token_offset) const noexcept {
        return {source_of(source_id)->token_at(token_offset), };
    }


    constexpr
    MjTokenSpan tokens_of(MjItemInfo item_info) const noexcept {
        return {source_of(item_info)->token_at(token(item_info)), item_info.};
    }


    constexpr
    MjTokenSpan tokens_of(const MjItem *item) const noexcept {
        return tokens_of(item->item_info());
    }


    /// Return the source location of the item info.
    MjSourceLocation source_location_of(MjItemInfo item_info) const noexcept {
        return MjSourceLocation(source_of(item_info), tokens_of(item_info));
    }


    ///
    /// Source Update Methods
    ///


    /// Add a new source file and return its source ID for future access.
    u32 add_source_file(const MjSourceFile *source_file) noexcept {
        _sources.push_back(source_file);
        return _sources.size() - 1;
    }
};
