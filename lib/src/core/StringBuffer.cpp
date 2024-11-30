#include <container/StringBuffer.hpp>


void StringBuffer::push(StringView string) {
    if (string.is_empty()) {
        return;
    }

    u32 len = string.size() > 255 ? 255 : string.size();

    // Make sure there is enough space before the end of the data.
    u32 size = len + 2;

    if (_back + size >= _capacity) {

        // Pop off anything stored at the end of the buffer because the back
        // pointer will be wrapped around to the beginning of data and the
        // front pointer must also be wrapped.
        while (_front > _back) {
            pop();
        }

        _data[_back] = 0;
        _back = 0;
    }

    // Pop off strings until there is enough room.
    if (_front >= _back && !is_empty()) {
        while (_front >= _back && _front < _back + size) {
            pop();
        }
    }

    // Write the string to the buffer [len (1), string (len), null(1)]
    _data[_back++] = len;

    while (len--) {
        _data[_back++] = *string++;
    }

    // Explicitly set the null terminator because the string might have been
    // truncated to fit.
    _data[_back++] = '\0';

    // Check for wrapping.
    if (_back == _capacity) {
        _back = 0;
    }

    _space_used += size;
    _size += 1;
}


void StringBuffer::pop() {
    if (is_empty()) {
        return;
    }

    u32 size = _data[_front] + 2;
    _front += size;

    // Wrap the front pointer.
    if (_data[_front] == 0) {
        _front = 0;
    }

    _space_used -= size;
    _size -= 1;
}
