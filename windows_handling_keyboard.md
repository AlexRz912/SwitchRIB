# Windows Keyboard Input Overview

- This is a brief summary of Keyboard Input handling from the driver to the window receiving user input

**Source:** [Microsoft Docs - About Keyboard Input](https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input)

## Defining Active Windows

### Active Window Management  
- **GetActiveWindow** / **SetActiveWindow**
  - `WM_ACTIVATE` : message sent by system to Window Default Proc to set keyboard focus to new active window

### Window Focus Management
- **GetFocus** / **SetFocus**
  - `WM_SETFOCUS` : message sent to window that gained focus
  - `WM_KILLFOCUS` : message sent to window that lost focus

### Additional Input Control
- **BlockInput** : blocks all keyboard and mouse input
- **SendInput** : sends input events (simulation of input event)

## Keystroke Messages

### Key Press Events
- **WM_KEYDOWN** : happens when a key is pressed
- **WM_SYSKEYDOWN** : system key pressed (not used by applications)

**Message Flags:**
- Extended Key flag
- Transition state flag
- Previous character
- Context code
- Repeat count

### Key Release Events
- **WM_KEYUP** : happens when a key is released
- **WM_SYSKEYUP** : system key released

> **Note:** System keys need to be passed from windowProcedure to `DefWindowProc` to handle alt

## Hardware Communication & Translation

### HID (Human Interface Devices) Specification
Modern keyboards use the **HID specification** to communicate with a computer. The keyboard driver:
1. Receives HID Usage values from the keyboard
2. Converts them to scan codes
3. Passes them to system message queue

### Message Translation

**TranslateMessage Function:**
- Translates keydowns into character messages
- Passes a `WM_KEYDOWN` or `WM_SYSKEYDOWN` message to the keyboard layout to convert it into character code

**Keyboard Layout & Language Management:**

Applications are generally not expected to manipulate input languages directly. Instead:
- The user sets up language and layout combinations
- The user switches among them

**ActivateKeyboardLayout:**
- Activates a specific keyboard layout for the current task
- Called when the user clicks into text marked with a different language
- Parameter `hkl` can be either:
  - A handle to the keyboard layout
  - A zero-extended language identifier

**LoadKeyboardLayout:**
- Called to load a keyboard layout based on a specific language
- Used to get the appropriate layout for a language