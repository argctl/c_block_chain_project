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

// not a stub probably but for test input, probably a driver
int pointers () {
  int number = 42;
  int *pointer = &number;
  int value = *pointer; 
  int value_ = pointer;
  int *bad_pointer = (int *)42;
  int bad_value = &bad_pointer;
  printf("number: ", number);
  printf("\n pointer(p): %p", pointer);
  printf("\n pointer(d): %d", pointer);
  printf("\n *pointer: %d", *pointer);
  printf("\n value: %d", value);
  printf("\n value_: %d", value_);
  printf("\n");
  printf("\n bad_pointer(p): %p", bad_pointer);
  printf("\n bad_pointer(d): %d", bad_pointer);
  printf("\n &bad_pointer(d): %d", &bad_pointer);
  //printf("\n *bad_pointer(d): %d", *bad_pointer);
  //printf("\n bad_value: %d", bad_value);
  return 0;
}
int *stub () {
  int *change = malloc(4 * sizeof(int *) + 4 * sizeof(char));  
  //change[1.5]
  return change;
}

// guess magic number to change, i.e. foobar is temp opcode to change footballarg foo_ba___r_
// creates variable length integer locking system with updates that chain
// pass the memory address in, copy, then change
//block(chars, sums, change);
int block(int *lowkey, int *keylow, int *change) {
  int djk = 0;
  for (int i = 0; i < 8; i++) {
    int* key = &lowkey + (i * sizeof(char)); // iterate char size var to get opcode key change
    char* yek = (char*)change + (djk * (sizeof(int*) + sizeof(char)));
    char cc = *yek;
    printf("cc after: %c", cc);
    if (*key == *yek) {
      int* wol = &keylow + (i * sizeof(int *)); // iterate int pointer size var to get value change of opcode result
      int* low = (int**)((char*)change + (djk * (sizeof(int*) + sizeof(char))) + sizeof(char)); //*? 
      djk += 1;
      printf("djk iterated i: %d", i);
      key = &wol;
    }
    // TODO - shift off of *change irregular shapped memory "array" 
  }
  // TODO - nothing, another function can check pointer location for correct opcode pairings.
  return 0;
}
// input source
// same pointers could allow for validation in this function
int* ledger() {
  char opt[9];
  printf("Enter 8 character opcode for vm: "); 
  scanf("%8s", opt);
  printf("you entered: %s\n", opt); 
  void* change = malloc(4 * sizeof(int *) + 4 * sizeof(char));  
  for (int i = 0; i < 8; i++) {
    // feed in correctly - set by reference (memory location in struct (don't use struct so i can time travel)
    if (i % 2 == 0) {
      // REVIEW - might need to just add to (char*)change directly
      char* c = (char*)change + (i * (sizeof(int *) + sizeof(char)));
      *c = opt[i];
      printf("c before: %c", *c); 
    } else {
      int** djk = (int**)((char*)change + (i * (sizeof(int *) + sizeof(char))) + sizeof(char));
      *djk = malloc(sizeof(int));
      **djk = opt[i] - '0';
    }
  }
  printf("\n changes: %d", change);
  return change;
}

int main() {
  //pointers();
  char array[8];
  int *sums = malloc(8 * sizeof(int *));
  int *chars = malloc(8 * sizeof(char)); // *?
  //int *change = malloc(4 * sizeof(int *) + 4 * sizeof(char));  
  int* change = ledger();
  //int *sums[8];
  memset(array, 'G', sizeof(array));
  for (int i = 0; i < 8; i++) {
    sums[i] = i;
  }
  for (int i = 0; i < 8; i++) {
    printf("%d ", sums[i]);
    chars[i] = array[i];
    printf("%d ", chars[i]);
  }
  block(chars, sums, change);
  // TODO - validate - chain of pointer diffs with ledger(out?)

  //printf("\n ref (address of pointer)/pointer/pointer! \n:");
  //printf("&chars(d): %d ", &chars);
  //printf("&chars(p): %p ", &chars);
  //printf("\n chars(p): %p ", chars);
  //printf("\n chars(d): %d ", chars);
  //uintptr_t ptr = (uintptr_t)chars;
  //printf("\n ptr(p): %p ", ptr);



  //block(&sums, &chars, &stub()); 

  free(sums);
  return 0;
}
