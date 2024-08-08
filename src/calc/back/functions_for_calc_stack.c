#include "s21_smartcalc.h"

int createStack_for_calc(Stack_calc **stack) {
  int status = OK;
  if (!(*stack = malloc(sizeof(Stack_calc)))) {
    status = OUT_OF_MEMORY;
  }
  (*stack)->size = INIT_SIZE;
  (*stack)->numbers = malloc((*stack)->size * sizeof(double));
  if ((*stack)->numbers == NULL) {
    free(stack);
    status = OUT_OF_MEMORY;
  }
  (*stack)->top = 0;
  return status;
}

void deleteStack_for_calc(Stack_calc **stack) {
  free((*stack)->numbers);
  free(*stack);
  *stack = NULL;
}

int resize_for_calc(Stack_calc *stack) {
  int status = OK;
  stack->size *= MULTIPLIER;
  stack->numbers = realloc(stack->numbers, stack->size * sizeof(double));
  if (stack->numbers == NULL) {
    status = STACK_OVERFLOW;
  }
  return status;
}

void push_for_calc(Stack_calc *stack, double value) {
  if (stack->top >= stack->size) {
    resize_for_calc(stack);
  }

  stack->numbers[stack->top] = value;
  stack->top++;
}

double pop_for_calc(Stack_calc *stack) {
  stack->top -= 1;
  return stack->numbers[stack->top];
}

double peek_for_calc(const Stack_calc *stack) {
  return stack->numbers[stack->top - 1];
}
