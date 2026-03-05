#include "handler.h"

#include "utils/utils.h"

int checkCopyShortcut(void) {
    if (_kbhit()) {
        return _getch();
    }
}