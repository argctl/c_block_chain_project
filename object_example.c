#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int (*function)(int, int);
  int (*add)(int, int);
  int operand;
  int operand_;
} Callable;

int add(int operand, int operand_) {
  return operand + operand_;
}

int multiply(int operand, int operand_) {
  return operand * operand_;
} 

int call(Callable *callable, char c) {
  if (c == 'm') return callable->function(callable->operand, callable->operand_);
  if (c == 'a') return callable->add(callable->operand, callable->operand_);
}
/*
int _call(Callable *callable, void* (*func)) {
  return callable-> 
}
*/

Callable* createCallable(int (*function)(int, int), int(*add)(int, int), int operand, int operand_) {
  Callable *callable = malloc(sizeof(Callable));
  callable->function = function;
  callable->add = add;
  callable->operand = operand;
  callable->operand_ = operand_;
  return callable;
}

int main () {
  Callable *callable = createCallable(multiply, add, 2, 1);
  int result = call(callable, 'm');
  int result_ = call(callable, 'a');
  printf("result: %d \n", result);
  printf("result_: %d \n", result_);
  free(callable);
  return 0;
}
