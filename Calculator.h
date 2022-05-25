#pragma once
#include<iostream>
#include<cctype>
#include<fstream>
#include<stack>
#include<queue>
#include<string>
#include<map>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::queue;
using std::stack;
using std::ostream;
using std::istream;
enum negative_sign_case { not_negative_sign, negative_and_brackets, is_negative_number };
struct data_type
{
	friend ostream& operator<<(ostream& os, data_type dt);
	data_type(double _number):
		is_symbol(false), number(_number), symbol(0) { }
	data_type(char _char) :
		is_symbol(true), number(0), symbol(_char) { }
	bool is_symbol;
	double number;
	char symbol;
};

inline ostream& operator<<(ostream& os, data_type dt)
{
	if (dt.is_symbol)
		os << dt.symbol;
	else
		os << dt.number;
	return os;
}
class Calculator
{
public:
	/* public interface */
	Calculator(string _infix);
	double get_result();

	/* temporary debug function */
	void get_infix()
	{
		while (!infix.empty())
		{
			cout << infix.front();
			infix.pop();
		}
	}
	void get_postfix()
	{
		while (!postfix.empty())
		{
			cout << postfix.front();
			postfix.pop();
		}
	}
private:
	/* core data member */
	string string_infix;
	queue<data_type> infix;
	queue<data_type> postfix;
	double result;

	/* core member function */
	queue<data_type>& simplify_infix();
	queue<data_type>& infix_to_postfix();
	double postfix_parsing();

	/* infix_to_postfix() helper member */
	bool is_higher_priority(char current, char stack_top);
	map<char, int> priority;
	map<char, int>& priority_initialize();
	negative_sign_case is_negative_sign(int index);
	/* postfix_parsing() helper member */
};

inline Calculator::Calculator(string _infix):
	string_infix(_infix),infix(simplify_infix()),postfix(infix_to_postfix()),result(postfix_parsing()), priority(priority_initialize()) { }

inline double Calculator::get_result()
{
	return result;
}

inline queue<data_type>& Calculator::simplify_infix()
{
	bool is_negative_number = false;
	queue<data_type> infix;
	infix.push(data_type('#'));
	infix.push(data_type('('));
	for (int i = 0; i < string_infix.size(); ++i)
	{
		negative_sign_case nsc = is_negative_sign(i);
	}
	infix.push(data_type(')'));
	return infix;
}

inline queue<data_type>& Calculator::infix_to_postfix()
{
	queue<data_type> postfix;
	stack<char> operators;
	operators.push('#');
	/*for (int i = 0; i < string_infix.size(); ++i)
	{
		switch (string_infix[i])
		{
		case '-':
		case '+':
		case '*':
		case '/':
		case '(':
		case ')':
		default:
			break;
		}
	}*/
}

inline bool Calculator::is_higher_priority(char current,char stack_top)
{
	return priority[current]> priority[stack_top];
}

inline map<char, int>& Calculator::priority_initialize()
{
	map<char, int> priority;
	priority['#'] = 0;
	priority['('] = 1;
	priority['+'] = 2;
	priority['-'] = 2;
	priority['*'] = 3;
	priority['/'] = 3;
	return priority;
}

inline negative_sign_case  Calculator::is_negative_sign(int index)
{
	if (!(string_infix[index] == '-' && (index == 0 || string_infix[index - 1] == '(')))
		return not_negative_sign;
	if (string_infix[index + 1]==')')
		return negative_and_brackets;
	return is_negative_number;
}










