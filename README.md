## AES-attack-modeling
Modelling two attacks on AES cipher with ECB, CBC, CFB modes


### Генерація рандомних значень
- Для генерації ключа і вектора ініціалізації використана бібліотека 
`<random>`, а саме `random_device` з надбудовою у вигляді `std::uniform_int_distribution<int> dist(0, 255);`  
- Для нас важливі саме значення від `0` до `255` тому що ці значення покривають
усі можливі значення одного байту інформації. 
#### Чи є даний спосіб генерації криптографічно стійким 
Згідно
[офіційній документації Visual Studio](https://learn.microsoft.com/en-us/cpp/standard-library/random?view=msvc-170#comments)
`random_device` є криптографічно стійким генератором. 
``` C++
unsigned char genRandomChar() 
{
    std::random_device rdSeed;  
    std::uniform_int_distribution<int> dist(0, 255); 
    dist.reset();  // for resetting cache

    return static_cast<unsigned char>(dist(rdSeed));
}
```
