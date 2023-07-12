#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "mail.h"

using std::vector;
using std::string;

using std::cin;
using std::cout;
using std::endl;
using std::next;

class User{
    public:
    User(){};
    User(const string& userName, const emailAddress& id, const string password){
        this->userName = userName;
        this->id = id;
        this->password = password;
    }

    ////function to let the main user directly insert his/her info
    void enterUserInfo();

    //functions of the mailBox
    void addToMailBox(const Mail& mail);
    void deleteFromMailBox();
    void showMailBox();
    void showPreviousMail();
    void showNextMail();

    //overload fuctions
    User operator=(const User& user);

    //getters and setters
    string getUserName()const{ return this->userName;}
    User setUserName(const string& userName){
        this->userName = userName;
        return *this;
    }

    string getPassword()const{ return this->password;}
    User setPassword(const string& password){
        this->password = password;
        return *this;
    }

    emailAddress getID()const{ return this->id;}
    User setID(const emailAddress& id){
        this->id = id;
        return *this;
    }

    User setID(const string& id){
        this->id.setName(id.substr(0, id.find('@')));
        this->id.setDomainName(id.substr(id.find('@') + 1, id.length() - 1));
    }

    User setMailBoxIndexer(int mailBoxIndexer){
        this->mailBoxIndexer = mailBoxIndexer;
    }

    Mail getFirstMail()const{
        return this->mailBox[this->mailBoxIndexer];
        }

    private:
    string userName;
    emailAddress id;
    string password;
    vector<Mail> mailBox;
    int mailBoxIndexer = -1;
    friend class ServerUser;
};
#endif