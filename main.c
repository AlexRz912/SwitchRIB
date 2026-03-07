#include <stdio.h>
#include <Windows.h>

int main() {
    const char* output = "FRXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    const size_t len = strlen(output) + 1;

    //Requires GetSystemInfo for page size and allocation granularity
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len); 
    LPVOID fdfd = VirtualAlloc(NULL, NULL, MEM_COMMIT, );
    //Could be potentially improved using HeapAlloc/VirtualAlloc
    /*
        HGLOBAL is a data structure specifically made for creating a handle
        a handle allows kernel to isolate memory access and give access to data via ids
    */
    memcpy(GlobalLock(hMem), output, len);
    // virtualLock
    GlobalUnlock(hMem); // GlobalUnlock ?
    // virtualUnlock

    OpenClipboard(0); // 
    EmptyClipboard(); // 
    SetClipboardData(CF_TEXT, hMem); // 
    CloseClipboard(); // 
    return 0;
}