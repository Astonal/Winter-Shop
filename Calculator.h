
#ifndef _CAL
#define _CAL
#include<string>

using namespace std;

bool judge_dot(string s);
bool judge_bra(string s);
bool judge_minus(string s);
bool judge_num(string s);
void eat_space(string& s);
void start_cal(string s);
void process_cal();
void output_work();
void process_minus(string &s);
void postfix_cal();
int priority(char s);
string calculate(string s);
string calculate();
#endif