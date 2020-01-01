 /*
             Reciprocal encoding
Reciprocal encoding means same algorithm is used to encode and decode a message.

rot13 is a reciprocal algorithm. It is a ceasar cipher where you advance each letter by 13 in the alphabet. Because there is 26 letters in the alphabet, advancing each letter of the encoded message by 13 will also return the encoded message to the original message.
*/

#include <iostream>
using namespace std;

string rot13(const string & s){
    string rotated{};
    for(const char & c:s){
        if(isalpha(c))
            if(isupper(c))
                rotated+=char((c-'A'+13)%26+'A');
            else
                rotated+=char((c-'a'+13)%26+'a');
        else rotated += c;
    }
    return rotated;
}

int main() {
    const string msg{"Hello World 2020"};
    const string rotated{rot13(msg)};
    cout<<"original:    "<<msg<<endl;
    cout<<"encrypted:   "<<rotated<<endl;
    cout<<"decrypted:   "<<rot13(rotated);
    return 0;
}
