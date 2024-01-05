#include<iostream>
#include"Goods.h"
#include<fstream>
#include<vector>
#include"tools.h"
#include<sstream>
#include"SQL.h"
#include<string>
#include"Calculator.h"
using namespace std;

static int totalgoods;
extern vector<user>u;

vector<goods>g;

string goods::g_rollid()
{	
	string id;
	int i = 0;
	stringstream s2;
	for (; i < g.size()+1; i++) {}
	s2 << i;
	string s = s2.str();
	if (i < 10)
	{
		id = "M00" + s;
	}
	else
		id = "M0" + s;
	return id;
}

void goods::getallgoods()
{
	g.clear();
	totalgoods = 0;
	fstream f("good.txt", ios::in | ios::out | ios::app);

	if (!f) { cerr << "fail"; return; }
	
	goods temp;
	while (f >> temp.g_id >> temp.g_name >> temp.g_price >> temp.g_num
		>> temp.g_des >> temp.g_uid >> temp.g_update_time >> temp.condition) {
		
		g.push_back(temp);
		//cout << temp.g_id;
		g[totalgoods].show_flag = false;
		totalgoods++;
	}

	//while (!f.eof()) {
	//	goods temp;
	//	f >> temp.g_id >> temp.g_name >> temp.g_price >> temp.g_num
	//		>> temp.g_des >> temp.g_uid >> temp.g_update_time >> temp.condition;
	//	g.push_back(temp);
	//	//cout << temp.g_id;
	//	g[totalgoods].show_flag = false;
	//	totalgoods++;
	//}
	//cout << g[0].g_id << endl;
	f.close();
}

istream& operator >>(istream& in, goods& goods)
{
	goods.g_id = goods::g_rollid();

U1:	cout << "请输入商品名称：";
	cin >> goods.g_name;
	if (goods.g_name.length() > 20)
	{
		cout << "商品名不能超过20个字符，请重新输入！";
		goto U1;
	}
	for (int j = 0; j < goods.g_name.length(); j++)
	{
		if (goods.g_name[j] < 65 || (goods.g_name[j] > 90 && goods.g_name[j] < 97) || goods.g_name[j]>122)
		{
			cout << endl << "商品名包含非英文字符，请重新输入！";
			goto U1;
		}
	}
	cout << endl << "请输入商品价格：";
	string money;
	bool money_flag = 1;
	//超过一位小数点要报错
	while (money_flag)
	{
		bool dot_flag = false;
		cin >> money;
		for (int j = 0; j < money.length(); j++)
		{
			if (money[j] == '.')
			{
				dot_flag = true;
				break;
			}
		}
		if (dot_flag)
		{
			int i = 0;
			for (; i < money.length(); i++)
			{
				//contains“.”
				if (i == money.length() - 1)
				{
					if (money[i] > '9' || money[i] < '0')
					{

						cout << "-----输入的金额有误，请重新输入-----" << endl;
						break;
					}
				}
				else if (i == money.length() - 2)
				{
					if (money[i] != '.' || ((money[i + 1] > '9' || money[i + 1] < '0')))
					{
						cout << "-----输入的金额有误，请重新输入-----" << endl;
						break;
					}
				}
				else
				{
					if (money[i] > '9' || money[i] < '0')
					{
						cout << "-----输入的金额有误，请重新输入-----" << endl;
						break;
					}
				}
			}
			if (i == money.length()) money_flag = 0;
		}
		if (!dot_flag)
			{
				int m = 0;
				for (; m < money.length(); m++)
				{
					if (money[m] > '9' || money[m] < '0')
					{
						cout << "-----输入的金额有误，请重新输入-----"<<endl;
						break;
					}
				}
				if (m == money.length()) money_flag = 0;
			}
	}
	goods.g_price = money;

	cout << endl << "请输入商品数量：";
	string num;
	
	bool num_flag = 1;
	while (num_flag)
	{	
		cin >> num;
		int p = 0;
		if (num[0] == '0')
		{
			cout<< "-----商品数量错误，请重新输入！-----" << endl;
			continue;
		}
		for (; p < num.length(); p++)
		{
			if (num[p] > '9' || num[p] < '0')
			{
				cout << "-----商品数量错误，请重新输入！-----"<<endl;
				break;
			}	
		}
		if (p == num.length()) num_flag = 0;
	}

	int n = atoi(num.c_str());//注意非法输入
	goods.g_num = n;
	
U4:	cout << endl << "请输入商品描述：";
	cin >> goods.g_des;
	if (goods.g_des.length() > 200)
	{
		cout << "商品描述不能超过200个字符，请重新输入！";
		goto U4;
	}
	goods.condition = "onsale";
	
	return in;
}

ostream& operator <<(ostream& out, goods& goods) {
	out << goods.g_id << " " << goods.g_name << " " << goods.g_price << " "
		<< goods.g_num << " " << goods.g_des << " " << goods.g_uid << " "
		<< goods.g_update_time << " " << goods.condition;
	return out;
}

void goods::g_show_head()
{
	cout << "商品ID" << "\t" << "名称" << "\t" << "价格" << "\t" << "上架时间" << "\t" << "卖家ID" << "\t"<<"数量"<<"\t"<<"商品状态" << endl;
}
//管理员
void goods::admin_g_show()
{
	if(g.size()==0)
	{
		cout << "-----暂时还没有商品信息-----" << endl<<endl;
		admin_showmenu();
	}
	else {
		cout.fill('*');
		cout.width(50);
		cout << '*' << endl;
		g_show_head();
		for (int i = 0; i < totalgoods; i++)
		{
			cout << g[i].g_id << "\t" << g[i].g_name << "\t" << g[i].g_price << "\t" << g[i].g_update_time << "\t" << g[i].g_uid << "\t"
				<< g[i].g_num << "\t";
			if (g[i].condition == "removed") { cout << "已下架" << endl; }
			else if (g[i].condition == "onsale") { cout << "销售中" << endl; }
			else cout << "状态异常" << endl;
		}
		cout.fill('*');
		cout.width(50);
		cout << '*' << endl;
		admin_showmenu();
	}
}

void goods::admin_g_search(string name)
{
	/*string name;
	cout << "请输入商品名称：";
	cin >> name;*/
	int len = name.length();
	int flag = 0;
	cout.fill('=');
	cout.width(80);
	cout << '=' << endl;

	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].g_name.length() >= len)
		{
			for (int j = 0; j < g[i].g_name.length() - len + 1; j++)
			{
				int m = 0;
				for (; m < len; m++)
				{
					if (g[i].g_name[j + m] != name[m])
						break;
				}
				if (m == len&&flag==0&&(!g[i].show_flag))
				{
					flag++;
					cout << "商品ID" << "\t" << "名称" << "\t" << "价格" << "\t" << "上架时间" << "\t" << "卖家ID"
						<< "\t" << "数量" << "\t" << "商品状态"<<endl;
					cout << g[i].g_id << "\t" << g[i].g_name << "\t" << g[i].g_price
						<< "\t" << g[i].g_update_time << "\t" << g[i].g_uid << "\t" << g[i].g_num << "\t";
					if (g[i].condition == "onsale")
						cout << "销售中" << endl;
					else if (g[i].condition == "removed")
						cout << "已下架" << endl;
					else cout << "状态异常" << endl;
					g[i].show_flag = true;
				}
				else if (m == len && flag > 0&& !(g[i].show_flag))
				{
					flag++;
					cout << g[i].g_id << "\t" << g[i].g_name << "\t" << g[i].g_price
						<< "\t" << g[i].g_update_time << "\t" << g[i].g_uid << "\t" << g[i].g_num << "\t";
					if (g[i].condition == "onsale")
						cout << "销售中" << endl;
					else if (g[i].condition == "removed")
						cout << "已下架" << endl;
					else cout << "状态异常" << endl;
					g[i].show_flag = true;
				}

			}


		}
	}
	for (int p = 0; p < g.size(); p++)
		g[p].show_flag = false;
	if (flag == 0)	cout << "没有找到您想要的商品！返回初始界面" << endl;
	cout.fill('=');
	cout.width(80);
	cout << '=' << endl;
	admin_showmenu();
}

void goods::admin_g_delete(string id,int i)
{
	/*cout << "请输入要下架的商品ID：";
	string id;
	cin >> id;*/
	switch (i)
	{
	case(1):
		for (int i = 0; i < g.size(); i++)
		{
			if (g[i].g_id == id)
			{
				g[i].condition = "removed";
				good_update();
			}
		}
		break;
	case(2):
		for (int i = 0; i < g.size(); i++)
		{
			if (g[i].g_id == id)
			{
				cout << endl << "确认要下架该商品吗？" << endl;
				cout.fill('*');
				cout.width(70);
				cout << '*' << endl;
				g_show_head();
				cout << g[i].g_id << "  " << g[i].g_name << "\t" << g[i].g_price << "\t" << g[i].g_update_time << "\t" << g[i].g_uid << "      "
					<< g[i].g_num << "      "<<g[i].condition<<endl;
				cout.fill('*');
				cout.width(70);
				cout << '*' << endl;
				cout << endl << "请选择(y/n)";
				string order;
				cin >> order;
				if (order == "y")
				{
					g[i].condition = "removed";
					good_update();
					cout << endl << "下架成功" << endl;
					admin_showmenu();
					return;
				}
				else if (order == "n")
				{
					cout << endl << "取消下架" << endl;
					admin_showmenu();
					return;
				}
				else {
					cout << endl << "指令有误" << endl;
					admin_showmenu();
					return;
				}
			}
		}
		cout << endl << "-----未找到输入的ID所对应的商品！-----" << endl << endl;
		admin_showmenu();
		return;
	}
}

void goods::admin_g_ban(string id)
{
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].g_uid == id)
				g[i].condition = "removed";	
	}
	good_update();
	return;
}

//卖家
void goods::g_update()
{
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	goods goods;
	//fstream io_file("good.txt", ios::in | ios::out | ios::app);
	goods.g_uid=u[i].u_id;
	goods.g_update_time = gettime();
	
	cin >> goods;//要判断商品输入是否正确

	cout << endl << endl << "请确认发布的商品信息无误！";
	cout << endl << "********************************";
	cout << endl << "商品名称：" << goods.g_name;
	cout << endl << "商品价格：" << goods.g_price;
	cout << endl << "商品数量：" << goods.g_num;
	cout << endl << "商品描述：" << goods.g_des;
	cout << endl << "********************************";
	cout << endl << endl << "您确认要发布商品吗？(y/n)";
	string judge;
	cin >> judge;
	if (judge == "n")
	{
		cout << endl << "取消发布成功！" << endl << endl;
		user::seller_showmenu();
	}
	else if (judge == "y")
	{//out << goods.g_id << " " << goods.g_name << " " << goods.g_price << " "
		//<< goods.g_num << " " << goods.g_des << " " << goods.g_uid << " "
			//<< goods.g_update_time << " " << goods.condition;
		string info = "INSERT INTO commodity VALUES (";
			
		string ginfo = goods.g_id + " " + goods.g_name + " " + goods.g_price + " " + to_string(goods.g_num) + " "
			+ goods.g_des + " " + goods.g_uid + " " + goods.g_update_time + " " + goods.condition;
		string getinfo = info + ginfo + ")";
		
		sql_seller(getinfo);
		//io_file << goods<<endl;
		
		cout << endl << "商品发布成功！" << endl << endl;
		getallgoods();
		user::seller_showmenu();
	}
	else {
		cout << endl << "-----指令错误！-----" << endl << endl;
		user::seller_showmenu();
	}
}

void goods::seller_g_show()
{
	//cout << g[0].g_id;
	int k = 0;
	for (; k < u.size(); k++)
	{
		if (u[k].login_state == 1)
			break;
	}
	for (int m = 0; m < g.size(); m++)
	{
		if (g[m].g_uid == u[k].u_id)
			goto F4;
	}
	cout << "-----未找到您发布的商品信息！即将返回卖家菜单-----" << endl;
	user::seller_showmenu();
	return;

F4:	cout.fill('*');
	cout.width(60);
	cout << '*' << endl;
	cout << "商品ID" << "\t" << "名称" << "\t" << "价格" << "\t" << "数量"<<"\t"<<"上架时间" << "\t" << "商品状态" << endl;

	for (int i = 0; i < g.size(); i++)
	{
		if(g[i].g_uid==u[k].u_id&&g[i].condition=="onsale")
		{ 
			cout << g[i].g_id << "\t" << g[i].g_name << "\t" << g[i].g_price << "\t" << g[i].g_num << "\t"<< g[i].g_update_time << "\t"<<"销售中"<<endl;
		}
		else if (g[i].g_uid == u[k].u_id && g[i].condition == "removed")
		{
			cout << g[i].g_id <<"\t"  << g[i].g_name << "\t" << g[i].g_price << "\t" << g[i].g_num << "\t" << g[i].g_update_time << "\t" << "已下架"<<endl;
		}
	}
	cout.fill('*');
	cout.width(60);
	cout << '*' << endl << endl;
	user::seller_showmenu();
}

void goods::seller_g_change()
{
	int k = 0;
	for (; k < u.size(); k++)
	{
		if (u[k].login_state == 1)
			break;
	}
	string id;
	cout << "请输入被修改商品的ID：";
	cin >> id;

	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].g_id == id && g[i].g_uid == u[k].u_id)
		{
			string order;
			cout << endl << "请输入被修改商品的属性（1.价格 2.描述）";
			getchar();
			cin >> order;
			if (order == "1" || order == "2")
			{
				string money;
				string des;
				if (order == "1") {
					cout << endl << "请输入被修改商品的价格：";
					bool money_flag = 1;
					//超过一位小数点要报错
					while (money_flag)
					{
						bool dot_flag = false;
						cin >> money;
						for (int j = 0; j < money.length(); j++)
						{
							if (money[j] == '.')
							{
								dot_flag = true;
								int i = 0;
								for (; i < money.length(); i++)
								{
									//contains“.”
									if (i == money.length() - 1)
									{
										if (money[i] > '9' || money[i] < '0')
										{

											cout << "-----输入的金额有误，请重新输入-----";
											break;
										}
									}
									else if (i == money.length() - 2)
									{
										if (money[i] != '.' || ((money[i + 1] > '9' || money[i + 1] < '0')))
										{
											cout << "-----输入的金额有误，请重新输入-----";
											break;
										}
									}
									else
									{
										if (money[i] > '9' || money[i] < '0')
										{
											cout << "-----输入的金额有误，请重新输入-----";
											break;
										}
									}
								}
								if (i == money.length()) money_flag = 0;
							}
							if (!dot_flag)
							{
								int m = 0;
								for (; m < money.length(); m++)
								{
									if (money[m] > '9' || money[m] < '0')
									{
										cout << "-----输入的金额有误，请重新输入-----";
										break;
									}
								}
								if (m == money.length()) money_flag = 0;
							}
						}
					}
				}
				else if (order == "2") {
					cout << endl << "请输入被修改商品的描述：";
					cin >> des;
				}
				if (order == "1") {
					cout << endl << "请确认修改的商品信息无误！";
					cout.fill('*');
					cout.width(40);
					cout << '*' << endl;
					cout << "商品ID：" << g[i].g_id << endl
						<< "商品名称：" << g[i].g_name << endl
						<< "商品价格：" << money << endl
						<< "商品描述：" << g[i].g_des << endl;
					cout.fill('*');
					cout.width(40);
					cout << '*' << endl;
				}
				else if(order=="2")
				{
					cout << endl << "请确认修改的商品信息无误！"<<endl;
					cout.fill('*');
					cout.width(40);
					cout << '*' << endl;
					cout << "商品ID：" << g[i].g_id << endl
						<< "商品名称：" << g[i].g_name << endl
						<< "商品价格：" << g[i].g_price << endl
						<< "商品描述：" << des << endl;
					cout.fill('*');
					cout.width(40);
					cout << '*' << endl;
				}
				string temp;
				cout << "确认修改？（y/n)";
				cin >> temp;
				if (temp == "y")
				{
					if (order == "1")
					{
						g[i].g_price = money;
						//good_update();
						string info = "UPDATE commodity SET gprice = ";
						string info2 = " WHERE gid = ";
						string getinfo = info + money + info2 + g[i].g_id;
						sql_seller(getinfo);
						user::seller_showmenu();
						return;
					}
					else {
						g[i].g_des = des;
						string info = "UPDATE commodity SET gdes = ";
						string info2 = " WHERE gid = ";
						string getinfo = info + des + info2 + g[i].g_id;
						sql_seller(getinfo);
						//good_update();
						user::seller_showmenu();
						return;
					}
				}
				else if (temp == "n")
				{
					cout << endl << "取消修改";
					user::seller_showmenu();
					return;
				}
				else {
					cout << endl << "指令有误";
					user::seller_showmenu();
					return;
				}
			}

			else {
				cout << endl << "-----指令错误！即将返回卖家菜单-----";
				user::seller_showmenu();
				return;
			}
		}
	}
	{
			cout << "-----未找到您权限范围内所输入ID对应的商品！即将返回卖家菜单-----";
			user::seller_showmenu();
			return;
	}
}

void goods::seller_g_delete()
{
	int k = 0;
	for (; k < u.size(); k++)
	{
		if (u[k].login_state == 1)
			break;
	}
	for (int m = 0; m < g.size(); m++)
	{
		if (g[m].g_uid == u[k].u_id)
			goto M5;
	}
	cout << "-----未找到您发布的商品信息！即将返回卖家菜单-----" << endl;
	user::seller_showmenu();
	return;

M5:	cout << "请输入要下架的商品ID：";
	string id;
	cin >> id;

	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].g_id == id&&g[i].g_uid==u[k].u_id&&g[i].condition=="onsale")
		{
			cout << endl << "确认要下架该商品吗？" << endl;
			cout.fill('*');
			cout.width(70);
			cout << '*' << endl;
			cout << "商品ID" << "\t" << "名称" << "\t\t" << "价格" << "\t" << "上架时间" << "\t" << "数量" << "\t" << "卖家ID" << "\t" << "商品状态" << endl;
			cout << g[i].g_id << "\t" << g[i].g_name << "\t\t" << g[i].g_price << "\t" << g[i].g_update_time << "\t" 
				<< g[i].g_num << "\t" << g[i].g_uid << "\t"<<"销售中"<<endl;
			
			cout.fill('*');
			cout.width(70);
			cout << '*' << endl;
			cout << endl << "确认要下架该商品吗？" << endl;
			cout << endl << "请选择(y/n)";
			string order;
			cin >> order;
			if (order == "y")
			{
				g[i].condition = "removed";
				//good_update();
				string info = "UPDATE commodity SET gcondition = removed WHERE gid = ";
				string info2 = info + g[i].g_id;
				sql_seller(info2);
				cout << endl << "下架成功"<<endl;
				user::seller_showmenu();
				return;
			}
			else if (order == "n")
			{
				cout << endl << "取消下架"<<endl;
				user::seller_showmenu();
				return;
			}
			else {
				cout << endl << "指令有误"<<endl;
				user::seller_showmenu();
				return;
			}
		}
	}
	cout << endl << "-----未找到输入的ID所对应的商品！-----" << endl << endl;
	user::seller_showmenu();
	return;
}
//买家
void goods::buyer_g_show()
{
	for (int m = 0; m < g.size(); m++)
	{
		if (g[m].condition == "onsale")
			goto F5;
	}
	cout << "-----未找到正在售卖的商品！即将返回买家菜单-----"<<endl;
	user::buyer_showmenu();
	return;

F5:	cout.fill('*');
	cout.width(60);
	cout << '*' << endl;
	cout << "商品ID" << "\t" << "名称" << "\t" << "价格" <<"\t"<<"数量" << "\t" << "上架时间" << "\t" << "商品状态" << endl;
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].condition == "onsale")
		{
			cout << g[i].g_id <<"\t"  << g[i].g_name << "\t" << g[i].g_price << "\t" << g[i].g_num << "\t" << g[i].g_update_time << "\t" << "销售中"<<endl;
		}
	}
	cout.fill('*');
	cout.width(60);
	cout << '*' << endl<<endl;
	user::buyer_showmenu();
}

void goods::buyer_g_buy()
{
	int k = 0;
	for (; k < u.size(); k++)
	{
		if (u[k].login_state == 1)
			break;
	}
	string id;
	cout << "请输入商品ID：";
	cin >> id;

	for(int i=0;i<g.size();i++)
	{
		if(g[i].g_id==id && g[i].g_uid==u[k].u_id)
		{
			cout << "-----不能购买自己的商品！即将返回买家菜单-----" << endl;
			user::buyer_showmenu();
			return;
		}

		else if (g[i].g_id == id)
		{
			string num;
			cout << endl << "请输入数量：";
			bool num_flag = 1;
			while (num_flag)
			{
				cin >> num;
				int p = 0;
				for (; p < num.length(); p++)
				{
					if (num[p] > '9' || num[p] < '0')
					{
						cout << "-----商品数量错误，请重新输入！-----" << endl;
						break;
					}
				}
				if (p == num.length()) num_flag = 0;
			}
			int n = atoi(num.c_str());
			float p = atof(g[i].g_price.c_str());

			cout.fill('*');
			cout.width(40);
			cout << '*' << endl;
			cout << "交易提醒！" << endl << "交易时间：" << gettime() << endl
				<< "交易单价：" << g[i].g_price << endl
				<< "交易数量：" <<n << endl;
			
			if (u[k].u_money >= p * n && g[i].g_num>=n)
			{
				string in_info1 = "INSERT INTO order VALUES (";
				string tid =order::t_rollid();
				string in_getinfo = in_info1 + tid + " " + g[i].g_id + " " + g[i].g_price + " "
					+ num + " " + gettime() + " " + g[i].g_uid + " " + u[k].u_id+")";

				g[i].g_num -= n;
				string up_info1 = "UPDATE commodity SET gnum = ";
				string gnum = to_string(g[i].g_num);
				string up_info2 = " WHERE gid = ";
				string up_getinfo = up_info1 + gnum + up_info2 + g[i].g_id;
				
				sql_buyer(in_getinfo);
				sql_buyer(up_getinfo);
				
				if (g[i].g_num == 0)
				{
					//UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = M001
					string re_info = "UPDATE commodity SET gcondition = removed WHERE gid = ";
					string re_getinfo = re_info + g[i].g_id;
					sql_buyer(re_getinfo);
				}

				string my_money = get_money();
				//cout << "表达式为 " << my_money<<endl;
				string final_money = calculate(my_money);
				//cout << "钱为：" << final_money << endl;
				u[k].u_money = atof(final_money.c_str());
				//u[k].u_money -= p * n;
				//cout << "金钱为" << u[k].u_money << endl;
				int m = user::user_find_s(g[i].g_uid);
				u[m].u_money += p * n;
				user_update();
				//user::getalluser();
				//u[k].login_state = 1;
				cout << "交易状态：交易成功" << endl << "您的余额：" << u[k].u_money << endl;

				//order::t_create(i, n, u[k].u_id);
				//user_update();
				//good_update();
				//order_update();
				cout.fill('*');
				cout.width(40);
				cout << '*' << endl<<endl;
				user::buyer_showmenu();
				return;
			}
			else if(u[k].u_money >= p * n && g[i].g_num < n){
				cout << "-----交易状态：交易失败，商品库存不足-----" << endl;
				cout.fill('*');
				cout.width(40);
				cout << '*' << endl << endl;
				user::buyer_showmenu();
				return;
			}
			else
			{
				cout << "-----交易状态：交易失败，您的钱包余额不足-----" << endl;
				cout.fill('*');
				cout.width(40);
				cout << '*' << endl << endl;
				user::buyer_showmenu();
				return;
			}
		}
	}
	cout << endl << "-----未找到所输入ID所对应的商品！即将返回买家菜单-----" << endl << endl;
	user::buyer_showmenu();
	return;
}

void goods::buyer_g_search(string name)
{
	/*string name;
	cout << "请输入商品名称：";
	cin >> name;*/
	int len = name.length();
	int flag = 0;
	cout.fill('=');
	cout.width(80);
	cout << '=' << endl;

	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].g_name.length() >= len &&g[i].condition=="onsale")
		{
			for (int j = 0; j < g[i].g_name.length() - len + 1; j++)
			{
				int m = 0;
				for (; m < len; m++)
				{
					if (g[i].g_name[j + m] != name[m])
						break;
				}
				if (m == len && flag == 0&&!(g[i].show_flag))
				{
					flag++;
					
					cout << "商品ID" << "\t" << "名称" << "\t" << "价格" << "\t" << "上架时间" << "\t" << "卖家ID"
						<< "\t" << "数量" << endl;
					cout << g[i].g_id << "\t" << g[i].g_name << "\t" << g[i].g_price
						<< "\t" << g[i].g_update_time << "\t" << g[i].g_uid << "\t" << g[i].g_num<<endl;
					g[i].show_flag = true;
				}
				else if (m == len && flag > 0&&!(g[i].show_flag))
				{
					flag++;
					cout << g[i].g_id << "\t" << g[i].g_name << "\t" << g[i].g_price
						<< "\t" << g[i].g_update_time << "\t" << g[i].g_uid << "\t" << g[i].g_num << endl;
					g[i].show_flag = true;
				}

			}


		}


	}
	for (int p = 0; p < g.size(); p++)
		g[p].show_flag = false;
	if (flag == 0)	cout << "没有找到您想要的商品！返回初始界面" << endl;
	cout.fill('=');
	cout.width(80);
	cout << '=' << endl;
	user::buyer_showmenu();
}

void goods::buyer_g_detail(string id)
{
	for (int m = 0; m < g.size(); m++)
	{
		if (g[m].condition == "onsale")
			goto F6;
	}
	cout << "-----未找到正在售卖的商品！即将返回买家菜单-----" << endl;
	user::buyer_showmenu();
	return;

F6:	/*string id;
	cout << "请输入您想要查看的商品ID：";
	cin >> id;*/
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].g_id == id&&g[i].condition=="onsale")
		{	
			cout << endl;
			cout.fill('*');
			cout.width(40);
			cout << '*' << endl;
			cout << "商品ID：" << g[i].g_id << endl
				<< "商品名称：" << g[i].g_name << endl
				<< "商品价格：" << g[i].g_price << endl
				<< "上架时间：" << g[i].g_update_time << endl
				<< "商品描述：" << g[i].g_des << endl
				<< "商品卖家：" << g[i].g_uid << endl;
			cout.fill('*');
			cout.width(40);
			cout << '*' << endl<<endl;
			user::buyer_showmenu();
			return;
		}
	}
	cout << endl << "-----未找到您权限范围内所输入ID对应的商品！-----" << endl << endl;
	user::buyer_showmenu();
	return;
}