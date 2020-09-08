/* 
 * CS:APP Data Lab 
 * 
 * <Yu-Wei Vincent Yeh 005123289>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x)
{
  //put each bytes into separate variables
  int x1 = x & 0xff;
  int x2 = (x >> 8) & 0xff;
  int x3 = (x >> 16) & 0xff;
  int x4 = (x >> 24) & 0xff;
  // get rid of pairs of one's that matched bit positions in each first 8 bits.
  int xorAll = x1 ^ x2 ^ x3 ^ x4;
  //get rid of the remaining pairs of ones until there's one bit unchecked
  xorAll = xorAll ^ (xorAll >> 4);
  xorAll = xorAll ^ (xorAll >> 2);
  xorAll = xorAll ^ (xorAll >> 1);
  //since the rest of the bits have been "cleared" of paired one's, we only need the first bit
  return xorAll & 0x01;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n)
{
  //shift right by n
  int righlessN = x >> n;
  //get number of remianing bits
  int remaining = 32 + (~n + 1);
  //get the first n bits of interest
  int leftshift = x << remaining;
  //clear out the possibility that the first n bits in righlessN are ones
  int rightFirstNOnes = righlessN >> remaining << remaining;
  return righlessN ^ (rightFirstNOnes ^ leftshift);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m)
{
  //each byte is 8 bits
  int nsh = n << 3;
  int msh = m << 3;
  //shift and & 0xff to get the two bytes
  int firstnum = (x >> nsh) & 0xff;
  int secondnum = (x >> msh) & 0xff;
  //xor the original order of bytes of interest with shifted version (other bits are padded with 0)
  //in order to see which elements in shifted version are different than original
  //xor x with the previous statement
  return x ^ (((firstnum << msh) + (secondnum << nsh)) ^ ((firstnum << nsh) + (secondnum << msh)));
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x)
{
  //see if k fits in 16 bits
  int k = (x << 16) >> 16;
  return !(k ^ x);
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)
{
  //de morgan's laws, making this equal to x and y
  return ~((~x) | (~y));
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y)
{
  //this can overflow only when x y have opposite sign
  int result = x + (~y + 1);
  //xs ys would be 1 if negative 0 if positive
  int xs = (x >> 31) & 0x01;
  int ys = (y >> 31) & 0x01;
  //get the sign of result
  int results = (result >> 31) & 0x01;
  //make sure signs are different
  int xorXSYS = xs ^ ys;
  //compare y sign with result's sign
  int yres = !(ys ^ results);
  //has to be different sign
  return !(xorXSYS & yres);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y)
{
  //get x and y's sign then check if the signs are the same
  int xs = (x >> 31) & 0x01;
  int ys = (y >> 31) & 0x01;
  int sameS = !(xs ^ ys);
  //check if they're equal to avoid an error
  int equal = !(x ^ y);
  //get the sign of x minus y
  int xminyS = ((x + (~y + 1)) >> 31) & 0x01;
  //x is greater than y when they have same sign and x minus y is positive or x is positive and y is negative
  //they also can't be equal
  return ((sameS & ~xminyS) | (~xs & ys)) & (!equal);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
{
  //shift left and right again to get the first n bits
  int shifted = 32 + (~n + 1);
  int k = (x << shifted) >> shifted;
  //only if we obtain same pattern again does it fit
  return !(k ^ x);
}
/*
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return ~x + 1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  //suppose x is t max m should become tmin, which is 100...
  int m = x + 1;
  //x plus m should be all ones thus k is 0
  int k = ~(x + m);
  //m can't be 0
  //also k + !m should be 0 and thus return 1
  return !(k + (!m));
}
