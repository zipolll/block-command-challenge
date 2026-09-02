#include "declaration.h"
//函数目标：根据一行输入指令，通过结构体，返回其是否合法，单词部分，数字部分
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

    //本行为空行
    if (a.size() == 0)
    {
        info.judgeresult = -1;
        return info;
    }
    //第一个字母
    if (!(a[ps] >= 'a' && a[ps] <= 'z'))
    {
        info.judgeresult = -1;
        return info;
    }
    //读取指令名
    while (ps < a.size() && (a[ps] >= 'a' && a[ps] <= 'z'))
    {
        info.name.push_back(a[ps]);
        ps++;
    }

    //合法指令
    if (valid_.find(info.name) == valid_.end())
    {
        info.judgeresult = -1;
        return info;
    }
    
    //跳过空格
    while (ps < a.size() && a[ps] == ' ')
    {
        ps++;
        if (ps < a.size() && a[ps] != ' ' && (a[ps] < '0' || a[ps] > '9'))
        {
            info.judgeresult = -1;
            return info;
        }
    }

    //读取数字
    string num1;
    while (ps < a.size() && a[ps] >= '0' && a[ps] <= '9')
    {
        num1.push_back(a[ps]);
        ps++;
    }

    //是否需要操作数
    if ((num1.size() != 0 && validnum[info.name] == 0) ||
        (num1.size() == 0 && validnum[info.name] != 0))
    {
        info.judgeresult = -1;
        return info;
    }

    if (!num1.empty())
        info.num = stoi(num1);

    //判断空地范围
    if (validnum[info.name] == 1 &&
        (info.num < 0 || info.num > space_ - 1))
    {
        info.judgeresult = -1;
        return info;
    }
    
    //指令跳转范围
    if (validnum[info.name] == 2 &&
        (info.num < 1 || info.num > numop_))
    {
        info.judgeresult = -1;
        return info;
    }

    //尾部只能是空格
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
