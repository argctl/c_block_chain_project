#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// virtual register - is one full 8 int array
// half register - is the size of 4 ints
// opcode appendage - fill 25 percent of full opcode to verify next chain
// A, C, F, G, E, D, L, L
// 0, 1, 2, 3, 4, 5, 6, 7
// block (op)
// A1, F7, G2, L7 
// A, C, F, G, E, D, L, L
// 1, 1, 7, 2, 4, 5, 7, 7

// not a stub probably but for test input, probably a driver
int *stub () {
  int *change = malloc(4 * sizeof(int *) + 4 * sizeof(char));  
  //change[1.5]
  return change;
}

// guess magic number to change, i.e. foobar is temp opcode to change footballarg foo_ba___r_
// creates variable length integer locking system with updates that chain
// pass the memory address in, copy, then change
int *block(int *lowkey, int *keylow, int *change) {
  // TODO -
  // create new pointer memory allocation with input vars (lowkey, keylow)
  // use lowkey (char analogue) to set keylow with change
  // push to a stack that can be referenced by block number
  //for (int i = 0; i < 8; i++) {
    // change is truly variable length if we just subject bytes for each iteration?
    //if (lowkey[i] == change[i])
  //} 
  return 0;
}

int main() {
  char opt[9];
  printf("Enter 8 character opcode for vm: "); 
  scanf("%8s", opt);
  printf("you entered: %s\n", opt); 
  char array[8];
  int *sums = malloc(8 * sizeof(int *));
  int *chars = malloc(8 * sizeof(char)); // *?
  int *change = malloc(4 * sizeof(int *) + 4 * sizeof(char));  
  //int *sums[8];
  memset(array, '0', sizeof(array));
  for (int i = 0; i < 8; i++) {
    sums[i] = i;
  }
  for (int i = 0; i < 8; i++) {
    printf("%d ", sums[i]);
    chars[i] = array[i];
    printf("%d ", chars[i]);
  }

  printf("\n ref (address of pointer)/pointer/pointer! \n:");
  printf("%d ", &chars);
  printf("%p ", chars);
  uintptr_t ptr = (uintptr_t)chars;
  printf("%p ", ptr);



  //block(&sums, &chars, &stub()); 

  free(sums);
  return 0;
}
