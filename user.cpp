#include <iostream>
#include "user.h"

using std::cin;
using std::cout;
using std::endl;

void User::enterUserInfo(){
    cout<<"user name: "; cin>>this->userName;
    this->id.enterEmailAdress();

    cout<<"password: "; cin>>this->password;
}

void User::addToMailBox(const Mail& mail){
    this->mailBox.push_back(mail);
    this->mailBoxIndexer++;
}

void User::deleteFromMailBox(){
    if(this->mailBoxIndexer == -1){
        cout<<endl;
        cout<<"\t\t\ttheir is no mails to delete"<<endl<<endl;
        return;
    }
    this->mailBox.erase(this->mailBox.begin() + this->mailBoxIndexer);
    if(this->mailBoxIndexer == this->mailBox.size()){
        this->mailBoxIndexer--;
    }
}

void User::showNextMail(){
    if(this->mailBoxIndexer == this->mailBox.size() - 1){
        cout<<endl;
        cout<<"\t\t\t their is no mail after..."<<endl<<endl;
        return;
    }
    this->mailBoxIndexer++;
}

void User::showPreviousMail(){
    if(this->mailBoxIndexer == 0){
        cout<<endl;
        cout<<"\t\t\t their is no mail before..."<<endl<<endl;
        return;
    }
    this->mailBoxIndexer--;
}

void User::showMailBox(){
    bool b = true;
    while(b){
        if(this->mailBoxIndexer == -1){
        cout<<endl;
        cout<<"\t\t\tyour mailBox is empty..."<<endl<<endl;
        return;
        }
        this->mailBox[this->mailBoxIndexer].displayMail();
        int choose;
        cout<<"+----------------------------------------+"<<endl;
        cout<<"1.Show next mail\n2.show previous mail\n3.delete mail\n0.return"<<endl;
        cout<<"+----------------------------------------+"<<endl;
        cin>>choose;
        switch (choose)
        {
        case 1:
            //system("cls");
            this->showNextMail();
            break;

        case 2:
            //system("cls");
            this->showPreviousMail();
            break;

        case 3:
            //system("cls");
            this->deleteFromMailBox();
            break;
        default:
            b = false;
            break;
        }
    }
    this->mailBoxIndexer = this->mailBox.size() - 1;
}

User User::operator=(const User& user){
    this->userName = user.userName;
    this->id = user.id;
    this->password = user.password;
    this->mailBox = user.mailBox;
    this->mailBoxIndexer = user.mailBoxIndexer;
    return *this;
}