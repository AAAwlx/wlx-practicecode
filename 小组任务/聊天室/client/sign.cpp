#include "public.hpp"
#include "clit.hpp"
int Clenit::login()
{
    string Id, Pass1, in; // 用户的id，密码
    Value info;
    int i;
    char r[BUFFERSIZE] = {0};
    std::cout << "请输入您的ID(3~20位)" << endl;
    std::cin >> Id;
    while (1)
    {
        if (Id.length() > 20 || Id.length() < 2)
        {
            std::cout << "您输入的昵称不符合规范，请重新输入一次" << endl;
            std::cin >> Id;
        }
        else
        {
            break;
        }
    }
    std::cout << "请输入您的密码" << endl;
    std::cin >> Pass1;
    while (1)
    {
        if (Pass1.length() > 20 || Pass1.length() < 3)
        {
            std::cout << "您输入的密码不符合规范，请重新输入一次" << endl;
            std::cin >> Pass1;
        }
        else
        {
            break;
        }
    }
    info["ID"] = Id;
    
    Massage m1(LOGIN, info, "0", "0");
    string s = m1.Serialization();
    Err::Write(cfd, s.c_str(),s.length());
    
    while (1)
    {
        if ((read(cfd, r, sizeof(r)))>0)
        {
            std::cout << r << endl;
            if (stoi(r) == -1234567){
                
                std::cout << "用户不存在,请您先注册账号" << endl;
                sign_up();
                break;
            }else{
                if (r == Pass1) {
                    std::cout << "欢迎使用╰(✿´⌣`✿)╯♡" << endl;
                    Value j;
                    j["ID"]=Id;
                    Massage m2("succeed",j,"0","0");
                    string s=m2.Serialization();
                    Err::Write(cfd, s.c_str(),s.length());
                    //main_mnue(Id);
                    break;
                }else{
                    std::cout << "您的密码错误，请重新输入(限三次）" << endl;
                    int count = 0;
                    while (count < 3){
                        cin >> in;
                        cout << count << endl;
                        if (in == r){
                            std::cout << "欢迎使用╰(✿´⌣`✿)╯♡" << endl;
                            Value j;
                            j["ID"]=Id;
                            Massage m2("succeed",j,"0","0");
                            string s=m2.Serialization();
                            Err::Write(cfd, s.c_str(),s.length());
                            //main_mnue(Id);
                        }else{
                            count++;
                            continue;
                        }
                    }
                    if (count >= 2){
                        Clenit::resetpassword(Id);
                    }
                }
            }
        }
    }
    return 0;
}

void Clenit::resetpassword(string ID)
{
    char r[BUFFERSIZE];
    string in;
    while (1)
    {
        std::cout << "+------------------+" << endl;
        std::cout << "|    3:找回密码    |" << endl;
        std::cout << "|      0:退出      |" << endl;
        std::cout << "+------------------+" << endl;
        std::cin >> in;
        if (in == Reset_Password)
        {
            Value j;
            j["ID"] = ID;
            Massage m1(Reset_Password, j, "0", "0");
            string s = m1.Serialization();
            Err::Write(cfd, s.c_str(),s.length());
            while (1)
            {
                if ((read(cfd, r, sizeof(r))))
                {
                    cout << r << endl;
                    Massage m2(r);
                    string Q = m2.Deserialization("Question"); // 验证问题
                    string A = m2.Deserialization("Answer");   // 答案
                    string P = m2.Deserialization("Pass");     // 用户密码
                    std::cout << "请回答验证问题" << endl;
                    std::cout << Q << endl;
                    std::cin >> in;
                    if (in == A)
                    {
                        cout << "您的密码是：" << P << endl;
                        login();
                        break;
                    }
                    else
                    {
                        cout << "验证未通过,即将强制退出" << endl;
                        Clenit::Exit();
                    }
                    break;
                }
            }
        }
        else if (in == EXIT)
        {
            Clenit::Exit();
        }
        else
        {
            std::cout << "您输入的选项不存在,请重新输入" << endl;
            continue;
        }
    }
}
int Clenit::sign_up()
{
    string name, Pass1, Pass2, Question, Answer1, Answer2, ID;
    Value info(Json::objectValue);
    std::cout << "请设置您的昵称" << endl;
    std::cin >> name;
    while (1)
    {
        if (name.length() > 20 || name.length() < 3)
        {
            std::cout << "您输入的昵称不符合规范，请重新输入一次" << endl;
            std::cin >> name;
        }
        else
        {
            break;
        }
    }
    std::cout << "请设置您的密码" << endl;
    std::cin >> Pass1;
    while (1)
    {
        if (Pass1.length() > 20 || Pass1.length() < 3)
        {
            std::cout << "您设置的密码不符合规范，请重新输入一次" << endl;
            std::cin >> Pass1;
        }
        else
        {
            std::cout << "请再次输入您设置的密码" << endl;
            std::cin >> Pass2;
            if (Pass1 == Pass2)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
    std::cout << "请设置您的验证问题" << endl;
    std::cin >> Question;
    std::cout << "请设置您的问题答案" << endl;
    std::cin >> Answer1;
    while (1)
    {

        std::cout << "请再次输入您设置的问题" << endl;
        std::cin >> Answer2;
        if (Answer1 == Answer2)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    info["Name"] = name;
    info["Pass"] = Pass1;
    info["Question"] = Question;
    info["Answer"] = Answer1;
    Massage m1(SIGN_UP, info, "0", "0");
    string s = m1.Serialization();
    Err::Write(cfd, s.c_str(),s.length());
    char r[BUFFERSIZE] = {0};
    while (1)
    {
        if ((read(cfd, r, sizeof(r))))
        {
            ID = r;
            std::cout << "您的用户id是：" << ID << endl;
            break;
        }
    }
    std::cout << "已跳转到登陆" << endl;
    login();
    return 0;
}
void Clenit::Exit()
{
    Value j;
    j["0"]="0";
    Massage m(EXIT, j, "0", "0");
    string s = m.Serialization();
    Err::Write(cfd, s.c_str(),s.length());
    std::cout << "再见,欢迎下次光临(๑•́ ₃ •̀๑)ｴｰ" << endl;
    std::cout << s << endl;
    Err::Close(cfd);
    exit(0);
}
void Clenit::sign_menu()
{
    string in; // 输入选项

    while (1)
    {
        std::cout << "+------------------+" << endl;
        std::cout << "|      聊天室      |" << endl;
        std::cout << "+------------------+" << endl;
        std::cout << "|                  |" << endl;
        std::cout << "|      0:退出      |" << endl;
        std::cout << "|      1:注册      |" << endl;
        std::cout << "|      2:登录      |" << endl;
        std::cout << "|                  |" << endl;
        std::cout << "+------------------+" << endl;
        std::cin >> in;
        system("clear");
        if (in == LOGIN)
        {
            if (Clenit::login() == 0)
            {
                continue;
            }
        }
        else if (in == SIGN_UP)
        {
            if (Clenit::sign_up() == 0)
            {
                continue;
            }
        }
        else if (in == EXIT)
        {
           Clenit::Exit();
        }
        else
        {
            std::cout << "您输入的选项不存在,请重新输入" << endl;
            continue;
        }
    }
    return;
}