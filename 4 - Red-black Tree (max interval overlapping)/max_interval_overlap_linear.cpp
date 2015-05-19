#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define LOW 0
#define HIGH 1

using namespace std;

class tree {
public:
	tree() { size = 0; end_size = 0; }
	~tree() {}
	void insert_interval(int s, int t);
	void delete_interval(int s, int t);
	int max_overlap();

	int S[100000];
	int T[100000];
	int end[100000];
	int LR[100000];
	int size, end_size;
};

void tree::insert_interval(int s, int t)
{
	S[size] = s;
	T[size] = t;
	size++;
}

void tree::delete_interval(int s, int t)
{
	for(int i = 0; i < size; i++) {
		if (s == S[i] && t == T[i]) {
			S[i] = S[size-1];
			T[i] = T[size-1];
			size--;
			break;
		}
	}
}

int tree::max_overlap()
{
	int max = 0, overlaps = 0;

	for(int i = 0; i < size; i++) {
		end[end_size] = S[i];
		LR[end_size] = LOW;
		end_size++;
	}
	for(int i = 0; i < size; i++) {
		end[end_size] = T[i];
		LR[end_size] = HIGH;
		end_size++;
	}
	for(int i = 0; i < end_size-1; i++) {
		int min = i;
		for(int j = i+1; j < end_size; j++) {
			if(end[j] < end[min]) {
				min = j;
			}
		}
		int swap = end[i];
		end[i] = end[min];
		end[min] = swap;
		swap = LR[i];
		LR[i] = LR[min];
		LR[min] = swap;
	}
	for(int i = 0; i < end_size; i++) {
		if (LR[i] == LOW) {
			overlaps++;
		}
		else {
			overlaps--;
		}
		if (overlaps > max) max = overlaps;
	}

	return max;
}

int main(int argc, char const *argv[])
{
	int n;	// number of instructions
	char inst;
	int interval[2];
	int max_overlap;
	tree tree;

	// get lines of instructions and operate to tree
	//printf("Enter number of instructions:\n");
	scanf("%d ", &n);
	for(int i = 0; i < n; i++) {
		cin >> inst >> interval[0] >> interval[1];
		switch (inst) {
			case 'a' :
				tree.insert_interval(interval[LOW], interval[HIGH]);
				break;
			case 'd' :
				tree.delete_interval(interval[LOW], interval[HIGH]);
				break;
			default :
				break;
		}
	}

	// compute maximum number of overlaps
	max_overlap = tree.max_overlap();
	printf("%d\n", max_overlap);

	return 0;
}