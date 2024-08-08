#include "s21_smartcalc.h"

int analize_number(char *input, char *output, int *i, int *size_output,
                   int *check_number_after_bracket) {
  int status = OK, check_number_correct = 0;
  if (input[*i] == 'x') {
    check_number_correct = 1;
    output[*size_output] = input[*i];
    *size_output += 1;
    *check_number_after_bracket += 1;
  } else if ((input[*i] >= '0' && input[*i] <= '9')) {
    if (*check_number_after_bracket == 1) {
      *check_number_after_bracket = 2;
    }
    check_number_correct++;
    output[*size_output] = input[*i];
    *size_output += 1;
    *i += 1;
    while ((input[*i] >= '0' && input[*i] <= '9') || input[*i] == '.') {
      output[*size_output] = input[*i];
      *size_output += 1;
      if (input[*i] == '.') {
        check_number_correct++;
      }
      *i += 1;
    }
    if (check_number_correct >= 1) {
      *i -= 1;
    }
  }
  if (check_number_correct > 2) {
    status = INCORRECT_INPUT;
  }
  if (check_number_correct > 0 && status != INCORRECT_INPUT) {
    output[*size_output] = ' ';
    *size_output += 1;
    status = NUMBER_FOUND;
  }
  return status;
}
// Алгоритм Дейкстра
int translate_from_infix_to_polish(char *input, char *output) {
  int size_input = strlen(input);
  int size_output = 0;
  int status = OK;
  Stack_t *stack = NULL;
  createStack(&stack);
  int check_number_after_bracket = 0;
  for (int i = 0; i < size_input; i++) {
    status = analize_number(input, output, &i, &size_output,
                            &check_number_after_bracket);
    if (status == INCORRECT_INPUT) break;
    if (status == OK && input[i] != ' ') {
      char operation[6] = {'\0'};
      status = search_operation(input, &i, operation);
      if (status != OK) break;
      search_unary(operation, &size_output, stack, check_number_after_bracket);
      St_element simbol;
      status =
          analize_operation(operation, &check_number_after_bracket, &simbol);
      if (status != OK) break;
      status = analize_stack(stack, output, &size_output, &simbol,
                             &check_number_after_bracket);
      if (status != OK) break;
    }
  }
  while (stack->top > 0) {
    St_element value = pop(stack);
    record_operation_to_output(output, value.operand, &size_output);
    if (value.operand == '(' || value.operand == ')') status = INCORRECT_INPUT;
  }
  if (status != INCORRECT_INPUT) {
    output[size_output] = '\0';
    size_output += 1;
    status = OK;
  }

  deleteStack(&stack);
  return status;
}

int analize_stack(Stack_t *stack, char *output, int *size_output,
                  St_element *simbol, int *check_number_after_bracket) {
  int status = OK;
  if (stack->top > 0) {
    if (simbol->operand == ')') {
      status = procces_bracket(stack, output, simbol, size_output);
      *check_number_after_bracket = 0;
    } else {
      procces_priority(stack, output, *simbol, size_output);
    }
  } else {
    push(stack, *simbol);
  }
  return status;
}

void procces_priority(Stack_t *stack, char *output, St_element value,
                      int *size_output) {
  St_element val2 = peek(stack);
  while (val2.priority >= value.priority && stack->top > 0 &&
         value.priority != 0 && val2.operand != 'x') {
    val2 = pop(stack);
    record_operation_to_output(output, val2.operand, size_output);
    if (stack->top > 0) {
      val2 = peek(stack);
    }
  }
  if (value.priority <= 4) {
    push(stack, value);
  }
}

void record_operation_to_output(char *output, char lexeme, int *size_output) {
  output[*size_output] = lexeme;
  *size_output += 1;
  output[*size_output] = ' ';
  *size_output += 1;
}

int process_comma(Stack_t *stack, char *output, St_element *val1,
                  int *size_output) {
  int status = OK;
  pop(stack);
  while (val1->operand != '(') {
    if ((int)stack->top == 0) {
      status = INCORRECT_INPUT;
      break;
    }
    *val1 = pop(stack);
    if (val1->operand != '(') {
      record_operation_to_output(output, val1->operand, size_output);
    }
  }
  if (status == OK) {
    push(stack, *val1);
  }
  return status;
}

int procces_bracket(Stack_t *stack, char *output, St_element *value,
                    int *size_output) {
  int status = OK;
  while (value->operand != '(') {
    if (stack->top == 0) {
      status = INCORRECT_INPUT;
      break;
    }
    *value = pop(stack);
    if (value->operand != '(') {
      record_operation_to_output(output, value->operand, size_output);
    }
  }
  if (status == OK && stack->top > 0) {
    *value = peek(stack);
    if (value->priority == 0 && value->operand != '(') {
      *value = pop(stack);
      record_operation_to_output(output, value->operand, size_output);
    }
  }
  return status;
}

int analize_operation(char *operation, int *check_number_after_bracket,
                      St_element *simbol) {
  int status = OK;
  if (strstr(NULL_PRIORITY, operation) != NULL) {
    *simbol = analize_for_functions(operation);
    if (simbol->operand == '(') {
      *check_number_after_bracket = 1;
    }
    simbol->priority = 0;
  } else if (strstr(ONE_PRIORITY, operation) != NULL) {
    simbol->priority = 1;
    simbol->operand = operation[0];
  } else if (strstr(TWO__PRIORITY, operation) != NULL) {
    simbol->priority = 2;
    simbol->operand = operation[0];
  } else if (strstr(THREE_PRIORITY, operation) != NULL) {
    simbol->priority = 3;
    simbol->operand = operation[0];
  } else if (strstr(FOUR_PRIORITY, operation) != NULL) {
    simbol->priority = 4;
    simbol->operand = operation[0];
  } else {
    status = INCORRECT_INPUT;
  }
  return status;
}

St_element analize_for_functions(char *operation) {
  St_element simbol;
  simbol.priority = 0;
  if (strcmp(operation, "cos") == 0) {
    simbol.operand = 'c';
  } else if (strcmp(operation, "sin") == 0) {
    simbol.operand = 's';
  } else if (strcmp(operation, "sqrt") == 0) {
    simbol.operand = 'q';
  } else if (strcmp(operation, "tan") == 0) {
    simbol.operand = 't';
  } else if (strcmp(operation, "atan") == 0) {
    simbol.operand = 'T';
  } else if (strcmp(operation, "acos") == 0) {
    simbol.operand = 'C';
  } else if (strcmp(operation, "asin") == 0) {
    simbol.operand = 'S';
  } else if (strcmp(operation, "ln") == 0) {
    simbol.operand = 'n';
  } else if (strcmp(operation, "log") == 0) {
    simbol.operand = 'g';
  } else if (strcmp(operation, "(") == 0) {
    simbol.operand = '(';
  } else if (strcmp(operation, ")") == 0) {
    simbol.operand = ')';
  } else if (strcmp(operation, ",") == 0) {
    simbol.operand = ',';
  }
  return simbol;
}

void search_unary(char *operation, int *size_output, Stack_t *stack,
                  int check_number_after_bracket) {
  if ((*size_output == 0 ||
       (peek(stack).operand == '(' && check_number_after_bracket == 1)) &&
      (operation[0] == '+' || operation[0] == '-')) {
    operation[0] = (operation[0] == '+') ? '#' : '~';
  }
}

int search_operation(char *input, int *number_simbol, char *operation) {
  int status = OK;
  if (*number_simbol > (int)strlen(input)) {
    status = INCORRECT_INPUT;
  }
  operation[0] = input[*number_simbol];
  if (operation[0] == '^') {
    operation[1] = '\0';
  } else if (operation[0] == 'm') {
    for (int i = 1; i < 3; i++) {
      if (*number_simbol + i > (int)strlen(input)) {
        status = INCORRECT_INPUT;
        break;
      } else {
        operation[i] = input[*number_simbol + i];
      }
    }
    *number_simbol += 2;
  } else if (operation[0] >= 97 && operation[0] <= 122) {
    int i = 1;
    if (*number_simbol + i > (int)strlen(input)) {
      status = INCORRECT_INPUT;
    } else {
      operation[i] = input[*number_simbol + i];
    }
    while (operation[i] != '(') {
      i++;
      if (*number_simbol + i > (int)strlen(input)) {
        status = INCORRECT_INPUT;
        break;
      } else {
        operation[i] = input[*number_simbol + i];
      }
      if (i > 4) {
        status = INCORRECT_INPUT;
        break;
      }
    }
    operation[i] = '\0';
    *number_simbol += i - 1;
  }
  return status;
}
