#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// DO YOU HAVE THE RIGHT DATA TRANSFORMATIONS?
// virtual register - is one full 8 int array
// half register - is the size of 4 ints
// THIS IS OUR IDEAL
// opcode appendage - fill 25 percent of full opcode to verify next chain
// each space is 0000 to 1111
// (A, C, F, G, E, D, L, L) x 50% of buffer space
// each space is 00000000 to 11111111
// (0, 1, 2, 3, 4, 5, 6, 7) x 100 % of buffer space
// block (op) // so important to stich next ops for validator send!
// (A1, F7, G2, L7) x 75% of buffer space + optional 25% (next instruction opcode)
// A, C, F, G, E, D, L, L
// 1, 1, 7, 2, 4, 5, 7, 7

// 25% = A, F, G, L

// Our reality:
// char with less-than-pointer level memory sharing capability (those chars aren't pointin' at my charzar, king)
// int pointer to share the result mapped to our opcode in chain.

// guess magic number to change, i.e. foobar is temp opcode to change footballarg foo_ba___r_
// creates variable length integer locking system with updates that chain
// pass the memory address in, copy, then change
//block(chars, sums, change);
int block(char* lowkey, int* keylow, void* change) {
  int djk = 0;
  while (djk != 4) {
    char* c = (char*)(change + (djk * (sizeof(int*) + sizeof(char))));  
    printf("\n *c: %c, lowkey[djk]: %c", *c, lowkey[djk]);
    if (lowkey[djk] == *c) {
      int* d = (int*)(change + (djk * (sizeof(int*) + sizeof(char))) + sizeof(char)); 
      printf("\n TODO - adjust number: %d", *d);
      keylow[djk] = *d;
    }
    djk++;
  }
  
  return 0;
}
// input source
// same pointers could allow for validation in this function

void* input(char* opt) {
  void* change = malloc(4 * sizeof(int *) + 4 * sizeof(char));
  for (int i = 0; i < 8; i++) {
    printf("\n opt[%d]: %c", i, opt[i]);
    if (i % 2 == 0) {
      char* c = (char*)(change + (i/2 * (sizeof(int*) + sizeof(char))));
      *c = opt[i];
    } else {
      int* j = (int*)(change + (i/2 * (sizeof(int*) + sizeof(char))) + sizeof(char));
      int k = opt[i] - '0';
      *j = k;
      //*j = opt[i] - '0';
    }
  } 
  for (int i = 0; i < 4; i++) {
    char* c = (char*)(change + (i * (sizeof(int*) + sizeof(char)))); 
    int* d = (int*)(change + (i * (sizeof(int*) + sizeof(char))) + sizeof(char));
    printf("\n c: %c", *c);
    printf("\n d: %d", *d);
  }
  //*change = &opt;
  return change;
}

char* cli() {
  //char opt[9];
  char* opt = malloc(sizeof(char) * 9);
  printf("\nEnter 8 character opcode for vm: "); 
  scanf("%8s", opt);
  printf("\nyou entered: %s\n", opt); 
  return opt;
}
char** question(char** history, char* code, int pc) {
  //dump?
  history = realloc(history, sizeof(char*) * pc);
  //char* words = malloc(8 * sizeof(char));
  char** c = (char**)((char*)history + (sizeof(char*) * pc)); 
  *c = code;
  // TODO - pointer increase size of history** to include words
  return c;
}
int** answer(int** results, int* variables, int pc) {
  int* names = malloc(8 * sizeof(int));
  int** i = (int**)((int*)results + (sizeof(int*) * pc));
  *i = variables;
  // TODO - pointer increase size of results** to include names
  return i;
}
int* ledger(char* code, int* variables, int pc) {
  // changes, solved blocks, input/output validators
  // store in memory and dump to storage
  // advertise segments on network to connect chains
  char** history = malloc(sizeof(char*));
  int** results = malloc(sizeof(int*));
  // TODO - look back one char pointer and int pointer, iterate pc;
  question(history, code, pc);
  answer(results, variables, pc);
  // LOGGING
  for (int i = 0; i < pc; i++) {
    //char* cc = history[i];
    char* cc = (char*)history + (sizeof(char*) * i);
    //int* dd = results[i];     
    printf("cc p: %p", cc);
    /*
    for (int j = 0; j < pc; j++) {
      printf("c: %c", cc[j]); 
      printf("d: %d", dd[j]);
      printf("\n");
    }
    */
  }
  void* change = input(cli());
  return change;
}

int main() {
  char array[8];
  char* code_seed = malloc(8 * sizeof(char)); // *?
  int* variable_seed = malloc(8 * sizeof(int *));
  int pc = 1;
  while (1) {
    int* change = ledger(code_seed, variable_seed, pc++);
    memset(array, 'G', sizeof(array));
    for (int i = 0; i < 8; i++) {
      variable_seed[i] = i;
    }
    for (int i = 0; i < 8; i++) {
    //printf("\n sums[%d]: %d ", i, variable_seed[i]);
      if (i == 7) code_seed[i] = 'H';
      code_seed[i] = array[i];
    //printf("\n chars[%d]: %c", i, code_seed[i]);
    }
  //printf("\n before: \n");
  //for (int i = 0; i < 8; i++) {
    //printf("%d, ", variable_seed[i]);
  //}
    block(code_seed, variable_seed, change);
  //printf("changed: ?\n");
    for (int i = 0; i < 8; i++) {
      printf("%d, ", variable_seed[i]);
    }
  }
  // TODO - validate - chain of pointer diffs with ledger(out?)
  //free(sums);
  return 0;
}
