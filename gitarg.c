#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "arg.c"
#include "array.c"

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

void tag (char g, int _t, char i, int _a, char t, int _r, char a, int _g) {
  //char* gtiatrag = (char*)malloc(sizeof(char) * 8);
  char t_ = _t;
  char a_ = _a;
  char r_ = _r;
  char g_ = _g;
  char gtiatrag[] = {g, t_, i, a_, t, r_, a, g_};
  array(gtiatrag);
}

int block (char* lowkey, int* keylow, void* change) {
  int djk = 0;
  int dk = 0;

  while (djk != 4) {
    char* c = (char*)(change + (djk * (sizeof(int*) + sizeof(char))));  
    int* d = (int*)(change + (djk * (sizeof(int*) + sizeof(char))) + sizeof(char)); 
    printf("\n *c: %c, lowkey[djk]: %c", *c, lowkey[djk]);
    if (lowkey[djk] == *c) {
      //printf("\n TODO - adjust number: %d", *d);
      keylow[djk] = *d;
    } else {
      dk += *d;
    }
    printf("\n keylow[djk]: %d, *d: %d \n", keylow[djk], *d);
    if (keylow[djk] == *d) {
      keylow[djk + 4] = *c;      
    }
    djk++;
  }
 /*
 for (int i = 4; i < 8; i++) {
   char* c = (char*)(change + ((i - 4) * (sizeof(int*) + sizeof(char)))); 
   int* d = (int*)(change + ((i - 4) * (sizeof(int*) + sizeof(char))) + sizeof(char));
   printf("\nblock c: %c", *c);
   printf("\nblock d: %d", *d);
  }
 */
  return dk;
}
// input source
// same pointers could allow for validation in this function
void* input(char* opt) {
  void* change = malloc(4 * sizeof(int *) + 4 * sizeof(char));
  for (int i = 0; i < 8; i++) {
    //printf("\n opt[%d]: %c", i, opt[i]);
    if (i % 2 == 0) {
      char* c = (char*)(change + (i/2 * (sizeof(int*) + sizeof(char))));
      *c = opt[i];
    } else {
      int* j = (int*)(change + (i/2 * (sizeof(int*) + sizeof(char))) + sizeof(char));
      int k = opt[i] - '0';
      *j = k;
    }
  } 
  /*
  for (int i = 0; i < 4; i++) {
    char* c = (char*)(change + (i * (sizeof(int*) + sizeof(char)))); 
    int* d = (int*)(change + (i * (sizeof(int*) + sizeof(char))) + sizeof(char));
    printf("\n c: %c", *c);
    printf("\n d: %d", *d);
  }
  */
  return change;
}

char* cli() {
  char* opt = malloc(sizeof(char) * 9);
  printf("\nEnter 8 character opcode for vm: "); 
  scanf("%8s", opt);
  printf("\nyou entered: %s\n", opt); 
  return opt;
}

void** ledger(char** history, int** results, char* code, int* variables, int pc, int cp) {
  // changes, solved blocks, input/output validators
  // store in memory and dump to storage
  // advertise segments on network to connect chains
  history = realloc(history, sizeof(char*) * (pc + 1));
  results = realloc(results, sizeof(int*) * (pc + 1));
  
  //tag('G', 1, 'G', 1, 'G', 1, 'G', 1);
  if (pc > atoi(getenv("GAT")) && strcmp(getenv("GAT"), "TAG") != 0) tag(history[pc - 1][0], results[pc - 1][0], history[pc - 1][1], results[pc - 1][1], history[pc - 1][2], results[pc - 1][2], history[pc - 1][3], results[pc - 1][3]);
  //if (atoi(getenv("GAT"))) tag(*history[0 + 4], *results[0 + 4], *history[1 + 4], *results[1 + 4], *history[2 + 4], *results[2 + 4], *history[3 + 4], *results[3 + 4]);
  printf("\ncp before g count: %d\n ", cp);
  for (int i = 0; i < 8; i++) {
    char g;
    // The current position is adjusted to the match the history on the front half of our "word" if we have merkle decay that isn't new virtual space
    // one more check for the code change or do we assume top layer check and this is volatile until dk set?
    if (cp < pc && cp > 0 && i < 4) {
      g = history[cp][i + 4];
      code[i] = g;
      printf("\ng: %c\n", g); 
      
    } 
    // The result related to history on the back half of a "word" is changeable by the DK iterator to copy the value across the ledger if the code matches
    if (pc > 0)
    if (i > 4 && g == history[pc - 1][i]) { 
      printf("setting results[%d][%i] - %d = variables[%d] - %d ", cp, i, results[cp][i], i, variables[i]);
      results[cp][i] = variables[i];
    }
  }
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
    printf("CH(I)[pc:%d]: \n", j);
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
// TODO - PARAMETERS (int maxWhileIterationsTempChain, int* variableSeedArray, char* codeSeedArray)

// TODO - return and set all variables, will require struct 
//void** tar(int pc, int** results, int* values, char** history, char* code, int cp, void* change, int dk) {
/*
void tar(int pc, int** results, int* values, char** history, char* code, int cp, void* change, int dk) {
}
*/
    
   
void chain(int* values, char* code) {
  Arg* arg = createInner(inner); 
  int pc = 0;
  int cp = 0; // copy stopper counter
  char** history = malloc(sizeof(char*));
  int** results = malloc(sizeof(int*));
  void* change;
  int dk = 0;
  while (1) {
    char* code_seed = malloc(8 * sizeof(char));
    int* variable_seed = malloc(8 * sizeof(int*));
    for (int i = 0; i < 8; i++) {
      variable_seed[i] = values[i];
      printf("code[i]: %c", code[i]);
      code_seed[i] = code[i];
    }
    void** ledge = ledger(history, results, code_seed, variable_seed, pc, cp);
    results = *((int***)ledge);
    history = *((char***)ledge + 1);
    pc++;
    int t = 1;
    char* buffer = (char*)malloc(sizeof(char) * 8);
    while (t) {
      buffer = arg->inner(arg->arg, arg->eta, arg->buffer, arg->addr_size, arg->recv_len);
      if (buffer[arg->recv_len]) {
        printf("received here!");
        t = 0; 
      }
    }
    printf("here!@received: %s\n", buffer);
    //change = (int*)input(cli()); // TODO - in this architecture
    change = (int*)input(buffer);
    for (int i = 4; i < 8; i++) {
      char* c = (char*)(change + ((i - 4) * (sizeof(int*) + sizeof(char))));
      code_seed[i] = *c;
      if (dk > 0) {
        int* d = (int*)(change + ((i - 4) * (sizeof(int*) + sizeof(char))) + sizeof(char));
        variable_seed[i] = dk;
      }
    }
    dk = block(code_seed, variable_seed, change);
    cp = cp <= 0 ? pc : cp - dk - 1;
  }
}

void* rig() {
  while (1) {
    char* tar = getenv("TAR");
    array(tar);
  }
}

void* unrig() {
  char* space = getenv("space");
  // REVIEW - better style to parse list or better secret storage from different variables
  int arg[] = {atoi(getenv("arg0")), atoi(getenv("arg1")), atoi(getenv("arg2")), atoi(getenv("arg3")), atoi(getenv("arg4")),  atoi(getenv("arg5")), atoi(getenv("arg6")), atoi(getenv("arg7"))};

  chain(arg, space);
}

int main() {
  pthread_t r, a;
  if (pthread_create(&r, NULL, rig, NULL)) {
    fprintf(stderr, "Error creating thread \n");
  } 
  if (pthread_create(&a, NULL, unrig, NULL)) {
    fprintf(stderr, "Error creating thread \n");
  } 

  pthread_join(r, NULL);
  pthread_join(a, NULL);

  return 0;
}
