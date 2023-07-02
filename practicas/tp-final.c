#include <stdio.h>
#include <stdlib.h>
#define WORDMAXSIZE 150

typedef struct _GTNode {
  char data;
  int accept_state;
  struct _GTNode *brother;
  struct _GTNode *children;
} GTNode;

typedef GTNode *NFA;

NFA createAutomaton() {
  NFA automaton = malloc(sizeof(GTNode));
  automaton->data = '\0';
  automaton->accept_state = 0;
  automaton->brother = NULL;
  return automaton;
}

NFA addWordToNFA(NFA automaton, char *word) {
  char letter = word[0];
  if (*(word++) != '\n') {
    if (automaton == NULL) {
      NFA new_state = malloc(sizeof(GTNode));
      new_state->data = letter;
      new_state->brother = NULL;
      new_state->children = addWordToNFA(NULL, word++);
      return new_state;
    }
    if (automaton->data == letter)
      automaton->children = addWordToNFA(automaton->children, word++);
    else
      automaton->brother = addWordToNFA(automaton->brother, word);
    return automaton;
  }
  if (automaton == NULL) {
    NFA new_state = malloc(sizeof(GTNode));
    new_state->data = letter;
    new_state->brother = NULL;
    new_state->children = NULL;
    return new_state;
  }
  if (automaton->data == letter)
    automaton->accept_state = 1;
  else
    automaton->brother = addWordToNFA(automaton->brother, word);
  return automaton;
}

NFA CreateDictFromFile(char *file_name) {
  NFA automaton = NULL;
  char word[WORDMAXSIZE];
  FILE *file = fopen(file_name, "r");
  while (fgets(word, WORDMAXSIZE, file))
    addWordToNFA(automaton, word);
  return automaton;
}

char *StringParser(NFA dict) { return NULL; }

int main() {
  NFA dict = CreateDictFromFile();
  char *result = StringParser();
  printf("%s\n", result);
  return 0;
}