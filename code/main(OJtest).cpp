//  用于OJ测试版
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct information
{
    string name;
    int num;
    int judgeresult;
};

int inbox(int *hand_, vector<int> &(initial), bool *hand_with_cube_, int *i_)
{
    *hand_ = initial[0];
    initial.erase(initial.begin());
    *hand_with_cube_ = 1; // 手上从此拥有积木
    return 0;
}

int outbox(int *hand_, vector<int> &result, bool *hand_with_cube, int *i_)
{
    if (*hand_with_cube == 1)
    {
        result.push_back(*hand_);
        *hand_with_cube = 0; // 手上从此没有积木
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}

int add(int num, int *hand_, vector<int> &space, bool *hand_with_cube_, vector<bool> &space_with_cube, int *i_)
{
    if (space_with_cube[num] == 1 && *hand_with_cube_ == 1) // 判断手上是否有积木，空地上是否有积木
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
// 为了说明“空格上没有方块”的情况，建议现在定义时将space的所有元素初始化为-1；

int sub(int num, int *hand_, vector<int> &space, bool *hand_with_cube_, vector<bool> &space_with_cube, int *i_)
{
    if (space_with_cube[num] == 1 && *hand_with_cube_ == 1) // 判断手上是否有积木，空地上是否有积木
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

int copyto(int num, int *hand_, vector<int> &space, bool *hand_with_cube_, vector<bool> &space_with_cube, int *i_)
{
    if (*hand_with_cube_ == 1) // 判断手上是否有积木
    {
        space[num] = *hand_;
        space_with_cube[num] = 1; // 从此编号为num的空格拥有积木
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}

int copyfrom(int num, int *hand_, vector<int> &space, bool *hand_with_cube_, vector<bool> &space_with_cube, int *i_)
{
    if (space_with_cube[num] == 1) // 判断空地是否有积木
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

int jump(int num, vector<string> &op, int *i_)
{
    if (num <= op.size() && num > 0)
    {
        *i_ = num - 2;
        return 0;
    }
    else
    {
        cout << "Error on instruction " << *i_ + 1 << endl;
        return -1;
    }
}

int jumpifzero(int num, int *hand_, vector<string> &op, bool *hand_with_cube_, int *i_)
{
    if (num <= op.size() && num > 0 && *hand_with_cube_ != 0)
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

int input(vector<string> &op)
{
    int numop = 0;
    cin >> numop;
    string rubbish;
    getline(cin, rubbish);
    for (int i = 0; i < numop; i++)
    {
        string temp;
        getline(cin, temp);
        op.push_back(temp);
    }
    return 0;
}

information judge(string a, map<string, int>& valid_, int space_, int numop_)
{
    map<string, int> validnum;
    //不需要数
    validnum["inbox"] = 0;
    validnum["outbox"] = 0;
	//需要空地数
    validnum["add"] = 1;
    validnum["sub"] = 1;
    validnum["copyto"] = 1;
    validnum["copyfrom"] = 1;
	//需要跳转数
    validnum["jump"] = 2;
    validnum["jumpifzero"] = 2;

    information info;
    info.num = -1;
    info.judgeresult = 0;
    int ps = 0;

    // ===== 本行为空行 =====
    if (a.size() == 0)
    {
        info.judgeresult = -1;
        return info;
    }

    // ===== 第一个字母 =====
    if (!(a[ps] >= 'a' && a[ps] <= 'z'))
    {
        info.judgeresult = -1;
        return info;
    }

    // ===== 读取指令名 =====
    while (ps < a.size() &&(a[ps] >= 'a' && a[ps] <= 'z'))
    {
        info.name.push_back(a[ps]);
        ps++;
    }

    // ===== 修补 2：合法指令 =====
    if (valid_.find(info.name) == valid_.end())
    {
        info.judgeresult = -1;
        return info;
    }

    // ===== 跳过空格 =====
    while (ps < a.size() && a[ps] == ' ')
    {
        ps++;
        if (ps < a.size() && a[ps] != ' ' && (a[ps] < '0' || a[ps] > '9'))
        {
            info.judgeresult = -1;
            return info;
        }
    }

    // ===== 读取数字 =====
    string num1;
    while (ps < a.size() && a[ps] >= '0' && a[ps] <= '9')
    {
        num1.push_back(a[ps]);
        ps++;
    }

    // ===== 是否需要操作数 =====
    if ((num1.size() != 0 && validnum[info.name] == 0) ||
        (num1.size() == 0 && validnum[info.name] != 0))
    {
        info.judgeresult = -1;
        return info;
    }
    
    if (!num1.empty())
        info.num = stoi(num1);

    // ===== 空地范围 =====
    if (validnum[info.name] == 1 &&
        (info.num < 0 || info.num > space_ - 1))
    {
        info.judgeresult = -1;
        return info;
    }

    // ===== 跳转范围 =====
    if (validnum[info.name] == 2 &&
        (info.num < 1 || info.num > numop_))
    {
        info.judgeresult = -1;
        return info;
    }

    // ===== 修补 5：尾部只能是空格 =====
    while (ps < a.size())
    {
        if (a[ps] != ' ')
        {
            info.judgeresult = -1;
            return info;
        }
        ps++;
    }

    return info;
}

int resultjudge(int sumop, vector<int> &result, vector<int> &objective)
{
    if (result == objective)
    {
        cout << "Success" << endl;
        return 0;
    }
    else
    {
        cout << "Fail" << endl;
        return -1;
    }
}

int functioning(int *hand_, vector<int> &initial, vector<int> &space, vector<int> &result, vector<string> &op, string ope, int *i_, map<string, int> &valid_, bool *hand_with_cube_, vector<bool> &space_with_cube)
{
    information judgeinfo = judge(ope, valid_, space.size(), op.size());
    string name0 = judgeinfo.name;
    int num0 = judgeinfo.num;
    int result0 = judgeinfo.judgeresult;
    if (result0 != 0)
    {
        cout << "Error on instruction " << *i_ + 1;
        return -1; // 静态出错
    }
    if (name0 == "inbox")
    {
        if (initial.empty())
            return 1; // inbox结束判断
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
        return jumpifzero(num0, hand_, op, hand_with_cube_, i_);
    return 0;
}

int operation(int *hand_, vector<int> &initial, vector<int> &space, vector<int> &result, vector<int> &objective, vector<string> &op, bool *hand_with_cube_, vector<bool> &space_with_cube, map<string, int> &valid_)
{
    vector<int> iinitial = initial; // 保存初始输入序列，便于每步操作前展示
    int sumop = 0;
    for (int i = 0; i < op.size(); i++)
    {
        int opresult = functioning(hand_, initial, space, result, op, op[i], &i, valid_, hand_with_cube_, space_with_cube);
        if (opresult == -1)
            return -1;
        if (opresult == 1)
            return resultjudge(sumop, result, objective);
    }
    return resultjudge(sumop, result, objective);
}

int level1()
{
    int hand = 0;                   // 机器人的手
    vector<int> initial = {1, 2};   // 输入列初始化
    vector<int> space;              // 空地列初始化
    vector<bool> space_with_cube;   // 空地上有无东西初始化
    vector<int> result;             // 储存输出序列
    vector<int> objective = {1, 2}; // 目标结果初始化
    bool hand_with_cube = 0;        // 手上有无东西初始化
    vector<string> op;              // 操作
    map<string, int> valid_;
    valid_["inbox"] = 1;
    valid_["outbox"] = 1;
    // 输入操作；
    if (input(op) != 0)
        return -1;
    // 执行操作
    return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}

int level2()
{
    int hand = 0;                                          // 机器人的手
    vector<int> initial = {3, 9, 5, 1, -2, -2, 9, -9};     // 输入列初始化
    vector<int> space(3, 0);                               // 空地列初始化
    vector<bool> space_with_cube(3, false);                // 空地上有无东西初化
    vector<int> result;                                    // 储存输出序列
    vector<int> objective = {-6, 6, 4, -4, 0, 0, 18, -18}; // 目标v结果初始化
    bool hand_with_cube = 0;                               // 手上有无东西初始化
    vector<string> op;                                     // 操作
    map<string, int> valid_;
    valid_["inbox"] = 1;
    valid_["outbox"] = 1;
    valid_["add"] = 1;
    valid_["sub"] = 1;
    valid_["jump"] = 1;
    valid_["jumpifzero"] = 1;
    valid_["copyfrom"] = 1;
    valid_["copyto"] = 1;
    // 输入操作；
    if (input(op) != 0)
        return -1;
    // 执行操作
    return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}

int level3()
{
    int hand = 0;                                      // 机器人的手
    vector<int> initial = {6, 2, 7, 7, -9, 3, -3, -3}; // 输入列初始化
    vector<int> space(3, 0);                           // 空地列初始化
    vector<bool> space_with_cube(3, false);            // 空地上有无东西初始化
    vector<int> result;                                // 储存输出序列
    vector<int> objective = {7, -3};                   // 目标v结果初始化
    bool hand_with_cube = 0;                           // 手上有无东西初始化
    vector<string> op;                                 // 操作
    map<string, int> valid_;
    valid_["inbox"] = 1;
    valid_["outbox"] = 1;
    valid_["add"] = 1;
    valid_["sub"] = 1;
    valid_["jump"] = 1;
    valid_["jumpifzero"] = 1;
    valid_["copyfrom"] = 1;
    valid_["copyto"] = 1;
    // 输入操作；
    if (input(op) != 0)
        return -1;
    // 执行操作
    return operation(&hand, initial, space, result, objective, op, &hand_with_cube, space_with_cube, valid_);
}

int main(void)
{
    int (*choice[])() = {level1, level2, level3};
    int levelchoice = -1;
    int x;
    cin >> x;
    levelchoice = x;
    choice[levelchoice - 1](); // 是否通关
    return 0;
}
