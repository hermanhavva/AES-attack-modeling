#include "aes.hpp"
#include <random>
#include <fstream>
#include <format>
#include <thread>
#include <chrono>
#include <deque>
#include "utilities.hpp"
#include "padding_oracle_attack.hpp"

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
    
    AES aes(AESKeyLength::AES_128);

    
    vector<unsigned char> cipherText = aes.EncryptCBC(plainTextVec, keyVec, iVec); 


    PaddingOracleAttack::tryAttackCBC(cipherText, aes, keyVec, iVec);
    
    return 0;
}