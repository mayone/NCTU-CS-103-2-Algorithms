#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM_WORDS 1024
#define MAX_WORD_LENGTH 32

int main(int argc, char const *argv[])
{
	int i, j, num_words;
	char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
	if (argc == 2) {
		num_words = atoi(argv[1]) < MAX_NUM_WORDS ? atoi(argv[1]) : MAX_NUM_WORDS;
	}
	else {
		num_words = MAX_NUM_WORDS;
	}

	srand(time(NULL));

	for(i = 0; i < num_words; i++) {
		for(j = 0; j < MAX_WORD_LENGTH; j++) {
			words[i][j] = 'a'+(rand()%26);
		}
		words[i][MAX_WORD_LENGTH-1] = '\0';
		printf("%s ", words[i]);
	}
	printf("\n");

	for(i = num_words-1; i >= 0; i--) {
		printf("%s ", words[i]);
	}
	printf("\n");

	return 0;
}