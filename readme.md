# SwitchRIB

##  Project

This is an educational project demonstrating a clipboard hijacker malware for Windows. The malware, once installed on a PC, monitors the clipboard for copied bank account details. If detected, it modifies the clipboard content to replace the original IBAN with a different one, potentially leading to incorrect fund transfers if the user does not verify the bank account details.

**Disclaimer:** This project is strictly for educational and research purposes to understand malware behavior and security vulnerabilities. Do not use or distribute this code for malicious intent.

## Development Approach

My initial approach involved checking if Ctrl+C was pressed. To do this, I took the time to research how Windows handles keyboard input, as documented in [windows_handling_keyboard.md](windows_handling_keyboard.md). However, as I was reading the docs, I could come up: simply monitoring the clipboard to modify its content if it looked like an IBAN.




