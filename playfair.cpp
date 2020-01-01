/*
                Encryption
            
Encryption is the process of obfuscating a message using keys.

Symmetrical encryption is when only one key can be used to both encrypt and decrypt a message.



              Playfair Cipher

This code is about a symmetrical encryption method called the Playfair cipher. The encryption is done using a key and a 5x5 alphabet table.


                    Key

The playfair key is a combination of letters of the alphabet(with one letter missing: usually it is 'j')

The key can be a word, but repeated letters are removed. The useful part of the key only contains unique characters.

example:hello => helo


                   Table

Now that we have a valid key "helo", we will create a 5x5 table for the encryption. This table contains all 25 letters of the alphabet(j missing) only once. We fill the table with the key, then goes in all other letters in alphabetical order.

example: helo
___________
|h|e|l|o|a|
-----------
|b|c|d|f|g|
-----------
|i|k|m|n|p|
-----------
|q|r|s|t|u|
-----------
|v|w|x|y|z|
-----------


                  Message

If the message has consecutive identical letters, they must be separated by 'x' and must be read in groups of two. Also if the number of letters is odd, a 'z' is added at the end.The letter 'j' can be replaced by 'i'.

example: helloworld => he lx lo wo rl dz

Then each groups of two letters get replace by two other letters in the table.

If the two letters are in same column, each letter gets replace by next letter down.

if the two letters are in same row, each letter gets replace by the neighbouring right sided letter.

if not in same row or column, take opposite corners of the rectangle that the two letters form.

Space and non alpha characters can be skipped over when looking up pairs. 

example: ab23c def => ab,cd,ef

All non alpha characters can be reinserted at thei respective indices, after the encryption is completed.


                Encryption
              
key: helo
table:
___________
|h|e|l|o|a|
-----------
|b|c|d|f|g|
-----------
|i|k|m|n|p|
-----------
|q|r|s|t|u|
-----------
|v|w|x|y|z|
-----------
message: hello world => he lx lo wo rl dz


"he" same row => "el"
"lx" same column => "dl"
"lo" same row => "oa"
"wo" rectangle => "ey"
"rl" rectangle => "es"
"dz" rectangle => "gx"

*/



#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Choice{
    ENCRYPT=1,
    DECRYPT=4
};

string playfair(string message, string key, Choice choice=ENCRYPT){
    cout<<message<<endl<<endl;
    message=message+'z';
    string result{};
    char missing='j',
         letter='a',
         table[5][5];
    for(unsigned r=0,ks=key.size();r<5;r++){
        for(unsigned c=0;c<5;c++){
            if(r*5+c<ks) table[r][c]=key[r*5+c];
            else{
                while(
                    key.find(letter)!=
                    string::npos 
                    or letter==missing
                )   letter++;
                table[r][c]=letter++;
            }
        }
    }
    //table print
    for(unsigned r=0;r<5;r++){
        for(unsigned c=0;c<5;c++)
            cout<<table[r][c]<<" ";
        cout<<endl;
    }
    //replace all 'j' by 'i'
    //insert x and make doubles
    vector<string>digraphs{};
    string digraph{};
    int count=0;
    char first;
    for(auto c:message){
        c=tolower(c);
        if(c==missing) c='i';
        if(isalpha(c)){
            if(count){
                if(c!=first){
                    digraph += c;
                    digraphs.push_back(digraph);
                    digraph = "";
                    count = 0;
                }else{
                    digraph += 'x';
                    digraphs.push_back(digraph);
                    digraph = c;
                }
            }else{
                digraph += c;
                count=1;
                first=c;
            }
        }else{
            digraph += c;
        }
    }
    //print digraphs
    cout<<endl;
    for(auto & d:digraphs) cout<<d<<" ";
    cout<<endl;
    
    for(auto & d:digraphs){
        char first=0,
             second;
        for(auto c:d){
            if(isalpha(c)){
                if(first) second=c;
                else first=c;
            }
        }
        int r1,r2,c1,c2;
        for(int r=0;r<5;r++){
            for(int c=0;c<5;c++){
                if(table[r][c]==first){
                    r1=r;c1=c;
                }
                if(table[r][c]==second){
                    r2=r;c2=c;
                }
            }
        }
        int index1=d.find(first);
        int index2=d.find(second);
        if(r1==r2){
            d[index1]=table[r1][(c1+choice)%5];
            d[index2]=table[r2][(c2+choice)%5];
        }else if(c1==c2){
            d[index1]=table[(r1+choice)%5][c1];
            d[index2]=table[(r2+choice)%5][c2];
        }else{
            if(choice==ENCRYPT){
                if(r1<r2&&c1<c2){
                d[index1]=table[r1][c2];
                d[index2]=table[r2][c1];
                }
                if(r1<r2&&c1>c2){
                d[index1]=table[r2][c1];
                d[index2]=table[r1][c2];
                }
                if(r1>r2&&c1<c2){
                d[index1]=table[r2][c1];
                d[index2]=table[r1][c2];
                }
                if(r1>r2&&c1>c2){
                d[index1]=table[r1][c2];
                d[index2]=table[r2][c1];
                }
            }else{
                if(r1<r2&&c1<c2){
                d[index1]=table[r2][c1];
                d[index2]=table[r1][c2];
                }
                if(r1<r2&&c1>c2){
                d[index1]=table[r1][c2];
                d[index2]=table[r2][c1];
                }
                if(r1>r2&&c1<c2){
                d[index1]=table[r1][c2];
                d[index2]=table[r2][c1];
                }
                if(r1>r2&&c1>c2){
                d[index1]=table[r2][c1];
                d[index2]=table[r1][c2];
                }
            }
        }
        result+=d;
    }
    cout<<result<<endl;
    return result;
}

int main() {
    string msg="Hello World";
    string key="playground";
    
    try{
        if("bfyvoc vupohg"!=playfair(msg,key))
            throw "test 1 failed";
        cout<<endl<<"Test 1 passed ✅"<<endl;
    }catch(char const * err){
        cout<<err;
    }
    cout<<endl<<endl;
    
    try{
        if("helxlo worldz"!=playfair("bfyvoc vupohg",key,DECRYPT))
            throw "test 1 failed";
        cout<<endl<<"Test 2 passed ✅"<<endl;
    }catch(char const * err){
        cout<<err;
    }
    return 0;
} 
