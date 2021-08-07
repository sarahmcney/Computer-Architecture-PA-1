#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int findlargest(int nums[], int size);
int main(int argc, char* argv[]) {

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }
  char numbers[10], numlargest[10];
  fscanf(fp, "%s", numbers);
  fscanf(fp, "%s", numlargest);

  int size = atoi(numbers);
  int largest = atoi(numlargest);

  int nums[size];
  for(int i = 0; i < size; i++) {
    char newnum[100];
    fscanf(fp, "%99s", newnum);
    nums[i] = atoi(newnum);
  }

  //sort array - descending
  int temp;
  for(int i = 0; i < size; i++) {
    for(int j = i+1; j < size; j++) {
      if(nums[i] < nums[j]) {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }

  for(int i = 0; i < largest; i++) {
    printf("%d ", nums[i]);
  }

  fclose(fp);

}

