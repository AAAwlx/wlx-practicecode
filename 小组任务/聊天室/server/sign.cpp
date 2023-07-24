#include"ser.hpp"
#include"../public/public.hpp"
void Server::sign_up(int cfd,Massage m)//注册
{
    Value info;
    string n=m.Deserialization("Name");
    string p=m.Deserialization("Pass");
    string q=m.Deserialization("Question");
    string a=m.Deserialization("Answer");
    User u(n,p,q,a);//初始化用户类
    string ID=u.distribute_id();//分配ID
    info["ID"]=ID;
    Massage m1(SIGN_UP,info,"0","0");
    string s=m1.Serialization();
    Err::Write(cfd,s.c_str(),s.length());//向客户端返回ID
    u.save_user(Userm);//保存用户信息
}
void Server::login(int cfd,Massage m)
{
    string id=m.Deserialization("ID");
    
}
bool Server::sign_menu(int cfd)
{
    cout << "进入sign" << endl;
    char r[BUFSIZ];
    while (fd_in[cfd]==false)
    {
        if(Err::Read(cfd,r,sizeof(r))>0)
        {
            Massage m(r);
            string o=m.takeMassage("option");
            cout << "sign循环" << endl;
            if(o==EXIT){
                Err::Close(cfd);
                return false;
            }else if(o==SIGN_UP)//注册
            {
                sign_up(cfd,m);
            }else if(o==LOGIN)//登陆
            {
                fd_in[cfd]=true;
            }
        }
    }
    
}