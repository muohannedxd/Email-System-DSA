#ifndef MAIL_SYSTEM_H
#define MAIL_SYSTEM_H
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <list>
#include "hash.h"


using std::string;
using std::queue;
using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::fstream;


class MailServer{
    public:
    MailServer(){
        laodUsers();
    }
    //manipulate our data from DSAs:
    void insertUser(const User& user);
    void removeUser(const User& user);
    void insertMail(const Mail& mail);
    void deleteMail();
    void sendMail(User*& reciever, const Mail& mailToSend)const;
    void activateQueue();

    //function to check if a user exists and not deleted and return his index in the hash table(return -1 if doesn't exist)
    int searchUser(const User& id);

    //manipulate our data from our dataBase(the file):
    void laodUsers();
    void saveUser(const User& user)const;
    void deleteUser(const User& user)const;
    void saveMail(const Mail& mail)const;
    void deleteMail(const Mail& mail)const;
    void savePassword(const User& user, const string& password);

    friend class ServerUser;
    private:
    fstream dataBase;
    HashTable user;
    queue<Mail> mail;
};
#endif