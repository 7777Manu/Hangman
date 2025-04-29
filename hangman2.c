#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_COUNT 5
#define WORD_LEN 20

const char* word_list[WORD_COUNT] = {
    "firewall", "malware", "trojan", "phishing", "cookie"
};

const char* virus_stages[MAX_TRIES + 1] = {
    "Clean system",
    "Minor threat detected",
    "Virus spreading",
    "Infected files found",
    "Core system breached",
    "Virus critical level",
    "SYSTEM FAILURE"
};

void draw_interface(const char* word, int* guessed, int wrong_guesses) {
    clear();
    mvprintw(1, 2, "VIRUS vs. ANTIVIRUS - IT Hangman Edition");
    mvprintw(3, 2, "Status: %s", virus_stages[wrong_guesses]);

    mvprintw(5, 2, "Word: ");
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i])
            printw("%c ", word[i]);
        else
            printw("_ ");
    }

    mvprintw(7, 2, "Wrong guesses: %d/%d", wrong_guesses, MAX_TRIES);
    mvprintw(9, 2, "Enter a letter: ");
    refresh();
}

void show_bsod() {
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "SYSTEM FAILURE");
    mvprintw(LINES / 2, (COLS - 30) / 2, "Simulated BSOD: Virus Took Over!");
    mvprintw(LINES / 2 + 2, (COLS - 28) / 2, "Press any key to restart...");
    attroff(COLOR_PAIR(2));
    refresh();
    getch();
}

void show_victory(const char* word) {
    clear();
    attron(COLOR_PAIR(3));
    mvprintw(LINES / 2 - 1, (COLS - 30) / 2, "✅ VIRUS ELIMINATED ✅");
    mvprintw(LINES / 2, (COLS - 30) / 2, "Word was: %s", word);
    mvprintw(LINES / 2 + 2, (COLS - 25) / 2, "You saved the system!");
    attroff(COLOR_PAIR(3));
    refresh();
    getch();
}

int is_word_guessed(const int* guessed, int len) {
    for (int i = 0; i < len; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    srand(time(NULL));
    const char* word = word_list[rand() % WORD_COUNT];
    int length = strlen(word);
    int guessed[WORD_LEN] = {0};
    int wrong_guesses = 0;
    int tried[26] = {0};

    while (1) {
        draw_interface(word, guessed, wrong_guesses);
        int ch = getch();
        ch = tolower(ch);

        if (!isalpha(ch)) continue;
        if (tried[ch - 'a']) continue;
        tried[ch - 'a'] = 1;

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (word[i] == ch) {
                guessed[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            wrong_guesses++;
        }

        if (is_word_guessed(guessed, length)) {
            show_victory(word);
            break;
        } else if (wrong_guesses >= MAX_TRIES) {
            show_bsod();
            break;
        }
    }

    endwin();
    return 0;
}
