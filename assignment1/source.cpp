#include "aes.hpp"
#include <random>


using std::cout; 
using std::endl;
using std::string;
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

void printMsg(vector<unsigned char> vecIn)
{
    for (auto& element : vecIn)
    {
        cout << element;
    }
    cout << endl;
}





int main() 
{
    string plainTextStr = "King Abacaba of Palindrome Land ruled wisely, his name mirroring the lands symmetry. One day, a riddle appeared: \"What begins and ends the same? \" Smiling, he answered, \"Everything here!\" The kingdom cheered, for their harmony was balanced.";
    cout << "The string size of plainText: " << plainTextStr.size() << endl;

    vector<unsigned char> plainTextVec(plainTextStr.begin(), plainTextStr.end());
    cout << "The vector size of plain text: " << plainTextVec.size() << endl;  

    //vector<unsigned char> keyVec = generateKey(128);
    //cout << "The size of key: " << keyVec.size() << endl;


    // std::vector<unsigned char> iVector = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    AES aes(AESKeyLength::AES_128);

    makePadding(plainTextVec); 
    printMsg(plainTextVec);


    //std::vector<unsigned char> cyphertext = aes.EncryptECB(plaintext, key);
    //std::vector<unsigned char> cyphertext = aes.EncryptCBC(plaintext, key, ivector);
    //std::vector<unsigned char> cyphertext = aes.EncryptCFB(plainTextVec, keyVec, iVector);
    //std::vector<unsigned char> decrypted = aes.DecryptCFB(cyphertext, keyVec, iVector);

    stripPadding(plainTextVec);
    printMsg(plainTextVec);
    return 0;
}