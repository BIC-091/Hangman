#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/**
 * Variables used for the game
 *
 * @param lifes Tries left until the game is lost
 * @param field Current status of the guess letters and letters left to guess
 * @param word_to_guess The word to guess
 * @param guess User guess
 */
struct Game{
    int lifes;
    char field[100];
    char word_to_guess[100];
    char guess[100];
};

/**
 * Outputs how many tries are left and the current the playing field
 *
 * @param field The current progress of the guessing
 * @param lifes Value of how many tries are left
 * @param length Is the length of the playing field
 */
void update_field(char *field, int* lifes){

    printf("\nMy word: ");
    int length = strlen(field);
    for(int i= 0; i < length; i++){
        printf("%c ", field[i]);
    }

    printf("\n");
    printf("\nYou have %d tries left.\n", *lifes);
 
}

/**
 * If the user enters a word it is compared to the guessing word. The user is informed if he won or lost
 *
 * @param hangman Is the word to guess
 * @param guess The users guess
 * @param lifes Is set to 0 if the wrong word is entered
 */
void compare_words(char *hangman, char *guess, int* lifes){

    if (strcmp(guess, hangman) == 0){
        printf("\nYou won!\n");
        
    } else {
        printf("\nWrong!\n");
        *lifes = 0;
        printf("\nYou lost! The word was %s.\n", hangman);
        }
}

/**
 * Compares the userinput letter with every letter of the word to guess and informs the user if he guessed right or not
 *
 * @param hangman Is the word to guess
 * @param guess The users guess
 * @param field The playing field
 * @param lifes If there is no match 1 life is taken
 * @param length The length of the word to guess
 * @param guess_found If a matching letter is found value is set to 1
 */
void compare_letter(char *hangman, char *guess, char *field,int* lifes){

    int length = strlen(hangman);
    int guess_found = 0;

    for(int i= 0; i < length; i++){
        if(guess[0] == hangman[i]){
            field[i] = guess[0];
            guess_found = 1;
        }
    }

    if(!guess_found){
        printf("\nWrong!\n");
        *lifes = *lifes -1;

    } else{
        printf("\nCorrect!\n");
    }
}

/**
 * Chooses randomly a word from the input file
 *
 * @param hangman Word from the input file is stored in this variable
 * @param inputfile File where the words for the game are stored
 * @param word_count Counts the number of words in the inputfile
 * @param random_numb Number that is randomly choosen
 * @param words 2D array that stores each word
 */
void choose_random_word(FILE *inputfile, char *hangman){
    
    int word_count = 0;
    int random_numb;
    char words[100][100];

    while (fscanf(inputfile, "%s", words[word_count]) != EOF) {
        word_count++;
    }
    srand(time(NULL));
    random_numb = rand() % word_count;

    strcpy(hangman, words[random_numb]);
    rewind(inputfile);
}

int main(int argc, char* argv[]) {

    /**
     * Opens the logfile in append mode and if its not possible it prints out an error
     * 
     * @param log_file_name String that contains the name of the logfile
     * @param log_file Opening the logfile in append mode
     */
    char log_file_name[] = "hangman_log.txt";
    FILE *log_file = fopen(log_file_name, "a");

    if (log_file == NULL) {
        printf("Error opening log file!\n");
        return 1;
    }

    /**
     * Checks if an input file was provided as a command line argument. If there is none it prints out an error
     * 
     */
    if (argc < 2) {
        printf("Please provide an input file with words to guess.\n");
        return 1;
    }

    /**
     * Opens the inputfile in read mode and if its not possible it prints out an error
     * 
     * @param input_file_name String that contains the name of the inputfile
     * @param input_file Opening the inputfile in read mode
     */
    char *input_file_name = argv[1];
    FILE *input_file = fopen(input_file_name, "r");

    if (input_file== NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    
    /**
     * Writes the starting date and time to the logfile
     * 
     * @param current_time Stores the current time 
     */
    time_t current_time = time(NULL);
    fprintf(log_file, "\nStart of game: %s\n", ctime(&current_time));

    struct Game test = {0,"", "", ""};

    while (1) {

        test.lifes = 10;

        /**
        * Making sure that the playing field is empty before generating a new word
        * 
        */
        char *temp = "\0";
        for(int i= 0; i < 101; i++){
            test.field[i] = *temp;
            }

        choose_random_word(input_file, test.word_to_guess);
        fprintf(log_file, "     Word to guess: %s\n", test.word_to_guess);

        /**
        * Playing field is being created
        * 
        */
        int length = strlen(test.word_to_guess);
        if(!strchr(test.field, '_')){
            char *temp = "_";
            for(int i= 0; i < length; i++){
                test.field[i] = *temp;
            }
        }

        /**
        * This do while loop ends when the user guesses the word or has no tries
        * 
        */
        do{

            update_field(test.field, &test.lifes);

            while (1) {
                printf("Guess a letter: \n");
                scanf(" %s", test.guess);            
                if (isalpha(test.guess[0])){
                    break;
                }
                printf("Invalid input. Please enter a letter.\n");
            }

            int length_guess = strlen(test.guess);
            for(int i = 0; i < length_guess; i++){
                test.guess[i] = tolower(test.guess[i]);
            }

            fprintf(log_file, "     Guess: %s   %s\n", test.guess, ctime(&current_time));

            if(length_guess == length) {
                compare_words(test.word_to_guess, test.guess, &test.lifes);
                break;

            } else{
                compare_letter(test.word_to_guess, test.guess, test.field, &test.lifes);
            }

            if(test.lifes == 0){
                printf("\nYou lost! The word was %s.\n", test.word_to_guess);
                break;
            }

            if(!strchr(test.field, '_')){
                printf("\nYou won!\n");
                break;
            }

        } while (test.lifes > 0);

        printf("Do you want to play again? (Y/N) ");
        char play_again;
        scanf(" %c", &play_again);

        if (tolower(play_again) != 'y') {
            fprintf(log_file, "\nEnd of game: %s\n", ctime(&current_time));
            break;
        }
    }
    
    fclose(input_file);
    fclose(log_file);
    return 0;
}
