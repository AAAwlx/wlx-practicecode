#include"ser.hpp"
#include"public.hpp"
void Server::sign_up(int cfd,Massage m)//注册
{
    Value info;
    string n=m.Deserialization("Name");
    string p=m.Deserialization("Pass");
    string q=m.Deserialization("Question");
    string a=m.Deserialization("Answer");
    User u(n,p,q,a,Library);//初始化用户类
    string ID=u.distribute_id();//分配ID
    Err::Write(cfd,ID.c_str(),ID.length());//向客户端返回ID
    u.save_user();//保存用户信息
}
void Server::login(int cfd,Massage m)//登陆
{
    string id=m.Deserialization("ID");//用户输入的id
    User u(id,Library);
    string Pass2=u.Inquire("Pass");
    if(Pass2=="0")//未在用户信息库中查找到该id
    {
        Err::Write(cfd,"NULL",sizeof("Null"));
        return;
    }
    string Pass1=m.Deserialization("Pass");//用户发来的密码
    if(Pass1==Pass2)
    {
        fd_in[cfd]=true;
        Err::Write(cfd,"succeed",sizeof("succeed"));
        //main_menu(cfd);
    }else
    {
        Err::Write(cfd,"fial",sizeof("fial"));
    }
}
void Server::resetpassword(int cfd,Massage m)
{
    string id=m.Deserialization("ID");
    User u(id,Library);
    Value v;
    string Q=u.Inquire("Question");
    string A=u.Inquire("Answer");
    string Pass2=u.Inquire("Pass");
    v["Question"]=Q;
    v["Answer"]=A;
    v["Pass"]=Pass2;
    FastWriter w;
    string s=w.write(v);
    Massage m2(Blank_option,s,"0","0");
}
bool Server::sign_menu(int cfd)
{
    cout << "进入sign" << endl;
    char r[BUFSIZ];
    int count=0;
    while (fd_in[cfd]==false)
    {
        if(Err::Read(cfd,r,sizeof(r))>0)
        {
            Massage m(r);
            string o=m.takeMassage("option");
            cout << "sign循环" << endl;
            if(o==EXIT||count>3){
                Err::Close(cfd);
                return false;
            }else if(o==SIGN_UP)//注册
            {
                Server::sign_up(cfd,m);
            }else if(o==LOGIN)//登陆
            {
                count++;
                Server::login(cfd,m);
            }
            if (r==Reset_Password)
            {
                Server::resetpassword(cfd,m);
            }
        }
    }
    return true;
}