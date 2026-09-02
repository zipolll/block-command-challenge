#include "declaration.h"
//界面输出相关
// 清屏
void screenclear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 辅助函数：将整数转换为指定宽度的居中字符串
string to_centered_string(int value, int width) {
    // 先把数字转成字符串
    string s = to_string(value);
    // 如果已经超出或等于宽度，直接返回（不截断）
    if (static_cast<int>(s.length()) >= width) {
        return s;
    }
    // 计算需要填充的总空格数
    int total_pad = width - static_cast<int>(s.length());
    int left_pad = total_pad / 2;          // 左边空格数
    int right_pad = total_pad - left_pad;   // 右边空格数（保证总和正确）

    return std::string(left_pad, ' ') + s + std::string(right_pad, ' ');
}

// 辅助函数：将整数格式化为 " X " 形式（宽度=3，居中）
string process1(int value, bool valuejudge) {
    if (valuejudge == 0) return "   "; // 空格表示空位
    return to_centered_string(value, 3);
}
string process2(int num, vector<int>& in_or_out)//需要导入当前位置！！
{
    if (in_or_out.empty() || num >= in_or_out.size())return "   ";
    return to_centered_string(in_or_out[num], 3);
}

//渲染当前状态
void render(vector<int>&initial, vector<int>&result, vector<int>&space, vector<bool>&space_with_cube, int hand, bool hand_with_cube)            // 机器人手上（-1 表示空手）
{
    //// 构建占位符映射
    map<string, string> vars =
    {
        {"I1", process2(0,initial)},
        {"I2", process2(1,initial)},
        {"I3", process2(2,initial)},
        {"I4", process2(3,initial)},
        {"I5", process2(4,initial)},
        {"I6", process2(5,initial)},
        {"I7", process2(6,initial)},
        {"I8", process2(7,initial)},
        {"O1", process2(0,result)},
        {"O2", process2(1,result)},
        {"O3", process2(2,result)},
        {"O4", process2(3,result)},
        {"O5", process2(4,result)},
        {"O6", process2(5,result)},
        {"O7", process2(6,result)},
        {"O8", process2(7,result)},
        {"HAND",process1(hand,hand_with_cube)} };
        for (int i = 0; i < 4; i++)
        {
            if (i < space.size())
                vars["S" + to_string(i + 1)] = process1(space[i], space_with_cube[i]);
            else
                vars["S" + to_string(i + 1)] = process1(0, 0);
        }
     /*定义模板（每一行是一个字符串，含占位符）*/
    vector<string> lines = {
        "    +---+     +---+                            +---+    ",
        "IN  |{I1}|     |{HAND}|                            |{O1}| OUT",
        "    +---+     +---+                            +---+    ",
        "    +---+     @   @                            +---+    ",
        "    |{I2}|     -----                            |{O2}|    ",
        "    +---+     |@ @|                            +---+    ",
        "    +---+       +                              +---+    ",
        "    |{I3}|     /   \\                            |{O3}|    ",
        "    +---+      | |                             +---+    ",
        "    +---+                                      +---+    ",
        "    |{I4}|     +---+ +---+ +---+ +---+          |{O4}|    ",
        "    +---+     |{S1}| |{S2}| |{S3}| |{S4}|          +---+    ",
        "    +---+     +---+ +---+ +---+ +---+          +---+    ",
        "    |{I5}|                                      |{O5}|    ",
        "    +---+                                      +---+    ",
        "    +---+                                      +---+    ",
        "    |{I6}|                                      |{O6}|    ",
        "    +---+                                      +---+    ",
        "    +---+                                      +---+    ",
        "    |{I7}|                                      |{O7}|    ",
        "    +---+                                      +---+    ",
        "    +---+                                      +---+    ",
        "    |{I8}|                                      |{O8}|    ",
        "    +---+                                      +---+    "
    };
    // 替换每一行中的占位符
    for (int i=0;i<lines.size();i++)
    {
        for (const auto& kv : vars) 
        {
            const string key = kv.first;
            const string value = kv.second;
            size_t pos;
            while ((pos = lines[i].find("{" + key + "}")) != string::npos)
            {
                lines[i].replace(pos, key.length() + 2, value);
            }
        }
        cout << lines[i]  <<endl;
    }
}

//关卡信息展示
void inform(vector<int> initial, vector<int> space, vector<int>objective, map<string, int>valid_)
{
    cout << "输入序列：";
    for (int i = 0; i < initial.size(); i++)
    {
        cout << initial[i];
        if (i != initial.size() - 1)
            cout << ' ';
        else
            cout << endl;
    }
    cout << "目标输出序列：";
    for (int i = 0; i < objective.size(); i++)
    {
        cout << objective[i];
        if (i != objective.size() - 1)
            cout << ' ';
        else
            cout << endl;
    }
    cout << "可用空地数：";
    cout << space.size() << endl;
    cout << "可用指令集：";
    for (auto& kv : valid_)
    {
        const string& key = kv.first;
        const int& value = kv.second;
        if (value == 1)
            cout << key << ' ';
    }
    cout << endl;
}

//评判结果展示
int resultjudge(int sumop, vector<int>& result, vector<int>& objective)
{
    cout << endl << "操作总数: " << sumop << endl;
    cout << "Result: ";
    for (auto s : result)
        cout << s << " ";
    cout << endl;
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

//当前指令
void current_code(vector<string> op, int i)
{
    cout << "======CODE======"<<endl;
    for (int j = 0; j < op.size(); j++)
    {
        if (j != i)
            cout << "        " << op[j] << endl;
        else
            cout << "current:" << op[j] << endl;
    }
}