//头文件集合
#pragma once
#define NOMINMAX
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <Windows.h>
#include <iomanip>
#include <limits.h>
using namespace std;
//静态检查结果信息结构体
struct information
{
    string name;
    int num;
    int judgeresult;
};
//8个功能函数声明
int inbox(int*, vector<int>&,bool*,int*);
int outbox(int* , vector<int>&,bool*,int*);
int add(int, int*, vector<int>&,bool*,vector<bool>&,int*);
int sub(int, int*, vector<int>&, bool*, vector<bool>&,int*);
int copyto(int, int*, vector<int>&, bool*, vector<bool>&,int*);
int copyfrom(int, int*, vector<int>&, bool* ,vector<bool>&,int*);
int jump(int, vector<string>&, int*);
int jumpifzero(int , int* , vector<string>& , bool* ,int* );
//操作及判断
int operation(int*, vector<int>&, vector<int>&, vector<int>&, vector<int>&, vector<string>&, bool*, vector<bool>&, map<string, int>&);
information judge(string, map<string, int>&, int, int);
int functioning(int*, vector<int>&, vector<int>&, vector<int>&, vector<string>&, string, int*, map<string, int>&, bool*, vector<bool>&);
//关卡及指令输入函数声明
int input(vector<string>&);
int levelchoose(void);
int level1();
int level2();
int level3();
int level4();
//界面输出相关函数声明
void screenclear();
string process1(int , bool );
string process2(int, vector<int>&);
void render(vector<int>&, vector<int>&, vector<int>&, vector<bool>&, int, bool);
void inform(vector<int>, vector<int>, vector<int>, map<string, int>);
void current_code(vector<string> op, int i);
int resultjudge(int, vector<int>&, vector<int>&);
string to_centered_string(int , int );