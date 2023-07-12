#ifndef MAIL_H
#define MAIL_H

#include <iostream>
#include <list>
#include <string>
#include "emailAddress.h"

#include <cstdlib>
#include <ctime>

using std::cout;
using std::string;
using std::list;

using std::cout;
using std::cin;
using std::getline;
using std::ws;


class Mail{
    public:
    Mail(){};
    ~Mail() = default;
    Mail(const emailAddress& sender, const emailAddress& receiver, const string& message){
        this->sender = sender;
        this->receiver = receiver;
        this->message.push_back(message);
    }

    //a function to display the mails in a good formate
    void displayMail()const;

    //a function to enter a mail from the very begining
    void enterMailInfo();

    //getters and setters
    emailAddress getSender()const{ return this->sender;}
    emailAddress getReceiver()const{ return this->receiver;}
    int getMailNumber()const{ return mailNumber;}
    list<string> getMessage()const{ return this->message;}

    Mail setSender(const emailAddress& sender){ 
        this->sender = sender;
        return *this;
    }

    Mail setSender(const string& sender){
        this->sender.setName(sender.substr(0, sender.find('@')));
        this->sender.setDomainName(sender.substr(sender.find('@') + 1, sender.length() - 1));
        return *this;
    }

    void enterSender(){
        this->sender.enterEmailAdress();
    }
    Mail setReceiver(const emailAddress& receiver){
        this->receiver = receiver;
        return *this;
    }

    Mail setReceiver(const string& receiver){
        this->receiver.setName(receiver.substr(0, receiver.find('@')));
        this->receiver.setDomainName(receiver.substr(receiver.find('@') + 1, receiver.length() - 1));
        return *this;
    }


    Mail setMessage(const list<string>& message){
        this->message = message;
        return *this;
    }
    Mail setMailNumber();
    Mail setMailNumber(int mailNumber);

    bool operator=(const Mail& mail);
    bool operator==(const Mail& mail);
    bool operator!=(const Mail& mail);

    private:
    emailAddress sender;
    emailAddress receiver;
    list<string> message;
    int mailNumber;

    friend class ServerUser;
};
#endif