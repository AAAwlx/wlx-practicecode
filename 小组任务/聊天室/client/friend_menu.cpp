#include"public.hpp"
#include"clit.hpp"
void Clenit::friendadd(string ID)
{
    string in;
    char a[BUFSIZ];
    Value j;
    cout<<"请输入新好友的id"<<endl;
    cin>>in;
    j["NEW_friendid"]=in;
    j["ID"]=ID;
    Massage m(ADD_FRIEND,j,"0","0");
    string s=m.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
    string r;
    while (1)
    {
        if(Err::Read(cfd,a,sizeof(a))){
            Massage m1(a);
            r=m1.Deserialization("return");
            if (r=="NULL")
            {
                cout<<"没有此用户，请再试一次"<<endl;
                friendadd(ID);
            }else if (r=="NotOnline")
            {
                cout<<"对方暂时不在线，稍后为您发送请求"<<endl;
            }else if(r=="Succeed")
            {
                cout<<"好友请求已发送"<<endl;
            }else if(r == "befriends"  ){
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
            cout<<r<<endl;
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
    cout<<"已发送查看好友状态请求"<<endl;
    while (1)
    {
        char r[BUFFERSIZE];
        if(Err::Read(cfd,r,sizeof(r))>0){
            Massage m(r);
            std::variant<Json::Value, std::string> result=m.takeMassage("content");
            Value flist=std::get<Json::Value>(result);
            Json::Value::Members members = flist.getMemberNames();
            for (const auto& key : members) {
                std::cout << "好友: " << key << "在线状态" << flist[key].asString() << std::endl;
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
    cout<<"已发送查看好友申请请求"<<endl;
    while (1)
    {
        char r[BUFFERSIZE];
        if(Err::Read(cfd,r,sizeof(r))>0){
            cout<<r<<endl;
            std::variant<Json::Value, std::string> result=m.takeMassage("content");
            Value rlist=std::get<Json::Value>(result);
            cout<<rlist<<endl;
            for (const auto& key : rlist.getMemberNames()) {
                std::cout << "id为: " << key <<"请求添加你为好友" << std::endl;
            }
            break;
        }
    }
    Value info;
    while (1)
    {
        string in,o;
        cout<<"请你输入你要处理的好友(输入-1结束)"<<endl;
        cin>>in;
        if(in=="-1"){
            break;
        }
        cout<<"请你输入你要处理的选项(accapt或refuse)"<<endl;
        while(1){
            cin>>o;
            if(o!="accapt"&&o!="refuse"){
                cout<<"您输入的选项不符合规范，请再试一次"<<endl;
            }else{
                break;
            }
        }
        info[in]=o;
    }
    Massage m1(MAS_FRIEND,info,"0","0");
    string s1=m1.Serialization();
    Err::Write(cfd,s1.c_str(),s.length());
    cout<<s1<<endl;
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
        cout << "|    6:解除屏蔽    |" << endl;
        cout << "|    0:退出界面    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin>>in;
        system("clear");
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
            Clenit::Exit();
            break;
        }else{
            cout<<"您输入的选项不符合规范,请重试"<<endl;
        }
    }
    return; 
}