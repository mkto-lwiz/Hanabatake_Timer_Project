# Hanabatake Timer - C Implementation

This is a C implementation of the Hanabatake Timer CLI program as described in the original README.md. The program is a Pomodoro-style productivity timer with a flower garden theme.

## Features Implemented

1. **CLI Interface**: Interactive menu navigation using arrow keys
2. **ANSI-colored UI**: Colorful terminal interface with ANSI escape sequences
3. **ASCII Art**: Optional ASCII art display (can be disabled with `--no-art`)
4. **Timer Functionality**: Pomodoro timer with focus (25 min) and break (5 min) sessions
5. **Command Line Options**:
   - `hanabatake` - Launch with ASCII art
   - `hanabatake --no-art` - Launch without ASCII art
   - `hanabatake --help` - Show help message

## Technical Details

- **Language**: C (compiled with Clang)
- **Platform**: Windows (uses Windows API for console operations)
- **Dependencies**: Standard C library, Windows.h, conio.h
- **Compilation**: Uses Clang compiler as specified in the requirements

## Code Structure

- `hanabatake.c` - Main source file containing all functionality
- `hanabatake.exe` - Compiled executable
- `test_hanabatake.bat` - Test script to demonstrate functionality

## Key Functions

1. `main()` - Entry point, handles command line arguments
2. `display_header()` - Shows ASCII art or simple header
3. `display_menu()` - Displays interactive menu with selection
4. `handle_input()` - Processes arrow key navigation and selections
5. `start_timer()` - Runs the countdown timer for focus/break sessions
6. `display_timer()` - Shows countdown timer with color coding
7. `beep_notification()` - Provides audio/visual notification when timer completes

## How to Compile

```bash
clang -o hanabatake.exe hanabatake.c
```

## How to Run

1. **With ASCII art**: `hanabatake.exe`
2. **Without ASCII art**: `hanabatake.exe --no-art`
3. **Help**: `hanabatake.exe --help`

## Navigation

- Use **UP/DOWN arrow keys** to navigate menu
- Press **ENTER** to select an option
- Press **'q'** to quit the program

## Timer Features

- Focus sessions: 25 minutes (configurable in code)
- Break sessions: 5 minutes (configurable in code)
- Visual countdown with color coding (red for focus, blue for break)
- Audio/visual notification when session completes
- Test mode uses 1-minute sessions for quick testing

## Future Enhancements (from original README)

This implementation covers Phase 1 (Functional Timer) from the original roadmap. Future enhancements could include:

1. **Persistence** - Export sessions to JSON, local file storage
2. **CLI UX Improvements** - Cross-platform support, better terminal rendering
3. **Visualization Layer** - Web dashboard with Three.js
4. **Session Classification** - Tag sessions (Work/Study/Coding/Reading)
5. **Statistics** - CLI analytics with total focus time, weekly trends
6. **Configuration System** - User config file for timer durations, themes

## Limitations

- Windows-only due to Windows API dependencies (`windows.h`, `conio.h`)
- Basic arrow key navigation (could be enhanced with more robust input handling)
- No persistence layer yet (sessions not saved to disk)

## Testing

Run the test script to see the program in action:
```bash
test_hanabatake.bat
```

Or test manually:
```bash
hanabatake.exe --help
hanabatake.exe --no-art