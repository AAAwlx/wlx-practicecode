#include"ser.hpp"
#include"public.hpp"
void Server::friendadd(int cfd,Massage m)
{
    string s1=m.Deserialization("NEW_friendid");//被加人的id
    User f(s1,Library);
    if(f.Inquire("ID")=="0"){//查询是否有此人存在
        Err::Write(cfd,"NULL",sizeof("NULL"));
        return ;
    }    
    string s2=m.Deserialization("ID");//
    User u(s2,Library);
    Value j= u.friend_List;
    if(j.isMember(s1)){
        Err::Write(cfd,"befriends",sizeof("befriends"));//如果好友列表中有被加人
        return;
    }else{
        int cfd2=user_cfd.at(s1);
        Value j;
        j["ID"]=s2;
        Massage m2(MAS_FRIEND,j,"0","0");
        string s3=m2.Serialization();
        Err::Write(cfd2,s3.c_str(),s3.length());//该请求应该被保存到被加人的好友申请的记录中
        Err::Write(cfd,"succeed",sizeof("succeed"));//向请求人发送请求成功转发
    }    
}
void Server::delfriend(int cfd,Massage m)
{
    string s1=m.Deserialization("Del_friend");
    string s2=m.Deserialization("ID");
    User u(s2,Library);
    Value j= u.friend_List;
    if (j.isMember(s1))
    {
        Err::Write(cfd,"NULL",sizeof("NULL"));
    }else{
        u.delete_friend(s1);
        Err::Write(cfd,"Succeed",sizeof("Succeed"));
    }
}
void Server::ignorefriend(int cfd,Massage m)
{
    string s1=m.Deserialization("Ign_friend");
    string s2=m.Deserialization("ID");
    User u(s2,Library);
    Value j= u.friend_List;
    if (j.isMember(s1))
    {
        Err::Write(cfd,"NULL",sizeof("NULL"));
    }else{
        u.shield_friend (s1);
        Err::Write(cfd,"Succeed",sizeof("Succeed"));
    }
}
void Server::viewfriend(int cfd,Massage m)
{
    string s2=m.Deserialization("ID");
    User u(s2,Library);
    Value j= u.friend_List;
    Value flist;
    if (j.isObject()) {
        Json::Value::Members members = j.getMemberNames();
        for (const auto& key : members) {
            int count=user_cfd.count(key);
            if(count>0){
                flist[key]="online";
            }else{
                flist[key]="not online";
            }
        }
    } 
    
    Massage m1("0",flist,"0","0");
    string s=m1.Serialization();
    Err::Write(cfd,s.c_str(),s.length());
}
void Server::friends_menu(int cfd)
{
    cout<<cfd<<"已进入好友管理界面"<<endl;
    char r[BUFFERSIZE];
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))>0){
            cout<<r<<endl;
            Massage m(r);
            string s=m.takeMassage("option");
            if (s==ADD_FRIEND){
                friendadd(cfd,m);
            }else if(s==DEL_FRIEND){
                delfriend(cfd,m);
            }else if(s==VIEW_FRIENDS){
                viewfriend(cfd,m);
            }else if(s==MAS_FRIEND){

            }else if(s==IGN_FRIEND){
                ignorefriend( cfd,m);
            }
        }    
    }
}