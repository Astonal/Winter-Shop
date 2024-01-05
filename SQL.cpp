#include<iostream>
#include<fstream>
#include"SQL.h"
#include"tools.h"
using namespace std;
//#define DEBUG

void sql_admin(string s)
{
	//SELECT * FROM commodity
	//string order1 = "SELECT * FROM commodity WHERE gname CONTAINS " + name;
	//string order1 = "UPDATE commodity SET gcondition = removed WHERE gid = " + ID;
	//"SELECT * FROM order"
	//"SELECT * FROM user"
	//string order1 = "UPDATE commodity SET gcondition = removed WHERE guid = " + id;
	//string order2 = "UPDATE user SET ucondition = inactive WHERE uid = " + id;
	fstream file2("commands.txt", ios::in | ios::out | ios::app);
	if (!file2)
	{
		cerr << "打开文件失败！";
		return;
	}
	file2 <<gettime_detail()<<" "<< s << endl;
	file2.close();

	string order1 = "SELECT * FROM commodity";
	string order2 = "SELECT * FROM order";
	string order3 = "SELECT * FROM user";

	if(s[0]=='S')
	{ 
		if (s == order1)
		{
			goods::admin_g_show();
		}
		else if (s == order2)
		{
			order::admin_t_show();
		}
		else if (s == order3)
		{
			user::admin_u_show();
		}
		else 
		{
			string::size_type pos_commodity = s.find("commodity");
			if (pos_commodity != string::npos)
			{
				string::size_type pos1 = s.find("CONTAINS");
				string name = s.substr(pos1 + 9);
				goods::admin_g_search(name);
			}
			else { cout << "error occurs!" << endl; }
		}
	}
	else if (s[0] == 'U')
	{
		string::size_type g_pos = s.find("commodity");
		string::size_type u_pos = s.find("user");
		if (g_pos != string::npos)
		{
			string::size_type pos1 = s.find("gid");
			string::size_type pos2 = s.find("guid");

			if (pos1 != string::npos)
			{
				string gid = s.substr(pos1 + 6);
				goods::admin_g_delete(gid,2);
			}
			else if (pos2 != string::npos)
			{
				string guid = s.substr(pos2 + 7);
				goods::admin_g_ban(guid);
			}
			else {
				cout << "error occurs!" << endl;
			}
		}
		else if (u_pos != string::npos)
		{
			string::size_type pos3 = s.find("uid");
			if (pos3 != string::npos)
			{
				string uid = s.substr(pos3 + 6);
				user::admin_u_ban(uid);
			}
			else cout << "error occurs!" << endl;
		}
		else{ cout << "error occurs!" << endl; }
	}
	else {cout << "error occurs!" << endl;}
}

void sql_seller(string s)
{
	//cout << s<<endl;
	//INSERT INTO commodity VALUES (冬奥会纪念币, 10.0, 10, 冬奥会纪念品)
	//SELECT * FROM commodity
//UPDATE commodity SET 价格/描述 = 12.0 WHERE 商品ID = M001
	//UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = M001
	//SELECT * FROM order
	fstream file2("commands.txt", ios::in | ios::out | ios::app);
	if (!file2)
	{
		cerr << "打开文件失败！";
		return;
	}
	file2 << gettime_detail() << " " << s << endl;
	file2.close();

	string order1 = "SELECT * FROM commodity";
	string order2 = "SELECT * FROM order";

	if (s[0] == 'S')
	{
		if (s == order1)
		{
			goods::seller_g_show();
		}
		else if (s == order2)
		{
			order::seller_t_show();
		}
		else { cout << "error occurs!" << endl; }
	}
	else if (s[0] == 'U')
	{
		string::size_type price_pos = s.find("gprice");
		string::size_type des_pos = s.find("gdes");
		string::size_type con_pos = s.find("gcondition");
		if (price_pos != string::npos)
		{
			good_update();
		}
		else if (des_pos != string::npos)
		{
			good_update();
		}
		else if (con_pos != string::npos)
		{
			good_update();
		}
		else { cout << "error occurs!" << endl; }

	}
	else if (s[0] == 'I')
	{
		//out << goods.g_id << " " << goods.g_name << " " << goods.g_price << " "
		//<< goods.g_num << " " << goods.g_des << " " << goods.g_uid << " "
			//<< goods.g_update_time << " " << goods.condition;
		fstream io_file("good.txt", ios::in | ios::out | ios::app);
		if(!io_file)
		{
			cout << "openfile error!" << endl;
		}
		string::size_type flag_pos = s.find('(');
		string info = s.substr(flag_pos + 1);
		info.pop_back();
		io_file << info << endl;
		io_file.close();
	}
	else { cout << "error occurs!" << endl; }
}

void sql_buyer(string s)
{
#ifdef DEBUG
	cout << s << endl;
#endif 
	/*SELECT* FROM commodity
	INSERT INTO order VALUES (T001, M001, 10.0, 2, 2022 - 02 - 13, U002, U001)
		SELECT * FROM commodity WHERE 名称 CONTAINS 纪念币
		SELECT * FROM order
		SELECT * FROM commodity WHERE 商品ID CONTAINS M001*/
	fstream file2("commands.txt", ios::in | ios::out | ios::app);
	if (!file2)
	{
		cerr << "打开文件失败！";
		return;
	}
	file2 << gettime_detail() << " " << s << endl;
	file2.close();

	string order1 = "SELECT * FROM commodity";
	string order2 = "SELECT * FROM order";

	if (s[0] == 'S')
	{
		if (s == order1)
		{
			goods::buyer_g_show();
		}
		else if (s == order2)
		{
			order::buyer_t_show();
		}
		else {
			string::size_type g_pos = s.find("commodity");
			if(g_pos!=string::npos)
			{
				string::size_type id_pos = s.find("gid");
				string::size_type name_pos = s.find("gname");
				if (id_pos != string::npos)
				{
					string::size_type pos1 = s.find("CONTAINS");
					string id = s.substr(pos1 + 9);
#ifdef DEBUG
//cout << id << endl;
#endif // DEBUG
					goods::buyer_g_detail(id);
				}
				else if (name_pos != string::npos)
				{
					string::size_type pos1 = s.find("CONTAINS");
					string name = s.substr(pos1 + 9);
					goods::buyer_g_search(name);
				}
				else { cout << "error occurs1!" << endl; }
			}
			else { cout << "error occurs2!" << endl; }
		}
	}
	else if (s[0] == 'I')
	{
		//string in_getinfo = in_info1 + tid + " " + g[i].g_id + " " + g[i].g_price + " "
		//+num + " " + gettime() + " " + g[i].g_uid + " " + u[k].u_id + ")";
		string::size_type t_pos = s.find("order");
		if (t_pos != string::npos)
		{
			fstream f;
			f.open("order.txt", ios::in | ios::out | ios::app);
			if (!f) { cerr << "fail"; return; }

			string::size_type flag_pos = s.find('(');
			string info = s.substr(flag_pos + 1);
			info.pop_back();
			f << info << endl;
			f.close();
			order::getallorder();
		}
		else { cout << "error occurs3!" << endl; }
	}
	else if (s[0] == 'U')
	{
		string::size_type gnum_pos = s.find("gnum");
		string::size_type re_pos = s.find("removed");
		if (gnum_pos != string::npos)
			good_update();
		else if (re_pos != string::npos)
		{
			string gid = s.substr(re_pos + 20);
			goods::admin_g_delete(gid, 1);
		}
		else cout << "error occurs!!" << endl;
	}
	else { cout << "error occurs4!" << endl; }
}