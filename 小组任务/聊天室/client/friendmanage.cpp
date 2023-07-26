#include"../public/public.hpp"
#include"clit.hpp"
void Clenit::friendadd(int cfd,string ID)
{
    string in;
    char r[BUFSIZ];
    Value j;
    cout<<"请输入新好友的id"<<endl;
    cin>>in;
    j["NEW_friendid"]=in;
    Massage m(ADD_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))){
            if (r=="NULL")
            {
                cout<<"没有此用户，请再试一次"<<endl;
                friendadd(cfd,ID);
            }else if (r=="Refuse")
            {
                cout<<"对方拒绝了你的申请"<<endl;
            }else if(r=="Succeed")
            {
                cout<<"你与id为"<<in<<"的用户已成功添加为好友"<<endl;
            }else if(strcmp(r, "befriends") == 0){
                 cout << "你们已经是好友了" << endl;
            }
            break;    
        }
    }
    return;
}
void Clenit::delfriend(int cfd,string ID)
{
    string in;
    char r[BUFSIZ];
    cout <<"请输入你要删除的好友id"<<endl;
    cin >> in;
    Value j;
    j["Del_friend"]=in;
    Massage m(DEL_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))){
            if (r=="NULL")
            {
                cout<<"你与id为"<<in<<"还不是好友，请输入正确id"<<endl;
                delfriend(cfd,ID);
            }else if(r=="Succeed")
            {
                cout<<"你已将id为"<<in<<"的用户已成功删除"<<endl;
            }
            break;    
        }
    }
    return;
}

void Clenit::ignorefriend(int cfd,string ID)
{
string in;
    char r[BUFSIZ];
    cout <<"请输入你要删除的好友id"<<endl;
    cin >> in;
    Value j;
    j["Del_friend"]=in;
    Massage m(DEL_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))){
            if (r=="NULL")
            {
                cout<<"你与id为"<<in<<"还不是好友，请输入正确id"<<endl;
                delfriend(cfd,ID);
            }else if(r=="Succeed")
            {
                cout<<"你已将id为"<<in<<"的用户已成功删除"<<endl;
            }
            break;    
        }
    }
    return;
}
void Clenit::viewfriend(int cfd,string ID)
{

}
void Clenit::friends_menu(int cfd,string ID)
{
    string in, s;
    Value friends;

    FastWriter w;
    
    friends["sender"] = ID;
    while (1)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:添加好友    |" << endl;
        cout << "|    2:删除好友    |" << endl;
        cout << "|    3:查看好友    |" << endl;
        cout << "|    4:好友请求    |" << endl;
        cout << "|    5:屏蔽好友    |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin>>in;
        if(in==ADD_FRIEND){
            friendadd(cfd,ID);
            continue;
        }else if(in==DEL_FRIEND){
            delfriend(cfd,ID);
            continue;
        }else if(in==VIEW_FRIENDS){

        }else if(in==MAS_FRIEND){
              
        }else if(in==IGN_FRIEND){
            ignorefriend(cfd,ID);
        }else if (in==EXIT)
        {
            break;
        }
    }
    return; 
}