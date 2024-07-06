#include <stdio.h>

int len_of_str(const char *str) {
    int i = 0;
    while (1) {
        if (str[i] == '\0') {
            return i;
        }
        i++;
    }
}

int has_char(const char str[], char c) {
    int len = len_of_str(str);
    for (int i = 0; i<len; i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}

void create_progress_word(char * progress_word, const char * from_word) {
    int len = len_of_str(from_word);
    for (int i =0; i<len; i++) {
        if (from_word[i] == ' ') {
            progress_word[i] = ' ';
        }
        else {
            progress_word[i] = '_';

        }
    }
    progress_word[len] = '\0';
}

void update_progress_word(const char * original_word, char *progress_word, char found_char) {
    for (int i = 0; i<len_of_str(original_word); i++) {
        if (original_word[i] == found_char)
            progress_word[i] = found_char;
    }
}


char get_char(void) {
    char ch = ' ';
    while (1) {
        char input = ' ';
        scanf("%c", &input);
        if (input == 10) {
            break;
        }
        ch = input;
    }
    return ch;
}

void run_game(const char * word_to_guess, int attempts) {
    int len = len_of_str(word_to_guess);
    char progress_word[len+1];
    create_progress_word(progress_word, word_to_guess);

    int won = 0;
    while (attempts > 0 && !won) {
        const char guessed_character = get_char();


        const int already_guessed = has_char(progress_word, guessed_character);
        const int guessed_right = has_char(word_to_guess, guessed_character);

        if (already_guessed) {
            printf("already correctly guessed %c.\n", guessed_character);
        }
        else if (guessed_right) {
            update_progress_word(word_to_guess, progress_word, guessed_character);
            printf("correct! %s\n", progress_word);

            won = !has_char(progress_word, '_');

        }
        else {
            attempts--;
            printf("incorrect character! %d/5 attempts left.\n", attempts);
        }
    }

    if (won) {
        printf("congrats, you have won.\n");
    }
    else {
        printf("thumb_down");
    }
}

int main() {
    const char * word = "saudi arabia";
    const int attempts = 5;

    run_game(word, attempts);

    return 0;
}



