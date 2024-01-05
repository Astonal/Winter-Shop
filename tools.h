
#ifndef _TOOLS
#define _TOOLS
#include"User.h"
#include <stdio.h>

using namespace std;

string gettime();
string gettime_detail();

class user get_userid();

void user_update();
void good_update();
void order_update();

bool admin_login();

void admin_showmenu();

string get_money();
#endif
