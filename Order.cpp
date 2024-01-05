#include<iostream>
#include<vector>
#include"Goods.h"

#include"Order.h"
#include<fstream>
#include"tools.h"
#include<sstream>
using namespace std;

static int totalorder;
vector<order> t;
extern vector<goods> g;
extern vector<user> u;
void order::t_showhead()
{
	cout << "订单ID"<<"\t"<<"商品ID"<<"\t"<<"交易单价"<<"\t"<<"数量"<<"\t"<< "交易时间" << "\t" << "卖家ID"<<"\t"<<"买家ID" << endl;
}

string order::t_rollid()
{
	string id;
	int i = 0;
	stringstream s3;
	for (; i < t.size() + 1; i++) {}
	s3 << i;
	string s = s3.str();
	if (i < 10)
	{
		id = "T00" + s;
	}
	else
		id = "T0" + s;
	return id;
}

void order::t_create(int i,int num,string buyer_id)
{
	/*string id = t_rollid();
	fstream f;
	f.open("order.txt", ios::in | ios::out | ios::app);
	if (!f) { cerr << "fail"; return; }
	f << id << " " << g[i].g_id << " " << g[i].g_price << " "
		<<num<< " "
		<< gettime() << " "
		<< g[i].g_uid << " " << buyer_id <<endl;
	f.close();
	getallorder();*/
}

void order::getallorder()
{
	t.clear();
	totalorder = 0;
	fstream f("order.txt", ios::in | ios::out | ios::app);
	if (!f) { cerr << "fail"; return; }
	/*char c;
	f >> c;
	if (f.eof())
	{
		f.close();
		return;
	}*/
	order temp;
	while (f >> temp.t_id >> temp.t_g_id >> temp.t_price
		>> temp.t_num >> temp.t_time >> temp.t_seller >> temp.t_buyer) {
		t.push_back(temp);
		totalorder++;  
	}
	f.close();
}

void order::admin_t_show()
{
	if (t.size() != 0)
	{
		cout.fill('*');
		cout.width(80);
		cout << '*' << endl;
		cout << "订单ID" << "\t" << "商品ID" << "\t" << "交易单价" << "\t" << "数量" << "\t"
			<< "交易时间" << "\t" << "卖家ID" << "\t" << "买家ID"<<endl;
		for (int i = 0; i < t.size(); i++)
		{
			cout << t[i].t_id << "\t" << t[i].t_g_id << "\t" << t[i].t_price << "\t\t" << t[i].t_num
				<< "\t" <<t[i].t_time<<"\t" <<t[i].t_seller << "\t" << t[i].t_buyer << endl;
		}
		cout.fill('*');
		cout.width(80);
		cout << '*' << endl<<endl;
		admin_showmenu();
	}
	else { 
		cout << "-----当前订单为空-----" << endl<<endl; 
		admin_showmenu();
	}
}

void order::seller_t_show()
{
	int k = 0;
	for (;k < u.size(); k++)
	{
		if (u[k].login_state == 1)
			break;
	}
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i].t_seller == u[k].u_id)
		{
			goto F1;
		}
	}
	cout << "-----未找到你已完成的订单信息！-----"<<endl<<endl;
	user::seller_showmenu();
	return;

F1:	cout.fill('*');
	cout.width(80);
	cout << '*' << endl;
	cout << "订单ID" << "\t" << "商品ID" << "\t" << "交易单价" << "\t" << "数量" << "\t"
		<< "交易时间" << "\t" << "买家ID"<<endl;
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i].t_seller == u[k].u_id)
		{
			cout << t[i].t_id << "\t" << t[i].t_g_id << "\t" << t[i].t_price << "\t\t" << t[i].t_num
				<< "\t" <<t[i].t_time<<"\t" << t[i].t_buyer << endl;
		}
	}
	cout.fill('*');
	cout.width(80);
	cout << '*' << endl<<endl;
	user::seller_showmenu();
	return;
}

void order::buyer_t_show()
{
	int k = 0;
	for (; k < u.size(); k++)
	{
		if (u[k].login_state == 1)
			break;
	}
	//cout << u[k].u_name<<endl;
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i].t_buyer == u[k].u_id)
		{
			goto F2;
		}
	}
	cout << "-----未找到你已完成的订单信息！-----"<<endl<<endl;
	user::buyer_showmenu();
	return;

F2:	cout.fill('*');
	cout.width(80);
	cout << '*' << endl;
	cout << "订单ID" << "\t" << "商品ID" << "\t" << "交易单价" << "\t" << "数量" << "\t"
		<< "交易时间" << "\t" << "卖家ID"<<endl;
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i].t_buyer == u[k].u_id)
		{
			cout << t[i].t_id << "\t" << t[i].t_g_id << "\t" << t[i].t_price << "\t\t" << t[i].t_num
				<< "\t" << t[i].t_time << "\t" << t[i].t_seller << endl;
		}
	}
	cout.fill('*');
	cout.width(80);
	cout << '*' << endl << endl;
	user::buyer_showmenu();
	return;
}