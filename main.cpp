#include <iostream>
#include "serverUser.h"
using namespace std;

MailServer ServerUser::ms;

int main(){
    ServerUser s;
    s.menu();
    return 0;
}