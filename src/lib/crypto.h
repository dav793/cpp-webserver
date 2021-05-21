#ifndef _Crypto_H
#define _Crypto_H
#include <string>
using namespace std;

string encrypt(string plain_data, string key);

string decrypt(string encrypted_data, string key);

#endif // Crypto_H