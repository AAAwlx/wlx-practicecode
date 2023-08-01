#include "public.hpp"
#include "clit.hpp"
void Clenit::directsend(string ID)
{

}
void Clenit::pchatspace(string ID)
{
    
}
void Clenit::privateChat(string ID)
{
    string in;
    while (1)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:私聊空间    |" << endl;//可显示部分聊天记录
        cout << "|    2.直接发送    |" << endl;
        cout << "|    0:退回上步    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin>>in;
        if(in==Pchat_space){
            Clenit::pchatspace(ID);
        }else if(in==Direct_send){
            Clenit::directsend(ID);
        }else if(in==EXIT){
            Clenit::Exit();
            break;
        }else{
            cout<<"您的输入不符合规范，请再次输入选项"<<endl;
            continue;
        }
    }
}