#include "public.hpp"
#include "clit.hpp"
std::atomic<bool> stopFlag;
Clenit::Clenit(int port, string ip)
    : server_port(port), server_ip(ip)
{
}
// 客户端关闭前关闭其与服务器连接的套接字
Clenit::~Clenit()
{
    Err::Close(cfd);
}
void Clenit::clirun()
{
    struct sockaddr_in serveradd;
    cfd=Err::Socket(AF_INET,SOCK_STREAM,0);
    memset(&serveradd,0,sizeof(serveradd));
    serveradd.sin_family=AF_INET;
    serveradd.sin_port=htons(server_port);
    serveradd.sin_addr.s_addr=inet_addr(server_ip.c_str());
    int ret=Err::Connect(cfd,( struct sockaddr *)&serveradd,sizeof(serveradd));
    if(ret==0){
        Clenit::sign_menu();
    }else{
        cout<<"连接失败"<<endl;
    }
}
