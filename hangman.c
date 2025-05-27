#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_TRIES 6
#define WORD_LEN 20
#define MAX_MESSAGE_LEN 100
#define MAX_WORDS 1000

typedef struct {
    char words[MAX_WORDS][WORD_LEN];
    int count;
} WordList;

typedef struct {
    int games_played;
    int games_won;
    int games_lost;
} Stats;

Stats stats = {0, 0, 0};
WordList easy_list = {0};
WordList medium_list = {0};
WordList hard_list = {0};

const char* bsod_errors[] = {
    "Critical error 0x000001DEAD: Memory infected.",
    "Virus deleted the operating system.",
    "Illegal access detected at sector 0xFFFF.",
    "Processor overloaded with fear.",
    "System completely compromised.",
    "System files corrupted by virus.",
    "BIOS infection detected!",
    "Kernel panic: too much digital chaos.",
    "Hard disk: No hope found anymore.",
    "Blue Screen of Fun initiated."
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

void delete_temp_file(int mistake_count) {
    char filename[256];
    snprintf(filename, sizeof(filename), "temp_files/file%d.tmp", mistake_count);
    remove(filename);
}

int get_hint(const char* word, const int* guessed, int len) {
    for (int i = 0; i < len; i++) {
        if (!guessed[i]) return i;
    }
    return -1;
}

void init_colors() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
}

int load_words(const char* filename, WordList* list) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;
    list->count = 0;
    while (fgets(list->words[list->count], WORD_LEN, file)) {
        list->words[list->count][strcspn(list->words[list->count], "\r\n")] = 0;
        if (strlen(list->words[list->count]) > 0) {
            list->count++;
            if (list->count >= MAX_WORDS) break;
        }
    }
    fclose(file);
    return 1;
}

void load_stats(Stats* s) {
    FILE* f = fopen("stats.dat", "r");
    if (!f) return;
    fscanf(f, "%d %d %d", &s->games_played, &s->games_won, &s->games_lost);
    fclose(f);
}

void save_stats(Stats* s) {
    FILE* f = fopen("stats.dat", "w");
    if (!f) return;
    fprintf(f, "%d %d %d\n", s->games_played, s->games_won, s->games_lost);
    fclose(f);
}

void glitch_effect(int max_duration_ms) {
    timeout(30);
    int elapsed = 0;
    int ch;
    while (elapsed < max_duration_ms) {
        for (int i = 0; i < 100; i++) {
            int y = rand() % LINES;
            int x = rand() % COLS;
            char c = 33 + rand() % 94;
            attron(COLOR_PAIR(4) | A_BOLD);
            mvaddch(y, x, c);
            attroff(COLOR_PAIR(4) | A_BOLD);
        }
        refresh();
        ch = getch();
        if (ch != ERR) break;
        napms(30);
        elapsed += 30;
    }
    timeout(-1);
}

void draw_virus(int wrong_guesses) {
    int start_row = 15;
    attron(COLOR_PAIR(4));
    for (int i = 0; i < MAX_TRIES; i++) {
        mvprintw(start_row + i, 0, "%*s", COLS, "");
    }
    for (int i = 0; i < wrong_guesses; i++) {
        mvprintw(start_row + i, 4, "  (x_x)  <- virus level %d", i + 1);
    }
    attroff(COLOR_PAIR(4));
}

void draw_title_with_logo() {
    const char* title = "VIRUS vs. ANTIVIRUS";
    const char* subtitle = "IT Hangman Edition";
    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(1, (COLS - strlen(title)) / 2, "%s", title);
    attroff(COLOR_PAIR(4) | A_BOLD);
    attron(COLOR_PAIR(5));
    mvprintw(2, (COLS - strlen(subtitle)) / 2, "%s", subtitle);
    attroff(COLOR_PAIR(5));
}

void draw_interface(const char* word, const int* guessed, int wrong_guesses, const int* tried, const char* difficulty_name) {
    clear();
    draw_title_with_logo();
    attron(COLOR_PAIR(6));
    char difficulty_text[MAX_MESSAGE_LEN];
    snprintf(difficulty_text, sizeof(difficulty_text), "Difficulty: %s", difficulty_name);
    mvprintw(4, (COLS - strlen(difficulty_text)) / 2, "%s", difficulty_text);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(5) | A_BOLD);
    const char* status_text = virus_stages[wrong_guesses];
    mvprintw(6, (COLS - strlen(status_text)) / 2, "%s", status_text);
    attroff(COLOR_PAIR(5) | A_BOLD);
    int word_len = strlen(word);
    int word_start_col = (COLS - (word_len * 2)) / 2;
    move(8, word_start_col);
    for (int i = 0; i < word_len; i++) {
        if (guessed[i]) {
            attron(COLOR_PAIR(3) | A_BOLD);
            addch(word[i]);
            attroff(COLOR_PAIR(3) | A_BOLD);
        } else {
            addch('_');
        }
        addch(' ');
    }
    char wrong_str[MAX_MESSAGE_LEN];
    snprintf(wrong_str, sizeof(wrong_str), "Wrong guesses: %d/%d", wrong_guesses, MAX_TRIES);
    mvprintw(10, (COLS - strlen(wrong_str)) / 2, "%s", wrong_str);
    const char* tried_text = "Letters tried: ";
    int total_len = strlen(tried_text);
    int tried_letters_count = 0;
    for (int i = 0; i < 26; i++) if (tried[i]) tried_letters_count += 2;
    total_len += tried_letters_count;
    int tried_x = (COLS - total_len) / 2;
    mvprintw(12, tried_x, "%s", tried_text);
    int pos_x = tried_x + strlen(tried_text);
    for (int i = 0; i < 26; i++) {
        if (tried[i]) {
            if (strchr(word, i + 'a')) {
                attron(COLOR_PAIR(3));
                mvaddch(12, pos_x++, i + 'a');
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(4));
                mvaddch(12, pos_x++, i + 'a');
                attroff(COLOR_PAIR(4));
            }
            mvaddch(12, pos_x++, ' ');
        }
    }
    mvprintw(16, (COLS - 30) / 2, "Files deleted: %d of 6", wrong_guesses);
    draw_virus(wrong_guesses);
    refresh();
}

void show_bsod() {
    glitch_effect(1000);
    clear();
    beep();
    flash();
    attron(COLOR_PAIR(2));
    for (int i = 0; i < LINES; i++) {
        mvhline(i, 0, ' ', COLS);
    }
    int err_index = rand() % (sizeof(bsod_errors) / sizeof(bsod_errors[0]));
    for (int i = 0; i < 20; i++) {
        int y = (LINES / 2 - 3) + rand() % 7;
        int x = (COLS - 30) / 2 + rand() % 10 - 5;
        mvprintw(y, x, "[[ SYSTEM FAILURE DETECTED ]]");
        refresh();
        napms(20);
    }
    attron(A_BOLD);
    mvprintw(LINES / 2 - 2, (COLS - 28) / 2, "[[ SYSTEM FAILURE DETECTED ]]");
    attroff(A_BOLD);
    mvprintw(LINES / 2, (COLS - strlen(bsod_errors[err_index])) / 2, "%s", bsod_errors[err_index]);
    mvprintw(LINES / 2 + 2, (COLS - 38) / 2, "Initiating memory dump... (just kidding)");
    mvprintw(LINES / 2 + 4, (COLS - 26) / 2, "Saving game stats... ERROR.");
    for (int i = 5; i >= 1; i--) {
        attron(A_BLINK);
        mvprintw(LINES / 2 + 6, (COLS - 36) / 2, "System will auto-reboot in %d...", i);
        attroff(A_BLINK);
        refresh();
        napms(1000);
    }
    flash();
    beep();
    clear();
    for (int i = 0; i <= COLS; i++) {
        mvhline(LINES / 2, 0, '#', i);
        refresh();
        napms(5);
    }
    attroff(COLOR_PAIR(2));
    refresh();
    napms(300);
}

void show_victory(const char* word) {
    clear();
    curs_set(0);
    int center_x = COLS / 2;
    int center_y = LINES / 2;
    const char* message1 = "VIRUS ELIMINATED!";
    const char* message2 = "The word was: ";
    const char* message3 = "System is secure!";
    attron(A_BOLD);
    for (int i = 0; i < (int)strlen(message1); i++) {
        attron(COLOR_PAIR(3));
        mvaddch(center_y - 2, center_x - strlen(message1)/2 + i, message1[i]);
        attroff(COLOR_PAIR(3));
        refresh();
        beep();
        napms(100);
    }
    attroff(A_BOLD);
    char line[100];
    snprintf(line, sizeof(line), "%s%s", message2, word);
    attron(COLOR_PAIR(6));
    mvprintw(center_y, center_x - strlen(line)/2, "%s", line);
    attroff(COLOR_PAIR(6));
    refresh();
    napms(700);
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(center_y + 2, center_x - strlen(message3)/2, "%s", message3);
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
    napms(1000);
    const char* explosion[] = {
        "   \\ | /    ",
        " '-.;;;.-'  ",
        "-==;;;;;==- ",
        " '-.;;;.-'  ",
        "   / | \\    "
    };
    for (int i = 0; i < 7; i++) {
        int color = (i % 2) ? 3 : 5;
        attron(COLOR_PAIR(color) | A_BOLD);
        for (int j = 0; j < 5; j++) {
            mvprintw(center_y + 4 + j, center_x - 6, "%s", explosion[j]);
        }
        attroff(COLOR_PAIR(color) | A_BOLD);
        refresh();
        beep();
        napms(200);
        clear();
    }
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(center_y, center_x - 18, "Press any key to continue...");
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
    getch();
}

void show_intro() {
    clear();
    attron(COLOR_PAIR(6));
    mvprintw(LINES / 2 - 2, (COLS - 30) / 2, "Initializing antivirus...");
    refresh();
    napms(1000);
    for (int i = 0; i < 20; i++) {
        mvprintw(LINES / 2, (COLS - 20) / 2 + i, "|");
        refresh();
        napms(70);
    }
    mvprintw(LINES / 2 + 2, (COLS - 25) / 2, "Scan complete.");
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

const char* choose_word(int difficulty) {
    switch (difficulty) {
        case 1: return easy_list.words[rand() % easy_list.count];
        case 2: return medium_list.words[rand() % medium_list.count];
        case 3: return hard_list.words[rand() % hard_list.count];
        default: return easy_list.words[0];
    }
}

void show_stats() {
    clear();
    attron(COLOR_PAIR(6));
    mvprintw(LINES / 2 - 3, (COLS - 20) / 2, "Game Statistics");
    mvprintw(LINES / 2 - 1, (COLS - 40) / 2, "Games played: %d", stats.games_played);
    mvprintw(LINES / 2, (COLS - 40) / 2, "Games won: %d", stats.games_won);
    mvprintw(LINES / 2 + 1, (COLS - 40) / 2, "Games lost: %d", stats.games_lost);
    mvprintw(LINES / 2 + 3, (COLS - 50) / 2, "Press 'R' to reset statistics");
    mvprintw(LINES / 2 + 4, (COLS - 45) / 2, "Press any other key to return...");
    attroff(COLOR_PAIR(6));
    refresh();
    int ch = getch();
    if (ch == 'R' || ch == 'r') {
        stats.games_played = 0;
        stats.games_won = 0;
        stats.games_lost = 0;
        save_stats(&stats);
        clear();
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(LINES / 2, (COLS - 23) / 2, "Game Statistics reset!");
        attroff(COLOR_PAIR(3) | A_BOLD);
        refresh();
        napms(1500);
    }
}

void game_loop(int difficulty) {
    const char* difficulty_name = (difficulty == 1) ? "Easy level" : (difficulty == 2) ? "Medium level" : "Hard level";
    const char* word = choose_word(difficulty);
    int word_len = strlen(word);
    int guessed[word_len];
    memset(guessed, 0, sizeof(guessed));
    int tried[26];
    memset(tried, 0, sizeof(tried));
    int wrong_guesses = 0;
    stats.games_played++;
    while (wrong_guesses < MAX_TRIES) {
        draw_interface(word, guessed, wrong_guesses, tried, difficulty_name);
        if (wrong_guesses >= 4) {
            int hint_index = get_hint(word, guessed, word_len);
            if (hint_index != -1) {
                mvprintw(14, (COLS - 30) / 2, "Hint: Try the letter '%c'", word[hint_index]);
                refresh();
            }
        }
        int ch = getch();
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z') {
            if (tried[ch - 'a']) continue;
            tried[ch - 'a'] = 1;
            int found = 0;
            for (int i = 0; i < word_len; i++) {
                if (word[i] == ch) {
                    guessed[i] = 1;
                    found = 1;
                }
            }
            if (!found) {
                wrong_guesses++;
                delete_temp_file(wrong_guesses);
            }
            if (is_word_guessed(guessed, word_len)) {
                stats.games_won++;
                draw_interface(word, guessed, wrong_guesses, tried, difficulty_name);
                show_victory(word);
                return;
            }
        }
    }
    stats.games_lost++;
    show_bsod();
}

void show_menu() {
    clear();
    draw_title_with_logo();
    attron(COLOR_PAIR(5));
    mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "1. Start");
    mvprintw(LINES / 2, (COLS - 20) / 2, "2. Game Statistics");
    mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "3. Exit");
    attroff(COLOR_PAIR(5));
    mvprintw(LINES - 2, 0, "Choose an option and press 1, 2 or 3 according to your preference...");
    refresh();
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_colors();
    srand(time(NULL));
    if (COLS < 60 || LINES < 24) {
        endwin();
        printf("The window must be at least 60x24. Resize the terminal.\n");
        return 1;
    }
    if (!load_words("easy.txt", &easy_list) ||
        !load_words("medium.txt", &medium_list) ||
        !load_words("hard.txt", &hard_list)) {
        endwin();
        printf("Error loading word files. Make sure the files easy.txt, medium.txt and hard.txt exist.\n");
        return 1;
    }
    load_stats(&stats);
    int choice = 0;
    while (1) {
        show_menu();
        int ch = getch();
        if (ch == '1') {
            show_intro();
            clear();
            attron(COLOR_PAIR(6));
            mvprintw(LINES / 2 - 2, (COLS - 25) / 2, "Choose the difficulty:");
            mvprintw(LINES / 2, (COLS - 20) / 2, "1. Easy level");
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "2. Medium level");
            mvprintw(LINES / 2 + 2, (COLS - 20) / 2, "3. Hard level");
            attroff(COLOR_PAIR(6));
            refresh();
            int diff_ch = getch();
            if (diff_ch >= '1' && diff_ch <= '3') {
                game_loop(diff_ch - '0');
                save_stats(&stats);
            }
        } else if (ch == '2') {
            show_stats();
        } else if (ch == '3') {
            break;
        }
    }
    endwin();
    return 0;
}
