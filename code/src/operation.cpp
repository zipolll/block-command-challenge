#include "declaration.h"
//函数目标：执行所有操作，并在每步操作后展示结果
//执行所有操作，返回结果判断
int operation(int* hand_, vector<int>& initial, vector<int>& space, vector<int>& result, vector<int>& objective,vector<string>& op, bool* hand_with_cube_, vector<bool>& space_with_cube, map<string, int>& valid_)
{
	vector<int> iinitial = initial; //保存初始输入序列，便于每步操作前展示
	screenclear();
	int sumop = 0;//操作步数统计
	for (int i = 0; i < op.size(); i++)
	{
		//每步操作前展示当前状态
		inform(iinitial, space, objective, valid_);
		current_code(op, i);
		//执行操作
		int opresult = functioning(hand_, initial, space, result, op, op[i], &i, valid_, hand_with_cube_, space_with_cube);
		if (opresult == -1)
			return -1;
		if (opresult == 1)
		{
			render(initial, result, space, space_with_cube, *hand_, *hand_with_cube_);
			screenclear();
			return resultjudge(sumop, result, objective);
		}
		sumop++;
		if(sumop > 1000)
		{
			cout << "Error: 操作步数超过了1000，可能进入死循环." << endl;
			return -1;
		}
		//每步操作后展示当前状态
		cout << "\n=== 第"<<sumop<<"步操作结果 == = " << endl;
		render(initial, result, space, space_with_cube, *hand_, *hand_with_cube_);
		cout << "\n=== 请按回车继续 ==="<<endl;
		cin.get();//等待用户按回车
		screenclear();
	}
	return resultjudge(sumop, result, objective);
}

//执行单条指令
int functioning(int* hand_, vector<int>& initial, vector<int>& space, vector<int>& result, vector<string>& op, string ope, int* i_, map<string, int>& valid_, bool* hand_with_cube_, vector<bool>& space_with_cube)
{
	//静态检查结果
	information judgeinfo = judge(
		ope,
		valid_,
		static_cast<int>(space.size()),
		static_cast<int>(op.size())
	);
	string name0 = judgeinfo.name;
	int num0 = judgeinfo.num;
	int result0 = judgeinfo.judgeresult;
	
	//静态出错
	if (result0 != 0)
	{
		cout << "Error on instruction " << *i_ + 1;
		return -1;
	}

	//inbox结束判断
	if (name0 == "inbox")
	{
		if (initial.empty())
			return 1;
		return inbox(hand_, initial, hand_with_cube_, i_);
	}

	if (name0 == "outbox")
		return outbox(hand_, result, hand_with_cube_, i_);

	if (name0 == "add")
		return add(num0, hand_, space, hand_with_cube_, space_with_cube, i_);

	if (name0 == "sub")
		return sub(num0, hand_, space, hand_with_cube_, space_with_cube, i_);

	if (name0 == "copyto")
		return copyto(num0, hand_, space, hand_with_cube_, space_with_cube, i_);

	if (name0 == "copyfrom")
		return copyfrom(num0, hand_, space, hand_with_cube_, space_with_cube, i_);

	if (name0 == "jump")
		return jump(num0, op, i_);

	if (name0 == "jumpifzero")
		return jumpifzero(num0, hand_, op, hand_with_cube_,i_);

	return -1;
}

