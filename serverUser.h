#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <cstdlib>
#include "mailServer.h"

class ServerUser{
    public:
    ServerUser(){};
    ServerUser(const User& account);
    void logIn();
    void logOut();
    void signIn();
    void signOut();
    void sendMail();
    void readEmails();
    void editPassword();
    void chooseAnAccount();

    //function to display in the console the possible actions that could be done by the user
    void menu();

    friend class MailServer;

    private:
    static MailServer ms;
    list<HashEntry*> account;
    HashEntry* activeAccount = nullptr;
};
#endif


