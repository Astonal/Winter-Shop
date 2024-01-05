
#ifndef _ORDER
#define _ORDER
#include<string>
#include"tools.h"


using namespace std;

class order
{
	friend string get_money();
	friend void order_update();
	string t_id;//max=4
	string t_g_id;
	string t_price;//precision 0.1
	int t_num;
	string t_time;//yyyy-mm-dd
	string t_seller;
	string t_buyer;

public:
	//admin使用
	static void admin_t_show();
	static void t_showhead();
	//通用
	static string t_rollid();
	static void getallorder();
	static void t_create(int i,int num,string buyer_id);
	//卖家
	static void seller_t_show();
	//买家
	static void buyer_t_show();
};
#endif