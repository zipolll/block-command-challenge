#include "declaration.h"
//4个关卡函数

int level1()
{
	int hand = 0;//机器人的手

	vector<int> initial = { 1,2 };//输入列初始化

	vector<int> space;//空地列初始化

	vector<bool> space_with_cube(2, false);//空地上有无东西初始化

	vector<int> result;//储存输出序列

	vector<int> objective = { 1,2 };//目标结果初始化

	bool hand_with_cube = 0;//手上有无东西初始化

	vector<string> op;//操作

	//有效指令集合
	map<string, int> valid_;
	valid_["inbox"] = 1;
	valid_["outbox"] = 1;

	//输出关卡信息：
	inform(initial, space, objective, valid_);

	//输入操作；
	if (input(op)!=0)
		return -1;

	//执行操作
	return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}

int level2()
{
	int hand = 0;//机器人的手

	vector<int> initial = { 3, 9, 5, 1, -2, -2, 9, -9 };//输入列初始化

	vector<int> space(3, 0);//空地列初始化

	vector<bool> space_with_cube(3, false);//空地上有无东西初始化

	vector<int> result;//储存输出序列

	vector<int>objective = { -6, 6, 4, -4, 0, 0, 18, -18 };//目标结果初始化

	bool hand_with_cube = 0;//手上有无东西初始化

	vector<string> op;//操作

	//有效指令集合
	map<string, int> valid_;
	valid_["inbox"] = 1;
	valid_["outbox"] = 1;
	valid_["add"] = 1;
	valid_["sub"] = 1;
	valid_["jump"] = 1;
	valid_["jumpifzero"] = 1;
	valid_["copyfrom"] = 1;
	valid_["copyto"] = 1;

	//输出关卡信息：
	inform(initial, space, objective, valid_);

	//输入操作；
	if (input(op) != 0)
		return -1;

	//执行操作
	return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}

int level3()
{
	int hand = 0;//机器人的手

	vector<int> initial = { 6, 2, 7, 7, -9, 3, -3, -3 };//输入列初始化

	vector<int> space(3, 0);//空地列初始化

	vector<bool> space_with_cube(3, false);//空地上有无东西初始化

	vector<int> result;//储存输出序列

	vector<int> objective = { 7,-3 };//目标结果初始化

	bool hand_with_cube = 0;//手上有无东西初始化

	vector<string> op;//操作

	//有效指令集合
	map<string, int> valid_;
	valid_["inbox"] = 1;
	valid_["outbox"] = 1;
	valid_["add"] = 1;
	valid_["sub"] = 1;
	valid_["jump"] = 1;
	valid_["jumpifzero"] = 1;
	valid_["copyfrom"] = 1;
	valid_["copyto"] = 1;

	//输出关卡信息：
	inform(initial, space, objective, valid_);

	//输入操作；
	if (input(op) != 0)
		return -1;

	//执行操作
	return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}

int level4()
{
	int hand = 0;//机器人的手

	vector<int> initial = { 5,7,9 };//输入列初始化

	vector<int> space(1, 0);//空地列初始化

	vector<bool> space_with_cube(1, false);//空地上有无东西初始化

	vector<int> result;//储存输出序列

	vector<int> objective = { 9,7,5 };//目标结果初始化

	bool hand_with_cube = 0;//手上有无东西初始化

	vector<string> op;//操作

	//有效指令集合
	map<string, int> valid_;
	valid_["inbox"] = 1;
	valid_["outbox"] = 1;
	valid_["add"] = 1;
	valid_["sub"] = 1;
	valid_["copyfrom"] = 1;
	valid_["copyto"] = 1;

	//输出关卡信息：
	inform(initial, space, objective, valid_);

	//输入操作；
	if (input(op) != 0)
		return -1;

	//执行操作
	return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}
