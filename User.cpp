#include"User.h"
#include"Goods.h"
#include"Order.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include"SQL.h"
#include"tools.h"
#include"main.h"
using namespace std;
vector<message>me;
vector<mon>d;
vector<user> u;
static int totaluser;
static int totalmoney;
static int totalmessage;
extern vector<goods>g;

class user get_userid()
{
	for (int i = 0; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			return u[i];
	}
}
string user::u_rollid()
{
	string id;
	int i = 0;
	stringstream s1;
	for (; i < u.size()+1; i++) {}
	s1 << i;
	string s = s1.str();
	if (i < 10)
	{
		id = "U00"+s;
	}
	else
		id = "U0" + s;
	return id;
}

istream& operator >>(istream& in, user &user)
{
	user.u_id = user::u_rollid();
U1:	cout << "请输入用户名：";//检查用户名和密码
	cin >> user.u_name;
	if (user.u_name.length() > 10)
	{
		cout << "用户名不能超过十个字符，请重新输入！";
		goto U1;
	}
	for (int j = 0; j < user.u_name.length(); j++)
	{
		if (user.u_name[j] < 65 || (user.u_name[j] > 90 && user.u_name[j] < 97) || user.u_name[j]>122)
		{
			cout << endl << "用户名中包含非英文字符，请重新输入！";
			goto U1;
		}
	}
	for (int i = 0; i < u.size(); i++)
	{
		if (u[i].u_name == user.u_name)
		{
			cout << endl << "该用户名已被注册，请重新输入！";
			goto U1;
		}
	}
U2:	cout << endl << "请输入密码：";
	cin >> user.u_word;
	if (user.u_word.length() > 20)
	{
		cout << "密码不能超过二十个字符，请重新输入！";
		goto U2;
	}
	for (int j = 0; j < user.u_name.length(); j++)
	{
		if (user.u_name[j]<48||(user.u_name[j]>58&&user.u_name[j] < 97 )|| user.u_name[j]>122)
		{
			cout << endl << "密码中不能包含非小写英文和数字的字符，请重新输入！";
			goto U2;
		}
	}
U3:	cout << endl << "请输入电话号码：";
	cin >> user.u_num;
	if (user.u_num.length() > 20)
	{
		cout << "联系方式不能超过二十个字符，请重新输入！";
		goto U3;
	}
	for (int j = 0; j < user.u_num.length(); j++)
	{
		if (user.u_num[j] < 48 || user.u_num[j] > 58)
		{
			cout << endl << "联系方式中不能包含非数字的字符，请重新输入！";
			goto U3;
		}
	}
U4:	cout << endl << "请输入地址：";
	cin >> user.address;
	if (user.address.length() > 40)
	{
		cout << "地址不能超过四十个字符，请重新输入！";
		goto U4;
	}
	for (int j = 0; j < user.address.length(); j++)
	{
		if (user.address[j] < 65 || (user.address[j] > 90 && user.address[j] < 97) || user.address[j]>122)
		{
			cout << endl << "地址中不能包含非字母的字符，请重新输入！";
			goto U4;
		}
	}
	user.u_money = 0;
	user.u_state = "active";
	user.login_state = 0;
	cout << endl << "-----注册成功！-----"<<endl;
	return in;
}

ostream& operator <<(ostream& out, user& user)
{
	out << user.u_id << ' '
		<< user.u_name << ' '
		<< user.u_word << ' '
		<< user.u_num << ' '
		<< user.address << ' '
		<< user.u_money << ' '
		<< user.u_state;
	return out;
}
//整体user功能函数
void user::getalluser()//复制用户
{	
	/*cout << "创建后1"<<endl;
	cout << totaluser << endl;
	cout << u.size() << endl;*/
	u.clear();
	/*cout << "创建后(clear）" << endl;
	cout << totaluser << endl;
	cout << u.size() << endl;*/
	totaluser = 0;
	fstream f("user.txt", ios::in | ios::out | ios::app);
	if (!f) { cerr << "fail"; return; }
	/*char c;
	f >> c;
	if (f.eof())
	{
		f.close();
		return;
	}
	else */
	user temp;
	while (f >> temp.u_id >> temp.u_name >> temp.u_word >> temp.u_num
		>> temp.address >> temp.u_money >> temp.u_state) {
		//cout << "hey!";
		u.push_back(temp);
		u[totaluser].login_state = 0;
		totaluser++;
	}
	//cout <<"total user is :" << totaluser << endl;
	/*cout << "创建后2" << endl;
	cout << u.size() << endl;*/
	f.close();
}

void user::user_create()
{
	/*cout << "创建前" << endl;
	cout << totaluser<<endl;
	cout << u.size()<<endl;*/
	fstream io_file("user.txt", ios::in | ios::out | ios::app);
	
	if(!io_file)
	{
		cerr << "打开文件失败！";
		return;
	}
	user user;
	cin >> user;
	io_file << user << endl;
	io_file.close();
	getalluser();
	display();
}

int user::user_find(string id)
{
	for (int i = 0; i < totaluser; i++)
	{
		if (u[i].u_name == id)
			return i;
	}
	return -1;//not fuoud
}

int user::user_find_s(string id)
{
	for (int i = 0; i < totaluser; i++)
	{
		if (u[i].u_id == id)
			return i;
	}
	return -1;//not fuoud
}

bool user::user_login()
{
	string tempname;
	string tempword;
	cout << endl << "请输入用户名：";
	cin >> tempname;
	int a = user_find(tempname);
	if (a == -1)
	{
		cout << endl<<"-----该用户名不存在！即将返回主菜单-----"<<endl<<endl;
		//display();
		return false;
	}
	else if (u[a].u_state=="inactive")
	{
		cout << endl << "-----该用户已被封禁！即将返回主菜单-----" << endl << endl;
		return false;
	}
	else {
		cout << endl << "请输入密码：";
		cin >> tempword;
		if (tempword == u[a].u_word)
		{
			cout << endl << "-----登陆成功-----" << endl;
			//cout << "now is " << u[a].u_id << " loading.."<<endl;
			u[a].login_state = 1;
			return true;
			//user_mainmenu();
		}
		else {
			cout << endl << "-----密码错误，即将返回主菜单-----" << endl<<endl;
			return false;
			//display();
		}
	}
}

void user::user_logout()
{
	for (int i = 0; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
		{
			u[i].login_state = 0;
			//cout << "now is " << u[i].u_id << "logout";
			cout << "-----退出登录成功，即将返回主菜单-----" << endl<<endl;
			//display();
			return;
		}
	}
}

void user::user_mainmenu()
{
	while (1)
	{
		string order;
		cout << "============================================" << endl;
		cout << "1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录" << endl;
		cout << "============================================" << endl << endl;
		cout << "请输入操作：";
		cin >> order;
		if (order == "1")
		{
			user::buyer_showmenu();
			break;
		}
		else if (order == "2")
		{
			user::seller_showmenu(); 
			break;
		}
		else if (order == "3")
		{
			user::user_info_menu();
			break;
		}
		else if (order == "4")
		{
			user::user_logout();
			display();
			break;
		}
		else { cout << "-----输入指令有误，请重新输入-----"<<endl; }
	}
}

//seller功能函数
void user::seller_showmenu()
{
	while (1)
	{
		string order;
		cout << "================================================================================================" << endl;
		cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面 7.查看商品留言 " << endl;
		cout << "================================================================================================" << endl << endl;
		cout << "请输入操作：";
		cin >> order;
		if (order == "1")
		{
			goods::g_update();//内含类sql调用
			break;
		}
		else if(order=="2")
		{ 
			sql_seller("SELECT * FROM commodity");
			//goods::seller_g_show();
			break;
		}
		else if (order == "3")
		{

			goods::seller_g_change();//sql inside
			break;
		}
		else if (order == "4")
		{
			goods::seller_g_delete();//sql inside
			break;
		}
		else if (order == "5")
		{
			sql_seller("SELECT * FROM order");
			//order::seller_t_show();
			break;
		}
		else if (order == "6")
		{
			user::user_mainmenu();
			break;
		}
		else if (order == "7")
		{
			user::seller_message_mainmenu();
			break;
		}
		else
		{
			cout << "-----指令有误，请重新输入-----"<<endl << endl;
		}
	}
}

//buyer功能函数
void user::buyer_showmenu()
{
	while (1)
	{
		string order;
		cout.fill('=');
		cout.width(100);
		cout << '=' << endl;
		cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面 7.查看商品留言" << endl;
		cout.fill('=');
		cout.width(100);
		cout << '=' << endl;
		cin >> order;
		if (order == "1")
		{
			//goods::buyer_g_show();
			sql_buyer("SELECT * FROM commodity");
			break;
		}
		else if (order == "2")
		{
			goods::buyer_g_buy();//sql inside
			break;
		}
		else if (order == "3")
		{
			string name;
			cout << "请输入商品名称：";
			cin >> name;
			string order = "SELECT * FROM commodity WHERE gname CONTAINS " + name;
			sql_buyer(order);
			//goods::buyer_g_search();
			break;
		}
		else if (order == "4")
		{
			sql_buyer("SELECT * FROM order");
			//order::buyer_t_show(); 
			break;
		}
		else if (order == "5")
		{
			string gid;
			cout << "请输入要查看的商品ID：";
			cin >> gid;
			string order = "SELECT * FROM commodity WHERE gid CONTAINS " + gid;
			sql_buyer(order);
			//goods::buyer_g_detail();
			break;
		}
		else if (order == "6")
		{
			user::user_mainmenu();
			break;
		}
		else if (order == "7")
		{
			user::buyer_message_mainmenu();
			break;
		}
		else { cout << "-----指令有误，请重新输入-----" << endl << endl; }
	}
}

//个人信息函数
void user::user_info_menu()
{
	while (1)
	{
		string order;
		cout.fill('=');
		cout.width(40);
		cout << "=" << endl;
		cout << "1.查看信息 2.修改信息 3.充值 4.返回用户主界面" << endl;
		cout.fill('=');
		cout.width(40);
		cout << "=" << endl;
		cout << endl << "请输入操作：";
		cin >> order;
		getchar();
		if (order == "1")
		{
			user::user_info_show();
			break;
		}
		else if (order == "2")
		{
			user::user_info_change();
			break;
		}
		else if (order == "3")
		{
			user::user_money_add();
			break;
		}
		else if (order == "4")
		{
			user::user_mainmenu();
			break;
		}
		else { cout << "-----指令有误，请重新输入-----"<<endl<<endl; }
	}
}

void user::user_info_show()
{
	//cout << "total user is(info ver):" << totaluser << endl;
	//cout << "u.size is" << u.size() << endl;
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
		{
			//cout << "now login is u[" << i << "]" << endl;
			break;
		}
	}
	cout.fill('*');
	cout.width(25);
	cout << "*" << endl;
	cout << "用户名：" << u[i].u_name<<endl;
	cout << "联系方式：" << u[i].u_num << endl;
	cout << "地址：" << u[i].address << endl;
	cout << "钱包余额：" << u[i].u_money << endl;
	cout.fill('*');
	cout.width(25);
	cout << "*" << endl<<endl;

	user_info_menu();
}

void user::user_money_add()
{
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	string money;
	bool dot_flag = false;
	cout << "请输入充值金额（一位小数）：";
	cin >> money;
	for (int j = 0; j < money.length(); j++)
	{
		if (money[j] == '.')
		{
			dot_flag = true;
			for (int i = 0; i < money.length(); i++)
			{
				//contains“.”
				if (i == money.length() - 1)
				{
					if (money[i] > '9' || money[i] < '0')
					{
						cout << "-----输入的金额有误，即将返回个人信息菜单-----"<<endl;
						user_info_menu();
						return;
					}
				}
				else if (i == money.length() - 2)
				{
					if (money[i] != '.' || ((money[i + 1] > '9' || money[i + 1] < '0')))
					{
						cout << "-----输入的金额有误，即将返回个人信息菜单-----"<<endl;
						user_info_menu();
						return;
					}
				}
				else
				{
					if (money[i] > '9' || money[i] < '0')
					{
						cout << "-----输入的金额有误，即将返回个人信息菜单-----"<<endl;
						user_info_menu();
						return;
					}
				}
			}
		}
	}	
	if (!dot_flag)
	{
		for (int m = 0; m < money.length(); m++)
		{
			if (money[m] > '9' || money[m] < '0')
			{
				cout << "-----输入的金额有误，即将返回个人信息菜单-----"<<endl;
				user_info_menu();
				return;
			}
		}
	}
	float n = atof(money.c_str());
	//cout << u[i].u_id;
	money_create(money, u[i].u_id);
	
	u[i].u_money += n;//要判断是否合乎标准
	cout << endl << "充值成功，当前余额：" << u[i].u_money;
	cout << endl << endl;
	user_update();
	user_info_menu();
}

void user::user_info_change()
{
	cout << "请选择修改的属性（1.用户名 2.联系方式 3.地址）：";
	
	string order;//getchar();
	cin >> order;
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	if (order == "1")
	{
		user_name_change(i);
		cout << endl;
		user_info_menu();
	}
	else if (order == "2")
	{
		user_num_change(i);
		cout << endl;
		user_info_menu();
	}
	else if (order == "3")
	{
		user_add_change(i);
		cout << endl;
		user_info_menu();
	}
	else {
		cout << endl << "-----输入的指令有误！即将返回个人信息菜单-----"<<endl<<endl;
		user_info_menu();
	}
}

void user::user_name_change(int i)
{
U2:	cout << endl << "请输入修改后的用户名：";
	string name;
	cin >> name;
	
	if (name.length() > 10)
	{
		cout << "用户名不能超过十个字符，请重新输入！";
		goto U2;
	}
	for (int j = 0; j < name.length(); j++)
	{
		if (name[j] < 65 || (name[j] > 90 && name[j] < 97) || name[j]>122)
		{
			cout << endl << "用户名中包含非英文字符，请重新输入！";
			goto U2;
		}
	}

	for (int i = 0; i < u.size(); i++)
	{
		if (u[i].u_name == name)
		{
			cout << endl << "该用户名已被注册，请重新输入！";
			goto U2;
		}
	}
	u[i].u_name = name;
	user_update();
}

void user::user_add_change(int i)
{
	cout << endl << "请输入修改后的地址：";
	string add;
U4:	cin >> add;
	if (add.length() > 40)
	{
		cout << "地址不能超过四十个字符，请重新输入！";
		goto U4;
	}
	for (int j = 0; j < add.length(); j++)
	{
		if (add[j] < 65 || (add[j] > 90 && add[j] < 97) || add[j]>122)
		{
			cout << endl << "地址中不能包含非字母的字符，请重新输入！";
			goto U4;
		}
	}
	u[i].address = add;
	user_update();
}

void user::user_num_change(int i)
{
	cout << endl << "请输入修改后的联系方式：";
	string num;
U3: cin >> num;
	if (num.length() > 20)
	{
		cout << "联系方式不能超过二十个字符，请重新输入！";
		goto U3;
	}
	for (int j = 0; j < num.length(); j++)
	{
		if (num[j] < 48 || num[j] > 58)
		{
			cout << endl << "联系方式中不能包含非数字的字符，请重新输入！";
			goto U3;
		}
	}
	u[i].u_num = num;
	user_update();
}

//管理员管理函数
void user::u_showhead()
{
	cout << "用户ID" << "\t" << "用户名" << "\t" << "联系方式" << "\t" << "地址" << "\t\t" << "钱包余额" << "\t" << "用户状态" << endl;
}

void user::admin_u_show()
{
	if(u.size()==0)
	{
		cout << "-----暂时没有已注册的用户-----"<<endl<<endl;
		admin_showmenu();
	}
	else {
		cout.fill('*');
		cout.width(70);
		cout << '*' << endl;
		u_showhead();
		for (int i = 0; i < u.size(); i++)
		{
			cout << u[i].u_id << "\t" << u[i].u_name << "\t" << u[i].u_num << "\t\t" << u[i].address << "\t\t"<<u[i].u_money<<"\t\t";
			if (u[i].u_state == "inactive")
			{
				cout << "封禁" << endl;
			}
			else if (u[i].u_state == "active")
			{
				cout << "正常" << endl;
			}
			else
			{
				cout << "状态异常" << endl;
			}
		}
		cout.fill('*');
		cout.width(70);
		cout << '*' << endl<<endl;
		admin_showmenu();
	}
}

void user::admin_u_ban(string id)
{
	/*cout << "请输入要封禁的用户ID：";
	string id;
	cin >> id;*/

	for (int i = 0; i < u.size(); i++)
	{
		if (u[i].u_id == id)
		{
			if (u[i].u_state == "inactive")
			{
				cout << endl << "不可重复封禁用户！" << endl;
				admin_showmenu();
				return;
			}
			else {
				cout << endl << "确认要封禁该用户吗？" << endl;
				cout.fill('*');
				cout.width(70);
				cout << '*' << endl;

				cout << "用户ID" << "\t" << "用户名" << "\t" << "联系方式" << "\t" << "地址" << "\t\t" << "钱包余额" << endl;
				cout << u[i].u_id << "\t" << u[i].u_name << "\t" << u[i].u_num << "\t" << u[i].address << "\t\t" << u[i].u_money<<endl;

				cout.fill('*');
				cout.width(70);
				cout << '*' << endl;
				cout << endl << "请选择(y/n)";
				string order;
				cin >> order;
				if (order == "y")
				{
					cout << endl << "封禁成功" << endl;
					admin_showmenu();
					//数组里的
					u[i].u_state = "inactive";
					//修改文档里的内容
					user_update();
					return;
				}
				else if (order == "n")
				{
					cout << endl << "取消封禁" << endl;
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
	}
	cout << endl << "未找到输入的ID所对应的用户！"<<endl<<endl;
	admin_showmenu();
	return;
}

//金钱订单函数
void user::money_create(string money,string id)
{
	fstream io_file("moneyorder.txt", ios::in | ios::out | ios::app);

	if (!io_file)
	{
		cerr << "打开文件失败！";
		return;
	}
	mon temp;
	temp.id = id;
	temp.dollar = money;
	io_file << temp.id<<" "<<temp.dollar << endl;
	io_file.close();
	getallmoney();
}

void user::getallmoney()
{
	d.clear();
	
	totalmoney = 0;
	fstream f("moneyorder.txt", ios::in | ios::out | ios::app);
	if (!f) { cerr << "fail"; return; }
	
	mon temp;
	while (f >> temp.id>>temp.dollar) {
		//cout << "hey!";
		d.push_back(temp);
		totalmoney++;
	}
	f.close();
}

//留言订单函数
void user::seller_message_mainmenu()
{
	while (1)
	{
		string order;
		cout << "===========================================================" << endl;
		cout << "1.查看收到的留言 2.查看发出的留言 3.发布留言 4.返回卖家界面" << endl;
		cout << "===========================================================" << endl << endl;
		cout << "请输入操作：";
		cin >> order;
		if (order == "1")
		{
			user::seller_message_receive();
			break;
		}
		else if (order == "2")
		{
			user::seller_message_sendcheck();
			break;
		}
		else if (order == "3")
		{
			user::seller_message_send();
			break;
		}
		else if (order == "4")
		{
			user::seller_showmenu();
			break;
		}
		else { cout << "-----输入指令有误，请重新输入-----" << endl; }
	}


}

void user::buyer_message_mainmenu()
{
	while (1)
	{
		string order;
		cout << "==========================================================" << endl;
		cout << "1.查看收到的留言 2.查看发出的留言 3.发布留言 4.返回买家界面" << endl;
		cout << "==========================================================" << endl << endl;
		cout << "请输入操作：";
		cin >> order;
		if (order == "1")
		{
			user::buyer_message_receive();
			break;
		}
		else if (order == "2")
		{
			user::buyer_message_sendcheck();
			break;
		}
		else if (order == "3")
		{
			user::buyer_message_send();
			break;
		}
		else if (order == "4")
		{
			user::buyer_showmenu();
			break;
		}
		else { cout << "-----输入指令有误，请重新输入-----" << endl; }
	}


}

void user::message_create(string from,string to,string time,string goodid,string info)
{
	fstream io_file("message.txt", ios::in | ios::out | ios::app);

	if (!io_file)
	{
		cerr << "打开文件失败！";
		return;
	}
	message temp;
	temp.from = from;
	temp.to = to;
	temp.time = time;
	temp.goodid = goodid;
	temp.info = info;
	io_file << temp.from << " " << temp.to <<" "<<temp.time<<" " << temp.goodid << " " << temp.info << endl;
	io_file.close();
	getallmessage();
}

void user::getallmessage()
{
	me.clear();

	totalmessage = 0;
	fstream f("message.txt", ios::in | ios::out | ios::app);
	if (!f) { cerr << "fail"; return; }

	message temp;
	while (f >> temp.from >>temp.to>>temp.time>>temp.goodid>>temp.info) {
		//cout << "hey!";
		me.push_back(temp);
		totalmessage++;
	}
	f.close();
}

void user::seller_message_receive()
{
	int i = 0;
	
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	
	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].to == u[i].u_id)
		{
			goto M1;
		}
	}
	cout << "未找到给您的商品留言" << endl;
	user::seller_message_mainmenu();
	return;

M1: cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	cout << "商品ID" << "\t" << "留言ID" << "\t" <<"留言时间"<<"\t" << "留言内容" << "\t" << endl;
//#define DEBUG
#ifdef DEBUG
	for (int q = 0; q < me.size(); q++)
	{
		cout <<"about info：："<<q<<"   goodid:  " << me[q].goodid << " from :  " << me[q].from << " to: " << me[q].to << "timeis:  " << me[q].time << " " << me[q].info << endl;
	}
#endif // DEBUG

	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].to == u[i].u_id)
		{
			cout << me[j].goodid << "\t" << me[j].from <<"\t"<<me[j].time << "\t" << me[j].info << endl;
		}
	}
	cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	user::seller_message_mainmenu();
}

void user::buyer_message_receive()
{
	int i = 0;

	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}

	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].to == u[i].u_id)
		{
			goto M1;
		}
	}
	cout << "未找到给您的商品留言" << endl;
	user::buyer_message_mainmenu();
	return;

M1: cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	cout << "商品ID" << "\t" << "留言ID" << "\t" <<"留言时间"<<"\t" << "留言内容" << "\t" << endl;
	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].to == u[i].u_id)
		{
			cout << me[j].goodid << "\t" << me[j].from << "\t"<<me[j].time<<"\t" << me[j].info << endl;
		}
	}
	cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	user::buyer_message_mainmenu();
}

void user::seller_message_sendcheck()
{
	int i = 0;

	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}

	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].from == u[i].u_id)
		{
			goto M1;
		}
	}
	cout << "未找到您发出的商品留言" << endl;
	user::seller_message_mainmenu();
	return;

M1: cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	cout << "商品ID" << "\t" << "留言ID" << "\t" << "留言时间" << "\t" << "留言内容" << "\t" << endl;
	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].from == u[i].u_id)
		{
			cout << me[j].goodid << "\t" << me[j].to << "\t" << me[j].time << "\t" << me[j].info << endl;
		}
	}
	cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	user::seller_message_mainmenu();
}

void user::buyer_message_sendcheck()
{
	int i = 0;

	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}

	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].from == u[i].u_id)
		{
			goto M1;
		}
	}
	cout << "未找到您发出的商品留言" << endl;
	user::buyer_message_mainmenu();
	return;

M1: cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	cout << "商品ID" << "\t" << "留言ID" << "\t" << "留言时间" << "\t" << "留言内容" << "\t" << endl;
	for (int j = 0; j < me.size(); j++)
	{
		if (me[j].from == u[i].u_id)
		{
			cout << me[j].goodid << "\t" << me[j].to << "\t" << me[j].time << "\t" << me[j].info << endl;
		}
	}
	cout.fill('*');
	cout.width(50);
	cout << '*' << endl;
	user::buyer_message_mainmenu();
}

void user::seller_message_send()
{
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	string time = gettime();
	string info;
	string id;
	string buyer;
	string seller = u[i].u_id;
	cout << "请输入您要发送信息的买家ID：" << endl;
	while (1)
	{
		cin >> buyer;
		int a = user_find_s(buyer);
		if (buyer == "end")
		{
			user::seller_message_mainmenu();
			return;
		}
		else if (buyer == u[i].u_id)
		{
			cout << "-----不可以给自己留言哦！请重新输入（输入end以中止留言）-----" << endl;
		}
		else if (a == -1)
		{
			cout << "-----未找到有该用户存在！请重新输入（输入end以中止留言）-----" << endl;
		}
		else if (a != -1 )
		{
			break;
		}
		
	}
	cout << "请输入您要留言商品的商品ID：" << endl;
	while (1)
	{
		int flag = 0;
		cin >>id;
		int m = 0;
		for (; m < g.size(); m++)
		{
			if (g[m].g_id == id&&g[m].g_uid==u[i].u_id&&g[m].condition=="onsale")
			{
				flag = 1;
				break;
			}
		}
		if (id == "end")
		{
			user::seller_message_mainmenu();
			return;
		}
		if (flag == 0)
		{
			cout << "-----未找到有该商品存在！请重新输入（输入end以中止留言）-----" << endl;
		}
		if (flag == 1)
		{
			break;
		}
	}
	cout << "请输入您要留言的内容：" << endl;
	cin >> info;
	message_create(seller, buyer,time, id, info);
	cout << "留言发布成功！" << endl;
	user::seller_message_mainmenu();
}

void user::buyer_message_send()
{
	int i = 0;
	for (; i < u.size(); i++)
	{
		if (u[i].login_state == 1)
			break;
	}
	string time = gettime();
	string info;
	string id;
	string seller;
	string buyer = u[i].u_id;
	cout << "请输入您要发送信息的卖家ID：" << endl;
	while (1)
	{
		cin >> seller;
		int a = user_find_s(seller);
		if (seller == "end")
		{
			user::buyer_message_mainmenu();
			return;
		}
		else if (seller == u[i].u_id)
		{
			cout << "-----不可以给自己留言哦！请重新输入（输入end以中止留言）-----" << endl;
		}
		else if (a == -1)
		{
			cout << "-----未找到有该用户存在！请重新输入（输入end以中止留言）-----" << endl;
		}
		else if (a != -1)
		{
			break;
		}
	}
	cout << "请输入您要留言商品的商品ID：" << endl;
	while (1)
	{
		int flag = 0;
		cin >> id;
		int m = 0;
		for (; m < g.size(); m++)
		{
			if (g[m].g_id == id&&g[m].condition=="onsale")
			{
				flag = 1;
				break;
			}
		}
		if (id == "end")
		{
			user::buyer_message_mainmenu();
			return;
		}
		if (flag == 0)
		{
			cout << "-----未找到有该商品存在！请重新输入（输入end以中止留言）-----" << endl;
		}
		if (flag == 1)
		{
			break;
		}
	}
	cout << "请输入您要留言的内容：" << endl;
	cin >> info;
	message_create(buyer, seller, time,id, info);
	cout << "留言发布成功！" << endl;
	user::buyer_message_mainmenu();
}