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
  int dk = 0;
  while (djk != 4) {
    char* c = (char*)(change + (djk * (sizeof(int*) + sizeof(char))));  
    int* d = (int*)(change + (djk * (sizeof(int*) + sizeof(char))) + sizeof(char)); 
    printf("\n *c: %c, lowkey[djk]: %c", *c, lowkey[djk]);
    if (lowkey[djk] == *c) {
      printf("\n TODO - adjust number: %d", *d);
      keylow[djk] = *d;
    } else {
      dk += *d;
    }
    djk++;
  }
  
  return dk;
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
    }
  } 
  for (int i = 0; i < 4; i++) {
    char* c = (char*)(change + (i * (sizeof(int*) + sizeof(char)))); 
    int* d = (int*)(change + (i * (sizeof(int*) + sizeof(char))) + sizeof(char));
    printf("\n c: %c", *c);
    printf("\n d: %d", *d);
  }
  return change;
}

char* cli() {
  char* opt = malloc(sizeof(char) * 9);
  printf("\nEnter 8 character opcode for vm: "); 
  scanf("%8s", opt);
  printf("\nyou entered: %s\n", opt); 
  return opt;
}

void** ledger(char** history, int** results, char* code, int* variables, int pc) {
  // changes, solved blocks, input/output validators
  // store in memory and dump to storage
  // advertise segments on network to connect chains
  // TODO - look back one char pointer and int pointer, iterate pc;
  history = realloc(history, sizeof(char*) * (pc + 1));
  results = realloc(results, sizeof(int*) * (pc + 1));
  
  history[pc] = code;
  results[pc] = variables;
  // I have char** history and int** result and want to return both from a function without using a struct but instead using a void pointer of pointers or void pointer
  void** ledge = malloc(sizeof(char**) + sizeof(int**));
  //if (pc > 0) printf("history[pc - 1]: pc: %d : %d <- [0]", pc, history[pc - 1][0]);
  for (int j = 0; j < pc; j++) {
    char* cc = history[j];
    //printf("*cc: %c", *cc); 
    int* dk = results[j];
    //printf("dk: %p, *dk: %d", dk, *dk);
    //printf("\nresults[%d]: %d", j, *dk);
    //printf("\nhistory[%d]: %c", j, history[j][0]);
    printf("CH(I)[pc]: \n");
    for (int i = 0; i < 8; i++) {
      printf("CH(I)[%d]: ", pc);
      printf("%c", cc[i]);
      printf("%d", dk[i]);
      printf("\n");
    }
  }
  *((int***)ledge) = results;
  *((char***)(ledge + 1)) = history;
  printf("\n*code[0]: %c \n", code[0]);
  //void* change = input(cli());
  return ledge;
}

int main() {
  char array[8];
  int pc = 0;
  char** history = malloc(sizeof(char*));
  int** results = malloc(sizeof(int*));
  int* change;
  int dk = 0; 
  while (1) {
    // if djk > 0, random split on next variable_seed, magic numbers on back half append loop
    char* code_seed = malloc(8 * sizeof(char)); // *?
    int* variable_seed = malloc(8 * sizeof(int*));
    
    printf("pc: %d", pc);
    memset(array, 'G', sizeof(array));
    for (int i = 0; i < 8; i++) {
      variable_seed[i] = i;
    }
    for (int i = 0; i < 8; i++) {
      code_seed[i] = array[i];
      if (i == 7) code_seed[i] = 'H';
    }
    if (dk > 0) {
      //printf("history[pc][0] pc=%d: %c \n", pc, *history[pc]);
      for (int i = 4; i < 8; i++) {
        //codehistory[pc][i]; //= dk; 
        //char* c = (char*)(change + (i * (sizeof(int*) + sizeof(char)))); 
        char* l = (char*)(change +(i * sizeof(int*) + sizeof(char)));
        printf("l: %p, lc: %c", l, *l); 
        code_seed[i] = (char*)(change + (i * (sizeof(char) + sizeof(int*)))); 
        // set results // Can have a random value or split value, but this will help create consensus
        //results
        //variable_seed[i] = dk; //(int*)(change + (i * sizeof(char) + sizeof(int*)) + sizeof(char));
      }
      // REVIEW - setting to 0 might be redundant.
      //dk = 0;
    }
    void** ledge = ledger(history, results, code_seed, variable_seed, pc);
    results = *((int***)ledge);
    history = *((char***)(ledge + 1));
    pc++;
    change = (int*)input(cli());
    dk = block(code_seed, variable_seed, change);
    // TODO - send/create/add virtual register with change op codes and values from variable_seed in ledger
    
    printf("'merkle' decay to assign char positional code: %d \n", dk);
  }
  return 0;
}
