#include "declaration.h"
//八个主要函数

int inbox(int* hand_, vector<int>& initial, bool* hand_with_cube_, int* i_)
{
    *hand_ = initial[0];
    initial.erase(initial.begin());
    *hand_with_cube_ = 1;//手上从此拥有积木
    return 0;
}

int outbox(int* hand_, vector<int>& result, bool* hand_with_cube, int* i_)
{
    if (*hand_with_cube == 1)
    {
        result.push_back(*hand_);
        *hand_with_cube = 0;//手上从此没有积木
        return 0;
    }
	else//动态出错则返回-1并输出错误指令
    {
        cout << "Error on instruction " << *i_ + 1<<endl;
        return -1;
    }
}

int add(int num, int* hand_, vector<int>& space, bool* hand_with_cube_, vector<bool>& space_with_cube, int* i_)
{
    if (space_with_cube[num] == 1 && *hand_with_cube_ == 1)//判断手上是否有积木，空地上是否有积木
    {
        *hand_ += space[num];
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}


int sub(int num, int* hand_, vector<int>& space, bool* hand_with_cube_, vector<bool>& space_with_cube, int* i_)
{
    if (space_with_cube[num] == 1 && *hand_with_cube_ == 1)
    {
        *hand_ -= space[num];
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}

int copyto(int num, int* hand_, vector<int>& space, bool* hand_with_cube_, vector<bool>& space_with_cube, int* i_)
{
    if (*hand_with_cube_ == 1)
    {
        space[num] = *hand_;
        space_with_cube[num] = 1;//从此编号为num的空格拥有积木,状态改变
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}

int copyfrom(int num, int* hand_, vector<int>& space, bool* hand_with_cube_, vector<bool>& space_with_cube, int* i_)
{
    if (space_with_cube[num] == 1)//判断空地上是否有积木
    {
        *hand_ = space[num];
        *hand_with_cube_ = 1;
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}

int jump(int num, vector<string>& op, int* i_)
{
	if (num <= op.size() && num > 0)//判断跳转到的指令是否在范围内
    {
		*i_ = num - 2;//-2是因为主循环里会再加1
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1<<endl;
        return -1;
    }
}

int jumpifzero(int num, int* hand_, vector<string>& op, bool*hand_with_cube_,int* i_)
{
	if (num <= op.size() && num > 0 && *hand_with_cube_ != 0)//判断跳转到的指令是否在范围内且手上有积木
    {
        if (*hand_ == 0)
            *i_ = num - 2;
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}