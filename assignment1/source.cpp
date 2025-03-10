#include "aes.hpp"
#include <random>
#include <fstream>
#include <format>
#include <thread>
#include <chrono>
#include <deque>
#include "utilities.hpp"
#include "padding_oracle_attack.hpp"
#include "bit_flip_attack.hpp"

using std::cout; 
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::format;


vector<unsigned char> keyVec = {
    189, 146, 221, 105,  91,  143, 152, 193, 217, 150, 112, 174, 57,  106, 110, 110 };  // generated with utilities.hpp



vector<unsigned char> iVec = {
    16, 136, 138, 19, 169, 162, 228, 121, 185, 115, 169, 149, 7, 245, 114, 236 };  // generated with utilities.hpp



string plainTextStr = "King Abacaba of Palindrome Land ruled wisely, his name mirroring the lands symmetry. One day, a riddle appeared: \"What begins and ends the same? \" Smiling, he answered, \"Everything here!\" The kingdom cheered, for their harmony was balanced.";
// string plainTextStr = "abacabaabacabaabacabaabacabaaabacabaabacabaabacabaabacabaa";
vector<unsigned char> plainTextVec(plainTextStr.begin(), plainTextStr.end());




int main() 
{   

    /*  Padding Oracle Attack

    AES aes(AESKeyLength::AES_128);
    
    vector<unsigned char> cipherText = aes.EncryptCBC(plainTextVec, keyVec, iVec); 

    PaddingOracleAttack::tryAttackCBC(cipherText, aes, keyVec, iVec);
    
    */ 


    /*  BitFlip Attack

    std::string plaintextStr = "Bob given 10 dollars to Alice";

    std::vector<unsigned char> plaintext(plaintextStr.begin(), plaintextStr.end());

    std::vector<unsigned char> key = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    std::vector<unsigned char> ivector = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    AES aes(AESKeyLength::AES_128);

    std::cout << "Plaintext: ";

    printVectorAsString(plaintext);
    
    makePadding(plaintext);

    std::vector<unsigned char> ciphertext = aes.EncryptCBC(plaintext, key, ivector);

    std::cout << "Original Ciphertext: ";
    printVectorAsString(ciphertext);

    bit_flipping(ivector, 10, 7);

    std::cout << "Modified Ciphertext: ";
    printVectorAsString(ciphertext);

    std::vector<unsigned char> modifiedPlaintext = aes.DecryptCBC(ciphertext, key, ivector);
    stripPadding(modifiedPlaintext);

    std::cout << "Modified Plaintext: ";
    printVectorAsString(modifiedPlaintext);

    */

    return 0;
}