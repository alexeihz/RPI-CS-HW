/* adder.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Use inputs d0, d1, and carry_in to compute both the sum
 * (which is returned) and the carry_out (passed by reference)
 *
 * Note that carry_out could be NULL, indicating that we do
 * not want to determine carry_out (i.e., only return the sum)
 */
int add_two_bits(int d0, int d1, int carry_in, int *carry_out)
{
  if (carry_out != NULL) {
    *carry_out = d0 & d1 | d0 & carry_in | d1 & carry_in;
  }
  return !d0 & !d1 & carry_in | !d0 & d1 & !carry_in | d0 & d1 & carry_in | d0 & !d1 & !carry_in;
}

void dec2bin(int dec, int width, int* bin) {
  for (int i = 0; i < width; ++i) {
    bin[i] = dec & 1;
    dec >>= 1;
  }
}

void bin2dec(int* bin, int width, int* dec) {
  *dec = 0;
  for (int i = 0; i < width; ++i) {
    *dec += bin[i] << i;
  }
}

int main()
{
  int i;
  int d0[4];
  int d1[4];
  int ci[4];
  int sum[4];

  int passed = 0, total = 0;
  int width = sizeof(d0) / sizeof(d0[0]);
  int actual, expected;
  for (int i = 0; i < powl(2, width); ++i) {
    for (int j = 0; j < powl(2, width); ++j) {
      dec2bin(i, width, d0);
      dec2bin(j, width, d1);
      sum[0] = add_two_bits(d0[0], d1[0], 0, &ci[1]);
      sum[1] = add_two_bits(d0[1], d1[1], ci[1], &ci[2]);
      sum[2] = add_two_bits(d0[2], d1[2], ci[2], &ci[3]);
      sum[3] = add_two_bits(d0[3], d1[3], ci[3], NULL);
      expected = (i + j) % (int)powl(2, width);
      bin2dec(sum, width, &actual);
      if (actual != expected) {
        printf("Test case failed: i = %d; j = %d; expected = %d; actual = %d\n", i, j, expected, actual);
      }
      else {
        passed++;
      }
      total++;
    }
  }
  printf("Test case passed: %d/%d\n", passed, total);

  return EXIT_SUCCESS;
}
