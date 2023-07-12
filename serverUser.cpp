#include <iostream>
#include "serverUser.h"

void ServerUser::logIn(){
    User s;
    int locationOfUser;
    s.id.enterEmailAdress();

    //we store the location of the user that has this email in a variable
    locationOfUser = ms.user.search(s);
    if(locationOfUser == -1){
        cout<<"this email doesn't exist, do you want to sign up?"<<endl;
        return;
    }

    //we point to the element (user) that we found in the HashTable
    HashEntry* user = &ms.user.array[locationOfUser];

    //password check
    string password;
    cout<<"Now enter your Password: "<<endl;
    cin>>password;
    while(password != user->element.getPassword()){
        cout<<"wrong password, please enter your correct one"<<endl; cin>>password;
    }

    //the pointer of the account that we logged in with is now inserted in the list of accounts
    account.push_back(user);
    if(activeAccount == nullptr){
        this->activeAccount = user;
    }
    cout<<endl;
    cout<<"\t\t\tthe user \" "<<user->element.getUserName()<<" \" "<<"logged in successfully"<<endl<<endl;

}

void ServerUser::logOut(){
    //emailAddress t;
    //cout<<"which email you want to log out from:"<<endl;
    //cout<<"enter the id of it: "<<endl;
    //t.enterEmailAdress();
    //log out means removing the pointer that point to the user from the user system vector
    //for(auto it = account.begin(); it != account.end(); it++) {
        //string emailNameOfaccount = (*it)->element.getID().getName();
        //if(emailNameOfaccount == emailNameOfT){
            //account.remove(*it);
            //break;
        //}
    //}

    if(activeAccount == nullptr){
        chooseAnAccount();
    }

    account.remove(activeAccount);
    activeAccount = nullptr;
    cout<<endl;
    cout<<"\t\t\tyou logged out successfully..."<<endl<<endl;
}

void ServerUser::signIn(){
    User s;
    s.enterUserInfo();

    //we check if this user exists already
    while(ms.user.search(s) != -1){
        cout<<"this id already exists, do you want to log in?"<<endl;
        cout<<"please write correctly your infomation."<<endl;
        s.enterUserInfo();
    }
    if(ms.user.insert(s)){
        //system("cls");
        cout<<endl;
        cout<<"\t\t\tuser inserted..."<<endl<<endl;
    }else{
        
        cout<<endl;
        cout<<"\t\t\ttheir is a problem..."<<endl<<endl;
    }
}

void ServerUser::signOut(){
    //emailAddress t;
    //cout<<"which email you want to sign out from:"<<endl;
    //cout<<"enter the id of it: "<<endl;
    //t.enterEmailAdress();
    //string emailNameOfT = t.getName();

    //sign out means removing the pointer that point to the user from the user system vector
    //and mark this user in the hash table as DELETED
    //for(auto it = account.begin(); it != account.end(); it++) {
        //string emailNameOfaccount = (*it)->element.getID().getName();
        //if(emailNameOfaccount == emailNameOfT){
           // break;
        //}
    //}

    if(activeAccount == nullptr){
        chooseAnAccount();
    }

    //we remove the user from the hash table
    activeAccount->info = DELETED;

    //we remove it from the list
    account.remove(activeAccount);
    activeAccount = nullptr;
    
    //system("cls");
    cout<<endl;
    cout<<"\t\t\tyou signed out successfully..."<<endl<<endl;
}

void ServerUser::readEmails(){
    if(activeAccount == nullptr){
        chooseAnAccount();
    }

    activeAccount->element.showMailBox();
}

void ServerUser::sendMail(){
    auto itr = this->account.begin();
    emailAddress fromAccountID;
    Mail draft;
    draft.enterMailInfo();

    string emailNameOfAccount = (*itr)->element.getID().getName();

            //serching for the sender user in the accounts
            for(itr = this->account.begin(); itr != this->account.end(); itr++){
                emailNameOfAccount = (*itr)->element.getID().getName();
                if(draft.getSender().getName() == emailNameOfAccount){
                    break;
                }
            }

            //in case the user enter invalid sender id
            while(draft.getSender().getName() != emailNameOfAccount){
                cout<<"the sender that you entered doesn't exist in your accounts please enter id of a correct sender: "<<endl;
                draft.enterSender();
                for(itr = this->account.begin(); itr != this->account.end(); itr++){
                    emailNameOfAccount = (*itr)->element.getID().getName();
                    if(draft.getSender().getName() == emailNameOfAccount){
                        break;
                    }
                }
            }

    this->ms.mail.push(draft);
    ms.activateQueue();
}

void ServerUser::chooseAnAccount(){
    /*
    emailAddress t;
    bool changed = false;
    cout<<"which email you will work with:"<<endl;
    cout<<"enter the id of it: "<<endl;
    t.enterEmailAdress();
    string emailNameOfT = t.getName();

    for(auto it = account.begin(); it != account.end(); it++) {
        string emailNameOfaccount = (*it)->element.getID().getName();
        if(emailNameOfaccount == emailNameOfT){
            activeAccount = (*it);
            changed = true;
            break;
        }
    }

    while(!changed){
    cout<<"please enter a correct id: "<<endl;
    t.enterEmailAdress();
    emailNameOfT = t.getName();

    for(auto it = account.begin(); it != account.end(); it++) {
        string emailNameOfaccount = (*it)->element.getID().getName();
        if(emailNameOfaccount == emailNameOfT){
            activeAccount = (*it);
            changed = true;
            break;
        }
    }
    }
    */
   int counterOfAccounts(1);
   cout<<"choose one between your accounts: "<<endl<<endl;
   for(auto it = account.begin(); it != account.end(); it++) {
    cout<<counterOfAccounts<<". ";
    (*it)->element.getID().printEmailAdress();
    counterOfAccounts++;
   }

   cout<<"0. return"<<endl;

   cin>>counterOfAccounts;

   if(counterOfAccounts > account.size() || counterOfAccounts < 1){
    return;
   }

   activeAccount = *next(account.begin(), counterOfAccounts - 1);
}

void ServerUser::editPassword(){
    if(activeAccount == nullptr){
        chooseAnAccount();
    }
    string password, confirmationOfPassword;
    //check if the user know his old password
    cout<<"enter the old password: "; cin>>confirmationOfPassword;
    while(activeAccount->element.getPassword() != confirmationOfPassword){
        cout<<"error, please enter your correct password: "; cin>>confirmationOfPassword;
    }

    cout<<"enter the new password: "; cin>>password;
    cout<<"enter it again please: "; cin>>confirmationOfPassword;
    while(password != confirmationOfPassword){
        cout<<"please enter it again correctly: "; cin>>confirmationOfPassword;
    }

    activeAccount->element.setPassword(password);

    //system("cls");
    cout<<endl;
    cout<<"\t\t\tpassword changed..."<<endl<<endl;
}

void ServerUser::menu(){
    bool b = true;
    while(b){
        int choose;
        if(activeAccount != nullptr){
            cout<<"Welcome "<<activeAccount->element.getUserName()<<" ,";
        }
        cout<<"choose what you want to do:"<<endl<<endl;

        if(this->account.size() != 0){
            cout<<"1.choose an account\n2.log in\n3.sign in\n4.log out\n5.sign out\n6.show mails\n7.send mail\n8.edit password\n0.stop"<<endl<<endl;
            cin>>choose;
            //system("cls");

            switch (choose)
            {
            case 1:
                chooseAnAccount();
                break;
            
            case 2:
                logIn();
                break;
            
            case 3:
                signIn();
                break;
            
            case 4:
                logOut();
                break;
            
            case 5:
                signOut();
                break;
            
            case 6:
                readEmails();
                break;

            case 7:
                sendMail();
                break;

            case 8:
                editPassword();
                break;

            default:
                 b = false;
                break;
            }
        }else{
            cout<<"1.log in\n2.sign in\n0.stop"<<endl<<endl;
            cin>>choose;
            //system("cls");

            switch (choose)
            {
            case 1:
                logIn();
                break;
            
            case 2:
                signIn();
                break;
            
            default:
                b = false;
                break;
            }
        }
    }
}