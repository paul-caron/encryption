 /*
                  Encryption
           
                      OTP
              
OTP stands for one time pad. It is an encryption method that uses a key that is meant to be destroyed after a single decryption usage. It is said to be a very solid encryption method. However, it is unsuitable for many pratical use mainly due to the fact it needs a key that is as long as the message. A 100 characters message needs a 100 characters key or more.

                      Key
The key is composed of randomly generated characters, typically alphabetical +/- digits characters, but we could use the full char/byte range of values instead and make a full range 256x256 table also for full char/byte encryption.

                    Table
In this example, we need a table that links an encrypted message character to a key character and finally to a decrypted character.



*/


#include <iostream>
#include <map>
#include <array>
#include <ctime>

using namespace std;

array <char,36> char_set;
map<char,map<char,char>>table;
map<char,map<char,char>>table2;

void init_char_set(){
    int cs_index=0;
    for(char c='a';c<='z';c++,cs_index++)
        char_set[cs_index]=c;
    for(char c='0';c<='9';c++,cs_index++)
        char_set[cs_index]=c;
    for(auto c:char_set) cout<<c;
    cout<<endl<<endl;
}

void init_table(){
    cout<<endl<<string(36,'-')<<endl;
    for(int row=0;row<36;row++){
        map<char,char>r_map{};
        map<char,char>r2_map{};
        for(int col=0;col<36;col++){
            r_map[char_set[(36+col-row)%36]]=char_set[col];
            r2_map[char_set[col]]=char_set[(36+col-row)%36];
        }
        table[char_set[row]]=r_map;
        table2[char_set[row]]=r2_map;
        for(auto c:char_set)
            cout<<r_map[c];
        cout<<endl;
        for(auto c:char_set)
            cout<<r2_map[c];
        cout<<endl<<string(36,'-');
        cout<<endl;
    }
    cout<<endl;
}

string get_key(int length){
    string key{};
    srand(time(0));
    for(int i=0;i<length;i++)
        key+=char_set[rand()%36];
    cout<<key;
    return key;
}

string get_OTP(string msg,string key,bool encrypt=1){
    string result{};
    for(size_t i=0;i<msg.size();i++){
        if(isalpha(msg[i])||isdigit(msg[i])){
        if(encrypt)
        result += table[msg[i]][key[i]];
        else
        result += table2[key[i]][msg[i]];
        }
        else result += msg[i];
    }
    return result;
}



int main() {


    cout<<"init char_set:\n";
    init_char_set();
    cout<<"init table:\n";
    init_table();
    cout<<"\ngenerated key:\n";
    string key=get_key(300);
    
    
    
    string msg{"pump up the jam, pump it up,\n"
    "while you feet are stompin`\n"
    "and the jam is pumpin'\n"
    "look at here the crowd is jumpin'\n"
    "pump it up a little more\n"
    "get the party going on the dance floor\n"
    "seek us that's where the party's at\n"
    "and you'll find out if you're too bad"};
    string encoded=get_OTP(msg,key);
    string decoded=get_OTP(encoded,key,0);
    
    
    
    cout<<"\n\n\n\noriginal:\n"<<msg;
        
    cout<<"\n\nencrypted:\n"<<encoded;
        
    cout<<"\n\ndecrypted:\n"<<decoded;
        
    cout<<string(10,'\n');
    
    
    return 0;
}



