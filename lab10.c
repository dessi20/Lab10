#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
    struct Trie *children[26];
    int isEndOfWord;
    int count;
}; 

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *node = malloc(sizeof(struct Trie));
    if (node) {
        node->isEndOfWord = 0;
        node->count = 0;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    while (*word) {
        int index = *word - 'a';
        if (!current->children[index]) {
            current->children[index] = createTrie();
        }
        current = current->children[index];
        word++;
    }
    current->isEndOfWord = 1;
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    while (*word) {
        int index = *word - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
        word++;
    }
    if (current->isEndOfWord) {
        return current->count;
    }
    return 0;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i]) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    int count = 0;
    fscanf(file, "%d\n", &count);
    char word[100];
    for (int i = 0; i < count; i++) {
        fscanf(file, "%s\n", word);
        pInWords[i] = calloc(strlen(word) + 1, sizeof(char));
        strcpy(pInWords[i], word);
    }
    fclose(file);
    return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}