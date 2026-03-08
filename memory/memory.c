#include "./memory.h"

HGLOBAL getStringHandle(const char * output, const size_t len) {
    HGLOBAL handle = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(handle), output, len);
    GlobalUnlock(handle);
    return handle;
}