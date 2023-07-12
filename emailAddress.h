#ifndef EMAILADRESS_H
#define EMAILADRESS_H

#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;

using std::cout;
using std::endl;
using std::cin;
using std::fstream;
using std::ios;

class emailAddress{
    public:
    emailAddress(const string& name, const string& domainName){
        this->name = correctName(name) ? name : "";
        this->domainName = correctDomainName(domainName) ? domainName : "";
    }
    emailAddress(){};

    void printEmailAdress()const{
        cout<<this->name<<"@"<<this->domainName<<endl;
    }

    //function to let the main user directly insert his email adress
    void enterEmailAdress();

    //function to check if the domain name is valid(maybe i will use it for another things later)
    bool correctEmailAdress(const string& str)const;
    bool correctDomainName(const string& str)const;
    bool correctName(const string& str)const;

    //getters and setters
    string getName()const{ return this->name;}
    string getDomainName()const{ return this->domainName;}

    emailAddress setName(const string& name){
        this->name = name;
        return *this;
    }
    emailAddress setDomainName(const string& domainName){
        this->domainName = correctDomainName(domainName)? domainName : this->domainName;
        return *this;
    }

    private:
    string name;
    string domainName;
};
#endif