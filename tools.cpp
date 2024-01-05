#include<stdio.h>
#include<iostream>
#include<sstream>
#include"tools.h"
#include"User.h"
#include"Goods.h"
#include"Order.h"
#include<vector>
#include<fstream>
#include"main.h"
#include"SQL.h"
using namespace std;
extern vector<mon>d;
extern vector<user> u;
extern vector<goods> g;
extern vector<order> t;

string get_money()
{
	string ans; 
	int flag = 0;
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	for (int j = 0; j <d.size() ; j++)
	{
		if (d[j].id == u[i].u_id)
		{
			flag = 1;
			ans += d[j].dollar;
			ans += " + ";
		}
	}
	//string::size_type pos1 = ans.find_last_of('+');
	//ans.erase(pos1);
	if (flag==1)
	{
		//cout << ans;
		ans.pop_back();
		ans.pop_back();
		ans.pop_back();
	}
	for (int m = 0; m < t.size(); m++)
	{
		if (t[m].t_buyer == u[i].u_id)
		{
			ans += " - ";
			ans += to_string(t[m].t_num) + " * " + t[m].t_price;
		}
	}
	for(int m=0;m<t.size();m++)
	{
		if (t[m].t_seller == u[i].u_id)
		{
			ans += " + ";
			ans +=to_string(t[m].t_num) + " * " + t[m].t_price;
		}
	}
	return ans;
}

string gettime()
{
	time_t tt;
	time(&tt);
	tt = tt + 8 * 3600;  // transform the time zone
	tm* t = gmtime(&tt);

	string t1 = to_string(t->tm_year+1900);
	string t2 = to_string(t->tm_mon+1);
	string t3 = to_string(t->tm_mday);
	string time = t1 + "-" + t2 + "-" + t3;
	return time;

}
string gettime_detail()
{
	time_t tt;
	time(&tt);
	tt = tt + 8 * 3600;  // transform the time zone
	tm* t = gmtime(&tt);

	string t1 = to_string(t->tm_year+1900);
	string t2 = to_string(t->tm_mon+1);
	string t3 = to_string(t->tm_mday);
	string t4 = to_string(t->tm_hour);
	string t5 = to_string(t->tm_min);
	string t6 = to_string(t->tm_sec);
	string time = t1 + "-" + t2 + "-" + t3 + " " + t4 + ":" + t5 + ":" + t6;
	return time;

}

//string gettime()
//{
//	SYSTEMTIME sys;
//	GetLocalTime(&sys);
//	stringstream s1,s2,s3;
//	s1 << sys.wYear;
//	s2 << sys.wMonth;
//	s3 << sys.wDay;
//	string t1 = s1.str();
//	string t2 = s2.str();
//	string t3 = s3.str();
//	string time = t1 + "-" + t2 + "-" + t3;
//	return time;
//}
//
//string gettime_detail()
//{
//	SYSTEMTIME sys;
//	GetLocalTime(&sys);
//	stringstream s1, s2, s3,s4,s5,s6;
//	s1 << sys.wYear;
//	s2 << sys.wMonth;
//	s3 << sys.wDay;
//	s4 << sys.wHour;
//	s5 << sys.wMinute;
//	s6 << sys.wSecond;
//	string t1 = s1.str();
//	string t2 = s2.str();
//	string t3 = s3.str();
//	string t4 = s4.str();
//	string t5 = s5.str();
//	string t6 = s6.str();
//	string time = t1 + "-" + t2 + "-" + t3+" "+t4+":"+t5+":"+t6;
//	return time;
//}


void user_update()
{
	fstream file1("user.txt", ios::out);
	if (!file1)
	{
		cerr << "打开文件失败！";
		return;
	}//////
	file1.close();
	fstream file2("user.txt", ios::in | ios::out|ios::app);
	if (!file2)
	{
		cerr << "打开文件失败！";
		return;
	}
//	file2 << "userID,username,password,phoneNumber,address,balance,userState" << endl;
	for (int i = 0; i < u.size(); i++)
	{
		file2 << u[i].u_id << " " << u[i].u_name << " " << u[i].u_word << " " << u[i].u_num
			<< " " << u[i].address << " " << u[i].u_money << " " << u[i].u_state << endl;
		//cout << "count i is:" << i << endl;
	}
	file2.close();
}

void good_update()
{
	fstream file1("good.txt", ios::out);
	if (!file1)
	{
		cerr << "打开文件失败！";
		return;
	}//////
	file1.close();
	fstream file2("good.txt", ios::in | ios::out | ios::app);
	if (!file2)
	{
		cerr << "打开文件失败！";
		return;
	}
	//file2 << "commodityID,commodityName,price,number,description,sellerID,addedDate,state" << endl;
	for (int i = 0; i < g.size(); i++)
	{
		file2 << g[i].g_id << " " << g[i].g_name << " " << g[i].g_price << " " << g[i].g_num << " "
			<< g[i].g_des << " " << g[i].g_uid << " " << g[i].g_update_time << " " << g[i].condition<<endl;
	}
	file2.close();
}

void order_update()
{
	fstream file1("order.txt", ios::out);
	if (!file1)
	{
		cerr << "打开文件失败！";
		return;
	}//////
	file1.close();
	fstream file2("order.txt", ios::in | ios::out | ios::app);
	if (!file2)
	{
		cerr << "打开文件失败！";
		return;
	}
//	file2 << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID" << endl;
	for (int i = 0; i < t.size(); i++)
	{
		file2 << t[i].t_id << " " << t[i].t_g_id << " " << t[i].t_price << " "
			<< t[i].t_num << " " << t[i].t_time << " " << t[i].t_seller << " " << t[i].t_buyer << endl;
	}
	file2.close();
}

bool admin_login()
{
	string adname;
	string adword;
	cout << "请输入管理员姓名：";
	cin >> adname;
	if (adname != "admin")
	{
		cout << "-----管理员账号不存在，登陆失败，返回主菜单-----" << endl << endl;
		//display();
		return false;
	}
	else
	{
		cout << "请输入密码：";
		cin >> adword;
		if (adword != "123456")
		{
			cout << "-----密码错误，登陆失败，返回主菜单-----" << endl << endl;
			//display();
			return false;
		}
		else
		{
			cout << endl << endl << "-----登陆成功-----" << endl << endl;
			//admin_showmenu();
			return true;
		}
	}
}

void admin_showmenu()
{
	while (1)
	{
		string order;
		cout << "=======================================================================================" << endl;
		cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
		cout << "=======================================================================================" << endl << endl;
		cout << "请输入操作：";
		cin >> order;
		if (order == "1")
		{
			//goods::admin_g_show();
			sql_admin("SELECT * FROM commodity");
			break;
		}
		else if (order == "2")
		{
			string name;
			cout << "请输入商品名称：";
			cin >> name;
			string order1 = "SELECT * FROM commodity WHERE gname CONTAINS " + name;
			//goods::admin_g_search();
			sql_admin(order1);
			break;
		}
		else if (order == "3")
		{
			string ID;
			cout << "请输入要下架的商品ID：";
			cin >> ID;
			string order1 = "UPDATE commodity SET gcondition = removed WHERE gid = " + ID;
			//goods::admin_g_delete();
			sql_admin(order1);
			break;
		}
		else if (order == "4")
		{
			//order::admin_t_show();
			sql_admin("SELECT * FROM order");
			break;
		}
		else if (order == "5")
		{
			//user::admin_u_show();
			sql_admin("SELECT * FROM user");
			break;
		}
		else if (order == "6")
		{
			//user::admin_u_ban();
			string id;
			cout << "请输入要封禁的用户ID：";
			cin >> id;
			string order1 = "UPDATE commodity SET gcondition = removed WHERE guid = " + id;
			string order2 = "UPDATE user SET ucondition = inactive WHERE uid = " + id;
			sql_admin(order1);
			sql_admin(order2);
			break;
		}
		else if (order == "7")
		{
			display();
			break;
		}
		else
		{
			cout << "-----指令有误-----"<<endl<<endl;
		}
	}
}