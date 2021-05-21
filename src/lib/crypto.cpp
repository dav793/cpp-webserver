#include <iostream>
#include <string>
using namespace std;

#include "lib/crypto.h"

// Primera solucion: binary XOR encription (no apropiado para cookie header)
//
string encrypt(string plain_data, string key) {
    string temp(key);
    while (key.size() < plain_data.size()) {
        key += temp;
    }
    
    for (int i = 0; i < plain_data.size(); ++i) {
        plain_data[i] ^= key[i];
    }
    return plain_data;
}

string decrypt(string encrypted_data, string key) {
    return encrypt(encrypted_data, key);
}
