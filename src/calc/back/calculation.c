#include "s21_smartcalc.h"

int calculating(char *output, double *result, double x) {
  int status = OK;
  int i = 0, length = strlen(output);
  Stack_calc *stack = NULL;
  createStack_for_calc(&stack);
  char *buffer;
  while (i < length && status == OK) {
    int size_buffer = search_size_buffer(i, output);
    buffer = (char *)malloc(size_buffer * sizeof(char));
    from_output_to_buffer(output, buffer, size_buffer, i);
    status = analize_buffer(buffer, stack, x);
    if (status == INCORRECT_INPUT) break;
    if (output[i] == ' ') {
      i++;
    } else {
      i += size_buffer;
    }
  }
  free(buffer);
  if (stack->top == 1) {
    *result = pop_for_calc(stack);
  } else {
    status = INCORRECT_INPUT;
  }
  deleteStack_for_calc(&stack);
  return status;
}

int search_size_buffer(int i, const char *output) {
  int result = 0;
  while (output[result + i] != ' ' && output[result + i] != '\0') {
    result++;
  }
  return result;
}

void from_output_to_buffer(char *output, char *buffer, int size_buffer,
                           int i_output) {
  for (int i = 0; i < size_buffer; i++) {
    buffer[i] = output[i_output + i];
  }
}

int analize_buffer(char *buffer, Stack_calc *stack, double x) {
  int status = OK;
  if (buffer[0] == 'x') {
    push_for_calc(stack, x);
  } else if (buffer[0] >= '0' && buffer[0] <= '9') {
    char *nbuf = buffer;
    double number = strtod(nbuf, &nbuf);
    push_for_calc(stack, number);
  } else {
    status = finding_function_from_buffer(buffer, stack);
  }
  return status;
}

int finding_function_from_buffer(char *buffer, Stack_calc *stack) {
  int status = OK;
  char unary_operation_array[11][1] = {{'c'}, {'s'}, {'t'}, {'C'}, {'S'}, {'T'},
                                       {'q'}, {'n'}, {'g'}, {'#'}, {'~'}};
  char binary_operation_array[6][1] = {{'+'}, {'-'}, {'*'},
                                       {'/'}, {'^'}, {'m'}};
  for (int i = 0; i < 11; i++) {
    char *rez = strchr(buffer, unary_operation_array[i][0]);
    if (rez != NULL) {
      status = unary_operation(stack, *rez);
      i = 11;
    }
  }
  for (int i = 0; i < 6; i++) {
    char *rez = strchr(buffer, binary_operation_array[i][0]);
    if (rez != NULL) {
      status = binary_operation(stack, *rez);
      i = 6;
    }
  }
  return status;
}

int binary_operation(Stack_calc *stack, char operation) {
  int status = OK;
  if (stack->top > 1) {
    double last = pop_for_calc(stack);
    double penult = pop_for_calc(stack);
    switch (operation) {
      case '+': {
        push_for_calc(stack, last + penult);
      }; break;
      case '-': {
        push_for_calc(stack, penult - last);
      }; break;
      case '*': {
        push_for_calc(stack, penult * last);
      }; break;
      case '/': {
        push_for_calc(stack, penult / last);
      }; break;
      case 'm': {
        push_for_calc(stack, fmod(penult, last));
      }; break;
      case '^': {
        push_for_calc(stack, pow(penult, last));
      }; break;
    }
  } else {
    status = INCORRECT_INPUT;
  }
  return status;
}

int unary_operation(Stack_calc *stack, char operation) {
  int status = OK;
  if (stack->top > 0) {
    double last = pop_for_calc(stack);
    switch (operation) {
      case 'c': {
        push_for_calc(stack, cos(last));
      }; break;
      case 's': {
        push_for_calc(stack, sin(last));
      }; break;
      case 't': {
        push_for_calc(stack, tan(last));
      }; break;
      case 'C': {
        push_for_calc(stack, acos(last));
      }; break;
      case 'S': {
        push_for_calc(stack, asin(last));
      }; break;
      case 'T': {
        push_for_calc(stack, atan(last));
      }; break;
      case 'q': {
        push_for_calc(stack, sqrt(last));
      }; break;
      case 'n': {
        push_for_calc(stack, log(last));
      }; break;
      case 'g': {
        push_for_calc(stack, log10(last));
      }; break;
      case '#': {
        push_for_calc(stack, +last);
      }; break;
      case '~': {
        push_for_calc(stack, -last);
      }; break;
    }
  } else {
    status = INCORRECT_INPUT;
  }
  return status;
}
