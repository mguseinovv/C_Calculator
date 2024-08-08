#include "s21_smartcalc.h"

int s21_smartcalc(char* input, double* result, double x) {
  char output[512] = {'\0'};
  int status = OK;
  status = translate_from_infix_to_polish(input, output);
  if (status == OK) {
    status = calculating(output, result, x);
  }
  return status;
}
