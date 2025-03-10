#include "aes.hpp"
#include <random>
#include <fstream>
#include <format>
#include <thread>
#include <chrono>
#include <unordered_set>

using std::cout; 
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::format;



vector<unsigned char> keyVec = {
    189, 146, 221, 105,  91,  143, 152, 193, 217, 150, 112, 174, 57,  106, 110, 110 };
    /* 224, 126, 17, 39, 27, 3, 242, 115, 58, 34, 209, 19, 55, 170, 52, 104,
       250, 46,  122, 133, 88,  172, 3,   209, 77,  200, 173, 150, 2,   247, 139, 9,
       22,  125, 151, 15,  99,  205, 240, 24,  60,  175, 230, 34,  103, 216, 6,   166,
       112, 67,  215, 205, 205, 42,  133, 22,  25,  175, 121, 121, 57,  194, 167, 152,
       121, 61,  127, 255, 179, 249, 34,  17,  254, 35,  134, 188, 237, 70,  219, 171,
       70,  11,  194, 34,  11,  48,  221, 252, 151, 39,  12,  55,  155, 254, 98,  169,
       229, 85,  84,  42,  89,  213, 195, 23,  157, 109, 99,  11,  79,  42,  187, 30*/


    vector<unsigned char> iVec = {
        16, 136, 138, 19, 169, 162, 228, 121, 185, 115, 169, 149, 7, 245, 114, 236 };
  /*250, 3, 25, 45, 157, 208, 217, 171, 60, 241, 94, 198, 172, 204, 229, 45,
    110, 101, 24, 5, 180, 8, 92, 183, 154, 208, 131, 154, 200, 90, 166, 218,
    16, 220, 251, 63, 206, 190, 147, 247, 195, 249, 11, 243, 216, 229, 119, 110,
    103, 35, 34, 20, 54, 18, 213, 108, 32, 77, 182, 11, 59, 205, 14, 65,
    207, 104, 171, 94, 57, 35, 221, 56, 112, 54, 195, 77, 172, 79, 91, 158,
    253, 51, 66, 138, 222, 157, 179, 137, 19, 89, 124, 147, 77, 95, 169, 235,
    65, 204, 45, 192, 166, 139, 179, 164, 0, 26, 171, 174, 66, 44, 0, 255 */



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

void printMsg(vector<unsigned char> vecIn)
{
    for (auto& element : vecIn)
    {
        cout << element;
    }
    cout << endl;
}

const int kBytesInBlock = 16;

string plainTextStr = "King Abacaba of Palindrome Land ruled wisely, his name mirroring the lands symmetry. One day, a riddle appeared: \"What begins and ends the same? \" Smiling, he answered, \"Everything here!\" The kingdom cheered, for their harmony was balanced.";
vector<unsigned char> plainTextVec(plainTextStr.begin(), plainTextStr.end());


void tryAttackCBC(vector<unsigned char> cipherText, AES& aes)
{
    if (cipherText.size() < 2 * kBytesInBlock)
    {
        cout << "Cipher text too small\n";
        return;
    }
    int curBytePos = cipherText.size() - 1 - kBytesInBlock, counter = 0;
    bool ifGuessed = false;
    //unsigned char curCh = 0;
    for (; curBytePos > kBytesInBlock; curBytePos--)  // for all bytes in pre last block
    {
        unsigned char curCh = 0;
        


        while (!ifGuessed && curCh < 256)
        {
            
            cipherText[curBytePos] = curCh;
            try
            {
                aes.DecryptCBC(cipherText, keyVec, iVec);  // only know if padding is okay or not 
                cout << format("Guesses valid padding for position: {} in pre-last block, the value of char {}, counter {}\n", curBytePos, static_cast<int>(curCh), counter);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                counter++;
                ifGuessed = true;
                for (int index = curBytePos; index <= cipherText.size() - 1 - kBytesInBlock; index++)
                {
                    cipherText[index] = cipherText[index] ^ counter ^ (counter + 1);
                }
                
            }
            catch (const std::invalid_argument& e)
            {
                cout << format("Invalid padding for position {}, char value {}, counter {}\n", curBytePos, static_cast<int>(curCh), counter);
            }
            // counter++;
            curCh++;
   
        }
        ifGuessed = false;

    }
        
 
}



int main() 
{

    

    AES aes(AESKeyLength::AES_128);
    
    //makePadding(plainTextVec);
    vector<unsigned char> cipherText = aes.EncryptCBC(plainTextVec, keyVec, iVec); 

    tryAttackCBC(cipherText, aes);


    printMsg(cipherText);

    vector<unsigned char> decryptText = aes.DecryptCBC(cipherText, keyVec, iVec);

    //stripPadding(decryptText);

    printMsg(decryptText);

    return 0;


    //cout << "The size of key: " << keyVec.size() << endl;



    makePadding(plainTextVec); 
    printMsg(plainTextVec);


    //std::vector<unsigned char> cyphertext = aes.EncryptECB(plaintext, key);
        //std::vector<unsigned char> cyphertext = aes.EncryptCFB(plainTextVec, keyVec, iVector);
    //std::vector<unsigned char> decrypted = aes.DecryptCFB(cyphertext, keyVec, iVector);

    stripPadding(plainTextVec);
    printMsg(plainTextVec);
    return 0;
}