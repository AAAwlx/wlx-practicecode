#include"ser.hpp"
#include"../public/public.hpp"
int main()
{
    Server server(SERVERPORT,"127.0.0.1");
    server.serun();
}