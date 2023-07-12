#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mail.h"


using std::cout;
using std::cin;
using std::getline;
using std::ws;

void Mail::displayMail()const{
    cout<<"+----------------------------------------+"<<endl;
    cout<<"An email from: "; this->sender.printEmailAdress();
    for(int i = 0; i < this->message.size(); i++){
        cout<<*next(this->message.begin(), i);
        cout<<endl;
    }
    cout<<endl;
    cout<<"+----------------------------------------+"<<endl<<endl;
}

void Mail::enterMailInfo(){
    cout<<"Email of the sender: "<<endl;
    this->sender.enterEmailAdress();
    cout<<"Email of the receiver: "<<endl;
    this->receiver.enterEmailAdress();

    cout<<"Now write the message that you want to send: "<<endl;
    cout<<"write . alone in a seperate line to finish writing"<<endl;
    string line;
    getline(cin>>ws, line);
    while(line != "."){
        message.push_back(line);
        getline(cin>>ws, line);
    }
    setMailNumber();
}

Mail Mail::setMailNumber(){
    srand(time(0));
    for(int i = 0; i < sender.getName().length() || i < receiver.getName().length(); i++){
        if(i < sender.getName().length()){
            this->mailNumber += int(sender.getName()[i]);
        }

        if(i < receiver.getName().length()){
            this->mailNumber += int(receiver.getName()[i]);
        }
    }

    this->mailNumber += rand();
    return *this;
}

Mail Mail::setMailNumber(int mailNumber){
    this->mailNumber = mailNumber;
}

bool Mail::operator=(const Mail& mail){
    this->sender = mail.sender;
    this->receiver = mail.receiver;
    this->mailNumber = mail.mailNumber;
    this->message = mail.message;
}

bool Mail::operator==(const Mail& mail){
    return this->mailNumber == mail.mailNumber;
}
bool Mail::operator!=(const Mail& mail){
    return !(*this == mail);
}