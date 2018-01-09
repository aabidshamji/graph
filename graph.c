/***********************************************************************
* Homework: Pointers, Functions, and Arrays
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define NUM_BINS 10

//Variable declarations
const unsigned int MAX_WIDTH = 60;
const unsigned int SAMPLE_SIZE = 1000;

// Function declarations
double modify (int *arr);
void rand_fill(double *arr);
void group_vals (double *source, int *output);
void cum_nums (int *arr, int *cum_arr);
void print_arr (int *arr, double factor, int cum);
int *max_arr (int *arr);
void test_randvals (double *arr);
void test_groups (int *arr);
void test_cum (int *arr);
void test_print (int *arr);

int
main (void){

  // Variable declaration
  double myints[SAMPLE_SIZE];
  int groups[NUM_BINS];
  int cum_vals[NUM_BINS];

  rand_fill(myints);
  test_randvals(myints);
  group_vals(myints, groups);
  test_groups(groups);
  cum_nums(groups, cum_vals);
  test_cum(cum_vals);
  double factor = modify(groups);
  test_print(groups);
  print_arr(groups, factor, 0);
  double cum_factor = modify(cum_vals);
  test_print(cum_vals);
  print_arr(cum_vals, cum_factor, 1);

  return 0;

} //main

/*
Function: test_randvals
Purpose: to check if the randomlly generated values are with between 0 and 1 inclusive
Preconditions: an array of size SAMPLE_SIZE has bee filled with random ints from rand_fill
Postconditions: if test is successful, nothing should happen!
*/
void
test_randvals (double *arr){

  for (int i = 0; i < SAMPLE_SIZE; i++) {
    assert (arr[i] >= 0);
    assert (arr[i] <= 1);
  }

} // test_randvals

/*
Function: test_groups
Purpose: to check if the ints have been groups properly
Preconditions: an array of size SAMPLE_SIZE has bee filled with random ints and grouped into a new array by group_vals
Postconditions: if test is successful, nothing should happen!
*/
void
test_groups (int *arr) {

  int max = 0;
  //finding the max
  for (int i = 0; i < NUM_BINS; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  //checking the the largest value is not bigger than the sample size
  assert(max <= SAMPLE_SIZE);

  //finding the sum
  int sum = 0;

  for (int i = 0; i < NUM_BINS; i++) {
    sum += arr[i];
  }

  // checking that the sum of the array it equal to the number of samples
  assert(sum == SAMPLE_SIZE);

} // test_groups

/*
Function: test_cum
Purpose: to check if array holding cumulative values is accurate
Preconditions: an array of size NUM_BINS has been modified into a cumulative array by cum_nums
Postconditions: if test is successful, nothing should happen!
*/
void
test_cum (int *arr) {

  for (int i = 0; i < NUM_BINS-1; i++) {
    assert(arr[i] <= arr[i+1]);
  }
  //assert(arr[NUM_BINS] == SAMPLE_SIZE);
} // test_cum


/*
Function: test_print
Purpose: to check if the arrays have been scaled properly before printing
Preconditions: the array has already been modified by modify()
Postconditions: if test is successful, nothing should happen!
*/
void
test_print (int *arr){
  int max = 0;

  for (int i = 0; i < NUM_BINS; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  assert(max <= MAX_WIDTH);
} //test-print

/*
Function: rand_fill
Purpose: to fill an array of size SAMPLE_SIZE with random doubles between 0 and 1 inclusive
Preconditions: the array is of size SAMPLE_SIZE and as already been declared with type double
Postconditions: for every element in array[n] = a random value between 0 and 1 inclusive
*/
void
rand_fill(double *arr) {

  srand(time(NULL));
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    arr[i] = pow((rand() / (double) RAND_MAX), 2);
  }

} //rand_fill

/*
Function: group_vals
Purpose: to discretize the values in the random array (input) and store the results in a new array (output)
Preconditions: source is an array of size SAMPLE_SIZE
the values in source are between 0 and 1 inclusive
output is an array of size NUM_BINS
both have been previously declared
Postconditions: The values are discretized into NUM_BINS bins
The value of any element in output does not exceed SAMPLE_SIZE
*/
void
group_vals (double *source, int *output){
  // calculating the size of each bin
  const float bin_size = 1 / (double) NUM_BINS;
  // setting the constraints for each bin
  double bin_min = 0;
  double bin_max = bin_min + bin_size;

  for (int i = 0; i < NUM_BINS; i++) {
    output[i] = 0;
  }

  for (int i = 0; i < NUM_BINS; i++) // checking for everybin
  {
    for (int j = 0; j < SAMPLE_SIZE; j++) // checking for every value in input
    {
      if (source[j] >= bin_min && source[j] < bin_max) // checking if the value belongs in the bin
      {
        output[i]++;
      }
    }
    bin_min += bin_size;
    bin_max = bin_min + bin_size;
  }
}  // group_vals

/*
Function: max_arr
Purpose: To find the largest value in an array
Preconditions: Array must be of type int and be of size NUM_BINS
Postconditions: returns the address of the largest value in the array
*/
int *
max_arr (int *arr) {

  int *max = 0;
  max = (int *)malloc(sizeof(int));
  //check max so far against each value in the array
  for (int i = 0; i < NUM_BINS; i++) {
    if (arr[i] > *max) {
      *max = arr[i];
    }
  }
  free(max);
  return max;

} // max_arr

/*
Function: modify
Purpose: to modify the values in the given array so that the largest value is equal to MAX_WIDTH
Preconditions: arr is of size NUM_BINS
Postconditions: the largest value in arr = MAX_WIDTH
the factor returned is the value that each element in arr was multiplied by
*/
double
modify (int *arr) {
  // get the largest value in the array
  int max = *max_arr(arr);
  // find the factor
  double factor = (double) MAX_WIDTH / (double) max;
  // modifys the array
  for (int i = 0; i < NUM_BINS; i++) {
    arr[i] = round((double) arr[i] * factor);
  }

  return factor;
} // modify


/*
Function: cum_nums
Purpose: To create a cumulative array
Preconditions:
Postconditions:
*/
void
cum_nums (int *arr, int *cum_arr) {
  cum_arr[0] = arr[0];

  for (int i = 0; i < NUM_BINS; i++) {
    cum_arr[i+1] = cum_arr[i] + arr[i+1];
  }
} //cum_nums

/*
Function: print_arr
Purpose: to print an array as a hisogram
Preconditions: The array has been grouped and modified
The array is of size NUM_BINS
The largest value in arr is == MAX_WIDTH
Postconditions: Prints a historgram using the array provided using *s
Each bin is on its own line
*/
void
print_arr (int *arr, double factor, int cum){

  if (cum) {
    printf("\n\nCUMULATIVE DISTRIBUTION\n");
  } // checks if it is printing a cumulative histogram

  printf("\nGenerating a histogram using the following parameters:\nNumber of Samples: %d\nNumber of Bins: %d\nMaximum Width: %d\n", SAMPLE_SIZE, NUM_BINS, MAX_WIDTH);
  printf("Scaling factor = %.3lf\n\n", factor);

  float bin_size = 1 / (double) NUM_BINS;
  double pbin_min = 0;
  double pbin_max = pbin_min + bin_size;

  printf("\t   Range | Frequency\n");
  for (int i = 0; i < NUM_BINS; i++)
  {
    printf("%.2lf < x <= %.2lf | ", pbin_min, pbin_max); // prints axis labels
    pbin_min += bin_size;
    pbin_max = pbin_min + bin_size;
    for (int j = 0; j < arr[i]; j++)
    {
      printf("*"); // prints frequency
    }
    printf("\n");
  }
} // print_arr
