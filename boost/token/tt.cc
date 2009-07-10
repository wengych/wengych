#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   string s = "This is,  a test\na:b:c\n\nkkk";
   tokenizer<> tok(s);
   for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
       cout << *beg << "\n";
   }
}

