#include "word.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

struct Word* newWord(char *word) {
  struct Word *toAdd = NULL;
  toAdd = (struct Word*) malloc(sizeof(struct Word));
  if (toAdd == NULL) {
    printf("somethings wrong");
    return NULL;
  }
  toAdd->word = (char *)malloc(strlen(word) + 1);
  strcpy(toAdd->word, word);
  toAdd->count = 1;
  toAdd->next = NULL;
  return toAdd;
}

int wordExist(struct Word* wordList, char *word) {
  struct Word *list = wordList;
  if (list == NULL) {
    return 0;
  }
  while (list != NULL) {
    if (strcmp(list->word, word) == 0) {
      (list->count)++;
      return 1;
    }
    list = list->next;
  }
  return 0;
}

struct Word *addWord(struct Word* wordList, char *word) {
  struct Word *list = wordList;
  struct Word *toAdd = newWord(word);
  if (wordList == NULL) {
    wordList = toAdd;
  } else {
    while (list->next != NULL) {
      list = list->next;
    }
    list->next = toAdd;
  }
  return wordList;
}

// new one
struct Word *parseFile(struct Word* wordList, int fd) {
  int rd = -1;
  int a = 0;
  char *newWord = (char *)malloc(25);
  int n=0;

  while (rd != 0) {
    rd = read(fd, newWord+n, 1);
    if(!(isalpha(newWord[n])) && !(newWord[n] == '\'')){
      newWord[n] = '\0';
      if (newWord[0] != '\0') {
        if (wordExist(wordList, newWord) == 0) {
          wordList = addWord(wordList, newWord);
        }
      }
      n = 0;
    }else{
      n++;
    }
  }

  free(newWord);
  newWord = NULL;
  close(fd);

  return wordList;
}

int longestWord(struct Word *wordList){
  struct Word *node = wordList;
  int longest = 0;
  while(node != NULL){
    if(strlen(node->word) > longest){
      longest = strlen(node->word);
    }
    node = node->next;
  }
  return longest;
}

char *spaceStr(int length){
  char* spaceStr = (char *)malloc(length);
  for(int i=0; i<length; i++){
    spaceStr[i] = ' ';
  }
  spaceStr[length] = '\0';
  return spaceStr;
}