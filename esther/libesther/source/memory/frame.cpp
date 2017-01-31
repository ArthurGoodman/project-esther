#include "frame.h"

#include "memorymanager.h"

Frame *frames = nullptr;

Frame::Frame(const std::function<void(const std::function<void(ManagedObject *&)> &)> &map)
    : map(map)
    , prev(0)
    , next(0) {
    link();
}

Frame::~Frame() {
    unlink();
}

void Frame::mapOnLocals(const std::function<void(ManagedObject *&)> &f) {
    map(f);
}

void Frame::link() {
    next = frames;

    if (frames)
        frames->prev = this;

    frames = this;
}

void Frame::unlink() {
    if (next)
        next->prev = prev;

    if (prev)
        prev->next = next;

    if (frames == this)
        frames = frames->next;
}

Frame *Frame::getNext() {
    return next;
}
