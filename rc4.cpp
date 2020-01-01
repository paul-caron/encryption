/*
               Encryption
               
                  RC4

Rivest Cipher 4, is a symmetrical encryption technique. This encryption method is no longer considered secure for TLS(https) but is still a beautiful algorithm to study and maybe even still use in some situations.

It uses a key that can have various length of up to 256 bytes. The key is then used to shape the T temporary box and indirectly also shaping the S box via the T box. 

The S box contains all numbers from 0 to 255, thus is an array of 256 in length. The S box will have multiple permutations based on how th T box was filled (which in turn depends on the key). Once the S box is setup, we can use it to drive a byte stream generator.

The generator uses a pseudo random generator algorithm to stream a byte value on command, a byte that will be used to cipher each byte coming from the message stream.

This was a very fun algorithm to implement. Very simple and I just love when I can plug in a generator somewhere in a code.
*/




#include <iostream>
#include <vector>
#include <ctime>
#include <functional>
using uc = unsigned char;
using namespace std;


vector<uc>get_S(vector<uc>key){
    vector<uc>S(256);
    vector<uc>T(256);
    for(unsigned i=0,ks=key.size();i<=255;i++){
        S[i]=i;
        T[i]=key[i%ks];
    }
    for(int i=0,j=0;i<=255;i++){
        j=(j+S[i]+T[i])%256;
        swap(S[i],S[j]);
    }
    return S;
}


vector<uc>get_key(){
    srand(time(0));
    size_t length=rand()%256+1;
    vector<uc>key(length);
    for(auto & b:key){
        b=(rand()%256);
    }
    return key;
}


function<uc()>PRG(vector<uc>S){
    int i=0, j=0;
    return [=]() mutable{
        while(1){
            i = (i+1)%256;
            j = (j+S[i]) %256;
            swap(S[i], S[j]);
            int t = (S[i]+S[j])% 256;
            return S[t];
        }
    };
}


vector<uc>rc4(vector<uc>msg,vector<uc>key){
    vector<uc>result{};
    auto S=get_S(key);
    auto generator=PRG(S);
    for(auto b:msg)
        result.push_back(generator()^b);
    return result;
}


int main() {
    string m="hello world";
    vector<uc>msg{};
    for(auto c:m) msg.push_back((uc)c);

    vector<uc>key{get_key()};
    vector<uc>encrypted{rc4(msg,key)};
    vector<uc>decrypted{rc4(encrypted,key)};
    
    
    cout<<"original: "<<m;
    cout<<"\n\nkey: ";
    for(auto b:key) cout<<hex<<int(b)<<" ";
    cout<<"\n\nencrypted: ";
    for(auto b:encrypted) cout<<int(b)<<" ";
    cout<<"\n\ndecrypted: ";
    for(auto b:decrypted) cout<<char(b);
    cout<<string(10,'\n');
    return 0;
}


 
