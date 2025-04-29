//acesta ruleaaza doar in consola
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_COUNT 5
#define WORD_LEN 20

const char* word_list[WORD_COUNT] = {
    "firewall", "trojan", "malware", "cookie", "phishing"
};

void displayWord(const char* word, const int* guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i])
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

int isWordGuessed(const int* guessed, int len) {
    for (int i = 0; i < len; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

int main() {
    srand(time(NULL));
    const char* secret = word_list[rand() % WORD_COUNT];
    int length = strlen(secret);
    int guessed[WORD_LEN] = {0};
    char tried_letters[26] = {0};
    int tries = 0;
    int game_over = 0;

    printf("💾 Welcome to Hangman - IT Edition!\n\n");

    while (!game_over) {
        printf("\nWord: ");
        displayWord(secret, guessed);
        printf("Misses: %d/%d\n", tries, MAX_TRIES);
        printf("Guess a letter: ");

        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (tried_letters[guess - 'a']) {
            printf("You've already tried '%c'!\n", guess);
            continue;
        }

        tried_letters[guess - 'a'] = 1;

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (secret[i] == guess) {
                guessed[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            tries++;
            printf("Wrong guess! ⚠️\n");
        } else {
            printf("Good job! ✅\n");
        }

        if (isWordGuessed(guessed, length)) {
            printf("\n🎉 You guessed the word: %s\n", secret);
            game_over = 1;
        } else if (tries >= MAX_TRIES) {
            printf("\n💀 You've been hanged! The word was: %s\n", secret);
            game_over = 1;
        }
    }

    return 0;
}
