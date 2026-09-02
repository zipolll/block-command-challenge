#include "declaration.h"
//主程序
int main(void)
{   
    vector<int>pass_or_not(4, 0);//是否通关
	int state = 0;//是否继续游玩
    do
    {
		//读取通关文件
        ifstream fin("levelpass.txt");
        for(int i=0;i<4;i++)
			fin >> pass_or_not[i];
        fin.close();

        //进入关卡并执行关卡内操作
        int(*choice[])() = { level1,level2,level3,level4 };
        int levelchoice = -1;
        levelchoice = levelchoose();
        if (levelchoice < 1 || levelchoice > 4)
            break;
        int if_pass = choice[levelchoice - 1]();//是否通关

        if (if_pass == 0)
            pass_or_not[levelchoice-1]=1;//0,1,2,3

		//写入通关文件
        ofstream fout("levelpass.txt");
        for (int i = 0; i < 4; i++)
			fout << pass_or_not[i] << endl;//通过第一关写0，第二关写1，第三关写2，第四关写3
        fout.close();

        //是否继续
        cout <<endl<< "您是否要接着游玩？是的话按0，不是的话按1" << endl;
        cin >> state;
        while(state != 0 && state != 1)
        {
            cout << "输入有误，请重新输入" << endl;
            cin >> state;
		}
        screenclear();
    } while (state == 0);
    cout << "再见，祝您生活愉快！！" << endl;

    return 0;
}
