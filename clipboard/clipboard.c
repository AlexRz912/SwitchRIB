#include "clipboard.h"

void modifyClipboard(HGLOBAL handle) {
    EmptyClipboard(); 
    SetClipboardData(CF_TEXT, handle); 
}

const char * getLatestClipboardValue() {
    HANDLE data = GetClipboardData(CF_TEXT);
    if (data == NULL) {
        return NULL;
    }
    
    const char * text = (const char *)GlobalLock(data);
    if (text == NULL) {
        return NULL;
    }
    
    return text;
}
