#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 2050
#define MAX_NUM_SYMBOLS 2050


typedef struct _node {
	char symbol;
	int occur;
	struct _node *l, *r;
} node;

typedef struct _huffman_tree {
	node *root;
	node **leaves;
	char **VLCode;	// variable-length code
	int num_leaves;
} *huffman_tree;

int compare(const void *a, const void *b)
{
	return (*((node **)b))->occur - (*((node **)a))->occur;	// decreasing order
	//return  (*((node **)a))->occur < (*((node **)b))->occur ? 1 : -1;	// for floating point number
}

int find_pos(char c, char *symbols, int num_symbols);

void build_huffman_tree(huffman_tree tree, char *symbols, int *occurs, int num_symbols);
void traverse_huffman_tree(huffman_tree tree);
void traverse(huffman_tree tree, node *n, char *code, int depth);
void show_codeword_table(huffman_tree tree);
char *huffman_encode(char *source, huffman_tree tree);
char *huffman_decode(char *bitstream, huffman_tree tree);
void release_huffman_tree(huffman_tree tree);

int main(int argc, char const *argv[])
{
	char *source;
	char *bitstream;
	char *result;
	int i, num_symbols = 0;
	int pos;
	char symbols[MAX_NUM_SYMBOLS];
	int occurs[MAX_NUM_SYMBOLS] = {0};
	huffman_tree tree = (struct _huffman_tree *)malloc(sizeof(struct _huffman_tree));

	source = (char *)calloc(sizeof(char), MAX_TEXT_SIZE);

	// get input text
	fgets(source, MAX_TEXT_SIZE, stdin);

	// obtain symbols
	for(i = 0; i < strlen(source); i++) {
		pos = find_pos(source[i], symbols, num_symbols);
		if (pos == num_symbols) {
			symbols[num_symbols++] = source[i];
		}
		occurs[pos]++;
	}

	/*
	for(i = 0; i < num_symbols; i++) {
		printf("symbol: %c, occurrences: %d\n", symbols[i], occurs[i]);
	}
	*/

	build_huffman_tree(tree, symbols, occurs, num_symbols);
	traverse_huffman_tree(tree);
	//show_codeword_table(tree);

	bitstream = huffman_encode(source, tree);
	//printf("bitstream:\n%s\n", bitstream);

	result = huffman_decode(bitstream, tree);
	printf("%s\n", result);

	free(source);
	free(bitstream);
	free(result);
	release_huffman_tree(tree);

	return 0;
}

int find_pos(char c, char *symbols, int num_symbols)
{
	int i;

	for(i = 0; i < num_symbols; i++) {
		if (c == symbols[i]) return i;
	}

	return num_symbols;
}

void build_huffman_tree(huffman_tree tree, char *symbols, int *occurs, int num_symbols)
{
	int i;
	node *temp;
	node **leaf = (node **)calloc(sizeof(node *), num_symbols);
	tree->num_leaves = num_symbols;
	tree->leaves = (node **)calloc(sizeof(node *), tree->num_leaves);

	// initialize the leaf node
	for(i = 0; i < num_symbols; i++) {
		leaf[i] = (node *)calloc(sizeof(node), 1);
		leaf[i]->symbol = symbols[i];
		leaf[i]->occur = occurs[i];
		leaf[i]->l = NULL;
		leaf[i]->r = NULL;
		tree->leaves[i] = (node *)calloc(sizeof(node), 1);
		*(tree->leaves[i]) = *(leaf[i]);
	}

	// build tree
	for(; num_symbols > 1; num_symbols--) {
		// sort by occurrences
		qsort(leaf, num_symbols, sizeof(node*), compare);
		// create internal node
		temp = (node *)malloc(sizeof(node));
		temp->occur = leaf[num_symbols-2]->occur + leaf[num_symbols-1]->occur;
		temp->l = leaf[num_symbols-2];
		temp->r = leaf[num_symbols-1];
		leaf[num_symbols-2] = temp;
	}
	tree->root = temp;

	for(i = num_symbols-1; i > 0; i--) {
		free(leaf[i]);
	}
	free(leaf);
}

void traverse_huffman_tree(huffman_tree tree)
{
	int i;
	int max_codeword_length = tree->num_leaves;
	char *code = (char *)calloc(sizeof(char), max_codeword_length);

	tree->VLCode = (char **)calloc(sizeof(char *), tree->num_leaves);
	for(i = 0; i < tree->num_leaves; i++) {
		tree->VLCode[i] = (char *)calloc(sizeof(char), max_codeword_length);
	}

	traverse(tree, tree->root, code, 0);

	free(code);
}

void traverse(huffman_tree tree, node *n, char *code, int depth)
{
	int i;

	if (n->l == NULL) {
		for(i = 0; i < tree->num_leaves; i++) {
			if (n->symbol == tree->leaves[i]->symbol) {
				strcpy(tree->VLCode[i], code);
				free(n);
				return;
			}
		}
	}

	code[depth] = '0';
	traverse(tree, n->l, code, depth+1);
	code[depth] = '1';
	traverse(tree, n->r, code, depth+1);
	code[depth] = '\0';
	free(n);
}

void show_codeword_table(huffman_tree tree)
{
	int i;

	for(i = 0; i < tree->num_leaves; i++) {
		printf("%c: %s\n", tree->leaves[i]->symbol, tree->VLCode[i]);
	}
}

char *huffman_encode(char *source, huffman_tree tree)
{
	int sid, bid, i, j;
	int len = strlen(source);
	char *bitstream = (char *)calloc(sizeof(char), strlen(source) * tree->num_leaves);

	for(sid = 0, bid = 0; sid < len; sid++) {
		for(i = 0; i < tree->num_leaves; i++) {
			if (source[sid] == tree->leaves[i]->symbol) {
				for(j = 0; j < strlen(tree->VLCode[i]); j++) {
					bitstream[bid++] = tree->VLCode[i][j];
				}
				break;
			}
		}
	}

	return bitstream;
}

char *huffman_decode(char *bitstream, huffman_tree tree)
{
	int bid, cid, rid, i, j;
	int len = strlen(bitstream);
	char *code = (char *)calloc(sizeof(char), tree->num_leaves);
	char *result = (char *)calloc(sizeof(char), strlen(bitstream));

	for(bid = 0, cid = 0, rid = 0; bid < len; bid++) {
		code[cid++] = bitstream[bid];
		for(i = 0; i < tree->num_leaves; i++) {
			if (!strcmp(code, tree->VLCode[i])) {
				result[rid++] = tree->leaves[i]->symbol;
				memset(code, 0, tree->num_leaves * sizeof(char));
				cid = 0;
			}
		}
	}

	free(code);

	return result;
}

void release_huffman_tree(huffman_tree tree)
{
	int i;

	for(i = tree->num_leaves-1; i >= 0; i--) {
		free(tree->leaves[i]);
		free(tree->VLCode[i]);
	}
	free(tree->leaves);
	free(tree->VLCode);
	free(tree);
}