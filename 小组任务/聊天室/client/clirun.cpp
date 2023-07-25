#include"../public/public.hppt"
#include"clit.hpp"
void Clenit::clirun()
{
    struct sockaddr_in serveradd;
    int cfd;
    cfd=Err::Socket(AF_INET,SOCK_STREAM,0);
    memset(&serveradd,0,sizeof(serveradd));
    serveradd.sin_family=AF_INET;
    serveradd.sin_port=htons(server_port);
    serveradd.sin_addr.s_addr=inet_addr(server_ip.c_str());
    int ret=Err::Connect(cfd,( struct sockaddr *)&serveradd,sizeof(serveradd));
    if(ret==0){
        Clenit::sign_menu(cfd);
    }else{
        cout<<"连接失败"<<endl;
    }
}
