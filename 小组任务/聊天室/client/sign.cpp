#include "../public/public.hpp"
#include "clit.hpp"
int Clenit::login(int cfd)
{
    string Id, Pass1, in; // 用户的id，密码
    Value info;
    int i;
    char r[BUFFERSIZE]={0};
    cout << "请输入您的ID(3~20位)" << endl;
    cin >> Id;
    while (1)
    {
        if (Id.length() > 20 || Id.length() < 3)
        {
            cout << "您输入的昵称不符合规范，请重新输入一次" << endl;
            cin >> Id;
        }
        else
        {
            break;
        }
    }
    cout << "请输入您的密码" << endl;
    cin >> Pass1;
    while (1)
    {
        if (Pass1.length() > 20 || Pass1.length() < 3)
        {
            cout << "您输入的密码不符合规范，请重新输入一次" << endl;
            cin >> Pass1;
        }
        else
        {
            break;
        }
    }
    info["ID"] = Id;
    info["Pass"] = Pass1;
    Massage m1(LOGIN, info, "0", "0");
    string s = m1.Serialization();
    Err::Write(cfd, s.c_str(), s.length());
    while (1)
    {
        if ((read(cfd, r, sizeof(r))))
        {
            if (strcmp(r, "succeed"))//登陆成功
            {
                cout << "欢迎使用╰(✿´⌣`✿)╯♡" << endl;
                main_mnue(cfd,Id);
                break;
            }
            else if (strcmp(r, "fail"))//密码错误
            {
                cout << "您的id或密码错误，请重新输入(限三次）" << endl;
                Clenit::login(cfd);
                break;
            }else if(strcmp(r,"NULL"))//用户不存在
            {
                cout<<"用户不存在,请您先注册账号"<<endl;
                sign_up(cfd);
                break;
            }
            else//三次以上密码错误进入验证状态
            {
                while (1)
                {
                    memset(&r,0,sizeof(r));
                    cout << "+------------------+" << endl;
                    cout << "|    1:找回密码    |" << endl;
                    cout << "|      0:退出      |" << endl;
                    cout << "+------------------+" << endl;
                    cin >> in;
                    if (in == Reset_Password)
                    {
                        Err::Write(cfd,"Reset_Password",sizeof("Reset_Password"));
                        while (1)
                        {
                            if ((read(cfd, r, sizeof(r)))){
                                Massage m2(r);
                                string Q=m2.Deserialization("Question");//验证问题
                                string A=m2.Deserialization("Answer");//答案
                                string P=m2.Deserialization("Pass");//用户密码
                                cout<<"请回答验证问题"<<Q<<endl;
                                cin>>in;
                                if(in==A){
                                    cout<<"您的密码是："<<P<<endl;
                                    login(cfd);
                                    break;
                                }else{
                                    cout<<"验证未通过,即将强制退出"<<endl;
                                    Err::Close(cfd);
                                    exit(0);
                                }
                            }
                        }
                        break;
                    }
                    else if (in == EXIT)
                    {
                        cout << "再见,欢迎下次光临(๑•́ ₃ •̀๑)ｴｰ" << endl;
                        Err::Close(cfd);
                        exit(0);
                    }else{
                        cout << "您输入的选项不存在,请重新输入" << endl;
                        continue;
                    }
                }
                break;
            }     
        }   
    }
    return;
}
int Clenit::sign_up(int cfd)
{
    string name,Pass1,Pass2,Question,Answer1,Answer2,ID;
    Value info;
    cout<<"请设置您的昵称"<<endl;
    while (1)
    {
        if (name.length() > 20 || name.length() < 3)
        {
            cout << "您输入的昵称不符合规范，请重新输入一次" << endl;
            cin >> name;
        }
        else
        {
            break;
        }
    }
    cout<<"请设置您的密码"<<endl;
    while (1)
    {
        if (Pass1.length() > 20 || Pass1.length() < 3)
        {
            cout << "您设置的密码不符合规范，请重新输入一次" << endl;
            cin >> Pass1;
        }
        else
        {
            cout<<"请再次输入您设置的密码"<<endl;
            cin >> Pass2;
            if(Pass1==Pass2){
                break;
            }else{
                continue;
            }    
        }
    }
    cout<<"请设置您的验证问题"<<endl;
    cin>>Question;
    cout<<"请设置您的问题答案"<<endl;cin>>Answer1;
    while(1){

        cout<<"请再次输入您设置的问题"<<endl;
        cin >> Answer2;
        if(Answer1==Answer2){
            break;
        }else{
            continue;
        }    
    }
    info["Name"]=name;
    info["Pass"]=Pass1;
    info["Question"]=Question;
    info["Answer"]=Answer1;
    Massage m1(SIGN_UP,info,"0","0");
    string s=m1.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    char r[BUFFERSIZE]={0};
    while (1)
    {
        if ((read(cfd, r, sizeof(r))))
        {
            Massage m2(r);
            ID=m2.Deserialization("ID");
            cout<<"您的用户id是："<<ID<<endl;
            break;
        }
    }
    cout<<"已跳转到登陆"<<endl;
    login(cfd);
}
void Clenit::sign_menu(int cfd)
{
    string in; // 输入选项

    while (1)
    {
        cout << "+------------------+" << endl;
        cout << "|      聊天室      |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|      0:退出      |" << endl;
        cout << "|      1:注册      |" << endl;
        cout << "|      2:登录      |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin >> in;
        system("clear");
        if (in == LOGIN)
        {
            if (Clenit::login(cfd) == 0)
            {
                continue;
            }
        }
        else if (in == SIGN_UP)
        {
            if (Clenit::sign_up(cfd) == 0)
            {
                continue;
            }
        }
        else if (in == EXIT)
        {
            cout << "再见,欢迎下次光临(๑•́ ₃ •̀๑)ｴｰ" << endl;
            Err::Close(cfd);
            exit(0);
        }
        else
        {
            cout << "您输入的选项不存在,请重新输入" << endl;
            continue;
        }
    }
    return;
}