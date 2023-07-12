#include "mailServer.h"

void MailServer::insertUser(const User& user){
    this->user.insert(user);
}

void MailServer::removeUser(const User& user){
    this->user.remove(user);
}

void MailServer::insertMail(const Mail& mail){
    this->mail.push(mail);

}

void MailServer::deleteMail(){
    this->mail.pop();
}


int MailServer::searchUser(const User& user){
    return this->user.contains(user);
}

void MailServer::activateQueue(){
    User s;
    emailAddress a;
    int locationOfUser;
    string recieverName = mail.front().getReceiver().getName();
    a.setName(recieverName);
    s.setID(a);


    //we store the location of the user that has this email in a variable
    locationOfUser = user.search(s);
    if(locationOfUser == -1){
        cout<<"the receiver of this mail doesn't exist in the mail server!!"<<endl;
        mail.pop();
        return;
    }

    User* recieverOfMail = &user.array[locationOfUser].element;
    Mail firstMailInQueue = mail.front();
    sendMail(recieverOfMail, firstMailInQueue);
    Mail firstMailOfReciever = recieverOfMail->getFirstMail();

    //we check if the first mail in the mail box of the receiver is this mail
    int counter = 0;
    while(firstMailInQueue != firstMailOfReciever && mail.size() == 1 && counter < 3){
        sendMail(recieverOfMail, firstMailInQueue);
        counter++;
    }
    mail.pop();

    if(counter == 3){
        cout<<endl;
        cout<<"\t\t\tcould not send your mail..."<<endl<<endl;
    }

    if(!mail.empty()){
        activateQueue();
    }
}

void MailServer::sendMail(User*& reciever, const Mail& mailToSend)const{
    reciever->addToMailBox(mailToSend);

    cout<<endl;
    cout<<"\t\t\tmessage sent successfully..." <<endl<<endl;
}

void MailServer::laodUsers(){
    //we open the file that we store the users in
    dataBase.open("dataBase.txt", ios::in);
    if(dataBase.is_open()){
        User tempOfUser;
        string userName, id, password;
        int mailBoxIndexer;

        while(dataBase>>userName>>id>>password>>mailBoxIndexer){

            //we bring the four basic info of the user from the file
            tempOfUser.setUserName(userName.erase(0, 9));
            tempOfUser.setID(id.erase(0, 3));
            tempOfUser.setPassword(password.erase(0, 9));
            tempOfUser.setMailBoxIndexer(mailBoxIndexer);

            //now we bring the mails of the user if he/she has
            if(mailBoxIndexer != -1){
                vector<Mail> mailsOfTempOfUser[mailBoxIndexer + 1];
                while(mailBoxIndexer != -1){

                    Mail tempOfMail;
                    string from;
                    int mailNumber;

                    //we start by bringging the three basic info about the mail
                    dataBase>>from>>mailNumber;

                    tempOfMail.setSender(from);
                    tempOfMail.setReceiver(id);
                    tempOfMail.setMailNumber(mailNumber);

                    list<string> message;
                    string line;

                    //now we bring the message that exists in this mail
                    while(dataBase>>line && line != "."){
                        message.push_back(line);
                    }

                    tempOfMail.setMessage(message);

                    mailsOfTempOfUser->push_back(tempOfMail);
                    mailBoxIndexer--;
                }
            }
        }
    }
}