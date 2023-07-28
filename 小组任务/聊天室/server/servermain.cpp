#include"ser.hpp"
#include"public.hpp"
redisContext* Library;
//启用一个redis库
int main()
{
    Server server(SERVERPORT,"127.0.0.1");
    server.serun();
}