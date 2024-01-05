#include"Calculator.h"
#include<iostream>
#include"Goods.h"
#include"Order.h"
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

vector<char> v;
vector<char> work;
vector<char> p;
vector<string> st;

int num_of_num = 0;
int num_of_op = 0;

int priority(char op)
{
	switch (op)
	{
	case'(':
		return 3;
	case'*':
	case'/':
		return 2;
	case'+':
	case'-':
		return 1;
	case')':
		return 4;
	case' ':
		return 0;
	default:
		return -1;
	}
}

bool judge_dot(string s)
{
	string m = s;
	eat_space(m);
	if (m.size() >= 4)
	{
		for (int i = 3; i < m.size(); i++)
		{
			if (m[i] >= 48 && m[i] <= 57 && m[i - 2] == '.')
			{
				cout << "小数位数大于1" << endl;
				return false;
			}
		}
	}


	return true;
}

bool judge_bra(string s)
{
	string m = s;
	eat_space(m);
	//cout << m << endl;
	int left_num = 0;
	int right_num = 0;
	//0.右括号比左括号早出现
	//1.数量不对等
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i] == '(')
			left_num++;
		if (m[i] == ')')
			right_num++;
		if (right_num > left_num)
		{
			cout << "圆括号不匹配" << endl;
			return false;
		}
	}
	if (left_num != right_num)
	{
		cout << "圆括号不匹配"<<endl;
		return false;
	}
	//2.空括号//3.只有带+的正整数的括号
	for (int i = 0; i < m.size()-1; i++)
	{
		if (m[i] == '(' && (m[i + 1] == ')'||m[i+1]=='+'))
		{
			cout << "圆括号使用有误1" << endl;
			return false;
		}
	}
	//3.2 数字和括号中间必须有符号   注意左括号和右括号
	if(m[0]>=48&&m[0]<=57&&m[1]=='(')
	{
		cout << "圆括号使用有误2" << endl;
		return false;
	}
	if(m[m.size()-2]==')'&&m[m.size()-1]>=48&&m[m.size()-1]<=57)
	{
		cout << "圆括号使用有误3" << endl;
		return false;
	}
	for (int i = 1; i < m.size() - 1; i++)
	{
		if(m[i+1]=='('&&m[i]>=48&&m[i]<=57)
		{
			cout << "圆括号使用有误4" << endl;
			return false;
		}
		if(m[i-1]==')'&&m[i]>=48&&m[i]<=57)
		{
			cout << "圆括号使用有误5" << endl;
			return false;
		}
	}
	//4.全是正整数或小数的括号
	int i = 0;
	int last_left = 0;
	int last_right = 0;
	while (i < m.size())
	{
		if (m[i] == '(')
		{
			last_left = i;
		}
		if (m[i] == ')')
		{
			last_right = i;
		}
		if (last_left < last_right)
		{
			int k = last_left + 1;
			for (; k < last_right; k++)
			{
				if ((m[k] < 48 || m[k]>57) && m[k] != '.')
					break;
			}
			if(k==last_right)
			{
				cout << "圆括号使用有误6" << endl;
				return false;
			}
		}
		i++;
	}

  return true;
}

bool judge_minus(string s)//判断负号和减号的差别
{
	string m = s;
	eat_space(m);
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i] == '-' && m[i + 1] == '-')
		{
			cout << "操作符误用"<<endl;
			return false;
		}
	}
	if (m[0] == '-')
		num_of_op -= 1;
	for (int i = 1; i < m.size(); i++)
	{
		if (m[i] == '-' && (m[i - 1] > 57 || m[i - 1] < 48))
			num_of_op -= 1;
	}
	return true;
}

bool judge_num(string s)//传入之前
{
	//cout << "num_of_op is:" << num_of_op<<endl;
	int num_flag = 0;
	int dot_flag = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 48 && s[i] <= 57)
		{
			num_of_num += 1;
			num_flag = 1;
		}
		while (num_flag == 1)
		{
			i++;
			if (s[i] == '.')
			{
				dot_flag++;
			}
			if ((priority(s[i]) >= 1 && priority(s[i]) <= 2))
			{
				//num_of_op += 1;
				break;
			}
			if (s[i] == ')')
			{
				break;
			}
			if ((s[i] > 57 || s[i] < 48) && s[i] != '.')//换言之，是空格
			{
				num_flag = 2;
			}
		}
		if (dot_flag > 1)
		{
			cout << "数字格式有误1"<<endl;//一个数内有多个小数点！
			return false;
		}
		if (i == s.size())
			break;//表明读到了 '\0'
		while (num_flag == 2)
		{
			if (dot_flag == 1)
			{
				cout << "数字格式有误2" << endl;
				num_of_num = 0;
				num_of_op = 0;
				return false;
			}
			i++;
			if (s[i] != ' ' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/')
			{
				//cout << s[i] << " " << i << endl;
				cout << "数字格式有误2" << endl;
				num_of_num = 0;
				num_of_op = 0;
				return false;
			}
			if (priority(s[i]) >= 1 && priority(s[i]) <= 2)
			{
				//num_of_op += 1;
				break;
			}
		}
		
		if (priority(s[i]) >= 1 && priority(s[i]) <= 2)
			num_of_op+=1;
		
		num_flag = 0;
		dot_flag = 0;
	}
	
	//单独检测小数点后没有跟数字
	for (int j = 0; j < s.size() - 1; j++)
	{
		if (s[j] == '.' && priority(s[j + 1]) >= 1 && priority(s[j + 1]) <= 2)
		{
			cout << "数字格式有误" << endl;
			num_of_num = 0;
			num_of_op = 0;
			return false;
		}
	}
	//单独监测操作符数量误用
	if (num_of_num - num_of_op == 1)
	{
	//	cout << "num is" << num_of_num << "  and op is" << num_of_op;
		num_of_num = 0;
		num_of_op = 0;
		return true;
	}
	else {
	//	cout <<"num is" <<num_of_num << "  and op is" << num_of_op;
		num_of_num = 0;
		num_of_op = 0;
		cout << "操作符误用" << endl;
		return false;
	}
}

void eat_space(string &s)   //处理掉空格
{
	while (1)
	{
		string::size_type pos = s.find(" ");
		if (pos != string::npos)
		{
			s.erase(pos,1);
		}
		else {
			break;
		}
	}
	//cout << "now is" << s;
}

void start_cal(string s) //压入起初表达式
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		v.push_back(s[i]);
	}
}

void process_cal()  //整
{
	int length = v.size();
	for (int i = 0; i < length; i++)
	{ 
		if (v[i] == ' ') { work.push_back(' '); }
		else if ((v[i] >= 48 && v[i] <= 57) || v[i] == '.')
		{
			work.push_back(v[i]);
		}
		else if (v[i] == ')')
		{
//#define DEBUG
#ifdef DEBUG
			for (int m = 0; m < p.size(); m++) { cout << p[m]<<endl; }
			cout << endl<<endl;
			for (int n = 0; n < work.size(); n++) { cout << work[n]<<endl; }
#endif // DEBUG
			work.push_back(' ');
			while (p[p.size() - 1] != '(')
			{
				char a = p[p.size() - 1];
				//cout << "what i put just now is" << a << endl;
				p.pop_back();
				work.push_back(a);
				work.push_back(' ');
			}
			if (p[p.size() - 1] == '(')
			{
				p.pop_back();
			}
		}
		else {
			work.push_back(' ');
			if (v[i] == '(')//   (
			{
				p.push_back(v[i]);
			}
			else if (p.size() == 0)
			{
				p.push_back(v[i]);
			}
			else if (priority(v[i]) >= 1 && priority(v[i] <= 3))//运算符
			{
				//cout << p.size();
				if (priority(v[i]) > priority(p[p.size() - 1]))
				{
					p.push_back(v[i]);
				}
				else
				{
						while (priority(v[i]) <= priority(p[p.size() - 1]))
						{
							if (p[p.size() - 1] == '(')
							{
								break;
							}
							else {
								char a = p[p.size() - 1];
								work.push_back(a);
								work.push_back(' ');
								p.pop_back();
							}

							if (p.size() == 0)break;

						}
						p.push_back(v[i]);
				}
				
			}
			
		}
	}

	while(p.size()>0)
	{
		char a = p[p.size()-1];
		work.push_back(' ');
		work.push_back(a);
		p.pop_back();
	}

}

void output_work()  //展示
{
	for (int i = 0; i < work.size(); i++)
	{
		cout << work[i];
	}
	cout << endl;
}

void process_minus(string &s)  //整负数
{
	string cal = s;
	//cout << cal<<endl;
	if (cal[0] == '-')
		cal.insert(cal.begin(), '0');
	for (int i = 1; i < cal.size(); i++)
	{
		if (cal[i] == '-' && (cal[i - 1] > 57 || cal[i - 1] < 48)&&cal[i-1]!=')')
		{
			cal.insert(cal.begin()+i, '0');
		}
	}

	s=cal;

}

void postfix_cal()  //后缀
{
	int length = work.size();
	string num;
	string backup;
	int j = 0;
	for (; j < length; j++)
	{
		backup += work[j];
		if (work[j] == ' ')
			break;
	}
	if (j == work.size())
	{
		st.push_back(backup);
		return;
	}


	for (int i = 0; i < length; i++)
	{
		if (work[i] != ' ')
		{
			if ((work[i] >= 48 && work[i] <= 57) || work[i] == '.')
			{
				num += work[i];
			}
			else if (work[i] == '+' || work[i] == '-' || work[i] == '*' || work[i] == '/')
			{
				float n = 0;
				string num1 = st[st.size()-1];
//#define DEBUG
#ifdef DEBUG
				cout << "num1 is"<<num1 << endl;
#endif 
				st.pop_back();
				string num2 = st[st.size()-1];
#ifdef DEBUG
				cout << "num2 is" << num2 << endl;
#endif
				st.pop_back();
				float n1 = atof(num1.c_str());
				float n2 = atof(num2.c_str());
				switch (work[i])
				{
				case'+':
					n = n2 + n1;
					break;
				case'-':
					n = n2 - n1;
					break;
				case'*':
					n = n1 * n2;
					break;
				case'/':
					if (n1 == 0)
					{
						cout << "除数为0" << endl;
						return;
					}
					n = n2 / n1;
					break;
				default:
					cout << "an error occurs when calculating stacknumbers!" << endl;
				}
				string result = to_string(n);
				st.push_back(result);
#ifdef DEBUG
				cout << "now the top is" << result << endl;
				cout << "now the size is" << st.size() << endl;
#endif
			}
		}
		else { 
			if(num!="\0")
			st.push_back(num);
			num.clear();
		}
	}
  //	cout << st[0];
	//cout << fixed << setprecision(1) << atof(st[0].c_str()) << endl;
}

string calculate()
{
	v.clear();
	work.clear();
	p.clear();
	st.clear();

	string er = "0";
	string s;
	cout << "please enter the formula:";
	getline(cin,s);
	if (s.size() == 0)
		return er;
	bool aa = judge_dot(s);
	if (aa == true)
	{
		bool a0 = judge_bra(s);
		if (a0 == true)
		{
			bool a1 = judge_minus(s);
			if (a1 == true)
			{
				bool a = judge_num(s);
				//cout << a;
				if (a == true) {
					eat_space(s);
					//cout << endl << s << endl;
					process_minus(s);
					start_cal(s);
					process_cal();
					//output_work();
					postfix_cal();
				}
			}
		}
	}
	string ans = st[0];
	string::size_type pos = ans.find('.');
	if (ans[pos + 1] == '0')
	{
		int a = atof(ans.c_str());
		return to_string(a);
	}
	else {
		if (ans[pos + 2] >= '5' && ans[pos + 2] <= '9')
		{
			float a = atof(ans.c_str());
			int b = 10 * a + 1;
			double c = b / 10.0;
			return to_string(c);
		}
		else if (ans[pos + 2] >= '0' && ans[pos + 2] <= '4')
		{
			ans.erase(pos + 2);
			return ans;
		}
		else { cout << "error occurs when set precision(1)" << endl; exit(-1); }
	}
}

string calculate(string all)
{
	v.clear();
	work.clear();
	p.clear();
	st.clear();

	string s = all;
	
	string er = "0";
	if (s.size() == 0)
		return er;
	bool aa = judge_dot(s);
	if (aa == true)
	{
		bool a0 = judge_bra(s);
		if (a0 == true)
		{
			bool a1 = judge_minus(s);
			if (a1 == true)
			{
				bool a = judge_num(s);
				//cout << a;
				if (a == true) {
					eat_space(s);
					//cout << endl << s << endl;
					process_minus(s);
					start_cal(s);
					process_cal();
					//output_work();
					postfix_cal();
				}
			}
		}
	}
	//cout << st.size();
	if (st.size() == 0)
		return er;
	string ans = st[0];
	//cout << ans;
	string::size_type pos = ans.find('.');
	if (pos == string::npos)
	{
		return ans;
	}
	else {
		if (ans[pos + 1] == '0')
		{
			int a = atof(ans.c_str());
			return to_string(a);
		}
		else {
			if (ans[pos + 2] >= '5' && ans[pos + 2] <= '9')
			{
				float a = atof(ans.c_str());
				int b = 10 * a + 1;
				double c = b / 10.0;
				return to_string(c);
			}
			else if (ans[pos + 2] >= '0' && ans[pos + 2] <= '4')
			{
				ans.erase(pos + 2);
				return ans;
			}
			else { cout << "error occurs when set precision(1)" << endl; exit(-1); }
		}
	}
}

//int main()
//{
//	string s = "3.0";
//	cout<<calculate(s);
//提供了带参数和不带参数的计算器函数
//}