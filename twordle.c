//Ian Sanchez
// 04/21/2026
//Project 10

#include <stdio.h>
#define WORD_LENGTH 5
#define MAX_GUESSES 6
#define READFILE "word.txt"

int filecheck(char word[]);
int getGuess(int guessNum, char guess[]);
void toLowerCase(char str[]);
int compareWords(char guess[], char word[]);
void displayGuesses(char guesses[][WORD_LENGTH + 1], int count, char word[], int solved[]);
int charInWord(char c, char word[]);
int alreadyCorrect(char guess[], char word[], int index);
void winMessage(char word[], int guesses);
int checkLetters(char guess[]);


int main(){

char word[WORD_LENGTH + 1];
char guesses[MAX_GUESSES][WORD_LENGTH + 1];
int guessCount = 0;
int won = 0;
int solved[WORD_LENGTH] = {0, 0, 0, 0, 0};

	if(!filecheck(word)){
		return 1;
	}

	while(guessCount < MAX_GUESSES && !won) {
		char guess[WORD_LENGTH + 1];
				if(getGuess(guessCount+1, guess)) {
					for(int i = 0; i <= WORD_LENGTH; i++) {
						guesses[guessCount][i] = guess[i];
					}
						guessCount++;
				for(int i = 0; i < WORD_LENGTH; i++) {
					if(guess[i] == word[i]) {
						solved[i] = 1;
					}
				}
				
					if(compareWords(guess, word)) {
						won = 1;
					}
				
				printf("================================\n");
					if(!won){
						displayGuesses(guesses, guessCount, word, solved);
					}
				}
	}
		if (won){
			winMessage(word, guessCount);
		}
		else{
			printf("You lost, better luck next time!\n");
		}
	return 0;
	
}

int filecheck(char word[]) {
	FILE *file = fopen(READFILE, "r");
		if(file == NULL){
			printf("Sorry, could not get today's word. Try again tomorrow.\n");
			return 0;
		}
	fscanf(file, "%5s", word);
	fclose(file);
	return 1;
}

void toLowerCase(char str[]) {
	int i = 0;
		while (str[i] != '\0') {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] = str[i] + ('a' - 'A');
			}
		i++;
		}
}


int getGuess(int guessNum, char guess[]) {
	
	if(guessNum == 6){
		printf("FINAL GUESS : ");
	}
	else{
		printf("GUESS %d! Enter your guess: ", guessNum);
	}
	scanf("%s", guess);
	
	int length = 0;
	while(guess[length] != '\0'){
		length++;
	}
	if(length != WORD_LENGTH){
		printf("Your guess must be 5 letters long.\nPlease try again: ");
		return 0;
	}
	if(!checkLetters(guess)){
		printf("Your guess must contain only letters.\nPlease try again: ");
		return 0;
	}
	toLowerCase(guess);
	return 1;
}

int checkLetters(char guess[]){
	int i = 0;
	while(guess[i] != '\0'){
		if(!(guess[i] >= 'a' && guess[i] <= 'z') && !(guess[i] >= 'A' && guess[i] <= 'Z')){
			return 0;
		}
		i++;
	}
	return 1;
}
int charInWord(char c, char word[]) {
	for (int i = 0; i < WORD_LENGTH; i++) {
		if (word[i] == c) {
			return 1;
		}
	}
	return 0;
}

int alreadyCorrect(char guess[], char word[], int index) {
	return guess[index] == word[index];
}

int compareWords(char guess[], char word[]) {
	for (int i = 0; i < WORD_LENGTH; i++) {
		if (guess[i] != word[i]) {
			return 0;
		}
	}
	return 1;
}

void displayGuesses(char guesses[][WORD_LENGTH + 1], int count, char word[], int solved[]) {
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < WORD_LENGTH; j++) {
			if (guesses[i][j] == word[j]) {
				printf("%c", guesses[i][j] - ('a' - 'A'));
			}
			else {
				printf("%c", guesses[i][j]);
			}
		}
	printf("\n");

	for (int j = 0; j < WORD_LENGTH; j++) {
		if (guesses[i][j] != word[j] && charInWord(guesses[i][j], word)) {
			int shouldPoint = 0;
			for (int k = 0; k < WORD_LENGTH; k++) {
				if (guesses[i][j] == word[k] && !solved[k]) {
					shouldPoint = 1;
				}
			}
	if (shouldPoint) {
		printf("^");
	}
		else{
			printf(" ");
		}

	}
		else {
			printf(" ");
		}
	}
		printf("\n");
	}
}
void winMessage(char word[], int guesses){
	
	printf("		");
	for(int i = 0; i < WORD_LENGTH; i++){
		
		printf("%c", word[i] - ('a' - 'A'));
	}
	printf("\n");
	
	printf("	You won in %d guess", guesses);
	if(guesses !=1){
		printf("es");
	}
	printf("!\n");
	
	if(guesses==1){
		printf("		GOATED!\n");
	}
	else if(guesses <= 3){
		printf("		Amazing!\n");
	}
	else if(guesses <= 5){
		printf("		Nice!\n");
	}
}
