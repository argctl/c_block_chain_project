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
  for (int i = 0; i < 8; i++) {
    // REVIEW
    char key = *((char*)lowkey + (i * sizeof(char))); // iterate char size var to get opcode key change
    //char key = lowkey[i];
    char* yek = (void*)change + (djk * (sizeof(int*) + sizeof(char)));
    //printf("*yek: %c", *yek);
    printf("\n key: %c", key);
    if (key == *yek) {
      printf("\n key: %d, *yek: %d: ", key, *yek);
      //int wol = *((int*)keylow + (i * sizeof(int *))); // iterate int pointer size var to get value change of opcode result
      int wol = keylow[i];
      int* low = *(int**)((void*)change + ((djk + 1) * (sizeof(int*) + sizeof(char))) + sizeof(char)); //*? 
      printf("\n wol, *low: %d, %d", wol, *low);
      keylow[i] = *low;
      djk += 2;
    }
    //printf("\nkey, *yek: %c, %c", key, *yek);
    //if (key == *yek) {
      // REVIEW
      //int* wol = (int*)keylow + (i * sizeof(int *)); // iterate int pointer size var to get value change of opcode result
      //int* low = (int**)((void*)change + (djk * (sizeof(int*) + sizeof(char))) + sizeof(char)); //*? 
      //printf("\n *wol, *low: %d, %d", *wol, *low);
      //djk += 1;
      //printf("\ndjk iterated i: %d", i);
      //key = &wol;
    //}
    // TODO - shift off of *change irregular shapped memory "array" 
  }
  // TODO - nothing, another function can check pointer location for correct opcode pairings.
  return 0;
}
// input source
// same pointers could allow for validation in this function

void* input(char* opt) {
  void* change = malloc(4 * sizeof(int *) + 4 * sizeof(char));
  for (int i = 0; i < 8; i++) {
    if (i % 2 == 0) {
      char* c = (char*)change + (i * (sizeof(int *) + sizeof(char)));
      *c = opt[i];
    } else {
      int** djk = (int**)((char*)change + (i * (sizeof(int *) + sizeof(char))) + sizeof(char));
      *djk = malloc(sizeof(int));
      **djk = opt[i] - '0';
    }
  }
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
int* ledger() {
  // changes, solved blocks, input/output validators
  void* change = input(cli());
  return change;
}

int main() {
  //pointers();
  char array[8];
  int* sums = malloc(8 * sizeof(int *));
  char* chars = malloc(8 * sizeof(char)); // *?
  //int *change = malloc(4 * sizeof(int *) + 4 * sizeof(char));  
  int* change = ledger();
  //int *sums[8];
  memset(array, 'G', sizeof(array));
  for (int i = 0; i < 8; i++) {
    sums[i] = i;
  }
  for (int i = 0; i < 8; i++) {
    printf("\n sums[%d]: %d ", i, sums[i]);
    chars[i] = array[i];
    printf("\n chars[%d]: %c", i, chars[i]);
  }
  printf("\n before: \n");
  for (int i = 0; i < 8; i++) {
    printf("%d, ", sums[i]);
  }
  block(chars, sums, change);
  printf("changed: ?\n");
  for (int i = 0; i < 8; i++) {
    printf("%d, ", sums[i]);
  }
  // TODO - validate - chain of pointer diffs with ledger(out?)

  free(sums);
  return 0;
}
