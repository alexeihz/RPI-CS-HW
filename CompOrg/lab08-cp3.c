/* lab08.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

/* define BIT type as a char (i.e., one byte) */ 
typedef char BIT;

/* function prototypes (basic gates) */
BIT not_gate( BIT );
BIT or_gate( BIT, BIT );
BIT and_gate( BIT, BIT );
BIT xor_gate( BIT, BIT );

/* function prototypes (combinational circuits) */
BIT multiplexer( BIT, BIT, BIT, BIT, BIT, BIT );
void decoder( BIT, BIT, BIT*, BIT*, BIT*, BIT* );

/* function prototypes (ALUs) */
BIT alu_1bit( BIT, BIT, BIT, BIT, BIT, BIT* );
void alu_4bit( BIT, BIT, BIT, BIT, BIT, BIT, BIT, BIT, BIT, BIT, BIT*, BIT*, BIT*, BIT*);

/* function prototype (floating point binary conversion) */
void ieee754encode( float value, char * encoded );

int combine(BIT, BIT, BIT, BIT);
void split(int val, BIT*, BIT*, BIT*, BIT*);

/* main() provides some unit testing */
int main()
{
   BIT A, B;
   BIT I0, I1, I2, I3;
   BIT O0, O1, O2, O3;
   BIT S0, S1;
   BIT OP0, OP1, CIN, COUT;
   BIT A0, A1, A2, A3, B0, B1, B2, B3, C0, C1, C2, C3, E0, E1, E2, E3;

   /* Unit test for NOT gate:
    *      _
    *  A | A
    * ---|---
    *  0 | 1
    *  1 | 0
    */
   printf( "===== Unit test for not_gate =====\n" );
   printf( "not_gate( A ) | RESULT\n" );
   printf( "--------------|--------\n" );
   printf( "not_gate( 0 ) | %d\n", not_gate( 0 ) );
   printf( "not_gate( 1 ) | %d\n", not_gate( 1 ) );
  

   /* Unit test for OR gate:
    *
    *  A  B | A OR B
    * ------|--------
    *  0  0 |   0
    *  0  1 |   1
    *  1  0 |   1
    *  1  1 |   1
    */
   printf( "\n===== Unit test for or_gate =====\n" );
   printf( "or_gate( A, B ) | RESULT\n" );
   printf( "----------------|--------\n" );

   for( A = 0 ; A < 2 ; A++ )
      for( B = 0 ; B < 2 ; B++ )
         printf( "or_gate( %d, %d ) | %d\n", A, B, or_gate( A, B ) );

   
   /* Unit test for AND gate:
    *
    *  A  B | A AND B
    * ------|--------
    *  0  0 |    0
    *  0  1 |    0
    *  1  0 |    0
    *  1  1 |    1
    */
   printf( "\n===== Unit test for and_gate =====\n" );
   printf( "and_gate( A, B ) | RESULT\n" );
   printf( "-----------------|--------\n" );

   for( A = 0 ; A < 2 ; A++ )
      for( B = 0 ; B < 2 ; B++ )
         printf( "and_gate( %d, %d ) | %d\n", A, B, and_gate( A, B ) );

   
   /* Unit test for XOR gate:
    *
    *  A  B | A XOR B
    * ------|--------
    *  0  0 |    0
    *  0  1 |    1
    *  1  0 |    1
    *  1  1 |    0
    */
   printf( "\n===== Unit test for xor_gate =====\n" );
   printf( "xor_gate( A, B ) | RESULT\n" );
   printf( "-----------------|--------\n" );

   for( A = 0 ; A < 2 ; A++ )
      for( B = 0 ; B < 2 ; B++ )
         printf( "xor_gate( %d, %d ) | %d\n", A, B, xor_gate( A, B ) );


   /* Unit test for 4-input multiplexer */
   printf( "\n===== Unit test for 4-input multiplexer =====\n" );
   printf( "multiplexer( S0, S1 ) | ( I0, I1, I2, I3 ) | RESULT ( I0 | I1 | I2 | I3 )\n" );
   printf( "----------------------|--------------------|------------------------------\n" );
   for( S0 = 0 ; S0 < 2 ; S0++ )
      for( S1 = 0 ; S1 < 2 ; S1++ )
         for( I0 = 0; I0 < 2; I0++ )
            for( I1 = 0; I1 < 2; I1++ )
               for( I2 = 0; I2 < 2; I2++ )
                  for( I3 = 0; I3 < 2; I3++ )
                     printf( "multiplexer( %2d, %2d ) | ( %2d, %2d, %2d, %2d ) | %2d\n",
                             S0, S1, I0, I1, I2, I3, multiplexer( I0, I1, I2, I3, S0, S1 ) );


   /* Unit test for 2-input decoder:
    *
    *  I0 I1 | O0 O1 O2 O3
    * -------|-------------
    *   0  0 |  1  0  0  0
    *   0  1 |  0  0  1  0
    *   1  0 |  0  1  0  0
    *   1  1 |  0  0  0  1
    */
   printf( "\n===== Unit test for 2-input decoder =====\n" );
   printf( "decoder( I0, I1 ) | ( O0, O1, O2, O3 )\n" );
   printf( "------------------|--------------------\n" );
   /*
    * TO DO: Implement test cases
    */
   for( I0 = 0 ; I0 < 2 ; I0++ )
      for( I1 = 0 ; I1 < 2 ; I1++ ) {
        decoder( I0, I1, &O0, &O1, &O2, &O3 );
        printf( "decoder( %2d, %2d ) | ( %2d, %2d, %2d, %2d )\n",
          I0, I1, O0, O1, O2, O3);
      }


   /* Unit test for 1-bit ALU:
    *  OP0 OP1 |  Operation
    * ---------|--------------
    *    0   0 |   A * B (AND)
    *    0   1 |   A + B (ADD)
    *    1   0 |   A + B (OR)
    *    1   1 |   A - B (SUB)
    *
    *  OP0 OP1 CIN  A  B | RESULT COUT
    * -------------------|-------------
    *    0   0   0  0  0 |      0    0
    *    0   0   0  0  1 |      0    0
    *    0   0   0  1  0 |      0    0
    *    0   0   0  1  1 |      1    1
    *    0   0   1  0  0 |      0    0
    *    0   0   1  0  1 |      0    1
    *    0   0   1  1  0 |      0    1
    *    0   0   1  1  1 |      1    1
    *    0   1   0  0  0 |      0    0
    *    0   1   0  0  1 |      1    0
    *    0   1   0  1  0 |      1    0
    *    0   1   0  1  1 |      0    1
    *    0   1   1  0  0 |      1    0
    *    0   1   1  0  1 |      0    1
    *    0   1   1  1  0 |      0    1
    *    0   1   1  1  1 |      1    1
    *    1   0   0  0  0 |      0    0
    *    1   0   0  0  1 |      1    0
    *    1   0   0  1  0 |      1    0
    *    1   0   0  1  1 |      1    1
    *    1   0   1  0  0 |      0    0
    *    1   0   1  0  1 |      1    1
    *    1   0   1  1  0 |      1    1
    *    1   0   1  1  1 |      1    1
    *    1   1   0  0  0 |      1    0
    *    1   1   0  0  1 |      0    0
    *    1   1   0  1  0 |      0    1
    *    1   1   0  1  1 |      1    0
    *    1   1   1  0  0 |      0    1
    *    1   1   1  0  1 |      1    0
    *    1   1   1  1  0 |      1    1
    *    1   1   1  1  1 |      0    1
    */
   printf( "\n===== Unit test for 1-bit alu =====\n" );
   printf( "alu_1bit( OP0, OP1, CIN, A, B ) | ( RESULT, COUT )\n" );
   printf( "--------------------------------|------------------\n" );
   /*
    * TO DO: Implement test cases
    */
   for( OP0 = 0 ; OP0 < 2 ; OP0++ )
      for( OP1 = 0 ; OP1 < 2 ; OP1++ )
         for( CIN = 0; CIN < 2; CIN++ )
            for( A = 0; A < 2; A++ )
               for( B = 0; B < 2; B++ )
                  printf("alu_1bit( %3d, %3d, %3d, %d, %d ) | ( %6d, %4d )\n",
                          OP0, OP1, CIN, A,  B, alu_1bit( OP0, OP1, CIN, A,  B, &COUT ), COUT );


   int failed = 0, total = 0, A4bit, B4bit, C4bit, expected = 0;
   printf( "\n===== Failed unit tests for 4-bit alu =====\n" );
   printf( "alu_4bit( OP0, OP1, A0, A1, A2, A3, B0, B1, B2, B3 ) | ( C0, C1, C2, C3 ) | expected ( E0, E1, E2, E3 )\n" );
   printf( "-----------------------------------------------------|--------------------|-----------------------------\n" );
   /*
    * TO DO: Implement test cases. Verify by comparing with the "expected" 
    * values and only print a message if there is a mismatch as shown in the example:
    * total++;
    * if ( !A3 ) A4bit = 0;
    * else A4bit = ~0x7;
    * A4bit |= A2 << 2;
    * A4bit |= A1 << 1;
    * A4bit |= A0;
    * if ( !B3 ) B4bit = 0;
    * else B4bit = ~0x7;
    * B4bit |= B2 << 2;
    * B4bit |= B1 << 1;
    * B4bit |= B0;
    * alu_4bit( OP0, OP1, A0, A1, A2, A3, B0, B1, B2, B3, &C0, &C1, &C2, &C3 );
    * if ( !C3 ) C4bit = 0;
    * else C4bit = ~0x7;
    * C4bit |= C2 << 2;
    * C4bit |= C1 << 1;
    * C4bit |= C0;
    * if ( !OP0 && OP1 ) expected = A4bit + B4bit;
    * E0 = expected & 0x01;
    * E1 = ( expected & 0x02 ) >> 1;
    * E2 = ( expected & 0x04 ) >> 2;
    * E3 = ( expected & 0x08 ) >> 3;
    * if ( ( expected & 0xf ) != ( C4bit & 0xf ) ) {
    *    printf( "alu_4bit( %3d, %3d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d ) "
    *            "| ( %2d, %2d, %2d, %2d ) | expected ( %2d, %2d, %2d, %2d )\n",
    *            OP0, OP1, A0, A1, A2, A3, B0, B1, B2, B3, C0, C1, C2, C3, E0, E1, E2, E3 );
    *    failed++;
    * }
    * Make sure you test all ALU operations on all possible combinations of input values.
    * Print statistics of failed and total test cases in the end.
    */

   for( OP0 = 0 ; OP0 < 2 ; OP0++ )
      for( OP1 = 0 ; OP1 < 2 ; OP1++ )
         for( A0 = 0; A0 < 2; A0++ )
            for( A1 = 0; A1 < 2; A1++ )
               for( A2 = 0; A2 < 2; A2++ )
                  for( A3 = 0; A3 < 2; A3++ )
                     for( B0 = 0; B0 < 2; B0++ )
                        for( B1 = 0; B1 < 2; B1++ )
                           for( B2 = 0; B2 < 2; B2++ )
                              for( B3 = 0; B3 < 2; B3++ ) {
                                 total++;
                                 A4bit = combine( A0, A1, A2, A3 );
                                 B4bit = combine( B0, B1, B2, B3 );
                                 alu_4bit( OP0, OP1, A0, A1, A2, A3, B0, B1, B2, B3, &C0, &C1, &C2, &C3 );
                                 if ( !OP0 && !OP1 ) expected = A4bit & B4bit;
                                 else if ( OP0 && !OP1 ) expected = A4bit | B4bit;
                                 else if ( !OP0 && OP1 ) expected = A4bit + B4bit;
                                 else expected = A4bit - B4bit;
                                 C4bit = combine( C0, C1, C2, C3 );
                                 split( expected, &E0, &E1, &E2, &E3 );
                                 if ( ( expected & 0xf ) != ( C4bit & 0xf ) ) {
                                      printf( "alu_4bit( %3d, %3d, %2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d ) "
                                              "| ( %2d, %2d, %2d, %2d ) | expected ( %2d, %2d, %2d, %2d )\n",
                                              OP0, OP1, A0, A1, A2, A3, B0, B1, B2, B3, C0, C1, C2, C3, E0, E1, E2, E3 );
                                      failed++;
                                 }
                              }
   printf("%d test cases out of %d failed.\n", failed, total);

   float value;
   char encoded[33];
   scanf("%f", &value);
   ieee754encode(value, encoded);

   return EXIT_SUCCESS;
}


int combine(BIT A0, BIT A1, BIT A2, BIT A3) {
   int result;
   if ( !A3 ) result = 0;
   else result = ~0x7;
   result |= A2 << 2;
   result |= A1 << 1;
   result |= A0;
   return result;
}

void split(int val, BIT *A0, BIT *A1, BIT *A2, BIT *A3) {
   *A0 = val & 0x01;
   *A1 = ( val & 0x02 ) >> 1;
   *A2 = ( val & 0x04 ) >> 2;
   *A3 = ( val & 0x08 ) >> 3;
   return;
}

BIT not_gate( BIT A )
{
   /* TO DO: implement logical NOT */
  if (A)
    return FALSE;
  else
    return TRUE;
}


BIT or_gate( BIT A, BIT B )
{
   /* TO DO: implement logical OR */
  if (A || B)
    return TRUE;
  else
    return FALSE;
}


BIT and_gate( BIT A, BIT B )
{
   /* TO DO: implement logical AND */
  if (A && B)
    return TRUE;
  else
    return FALSE;
}


BIT xor_gate( BIT A, BIT B )
{
   /* TO DO: implement logical XOR */
  if ((A && !B) || (!A && B))
    return TRUE;
  else
    return FALSE;
}


BIT multiplexer( BIT I0, BIT I1, BIT I2, BIT I3, BIT S0, BIT S1 )
{
   /* TO DO: implement a 4-input multiplexer */
  if ( (I0 && !S0 && !S1) || (I1 && S0 && !S1) || 
       (I2 && !S0 && S1) || (I3 && S0 && S1) )
    return TRUE;
  else
    return FALSE;
}


void decoder( BIT I0, BIT I1, BIT *O0, BIT *O1, BIT *O2, BIT *O3 )
{
   /* TO DO: implement a 2-input decoder */
  *O0 = FALSE;
  *O1 = FALSE;
  *O2 = FALSE;
  *O3 = FALSE;

  if (!I0 && !I1)
    *O0 = TRUE;
  else if (I0 && !I1)
    *O1 = TRUE;
  else if (!I0 && I1)
    *O2 = TRUE;
  else if (I0 && I1)
    *O3 = TRUE;
  
  return;
}


BIT alu_1bit( BIT OP0, BIT OP1, BIT CIN, BIT A, BIT B, BIT *COUT )
{
   /* TO DO: implement a 1-bit ALU */
   if ( OP0 && OP1 ) *COUT = or_gate( or_gate( and_gate( A, not_gate( B ) ), and_gate( A, CIN ) ), and_gate( not_gate( B ), CIN ) );
   else *COUT = or_gate( or_gate( and_gate( A, B ), and_gate( A, CIN ) ), and_gate( B, CIN ) );
   if ( !OP0 && !OP1 ) return and_gate( A, B );
   else if ( OP0 && !OP1 ) return or_gate( A, B );
   else if ( !OP0 && OP1 ) return or_gate( and_gate( xor_gate( A, B ), not_gate( CIN ) ),
                                           and_gate( not_gate( xor_gate( A, B ) ), CIN ) );
   else return or_gate( and_gate( xor_gate( A, not_gate ( B ) ), not_gate( CIN ) ),
                        and_gate( not_gate( xor_gate( A, not_gate ( B ) ) ), CIN ) );
}


void alu_4bit( BIT OP0, BIT OP1, BIT A0, BIT A1, BIT A2, BIT A3, 
              BIT B0, BIT B1, BIT B2, BIT B3,
              BIT *C0, BIT *C1, BIT *C2, BIT *C3 )
{
   /* TO DO: implement a 4-bit ALU */
   BIT CARRY;
   if ( OP0 && OP1 ) *C0 = alu_1bit(OP0, OP1, TRUE, A0, B0, &CARRY);
   else *C0 = alu_1bit(OP0, OP1, FALSE, A0, B0, &CARRY);
   *C1 = alu_1bit(OP0, OP1, CARRY, A1, B1, &CARRY);
   *C2 = alu_1bit(OP0, OP1, CARRY, A2, B2, &CARRY);
   *C3 = alu_1bit(OP0, OP1, CARRY, A3, B3, &CARRY);
   return;
}

void ieee754encode( float value, char * encoded )
{
     /* TO DO: implement a function to encode a floating-point value
      * in the IEEE 754-1985 form
      */
  printf("input: %g\n", value);

  encoded[32] = '\0';

  // Determine sign
  if (value < 0)
    encoded[0] = '1';
  else
    encoded[0] = '0';
  printf("sign: %c\n", encoded[0]);


  // Determine fraction/mantissa

  // Separate value into integer and fractional pieces
  int integer = (int)fabs(value);
  float fraction = fabs(value - (float)((int)value));
  int exponent = 0;

  // Get binary representation with 'divide by 2' algorithm
  int stack[32];
  int pos = 0;
  while (integer != 0) {
    if (integer % 2 == 0)
      stack[pos++] = 0;
    else
      stack[pos++] = 1;
    integer /= 2;
  }

  if (pos > 0)
    exponent = pos - 1;

  // write into fraction by popping stack -- ignore leading 1 (normalized form)
  pos -= 2;
  int index = 9; // start index in encoded for writing fraction/mantissa

  while (pos >= 0 && index < 32) {
    if (stack[pos--] == 0)
      encoded[index++] = '0';
    else
      encoded[index++] = '1';
  }

  // Get fractional representation with 'multiply by 2' algorithm
  pos = 0; // use this to track exponent again if necessary (-1 < value < 1)
  int normalized = 0;
  while (fraction != 0.0 && index < 32) {
    fraction *= 2.0;
    if (fraction >= 1.0) {
      encoded[index++] = '1';
      fraction -= 1.0;
    } else {
      encoded[index++] = '0';
    }
    // value is purely fractional, normalize
    if (index == 10 && !normalized) {
      --pos;
      if (encoded[index - 1] == '1') {
        index = 9;
        normalized = 1;
      }
      else {
        index = 9;
      }
    }
  }
  while (index < 32)
    encoded[index++] = '0';

  printf("fraction: %s\n", &encoded[9]);


  // Determine binary exponent again with divide by 2

  if (exponent == 0)  // if value is only fractional
    exponent = pos;

  exponent += 127;
  index = 8;
  while (exponent != 0 && index > 0) {
    if (exponent % 2 == 0)
      encoded[index--] = '0';
    else
      encoded[index--] = '1';
    exponent /= 2;
  }
  while (index > 0)
    encoded[index--] = '0';

  printf("exponent: ");
  for (int i = 1; i < 9; ++i)
    printf("%c", encoded[i]);
  printf("\n");

  printf("output: %s\n", encoded);

  return;
}
