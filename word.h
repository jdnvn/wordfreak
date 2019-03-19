/* structure for each word in the list. Has a string value 'word'
for the actual text, a 'count' value for the frequency of the word,
and a 'next' pointer for the next word in a list. */
struct Word {
	char *word;
	int count;
	struct Word *next;
};

// creates and returns a new Word struct given a 'word' string
struct Word* newWord(char *word);

/* Checks if a specified 'word' string occurs in the word list.
if not, it returns 0 and if it does exist it increments the frequency
and returns 1. */
int wordExist(struct Word* wordList, char *word);

// Adds a specified word to the list and returns the newly updated list
struct Word* addWord(struct Word* wordList, char *word);

/* Reads through the specified file directory letter by letter and parses 
the words into a linked list of Word structs. It returns the finished list. */
struct Word* parseFile(struct Word* wordList, int fd);

/* Used for formatting, finds the longest word's length
 in the completed list and returns it. */
int longestWord(struct Word *wordList);

// Also used for formatting, returns a string of spaces to write to standard output
char *spaceStr(int length);