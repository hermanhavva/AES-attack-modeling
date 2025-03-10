#pragma once

#include "aes.hpp"
#include <random>
#include <fstream>
#include <format>
#include <thread>
#include <chrono>
#include <deque>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::format;

const int kBytesInBlock = 16;

class PaddingOracleAttack
{
public:
	static void tryAttackCBC(
        vector<unsigned char>       cipherText, 
        AES&                        aes, 
        const vector<unsigned char> keyVec, 
        const vector<unsigned char> iVec)  // the KEY and iVec only needed to call DecryptCBC() method (API)
    {
        if (cipherText.size() < 2 * kBytesInBlock)
        {
            cout << "Cipher text too small\n";
            return;
        }

        int curBytePos = cipherText.size() - 1 - kBytesInBlock;
        int blockGuessedCounter = 0;
        std::deque<unsigned char> guessedMsg;


        while (cipherText.size() - kBytesInBlock * blockGuessedCounter > kBytesInBlock)
        {
            vector<unsigned char> cipherTextCopyTruncated(cipherText.begin(), cipherText.begin() + cipherText.size() - kBytesInBlock * blockGuessedCounter);

            unsigned char guessedCounter = 0x00;
            bool ifGuessed = false;


            for (; kBytesInBlock && guessedCounter < kBytesInBlock; curBytePos--)  // for all bytes in pre last block
            {
                unsigned char curCh = 0;

                while (!ifGuessed && curCh < 256)
                {

                    cipherTextCopyTruncated[curBytePos] = curCh;
                    try
                    {
                        aes.DecryptCBC(cipherTextCopyTruncated, keyVec, iVec);  // only know if padding is okay or not 
                        cout << format("Guesses valid padding for position: {} in pre-last block, the value of char {}, counter {}\n", curBytePos, static_cast<int>(curCh), guessedCounter);
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        guessedCounter++;
                        ifGuessed = true;

                        guessedMsg.push_front(curCh ^ guessedCounter ^ cipherText[curBytePos]);  // trying to recover plaintext 

                        for (int index = curBytePos; index <= cipherTextCopyTruncated.size() - 1 - kBytesInBlock; index++)
                        {
                            cipherTextCopyTruncated[index] = cipherTextCopyTruncated[index] ^ guessedCounter ^ (guessedCounter + 1);
                        }
                    }
                    catch (const std::invalid_argument& e)
                    {
                        cout << format("Invalid padding for position {}, char value {}, counter {}\n", curBytePos, static_cast<int>(curCh), guessedCounter);
                    }

                    curCh++;

                }
                ifGuessed = false;

            }

            blockGuessedCounter++;
        }

        cout << "Plain text excluding first block:\n";
        for (auto& ch : guessedMsg)
        {
            cout << ch;
        }
    }	

};
