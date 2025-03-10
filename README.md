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
**Передмова:** із допомогою першої атаки, маючи ciphertext, ми можемо відновити plaintext усіх блоків, окрім першого. 
А із допомогою другої атаки ми можемо змінити вміст 1 блоку.

#### Padding oracle attack (Serge Vaudenay's attack)
Ця атака на AES CBC полягає в тому, що ми послідовно змінюємо
байт передостанього блоку шифротексту, тим самим ми намагаємось 
імітувати валідний padding у відкритому тексті. Коли оракул каже нам, що padding валідний, 
то ми можемо почати підбирати наступний байт передостанього блоку шифротексту, щоб отримати ще один, але більший padding.  
- Ми можемо відновити `DecK(cyphertext)` за властивістю операції `xor`: 
```
    known_value1 xor unknown_value = known_value2 ==> 
==> unknown_value = known_value2 xor known_value1
```
Потім для кожного байта виконуємо xor з байтом початкового plaintext'у. В нашому коді це виглядає так: 
```
guessedMsg.push_front(curCh ^ guessedCounter ^ cipherText[curBytePos]);  // trying to recover plaintext 
```
#### CBC Bit-Flipping Attack
Для СВС режиму вектор ініціалізації напряму впливає на перший блок при 
дешифруванні. Вважаючи вектор ініціалізації публічним, зловмисник може змінити
певні біти вектору, напряму впливаючи на вихідний текст при дешифруванні.
В прикладі корисне навантаження повідомлення обмежене одним блоком, 
зловмисник підроблює 10 байт повідомлення операцією XOR. 
Це перетворює повідомлення з "Bob given 10 dollars to Alice" на "Bob given 
60 dollars to Alice", не втрачаючи цілісності інших байтів.

### Структура репозиторія 
- Файли з логікою імлементації: 
1. `bit_flip_attack.hpp`
2. `padding_oracle_attack.hpp`
3. `aes.hpp`
4. `utilities.hpp` - допоміжний функціонал
- Файл з точкою входу у програму: 
1. `source.cpp`