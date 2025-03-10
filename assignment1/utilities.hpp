#pragma once

#include <random>
#include <vector>

using std::vector;


unsigned char genRandomChar()
{
    std::random_device rdSeed;
    std::uniform_int_distribution<int> dist(0, 255);
    dist.reset();  // for resetting cache

    return static_cast<unsigned char>(dist(rdSeed));
}

vector<unsigned char> generateKey(const int len)
{
    vector<unsigned char> result(len);

    for (int i = 0; i < len; i++)
    {
        result[i] = genRandomChar();
    }
    return result;
}

void printVectorAsString(const std::vector<unsigned char>& data) {
    for (unsigned char c : data) {
        std::cout << c;
    }
    std::cout << std::endl;
}

