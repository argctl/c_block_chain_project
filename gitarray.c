//#include <stdlib.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

#include "arg.c"
#include "array.c"

char** gitarray (char** history, int** results, int x, int y) {
  // Integer reference and character reference differ if we size of network packet 
  // x is start position, y is end position
  int size = y - x;
  //char** space = (char**)malloc(size * (sizeof(char) * 16)); 
  char** space = (char**)malloc(size * sizeof(char*));
  for (int i = x; i < y; i++) {
    //char* loc = (space + (sizeof(char) * 8));
    space[i] = (char*)malloc(sizeof(char*) * 16);
    for (int d = 0; d < 16; d++) {
      //space[i][j] = history[i][j] + (char)result[i][j];
      //char* pos = loc + (sizeof(char) * j);
      //char result = results[i][d];
      //space[i][d] = d % 2 ? history[i][d] : results[i][d]; // + (char)results[i][d];
      //space[i][d] = d % 2 ? results[i][d > 7 ? d - 8 : d] : history[i][d > 7 ? d - 8 : d]; // 0, 2, 4, 6, 8, 10, 12, 14
      space[i][d] = d % 2 ? results[i][d > 7 ? d - 8 : d] : history[i][d > 7 ? d - 8 : d];  
      // 0, 2, 4, 6, 8, 10, 12, 14
      //space[i][d-1] = history[i][d];
      //space[i][d+1] = results[i][d];
      //space[i][d] = results[i][d > 7 ? d - 8 : d]; // 1, 3, 5, 7, 9, 11, 13, 15
      printf(" %c, %c", space[i][d], space[i][d + 1]);

    }
    printf("\n");
  }
  return space;
}

Arg* gitar (int x, int y) {
  int* tar = (int*)malloc(sizeof(int));
  *tar = x * y * 16;
  Arg* arg = createInner(inner);
  return arg;
}

int main () {
  int x = 0;
  int y = 10;
  int size = y - x;

  Arg* arg = gitar(x, y);

  int** results = (int**)malloc((y - x) * sizeof(int*));
  char** history = (char**)malloc(size * sizeof(char*));
  for (int i = 0; i < y; i++) {
    results[i] = (int*)malloc(8 * sizeof(int*));
    history[i] = (char*)malloc(8 * sizeof(char*));
    for (int d = 0; d < 8; d++) {
      results[i][d] = 72;
      history[i][d] = 'G';
      printf("\n results[%d][%d]: %d", i, d, results[i][d]);
      printf("\n history[%d][%d]: %c", i, d, history[i][d]);
    }
  }
  char** space = gitarray(history, results, x, y);
  for (int i = 0; i < y; i++) {
    printf("\nspace: ");
    for (int d = 0; d < 16; d++) {
      printf("%c", space[i][d]);
      //printf("\n (2) results[%d][%d]: %d", i, d, results[i][d]);
      //printf("\n history[%d][%d]: %c", i, d, history[i][d]);
    }
    printf("\n");
  }
  //printf("\n");
  return 0;
}

