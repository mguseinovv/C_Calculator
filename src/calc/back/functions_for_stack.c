#include "s21_smartcalc.h"

int createStack(Stack_t **stack) {
  int status = OK;
  if (!(*stack = malloc(sizeof(Stack_t)))) {
    status = OUT_OF_MEMORY;
  }
  (*stack)->size = INIT_SIZE;
  (*stack)->data = malloc((*stack)->size * sizeof(St_element));
  if ((*stack)->data == NULL) {
    free(stack);
    status = OUT_OF_MEMORY;
  }
  (*stack)->top = 0;
  return status;
}

void deleteStack(Stack_t **stack) {
  free((*stack)->data);
  free(*stack);
  *stack = NULL;
}

int resize(Stack_t *stack) {
  int status = OK;
  stack->size *= MULTIPLIER;
  stack->data = realloc(stack->data, stack->size * sizeof(St_element));
  if (stack->data == NULL) {
    status = STACK_OVERFLOW;
  }
  return status;
}

void push(Stack_t *stack, St_element value) {
  if (stack->top >= stack->size) {
    resize(stack);
  }
  stack->data[stack->top] = value;
  stack->top++;
}

St_element pop(Stack_t *stack) {
  stack->top--;
  return stack->data[stack->top];
}

St_element peek(const Stack_t *stack) { return stack->data[stack->top - 1]; }
