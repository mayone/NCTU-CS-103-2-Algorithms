#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_WORDS 1024
#define MAX_WORD_LENGTH 32
#define MAX_LINE_SIZE (MAX_NUM_WORDS*(MAX_WORD_LENGTH+1))
#define TABLE_SIZE (MAX_NUM_WORDS*2 -1)


typedef struct _drawer {
	char word[MAX_WORD_LENGTH];
} drawer;

typedef struct _hash_table {
	int not_empty[TABLE_SIZE];
	drawer drawers[TABLE_SIZE];
} hash_table;

int insert_line(char *line, hash_table *table);
int search_line(char *line, hash_table *table, int num_words);

void insert(char *word, hash_table *table);
int search(char *word, hash_table *table);

int h(int k, int i);

int main(int argc, char const *argv[])
{
	int i, match, num_words;
	char line[MAX_LINE_SIZE];
	hash_table table;

	// get line of words and insert to table
	fgets(line, MAX_LINE_SIZE, stdin);
	num_words = insert_line(line, &table);

	// get line of words and search in table
	fgets(line, MAX_LINE_SIZE, stdin);
	match = search_line(line, &table, num_words);
	if (match) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}

	return 0;
}

int insert_line(char *line, hash_table *table)
{
	int pos = 0, num_words = 0;
	char word[MAX_WORD_LENGTH];

	while(pos < strlen(line)) {
		sscanf(line+pos, "%s", word);
		num_words++;
		insert(word, table);
		pos += strlen(word)+1;
	}

	return num_words;
}

int search_line(char *line, hash_table *table, int num_words)
{
	int pos = 0, match = 1, word_count = 0;
	char word[MAX_WORD_LENGTH];

	while(pos < strlen(line)) {
		sscanf(line+pos, "%s", word);
		word_count++;
		match &= search(word, table);
		pos += strlen(word)+1;
	}
	if (word_count != num_words) {
		match = 0;
	}

	return match;
}

void insert(char *word, hash_table *table)
{
	int i, key = 0, drawer_id, existed = 0;
	int h1, h2;

	for(i = 0; i < strlen(word); i++) {
		key += word[i];
	}

	i = 0;
	h1 = key % TABLE_SIZE;
	h2 = 1 + (key % (TABLE_SIZE-1));
	drawer_id = (h1 + i*h2) % TABLE_SIZE;
	while(table->not_empty[drawer_id]) {
		if (!strcmp(table->drawers[drawer_id].word, word)) {
			existed = 1;
			break;
		}
		drawer_id = (h1 + ++i*h2) % TABLE_SIZE;
	}

	if (!existed) {
		strcpy(table->drawers[drawer_id].word, word);
		table->not_empty[drawer_id] = 1;
	}
}

int search(char *word, hash_table *table)
{
	int i, key = 0, drawer_id, found = 0;
	int h1, h2;

	for(i = 0; i < strlen(word); i++) {
		key += word[i];
	}

	i = 0;
	h1 = key % TABLE_SIZE;
	h2 = 1 + (key % (TABLE_SIZE-1));
	drawer_id = (h1 + i*h2) % TABLE_SIZE;
	while(table->not_empty[drawer_id]) {
		if (!strcmp(table->drawers[drawer_id].word, word)) {
			found = 1;
			break;
		}
		drawer_id = (h1 + ++i*h2) % TABLE_SIZE;
	}

	return found;
}

int h(int k, int i)
{
	int h1, h2;
	h1 = k % TABLE_SIZE;
	h2 = 1 + (k % (TABLE_SIZE-1));

	return (h1 + i*h2) % TABLE_SIZE;
}