#include"public.hpp"
#include"clit.hpp"
void Clenit::friendadd(string ID)
{
    string in;
    char r[BUFSIZ];
    Value j;
    cout<<"请输入新好友的id"<<endl;
    cin>>in;
    j["NEW_friendid"]=in;
    j["ID"]=ID;
    Massage m(ADD_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))){
            if (r=="NULL")
            {
                cout<<"没有此用户，请再试一次"<<endl;
                friendadd(ID);
            }else if (r=="Refuse")
            {
                cout<<"对方拒绝了你的申请"<<endl;
            }else if(r=="Succeed")
            {
                cout<<"好友请求已发送"<<endl;
            }else if(strcmp(r, "befriends") == 0){
                cout << "你们已经是好友了" << endl;
            }
            break;    
        }
    }
    return;
}
void Clenit::delfriend(string ID)
{
    string in;
    char r[BUFSIZ];
    cout <<"请输入你要删除的好友id"<<endl;
    cin >> in;
    Value j;
    j["Del_friend"]=in;
    j["ID"]=ID;
    Massage m(DEL_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))){
            if (r=="NULL")
            {
                cout<<"你与id为"<<in<<"还不是好友，请输入正确id"<<endl;
                delfriend(ID);
            }else if(r=="Succeed")
            {
                cout<<"你已将id为"<<in<<"的用户已成功删除"<<endl;
            }
            break;    
        }
    }
    return;
}

void Clenit::ignorefriend(string ID)
{
    string in;
    char r[BUFSIZ];
    cout <<"请输入你要屏蔽的好友id"<<endl;
    cin >> in;
    Value j;
    j["Ign_friend"]=in;
    j["ID"]=ID;

    Massage m(DEL_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))){
            if (r=="NULL")
            {
                cout<<"你与id为"<<in<<"还不是好友，请输入正确id"<<endl;
                delfriend(ID);
            }else if(r=="Succeed")
            {
                cout<<"你已将id为"<<in<<"的用户已成功屏蔽"<<endl;
            }
            break;    
        }
    }
    return;
}
void Clenit::viewfriend(string ID)
{
    Value j;
    j["ID"]=ID;
    Massage m(VIEW_FRIENDS,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    cout<<"已发送查看请求"<<endl;
    while (1)
    {
        char r[BUFFERSIZE];
        if(Err::Read(cfd,r,sizeof(r))>0){
            Massage m(r);
            std::variant<Json::Value, std::string> result=m.takeMassage("option");
            Value flist=std::get<Json::Value>(result);
            for (const auto& key : flist.getMemberNames()) {
                std::cout << "好友: " << key << ", 状态 " << flist[key].asString() << std::endl;
            }
            break;
        }
    }
   
}
void Clenit::friendrequests(string ID)
{
    Value j;
    j["ID"]=ID;
    Massage m(MAS_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
}
void Clenit::friends_menu(string ID)
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
            Clenit::friendadd(ID);
        }else if(in==DEL_FRIEND){
            Clenit::delfriend(ID);
        }else if(in==VIEW_FRIENDS){
            Clenit::viewfriend(ID);
        }else if(in==MAS_FRIEND){
            Clenit::friendrequests(ID);
        }else if(in==IGN_FRIEND){
            Clenit::ignorefriend(ID);
        }else if (in==EXIT)
        {
            break;
        }else{
            cout<<"您输入的选项不符合规范,请重试"<<endl;
        }
    }
    return; 
}