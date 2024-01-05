#ifndef _USER
#define _USER
#include<string>
#include"tools.h"
#include<vector>

using namespace std;

struct mon {
	string id;
	string dollar;
};

struct message {
	string from;
	string to;
	string time;
	string goodid;
	string info;
	
};

class user{
	friend user get_userid();
	friend void user_update();
	friend class order;
	friend class goods;
	friend string get_money();
public:
	static void user_create();
	static bool user_login();
	static void user_logout();
	static string u_rollid();

	static void user_mainmenu();//select buyers and sellers

	static void user_info_menu();
	static void user_info_show();
	static void user_info_change();
	static void user_name_change(int i);
	static void user_num_change(int i);
	static void user_add_change(int i);
	static void user_money_add();

	static int user_find(string id);
	static int user_find_s(string id);

	//seller:
	static void seller_showmenu();

	//buyer
	static void buyer_showmenu();

	friend istream& operator >>(istream& in, user &user);
	friend ostream& operator <<(ostream& out, user& user);
	
	static void getalluser();
	//admin
	static void u_showhead();
	static void admin_u_show();
	static void admin_u_ban(string id);
	
	static void getallmoney();
	static void money_create(string money,string id);

	static void seller_message_mainmenu();
	static void buyer_message_mainmenu();
	static void seller_message_receive();
	static void buyer_message_receive();
	static void seller_message_sendcheck();
	static void buyer_message_sendcheck();
	static void seller_message_send();
	static void buyer_message_send();
	static void getallmessage();
	static void message_create(string from, string to,string time,string goodid,string info);

private:
	string u_id;
	string u_name;//only english, max=10
	string u_word;//no capital and numbers,max = 20
	string u_num;//no more than 20
	string address;//only english,no more than 40
	float u_money=0;//precision 0.1
	string u_state;//active-1 inactive-0
	bool login_state;

};
#endif 