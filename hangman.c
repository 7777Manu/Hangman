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

void glitch_effect() {
    for (int i = 0; i < 50; i++) {  // mai multe artefacte
        int y = rand() % LINES;
        int x = rand() % COLS;
        char chaos = 33 + rand() % 94;  // caractere vizibile, variate
        attron(COLOR_PAIR(5));
        mvaddch(y, x, chaos);
        attroff(COLOR_PAIR(5));
    }
    refresh();
    napms(100);
}


void draw_virus(int wrong_guesses) {
    int start_row = 12;
    attron(COLOR_PAIR(4));
    for (int i = 0; i < MAX_TRIES; i++) {
        mvprintw(start_row + i, 0, "%*s", COLS, "");  // curăță linia complet
    }
    for (int i = 0; i < wrong_guesses; i++) {
        mvprintw(start_row + i, 4, "  (x_x)  <- virus level %d", i + 1);
    }
    attroff(COLOR_PAIR(4));
}

void draw_title_with_logo(int COLS) {
    const char* logo_lines[] = {
        "  /\\",
        " /  \\",
        " |[]|",
        " \\__/"
    };

    const char* line1 = "VIRUS VS. ANTIVIRUS";
    const char* line2 = "HANGMAN EDITION";

    // Dimensiuni logo
    int logo_width = 5; // cel mai lung line are 5 caractere

    // Calculăm start col pentru titlu, lăsând spațiu pentru logo + 2 spații
    int title_start_col = (COLS - strlen(line1) - logo_width - 2) / 2 + logo_width + 2;
    int title_start_col2 = (COLS - strlen(line2) - logo_width - 2) / 2 + logo_width + 2;

    // Desenăm logo în stânga, de la linia 0 la 3
    for (int i = 0; i < 4; i++) {
        mvprintw(i, title_start_col - logo_width - 2, "%s", logo_lines[i]);
    }

    attron(A_BOLD);
    mvprintw(1, title_start_col, "%s", line1);
    mvprintw(2, title_start_col2, "%s", line2);
    attroff(A_BOLD);
}


void draw_interface(const char* word, int* guessed, int wrong_guesses, const int* tried) {
    for (int row = 1; row < 15; row++) {
    move(row, 0);
    clrtoeol();
}
    attron(COLOR_PAIR(5));
    mvprintw(3, 2, "Status: %s", virus_stages[wrong_guesses]);
    attroff(COLOR_PAIR(5));

    mvprintw(5, 2, "Word: ");
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i])
            printw("%c ", word[i]);
        else
            printw("_ ");
    }

    mvprintw(7, 2, "Wrong guesses: %d/%d", wrong_guesses, MAX_TRIES);

    mvprintw(9, 2, "Letters tried: ");
    for (int i = 0; i < 26; i++) {
        if (tried[i]) printw("%c ", i + 'a');
    }

    mvprintw(11, 2, "Enter a letter: ");
    refresh();
    draw_virus(wrong_guesses);
    draw_title_with_logo(COLS);

}

void show_bsod() {
    clear();
    attron(COLOR_PAIR(2));
    for (int i = 0; i < LINES; i++) {
        mvhline(i, 0, ' ', COLS);
    }
    mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "💀 SYSTEM FAILURE 💀");
    mvprintw(LINES / 2, (COLS - 36) / 2, "Simulare BSOD: Virusul a infectat sistemul!");
    mvprintw(LINES / 2 + 2, (COLS - 30) / 2, "Apasa orice tasta pentru restart...");
    attroff(COLOR_PAIR(2));
    refresh();
    getch();
}

void show_victory(const char* word) {
    clear();
    attron(COLOR_PAIR(3));
    mvprintw(LINES / 2 - 1, (COLS - 30) / 2, "✅ VIRUS ELIMINAT ✅");
    mvprintw(LINES / 2, (COLS - 30) / 2, "Cuvantul era: %s", word);
    mvprintw(LINES / 2 + 2, (COLS - 30) / 2, "Sistemul este in siguranta!");
    attroff(COLOR_PAIR(3));
    refresh();
    getch();
}

void show_intro() {
    clear();
    attron(COLOR_PAIR(6));
    mvprintw(LINES / 2 - 2, (COLS - 30) / 2, "Initializam antivirusul...");
    refresh();
    napms(1000);
    for (int i = 0; i < 20; i++) {
        mvprintw(LINES / 2, (COLS - 20) / 2 + i, "|");
        refresh();
        napms(70);
    }
    mvprintw(LINES / 2 + 2, (COLS - 25) / 2, "Scanare completa.");
    attroff(COLOR_PAIR(6));
    refresh();
    napms(800);
}

int is_word_guessed(const int* guessed, int len) {
    for (int i = 0; i < len; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

int main() {
    initscr();
    int COLS = getmaxx(stdscr);
    int LINES = getmaxy(stdscr);

    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);   // titlu
    init_pair(2, COLOR_WHITE, COLOR_BLUE);    // BSOD
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // victorie
    init_pair(4, COLOR_RED, COLOR_BLACK);     // virus
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // status
    init_pair(6, COLOR_CYAN, COLOR_BLACK);    // intro

    srand(time(NULL));

    show_intro();
    show_intro();
clear();
refresh();
    int playing = 1;
    while (playing) {
        const char* word = word_list[rand() % WORD_COUNT];
        int length = strlen(word);
        int guessed[WORD_LEN] = {0};
        int wrong_guesses = 0;
        int tried[26] = {0};
        int game_over = 0;

        while (!game_over) {
            draw_interface(word, guessed, wrong_guesses, tried);
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

            if (found) {
                mvprintw(13, 2, "🛡️ Litera corecta!");
                clrtoeol();
            } else {
                wrong_guesses++;
                glitch_effect();
                mvprintw(13, 2, "⚠️ Virusul avanseaza...");
                clrtoeol();
            }

            refresh();
            napms(700);

            if (is_word_guessed(guessed, length)) {
                show_victory(word);
                game_over = 1;
            } else if (wrong_guesses >= MAX_TRIES) {
                show_bsod();
                game_over = 1;
            }
        }

        clear();
        mvprintw(LINES / 2, (COLS - 30) / 2, "Joci din nou? (y/n): ");
        refresh();
        int answer = tolower(getch());
        if (answer != 'y') {
            playing = 0;
        }
    }

    endwin();
    return 0;
}
