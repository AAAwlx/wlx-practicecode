#include"ser.hpp"
#include"public.hpp"

void Server::main_menu(int cfd,string ID)
{
    char r[BUFFERSIZE];
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))>0){
            cout<<r<<endl;
            Massage m(r);
            std::variant<Json::Value, std::string> result=m.takeMassage("option");
            std::string s = std::get<std::string>(result);
            if (s==PRIVATE){
                
            }else if(s==GROUP){

            }else if(s==FRIENDS_MENU){
                friends_menu(cfd);
            }else if(s==FILE_MANAGE){

            }else if (s==EXIT)
            {
                size_t numDeleted = user_cfd.erase(ID);//删除标记在线的键值对
                if (numDeleted > 0) {
                    std::cout << "已删除键为 " << ID << " 的键值对" << std::endl;
                }
                break;
            }
        }    
    }
    return ;
}