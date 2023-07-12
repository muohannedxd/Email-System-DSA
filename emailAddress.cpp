#include <iostream>
#include <fstream>
#include "emailAddress.h"

using std::cout;
using std::endl;
using std::cin;
using std::fstream;
using std::ios;

void emailAddress::enterEmailAdress(){
    cout<<"email name: "; cin>>this->name;
    while(!correctName(this->name)){
        cout<<"please enter a correct name: "; cin>>this->name;
    }

    cout<<"email domain name: "; cin>>this->domainName;
    while(!correctDomainName(this->domainName)){
        cout<<"please enter a correct domain name: "; cin>>this->domainName;
    }
}

bool emailAddress::correctEmailAdress(const string& str)const{
    return correctName(str.substr(0, str.find('@'))) && correctDomainName(str.substr(str.find('@') + 1, str.length() - 1));
}

bool emailAddress::correctDomainName(const string& str)const{
    fstream validDomainNamesFile; validDomainNamesFile.open("validDomainNames.txt", ios::in);
    string line;
    while(validDomainNamesFile>>line){
        if(line == str){
            return true;
        }
    }
    return false;
}

bool emailAddress::correctName(const string& str)const{
    if(str.length() > 20){
        return false;
    }
    string notAllowedLetters = "@^\\][)(}{\"#\'&~+-/*:;,!?§<>";
    for(int i = 0; i < str.length(); i++){
        for(int j = 0; j < notAllowedLetters.length(); j++){
            if(str[i] == notAllowedLetters[j]){
                return false;
            }
        }
    }
    return true;
}