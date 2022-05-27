#pragma once
#include<iostream>
#include<cctype>
#include<fstream>
#include<stack>
#include<queue>
#include<string>
#include<map>
enum character_case 
{
	is_digit,
	is_operator,
	is_negative_sign
};

//Store an operand or operator.
struct data_type
{
	////debug  function
	//friend std::ostream& operator<<(std::ostream& os, data_type dt);
	data_type(double _number):
		is_symbol(false), number(_number), symbol(0) { }
	data_type(char _char) :
		is_symbol(true), number(0), symbol(_char) { }
	bool is_symbol;
	double number;
	char symbol;
};

//inline std::ostream& operator<<(std::ostream& os, data_type dt)
//{
//	if (dt.is_symbol)
//		os << dt.symbol;
//	else
//		os << dt.number;
//	return os;
//}

//Evaluates an infix expression as a string.
class Calculator
{
public:
	/* public interface */
	Calculator(std::string _infix);
	double get_result();

	/* temporary debug function */
	/*void get_infix()
	{
		while (!infix.empty())
		{
			std::cout << infix.front()<<" ";
			infix.pop();
		}
	}
	void get_postfix()
	{
		while (!postfix.empty())
		{
			std::cout << postfix.front()<<" ";
			postfix.pop();
		}
	}*/
private:
	/* core data member */
	std::map<char, int> priority;
	std::string string_infix;
	std::queue<data_type> infix;
	std::queue<data_type> postfix; 
	double result;

	/* core member function */
	//Convert string to infix expression and simplify.
	std::queue<data_type> simplify_infix();
	std::queue<data_type> infix_to_postfix();
	double postfix_parsing();

	/* infix_to_postfix() helper member */
	bool is_higher_priority(char current, char stack_top);
	character_case get_character_case (int index);
	//Extract double from string.
	double get_digit(int& i);
	std::map<char, int> priority_initialize();

	/* postfix_parsing() helper member */
	double two_number_operation(std::stack<double>& digit, char ops);
};

inline Calculator::Calculator(std::string _infix):
	string_infix(_infix), priority(priority_initialize()),infix(simplify_infix()),postfix(infix_to_postfix()),result(postfix_parsing()){ }

inline double Calculator::get_result()
{
	//In the IEEE-754 standard -0 will be printed out.
	if(result==-0)
		return 0.0;
	else
		return result;
}

inline std::queue<data_type> Calculator::simplify_infix()
{
	//The logic is in the document.
	std::queue<data_type> infix;
	//e.g: 1+2 -> (1+2)
	infix.push(data_type('('));
	for (int i = 0; i < string_infix.size(); ++i)
	{
		//Ignore '='. Usually it can be deleted.
		if (string_infix[i] == '=')
			continue;
		character_case nsc = get_character_case (i);
		switch (nsc)
		{
		case is_digit:
			infix.push(data_type(get_digit(i)));
			break;
		case is_operator:
			infix.push(data_type(string_infix[i]));
			break;
		case is_negative_sign:
			//e.g: -(1+2)->(0-(1+2))
			infix.push(data_type(0.0));
			infix.push(data_type('-'));
			break;
		default:
			std::cout << "Error in simplify_infix!";
			break;
		}
	}
	infix.push(data_type(')'));
	return infix;
}

inline std::queue<data_type> Calculator::infix_to_postfix()
{
	
	//The logic is in the document.
	std::queue<data_type> postfix;
	std::stack<char> operators;
	char ops;
	while (!infix.empty())
	{
		//digit
		if (!infix.front().is_symbol)
			postfix.push(infix.front());
		//operator 
		else
		{
			//The highest priority element must be at the top of the std::stack.
			ops = infix.front().symbol;
			switch (ops)
			{
			case '+':
			case '-':
			case '*':
			case '/':
				if (is_higher_priority(ops, operators.top()))
					operators.push(ops);
				else
				{
					while (!is_higher_priority(ops, operators.top()))
					{
						postfix.push(data_type(operators.top()));
						operators.pop();
					}
					operators.push(ops);
				}
				break;
			case '(':
				operators.push(ops);
				break;
			case ')':
				while (operators.top() != '(')
				{
					postfix.push(data_type(operators.top()));
					operators.pop();
				}
				//pop '('
				operators.pop();
				break;
			default:
				std::cout << "Error in infix_to_postfix!";
				break;
			}
		}
		infix.pop();
	}
	//Process the remaining elements on the std::stack.
	while (!operators.empty())
	{
		postfix.push(operators.top());
		operators.pop();
	}
	return postfix;
}

inline double Calculator::postfix_parsing()
{
	//The logic is in the document.
	std::stack<double> digit;
	while (!postfix.empty())
	{
		if (!postfix.front().is_symbol)
			digit.push(postfix.front().number);
		else
			digit.push(two_number_operation(digit, postfix.front().symbol));
		postfix.pop();
	}
	return digit.top();
}

inline bool Calculator::is_higher_priority(char current,char stack_top)
{
	return priority[current] > priority[stack_top];
}

inline character_case Calculator::get_character_case (int index)
{
	//Negative sign determination: "(-" or "-"(iff index==0)
	if (isdigit(string_infix[index]))
		return is_digit;
	else if (string_infix[index] == '-' && (index == 0 || string_infix[index - 1] == '('))
			return is_negative_sign;
	else
		return is_operator;
}

inline double Calculator::get_digit(int& i)
{
	//Notice:i will be changed to the first index that is not a digit or a decimal point.
	std::string str_digit;
	while (isdigit(string_infix[i+1])|| string_infix[i+1]=='.')
	{
		str_digit += string_infix[i];
		++i;
	}
	str_digit += string_infix[i];
	//stod() converts string to double.
	return std::stod(str_digit);
}

inline std::map<char, int> Calculator::priority_initialize()
{
	std::map<char, int> priority;
	priority['('] = 1;
	priority['+'] = 2;
	priority['-'] = 2;
	priority['*'] = 3;
	priority['/'] = 3;
	return priority;
}

inline double Calculator::two_number_operation(std::stack<double>& digit, char ops)
{
	//Take 2 operands from the stack.The second is the first operand.
	double value=0.0;
	double second = digit.top();
	digit.pop();
	double first = digit.top();
	digit.pop();
	switch (postfix.front().symbol)
	{
	case '+':
		value = first + second;
		break;
	case '-':
		value = first - second;
		break;
	case '/':
		value = first / second;
		break;
	case '*':
		value = first * second;
		break;
	default:
		std::cout << "Error is in postfix_parsing.";
		break;
	}
	return value;
}
