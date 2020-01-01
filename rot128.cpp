 /*
             Reciprocal encoding
Reciprocal encoding means same algorithm is used to encode and decode a message.

rot128(many call it that way but may not be an official term) is a reciprocal algorithm. Each byte has a range of 0-255. Adding 128 to each byte will obfuscated the byte and adding another 128 again returns it to its original value. Byte overflow is not a problem and will happen naturally and is the reason this algorithm works.
*/

#include <iostream>
using namespace std;

string rot128(const string & s){
    string rotated{};
    for(const char & c:s){
        rotated += char(c + 128);
    }
    return rotated;
}

int main() {
    const string msg{"Hello World 2020"};
    const string rotated{rot128(msg)};
    cout<<"original:    "<<msg<<endl;
    cout<<"encrypted:   "<<rotated<<endl;
    cout<<"decrypted:   "<<rot128(rotated);
    return 0;
}
