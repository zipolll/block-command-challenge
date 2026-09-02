#include "declaration.h"
//说明指令输入规则，并实现从键盘或文件输入指令
int input(vector<string>&op)
{
	string rubbish;
	int way = 0, numop = 1;
	cout << "键盘输入规则：" << endl;
	cout << "先输入操作总数，再逐行输入操作指令，开头不允许输入空格；" << endl;
	cout << "文件输入规则：" << endl;
	cout<<"无需输入操作数，将操作指令按行写入名为inputorder.txt的文件中，开头不允许输入空格；" << endl;
	cout << "请选择指令输入方式：0（键盘）；1（文件）:";
	cin >> way;
	while(way!=0&&way!=1)
	{
		cout<<"指令不符合要求,请重新输入：";
		cin>>way;
	}
	//清除缓冲区残留的换行符
	getline(cin, rubbish);
	if (way == 0)
	{
		//键盘输入
		cout << "请输入操作总数：";
		cin >> numop;
		string temp;
		getline(cin, temp);
		for (int i = 0; i < numop; i++)
		{
			getline(cin, temp);
			op.push_back(temp);
		}

		return 0;
	}
	else 
	{
		//文件输入
		string container;
		ifstream fin;
		fin.open("inputorder.txt");
		if (!fin)
		{
			cout << "Error on opening file";
			return -1;
		}			
		while (getline(fin, container))
		{
			op.push_back(container);
		}
		fin.close();
		return 0;
	}
}
