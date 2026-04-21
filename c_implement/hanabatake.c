#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// ANSI color codes for Windows
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Timer constants
#define FOCUS_TIME 25 * 60  // 25 minutes in seconds
#define BREAK_TIME 5 * 60   // 5 minutes in seconds

// Menu options
typedef enum {
    OPTION_START_TIMER,
    OPTION_SETTINGS,
    OPTION_STATS,
    OPTION_EXIT,
    OPTION_COUNT
} MenuOption;

// ASCII art for Hanabatake (flower garden)
const char* ascii_art = 
    "    _    _    _    _    _    _    \n"
    "   / \\  / \\  / \\  / \\  / \\  / \\   \n"
    "  ( H )( A )( N )( A )( B )( A )  \n"
    "   \\_/  \\_/  \\_/  \\_/  \\_/  \\_/   \n"
    "    _    _    _    _    _    _    \n"
    "   / \\  / \\  / \\  / \\  / \\  / \\   \n"
    "  ( T )( A )( K )( E )(   )(   )  \n"
    "   \\_/  \\_/  \\_/  \\_/  \\_/  \\_/   \n"
    "                                  \n"
    "        🌸  Flower Garden Timer  🌸\n"
    "                                  \n";

// Function prototypes
void clear_screen();
void display_header(int show_art);
void display_menu(int selected);
void handle_input(int *selected, int *running);
void start_timer(int minutes, const char* mode);
void display_timer(int seconds, const char* mode);
void beep_notification();

int main(int argc, char *argv[]) {
    int show_art = 1;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--no-art") == 0) {
            show_art = 0;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Hanabatake Timer - A Pomodoro-style productivity timer\n");
            printf("Usage: hanabatake [options]\n");
            printf("Options:\n");
            printf("  --no-art    Launch without ASCII art\n");
            printf("  --help      Show this help message\n");
            return 0;
        }
    }
    
    // Enable ANSI escape sequences on Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    int selected_option = 0;
    int running = 1;
    
    while (running) {
        clear_screen();
        display_header(show_art);
        display_menu(selected_option);
        handle_input(&selected_option, &running);
    }
    
    clear_screen();
    printf(ANSI_COLOR_CYAN "Thank you for using Hanabatake Timer! 🌸\n" ANSI_COLOR_RESET);
    return 0;
}

void clear_screen() {
    system("cls");
}

void display_header(int show_art) {
    if (show_art) {
        printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, ascii_art);
    } else {
        printf(ANSI_COLOR_CYAN "========================================\n");
        printf(ANSI_COLOR_CYAN "      Hanabatake Timer v1.0          \n");
        printf(ANSI_COLOR_CYAN "    Productivity Blossoms Here      \n");
        printf(ANSI_COLOR_CYAN "========================================\n" ANSI_COLOR_RESET);
    }
    printf("\n");
}

void display_menu(int selected) {
    const char* options[OPTION_COUNT] = {
        "Start Pomodoro Timer (25 min focus / 5 min break)",
        "Settings",
        "View Statistics",
        "Exit"
    };
    
    printf(ANSI_COLOR_YELLOW "Use UP/DOWN arrows to navigate, ENTER to select\n" ANSI_COLOR_RESET);
    printf("------------------------------------------\n\n");
    
    for (int i = 0; i < OPTION_COUNT; i++) {
        if (i == selected) {
            printf(ANSI_COLOR_GREEN "  > " ANSI_COLOR_RESET);
            printf(ANSI_COLOR_GREEN "[ %s ]\n" ANSI_COLOR_RESET, options[i]);
        } else {
            printf("    ");
            printf("%s\n", options[i]);
        }
    }
    printf("\n------------------------------------------\n");
}

// Function to get arrow key input on Windows
int get_arrow_key() {
    int ch = _getch();
    if (ch == 0 || ch == 224) { // Arrow keys produce two codes
        ch = _getch();
        switch (ch) {
            case 72: return 1; // Up arrow
            case 80: return 2; // Down arrow
            case 77: return 3; // Right arrow (Enter alternative)
            case 75: return 4; // Left arrow
        }
    }
    return ch; // Return regular character
}

void handle_input(int *selected, int *running) {
    printf("\nPress UP/DOWN to navigate, ENTER to select, 'q' to quit");
    
    int ch = get_arrow_key();
    
    if (ch == 'q' || ch == 'Q') {
        *running = 0;
        return;
    }
    
    switch (ch) {
        case 1: // Up arrow
            *selected = (*selected - 1 + OPTION_COUNT) % OPTION_COUNT;
            return;
        case 2: // Down arrow
            *selected = (*selected + 1) % OPTION_COUNT;
            return;
        case 13: // Enter key
        case 3:  // Right arrow (alternative)
            // Process selection
            break;
        default:
            return; // Ignore other keys
    }
    
    // If we get here, Enter was pressed
    switch (*selected) {
        case OPTION_START_TIMER:
            clear_screen();
            printf(ANSI_COLOR_GREEN "Starting Pomodoro Timer...\n" ANSI_COLOR_RESET);
            printf("Focus session: 25 minutes\n");
            // For testing, use shorter times
            start_timer(1, "FOCUS");
            printf("\nBreak session: 5 minutes\n");
            start_timer(1, "BREAK");
            printf(ANSI_COLOR_GREEN "\nPomodoro cycle completed! 🌸\n" ANSI_COLOR_RESET);
            printf("Press any key to continue...");
            _getch();
            break;
            
        case OPTION_SETTINGS:
            clear_screen();
            printf(ANSI_COLOR_YELLOW "Settings Menu\n" ANSI_COLOR_RESET);
            printf("(Feature coming soon)\n");
            printf("Press any key to continue...");
            _getch();
            break;
            
        case OPTION_STATS:
            clear_screen();
            printf(ANSI_COLOR_CYAN "Statistics\n" ANSI_COLOR_RESET);
            printf("Total focus sessions: 0\n");
            printf("Total focus time: 0 minutes\n");
            printf("Current streak: 0 days\n");
            printf("\nPress any key to continue...");
            _getch();
            break;
            
        case OPTION_EXIT:
            *running = 0;
            break;
    }
}

void start_timer(int minutes, const char* mode) {
    int total_seconds = minutes * 60;
    time_t start_time = time(NULL);
    char time_str[26];
    
    // Use ctime_s to avoid deprecation warning
    ctime_s(time_str, sizeof(time_str), &start_time);
    
    printf("\n%s timer started at: %s", mode, time_str);
    printf("Time remaining: ");
    
    for (int remaining = total_seconds; remaining >= 0; remaining--) {
        display_timer(remaining, mode);
        Sleep(1000); // Sleep for 1 second
    }
    
    printf("\n");
    beep_notification();
    printf(ANSI_COLOR_GREEN "%s session completed! 🌸\n" ANSI_COLOR_RESET, mode);
}

void display_timer(int seconds, const char* mode) {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    
    const char* color = (strcmp(mode, "FOCUS") == 0) ? ANSI_COLOR_RED : ANSI_COLOR_BLUE;
    
    // Move cursor to beginning of line and print timer
    // Using spaces to clear any leftover characters
    printf("\r%s%s: %02d:%02d remaining          " ANSI_COLOR_RESET, color, mode, minutes, secs);
    fflush(stdout);
}

void beep_notification() {
    // Simple beep for notification
    printf("\a"); // System beep
    // Additional visual notification
    for (int i = 0; i < 3; i++) {
        printf(ANSI_COLOR_YELLOW "✨ " ANSI_COLOR_RESET);
        fflush(stdout);
        Sleep(300);
    }
    printf("\n");
}