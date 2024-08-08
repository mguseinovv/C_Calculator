#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FALSE 0
#define ERROR_TRUE 1
#define OK 0
#define NUMBER_FOUND 3
#define INCORRECT_INPUT 1
#define MULTIPLIER 2
#define INIT_SIZE 3
#define STACK_OVERFLOW 100
#define STACK_UNDERFLOW 101
#define OUT_OF_MEMORY 102
#define INPUT_UNDERFLOW 103

#define OPERANDS "0123456789"
#define NULL_PRIORITY "cos sin tan acos asin atan sqrt ln log ( ) ,"
#define ONE_PRIORITY "+-"
#define TWO__PRIORITY "*/ mod"
#define THREE_PRIORITY "^"
#define FOUR_PRIORITY "~#"
#define ALL_OPERATION "+-*^/mod"

typedef struct St_element {
  char operand;
  int priority;
} St_element;

typedef struct Stack_tag {
  St_element *data;
  int size;
  int top;
} Stack_t;

typedef struct Stack_calc {
  double *numbers;
  int size;
  int top;
} Stack_calc;

int s21_smartcalc(char *input, double *result, double x);

int translate_from_infix_to_polish(char *input, char *output);
int analize_number(char *input, char *output, int *i, int *size_output,
                   int *check_number_after_bracket);
int search_operation(char *input, int *number_simbol, char *operation);
int analize_stack(Stack_t *stack, char *output, int *size_output,
                  St_element *simbol, int *check_number_after_bracket);
int analize_operation(char *operation, int *check_number_after_bracket,
                      St_element *simbol);
void search_unary(char *operation, int *size_output, Stack_t *stack,
                  int check_number_after_bracket);
St_element analize_for_functions(char *operation);
int process_comma(Stack_t *stack, char *output, St_element *val1,
                  int *size_output);
int procces_bracket(Stack_t *stack, char *output, St_element *value,
                    int *size_output);
void procces_priority(Stack_t *stack, char *output, St_element value,
                      int *size_output);
void record_operation_to_output(char *output, char lexeme, int *size_output);

int calculating(char *output, double *result, double x);
int search_size_buffer(int i, const char *output);
void from_output_to_buffer(char *output, char *buffer, int size_buffer,
                           int i_output);
int analize_buffer(char *buffer, Stack_calc *stack, double x);
int finding_function_from_buffer(char *buffer, Stack_calc *stack);
int binary_operation(Stack_calc *stack, char operation);
int unary_operation(Stack_calc *stack, char operation);

int createStack(Stack_t **stack);
void deleteStack(Stack_t **stack);
int resize(Stack_t *stack);
void push(Stack_t *stack, St_element value);
St_element pop(Stack_t *stack);
St_element peek(const Stack_t *stack);

int createStack_for_calc(Stack_calc **stack);
void deleteStack_for_calc(Stack_calc **stack);
int resize_for_calc(Stack_calc *stack);
void push_for_calc(Stack_calc *stack, double value);
double pop_for_calc(Stack_calc *stack);
double peek_for_calc(const Stack_calc *stack);

#endif  // S21_SMARTCALC_H
