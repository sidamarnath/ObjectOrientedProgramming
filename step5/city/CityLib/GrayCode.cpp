/**
 * @file GrayCode.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "GrayCode.h"

/**
 * Increment a gray code value.
 * @param code Code to increment
 * @return Next gray code value
 */
unsigned int GrayCode::Increment(unsigned int code)
{
    // Determine the parity of the code by counting
    // the number of set bits
    int sets = 0;
    for(int i=0; i<32; i++)
    {
        if(code & (1 << i))
        {
            sets++;
        }
    }

    if(sets & 1)
    {
        // Parity is odd
        // Determine the right-most set bit
        unsigned int rightMostOne;
        for(rightMostOne=0; rightMostOne<32; rightMostOne++)
        {
            if(code & (1 << rightMostOne))
            {
                break;
            }
        }

        code ^= (1 << (rightMostOne + 1));
    }
    else
    {
        // Parity if even
        code ^= 1;
    }

    return code;
}
