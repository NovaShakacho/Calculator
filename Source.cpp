#include<iostream>
#include<fstream>
#include"Calculator.h"
using namespace std;
//int main(void)
//{
//	string infix;
//	cout << "Please input a infix expression:";
//	getline(cin, infix);
//	Calculator calculator(infix);
//	cout << "Result: " << calculator.get_result();
//	return 0;
//}

int main(void)
{
	string infix;
	//Can't use ios::binary!
	//The default(windows) newline character of txt file is CRLF(\r\n), but getline is \n.
	//Non-binary mode \r\n will be automatically converted to \n by the system, while binary mode will not.
	ifstream ifs("input.txt",ios::in);
	ofstream ofs("output.txt",ios::out);
	while (getline(ifs, infix))
	{
		Calculator calculator(infix);
		ofs << infix << calculator.get_result() << "\n";
	}
	cout << "Accept!" << endl;
	return 0;
}