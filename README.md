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
### Проведені атаки
#### Padding oracle attack (Serge Vaudenay's attack)
Ця атака на AES CBC полягає в тому, що ми послідовно змінюємо
байт передостанього блоку шифротексту, тим самим ми намагаємось 
імітувати валідний padding у відкритому тексті. Коли оракул каже нам, що padding валідний, 
то ми можемо почати підбирати padding на ще один байт.  
- Ми можемо відновити `DecK(cyphertext)` за властивістю операції `xor`: 
```
    known_value1 xor unknown_value = known_value2 ==> 
==> unknown_value = known_value2 xor known_value1
```
Потім для кожного байта виконуємо xor з байтом початкового plaintext'у. В нашому коді це виглядає так: 
```
guessedMsg.push_front(curCh ^ guessedCounter ^ cipherText[curBytePos]);  // trying to recover plaintext 
```

