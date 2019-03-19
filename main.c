#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "word.h"

int main(int argc, char *argv[]) {

  // list of all words found (head pointer)
  struct Word *words = NULL;

  if (argc > 1) {
    int i = 1;
    while (i < argc) {
      int fd = open(argv[i], O_RDONLY);
      if (fd == -1) {
        fprintf(stderr, "Failed to open and read the file.\n");
        exit(1);
      }
      words = parseFile(words, fd);
      i++;
    }
  }else if(getenv("WORD_FREAK") != NULL){
    int fd = open(getenv("WORD_FREAK"), O_RDONLY);
    words = parseFile(words, fd);
  }else{
    words = parseFile(words, STDIN_FILENO);
  }


  int maxLength = longestWord(words);
  struct Word *temp = words;
  while (temp != NULL) {
    char output[maxLength+10];
    char *spaces = spaceStr(maxLength-strlen(temp->word));

    int length = sprintf(output, "%s%s: %i\n", temp->word, spaces, temp->count);
    write(1, output, length);

    free(spaces);
    spaces = NULL;
    temp = temp->next;
  }

  free(words);
  words = NULL;
  return 0;
}