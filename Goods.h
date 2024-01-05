
#ifndef _GOODS
#define _GOODS
#include<string>
#include"tools.h"


using namespace std;

class goods{
	friend void good_update();
	friend class user;
	friend class order;

private:
	string g_id;//max==4
	string g_name;//max==20
	string g_price;//precision 0.1
	int g_num;
	string g_des;//max==200
	string g_uid;
	string g_update_time;//yyyy-mm-dd
	string condition;//sale or soldout
	bool show_flag;

public:
	friend istream& operator >>(istream& in, goods& goods);
	friend ostream& operator <<(ostream& out, goods& goods);
	static string g_rollid();//商品号生成
	static void getallgoods();
	static void g_show_head();//展示商品表头
	//admin
	static void admin_g_show();
	static void admin_g_search(string name);
	static void admin_g_delete(string id,int i);
	static void admin_g_ban(string uid);
	//seller
	static void seller_g_show();
	static void g_update();
	static void seller_g_change();
	static void seller_g_delete();
	//buyer
	static void buyer_g_show();
	static void buyer_g_buy();
	static void buyer_g_search(string name);
	static void buyer_g_detail(string id);
};
#endif