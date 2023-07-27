#include "public.hpp"
#include "clit.hpp"
void Clenit::main_mnue(string ID)
{
    string in;
    char r[BUFSIZ];
    while (true)
    {
        bzero(r, sizeof(r));
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:私聊        |" << endl;
        cout << "|    2:群菜单      |" << endl;
        cout << "|    3:好友管理    |" << endl;
        cout << "|    4.文件管理    |" << endl;
        cout << "|    0:回到上步    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin >> in;
        Err::Write(cfd, in.c_str(), in.length());
        system("clear");
        if (in == PRIVATE)
        {
            privateChat(ID);
            continue;
        }
        else if (in == GROUP)
        {
            group_menu(ID);
            continue;
        }
        else if (in == FRIENDS_MENU)
        {
            friends_menu(ID);
            continue;
        }else if(in==FILE_MANAGE)
        {
            file_menu(ID);
        }else if (in==EXIT)
        {
            break;
        }else{
            cout<<"您的输入不符合规范，请再次输入选项"<<endl;
            continue;
        }
    }
    return;    
} 