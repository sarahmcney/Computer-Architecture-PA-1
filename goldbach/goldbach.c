#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Function declerations
bool is_prime(int n);
bool is_odd(int n);
void goldbach(int n);

int main(int argc, char* argv[]) {
  int number = atoi(argv[1]);
  //bool result = is_prime(number);
  //printf("%d\n", result);
  goldbach(number);
  return EXIT_SUCCESS;
}

bool is_prime(int n){
  if(n < 2) { return false; }
  for(int i = 2; i <= sqrt(n); i++) { //double check the <= sqrt
    if((n % i) == 0) {
      return false;
    }
  }
  return true;
}

bool is_odd(int n) { 
  if(n % 2 == 0) { return false; }
  return true;
}

void goldbach(int n) {
  if(!is_odd(n)) { 
    perror("invalid -- must input odd number\n");
    //return EXIT_FAILURE;
  }
  int primes[3] = {0, 0, 0};
  for(int i = (n - 4); i >= 2; i--) {
    if(is_prime(i)) {
      if((primes[0] == 0) && (n - i >= 4)) {
        primes[0] = i;
        continue;
      }
      else if((primes[1] == 0) && (n - primes[0] - i >= 2)) {
        primes[1] = i;
        continue;
      }
      else if((primes[2] == 0) && (primes[0] + primes[1] + i == n)) {
        primes[2] = i;
      }
    }
  }

  int num = 2;
  while(primes[2] == 0) {
    if(primes[0] + primes[1] + num == n) {
      primes[2] = num;
    }
    else {
      num += 1;
    }
  }
  printf("%d = %d + %d + %d\n", n, primes[0], primes[1], primes[2]);
}