/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) 
{
    //x ^ y == (x | y) & (~x | ~y)
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) 
{
    //zero with a non-zero returns '0'
    if (!x && y)
        return 0;
    if (x && !y)
        return 0;
    //get sign_bit of each number
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    return !(sign_x ^ sign_y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) 
{
    int e = 0;  // store the position of the '1'
    // if v>2^16-1, e += 16
    e = (v > 65535) << 4;
    // cut off the back half if v>2^16-1
    v >>= (v > 65535) << 4;

    //'|' can be used as '+' here
    e |= (v > 255) << 3;
    v >>= (v > 255) << 3;

    e |= (v > 15) << 2;
    v >>= (v > 15) << 2;

    e |= (v > 3) << 1;
    v >>= (v > 3) << 1;

    e |= (v >> 1);

    return e;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) 
{
    // n and m*8 to get the index of the need-changed numbers
    int n_pos = n << 3;
    int m_pos = m << 3;
    // extract the numbers to be changed 
    int n_num = (x >> n_pos) & 0xFF;
    int m_num = (x >> m_pos) & 0xFF;
    // make n_pos and m_pos of x to be 0
    x &= ~((0xFF << n_pos) | (0xFF << m_pos));
    // get the result
    x |= (n_num << m_pos) | (m_num << n_pos);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) 
{
    // store the reversed number
    unsigned rev_num = 0;

    int i = 0;
    while (!(i & 0b100000)) {
        // add the lowest number of v to the highest position of rev_num
        rev_num <<= 1;
        rev_num |= 1 & v;
        v >>= 1;
        i += 1;
    }
    return rev_num;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) 
{
    // do arithmathic shift first
    int arith = x >> n;
    // make the head n bits to be '0'
    int mask = ~(((1 << 31) >> n) << 1);
    return arith & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) 
{
    int f = ~x;
    int cnt = (!!(f & 0xffff0000)) << 4;
    f >>= cnt;
    int temp = (!!(f & 0xff00)) << 3;
    f >>= temp;
    cnt |= temp;
    temp = (!!(f & 0xf0)) << 2;
    f >>= temp;
    cnt |= temp;
    temp = (!!(f & 0xc)) << 1;
    f >>= temp;
    cnt |= temp;
    temp = (!!(f & 2));
    cnt |= temp;
    return 33 + (~(cnt + (!!(x ^ 0xffffffff))));
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) 
{
    int s = x & 0x80000000;
    int exp = 30;
    // x = 0
    if (!x)
        return 0;
    // inf
    if (x == 0x80000000)
        return 0xcf000000;
    if (s)
        x = ~x + 1;
    while (!(x & (1 << exp)))
        exp--;
    if (exp <= 23)
        x <<= (23 - exp);
    // round
    else
    {
        x += (1 << (exp - 24));
        if (x << (55 - exp))
            ;
        else
            x &= (0xffffffff << (exp - 22));
        if (x & (1 << exp))
            ;
        else
            exp++;
        x >>= (exp - 23);
    }
    x = x & 0x007fffff;
    exp = (exp + 127) << 23;
    return s | exp | x;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) 
{
    unsigned s = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    // NaN or inf
    if (exp == 0xFF)
        return uf;
    //unnormalised
    if (exp == 0)
    {
        if (frac == 0)
            return uf;
        else
        {
            //*2
            frac <<= 1;
            //if overflow
            if (frac & 0x800000)
            {
                exp = 1;
                frac &= 0x7FFFFF;
            }
        }
    }
    //normalised
    else
    {
        exp += 1;
        //if inf by +1
        if (exp == 0xFF)
            frac = 0;
    }
    return s | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) 
{
    unsigned int s = uf2 >> 31;
    unsigned int exp = (uf2 >> 20) & 0x7FF;
    int E = exp - 1023;
    int farc_high = (uf2 << 12);
    int frac_low = uf1;
    int result = 0;
    if (E >= 32)
        return 0x80000000;
    if (E < 0)
        return 0;
    if (E <= 20) 
    {
        result = (1 << E) | (farc_high >> (20 - E));
    } 
    else 
    {
        result = (1 << E) | (farc_high << (E - 20)) | (frac_low >> (52 - E));
    }
    if (s) 
    {
        result = -result;
    }
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) 
{
    int exp = x + 127;
    //frac = 0
    if (x > 127)
    {
        return 0x7F800000;
    }
    else if (x < -149)
    {
        return 0;
    } 
    if (x >= -126)
    {
        return exp << 23;
    }
    return (0 << 31) | (exp << 23);
}
