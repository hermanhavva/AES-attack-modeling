#pragma once

#include <vector>

using std::vector;

void bit_flipping(std::vector<unsigned char>& ciphertext, int position, int xor_value)
{
    ciphertext[position] ^= xor_value;
}