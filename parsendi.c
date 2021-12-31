#include <stdlib.h>
#include <unistd.h>

int wordy(char c) {
  return c && c != ' ';
}

int get_word_count(char *string) {
  int word_count = 0;
  while (*string) {
    if (wordy(*string)) {
      word_count ++;
    }
    while (wordy(*string)) {
      string ++;
    }
    if (*string) {
      string ++;
    }
  }
  return word_count;
}

int get_length(char *string) {
  int length = 0;
  while (wordy(*string)) {
    length ++;
    string ++;
  }
  return length;
}

char *get_copy(char *string) {
  char *copy = malloc(sizeof (char[get_length(string) + 1]));
  char *copy_copy = copy;
  while (wordy(*string)) {
    *copy = *string;
    string ++;
    copy ++;
  }
  *copy = '\0';
  return copy_copy;
}

char **parse_args(char *string) {
  int word_count = get_word_count(string);
  char **words = malloc(sizeof (char *[word_count + 1]));
  for (int i = 0; i < word_count; i ++) {
    while (*string == ' ') {
      string ++;
    }
    words[i] = get_copy(string);
    while (wordy(*string)) {
      string ++;
    }
  }
  words[word_count] = NULL;
  return words;
}

int main() {
  char **args = parse_args("ls -a -l");
  execvp(args[0], args);
  return 0;
}
