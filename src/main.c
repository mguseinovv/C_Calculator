#include "calc/back/s21_smartcalc.h"

int main(void) {
  char output[255] = {'\0'};
  char* input = {"1+2-1*2+5^2+(1-3)"};
  double result = 0;
  size_t len = 0;
  int status = OK;
  s21_smartcalc(input, &result, 0);
  printf("input = [%s]\n", input);

  printf("result = [%lf]\n", result);

  return 0;
}
