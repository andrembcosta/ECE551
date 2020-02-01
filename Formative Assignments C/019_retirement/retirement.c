#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double updateBalance(double balance, int age, retire_info info) {
  printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, balance);
  balance += balance * info.rate_of_return + info.contribution;
  return balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int age = startAge;

  for (int i = 0; i < working.months; i++) {
    balance = updateBalance(balance, age, working);
    age++;
  }

  for (int i = 0; i < retired.months; i++) {
    balance = updateBalance(balance, age, retired);
    age++;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
