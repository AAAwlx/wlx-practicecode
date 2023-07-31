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
    return;
}
void Server::login(int cfd,Massage m,int count)//登陆
{
    string id=m.Deserialization("ID");//用户输入的id
    User u(id,Library);
    string Pass2=u.Inquire("Pass");
    cout<<Pass2<<"+"<<endl;
    Err::Write(cfd,Pass2.c_str(),Pass2.length());
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
    Massage m2(Reset_Password,v,"0","0");
    string s1=m2.Serialization();
    cout<<s1<<endl;
    Err::Write(cfd,s1.c_str(),s1.length());
}
bool Server::sign_menu(int cfd)
{
    cout << "进入sign" << endl;
    char r[BUFSIZ];
    int count=0;
    
    while (fd_in[cfd]==false)
    {
        if((read(cfd, r, sizeof(r)))>0)
        {
            cout << r << endl;
            string s=r;
            Massage m(s);
            std::variant<Json::Value, std::string> result=m.takeMassage("option");
            std::string o = std::get<std::string>(result);
            cout << o << endl;
            cout << "sign循环" << endl;
            if(o==EXIT){
                Err::Close(cfd);
                cout<<cfd<<"已离开"<<endl;
                return true;
            }else if(o==SIGN_UP)//注册
            {
                Server::sign_up(cfd,m);
            }else if(o==LOGIN)//登陆
            {
                count++;
                Server::login(cfd,m,count);
            }
            if (o==Reset_Password)
            {
                Server::resetpassword(cfd,m);
            }
            if (o=="succeed")
            {
                cout<<cfd<<"已登陆"<<endl;
                string ID=m.Deserialization("ID");
                user_cfd[ID]=cfd;
                //Server::()
                user_cfd.erase(ID);
            }
            
        }
    }
    return false;
}