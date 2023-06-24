
# Hangman

The main function of this program is to play a game of hangman. It uses a struct called "Game" to store variables related to the game such as the number of lives left, the current status of the guessing letters, and the word to guess. The program uses several functions to perform different tasks in the game.

Following libraries need to be linked to the application:

stdio.h, stdlib.h, string.h, ctype.h, time.h

Execution:

The application is executed by entering ./"Exec_File_Name" "words.txt"

The application will choose a random word from the words text file and print _ for each letter of the word.

You are expected to guess letter by letter or enter the whole word at once. For each wrong guess you will lose 1 point. You have 10 tries. If you guess the whole word wrong you also lose. After entering your guess press enter. If you guessed right the application will show you were the letters are placed in the word and you can guess again. If not the field will not change. 

After you guessed the word or lost all your tries the application will ask you if you want to play again.Enter Y if you want to play again and N if you want to end the game.

You can see when you started your game, your guesses and when you ended the game in the hangman_log.

Completed Tasks:

The main task was solved. The first point was done in an earlier stage of the application via scanf, where the playe could enter a word to guess. It was replaced by the input file.

Task 2 was solved with a function.

Task 3 was solved.

Task 4 was solved.