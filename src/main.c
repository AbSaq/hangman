#include <stdio.h>


enum GuessResult {
    CORRECT_GUESS,
    INCORRECT_GUESS,
    DONE_GUESS,
};

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
    const int len = len_of_str(str);
    for (int i = 0; i<len; i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}

void create_progress_word(char * progress_word, const char * from_word) {
    const int len = len_of_str(from_word);
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
        if (input == 10 && ch == ' ') {
            continue;;
        }
        if (input == 10 && ch != ' ') {
            break;
        }
        ch = input;


    }
    return ch;
}

enum GuessResult result_of_guess(const char guessed_character, const char * word_to_guess, const char * progress_word) {
    if (has_char(progress_word, guessed_character)) {
        return DONE_GUESS;
    }
    else if (has_char(word_to_guess, guessed_character)) {
        return CORRECT_GUESS;
    }
    return INCORRECT_GUESS;
}

void run_game(const char * word_to_guess, int attempts) {
    int len = len_of_str(word_to_guess);
    char progress_word[len+1];
    create_progress_word(progress_word, word_to_guess);

    int won = 0;
    printf("guess the word %s.\n", progress_word);
    while (attempts > 0 && !won) {
        const char guessed_character = get_char();


        const enum GuessResult result = result_of_guess(guessed_character, word_to_guess, progress_word);

        if (result == DONE_GUESS) {
            printf("already correctly guessed '%c'.\n", guessed_character);
        }
        else if (result == CORRECT_GUESS) {
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

int is_wanted_category(char * line, char * category) {
    if (len_of_str(line)-4 != len_of_str(category)) {
        return 0;
    }
    const int len = len_of_str(category);
    for (int i = 0; i<len; i++) {
        if (line[i+3] != category[i]) {
            return 0;
        }
    }
    return 1;
}

void remove_new_line(char * word) {
    int len = len_of_str(word);
    for (int i = 0; i<len; i++) {
        if (word[i] == '\n') {
            word[i] = '\0';
            return;
        }
    }
}

void get_word_from_file(char * word, char * category) {
    FILE *words = fopen("src\\words.txt", "r");
    while (1) {
        char line[50];
        fgets(line, 50, words);

        if (line[0] == 'c' && line[1] == ':'  && line[2] == ' ') {
            const int is_wanted_categor = is_wanted_category(line, category);
            if (is_wanted_categor) {
                fgets(word, 50, words);
                remove_new_line(word);
                return;
            }
        }
    }
}

int main() {
    char word[50];
    get_word_from_file(word, "fruits");
    const int attempts = 5;

    run_game(word, attempts);

    return 0;
}



