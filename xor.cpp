/*
             Reciprocal encoding
Reciprocal encoding means same algorithm is used to encode and decode a message.

Xor is a reciprocal algorithm. Each byte is transformed using xor to obfuscate. Then transformed again using same xor algorithm to reveal original value.

Is not really a rotation algorithm but i call rotXor to keep in the naming tradition of the famous rot13 algorithm.
*/

#include <iostream>
using namespace std;

string rotXor(const string & s){
    string rotated{};
    for(const char & c:s){
        rotated += 255^c;
    }
    return rotated;
}

int main() {
    const string msg{"Hello World 2020"};
    const string rotated{rotXor(msg)};
    cout<<"original:    "<<msg<<endl;
    cout<<"encrypted:   "<<rotated<<endl;
    cout<<"decrypted:   "<<rotXor(rotated);
    return 0;
} 
