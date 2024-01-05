#include<iostream>
#include<fstream>
#include"tools.h"
#include"Goods.h"
#include"Order.h"
#include<stdio.h>
using namespace std;

const char* RESET = "\033[0m";
const char* FRONT_RED = "\033[31m";
const char* FRONT_YELLOW="\033[33m";
const char* FRONT_BLUE = "\033[34m";
const char* FRONT_DG = "\033[36m";
const char* BACK_WHITE = "\033[47m";
const char* BOLD="\033[1m";

void display()
{
	int flag = 0;
	while (flag == 0)
	{
		string order;
		printf("%s",FRONT_YELLOW);
		cout << "===============================================" << endl;
		cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
		cout << "===============================================" << endl;
		printf("%s",RESET);
		cout << "输入操作：";
		cin >> order;
		if (order == "1")
		{
			flag = 1;
			bool a = admin_login();
			if (!a) { flag = 0; }
			if(a) { admin_showmenu(); }
		}
		else if (order == "2")
		{
			flag = 1;
			user::user_create();
		}
		else if (order == "3")
		{
			flag = 1;
			bool b = user::user_login();
			if (!b) { flag = 0; }
			if (b) { user::user_mainmenu(); }
		}
		else if (order == "4")
		{
			flag = 1;
			cout << endl << "-----退出程序，欢迎下次使用-----"<<endl;
		}
		else {
			cout << endl << "-----指令有误，请重新输入！-----"<<endl;
		}
	}
}

int main()
{
	const char* first= "Welcome to";	
	const char*last= "----------欢迎来到冬奥会纪念品交易平台----------";
	printf("%s%s%s%s%s\n",BACK_WHITE,FRONT_RED,BOLD,first,RESET);
	printf("%s%s%s\n",BACK_WHITE,FRONT_DG,BOLD);
	cout << "   ____  _                       _            __  __            _        _     _ "<<endl;
	cout << "  / __ \\| |                     (_)          |  \\/  |          | |      | |   | |"<<endl;
	cout << " | |  | | |_   _ _ __ ___  _ __  _  ___ ___  | \\  / | __ _ _ __| | _____| |_  | |" << endl;
	cout << " | |  | | | | | | '_ ` _ \\| '_ \\| |/ __/ __| | |\\/| |/ _` | '__| |/ / _ \\ __| | |" << endl;
	cout << " | |__| | | |_| | | | | | | |_) | | (__\\__ \\ | |  | | (_| | |  |   <  __/ |_  | |" << endl;
	cout << "  \\____/|_|\\__, |_| |_| |_| .__/|_|\\___|___/ |_|  |_|\\__,_|_|  |_|\\_\\___|\\__| |_|" << endl;
	cout << "            __/ |         | |                                                 (_)" << endl;
	cout << "           |___/          |_|                                                    " << endl;
	
	printf("%s\n\n",RESET);
	printf("%s%s%s%s%s\n\n",RESET,FRONT_YELLOW,BOLD,last,RESET);
	user::getalluser();
	goods::getallgoods();
	order::getallorder();
	user::getallmoney();
	user::getallmessage();
	
	display();
	
	return 0;
}