#include <stdio.h>
#include <stdlib.h>



int len_of_str(char *str) {
    int i = 0;
    while (1) {
        if (str[i] == '\0') {
            return i;
        }
        i++;
    }
}

int has_char(char str[], char c) {
    int len = len_of_str(str);
    for (int i = 0; i<len; i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}

void create_progress_word(char * progress_word) {
    int len = len_of_str(progress_word);
    for (int i =0; i<len; i++) {
        progress_word[i] = '_';
    }
    progress_word[len-1] = '\0';
}

void update_progress_word(char *original_word, char *empty_word, char found_char) {
    //printf("update_progress (%s) (%s) (%c)\n", original_word, empty_word, found_char);
    for (int i = 0; i<len_of_str(original_word); i++) {
        if (original_word[i] == found_char)
            empty_word[i] = found_char;
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

int main() {
    short int attempts = 5;
    char word_to_guess[] = "dread";
    int len = len_of_str(word_to_guess);

    char progress_word[len+1];
    create_progress_word(progress_word);

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

            if (!has_char(progress_word, '_')) {
                won = 1;
            }
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

