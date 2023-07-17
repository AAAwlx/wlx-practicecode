#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#define BUFSIZE 1024
#define port 12345
#define MAX_CLIENTS 10
enum
{
    STATE_R = 1, /* 读态*/
    STATE_W,     /* 写态 */
    STATE_Ex,    /* 异常态 */
    STATE_T      /* 退出态 */
};
typedef struct fsm_t
{
    int state; // 状态
    int rfd;   // 读端
    int wfd;   // 写端
    char buffer[BUFSIZE];

} fsm_t;

void sys_error(char *p)
{
    perror(p);
    exit(0);
}
int main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    int cfd[MAX_CLIENTS];
    if (sfd == -1)
    {
        sys_error("socket()");
    }
    struct sockaddr_in sever, client;
    memset(&sever, 0, sizeof(sever));
    sever.sin_family = AF_INET;
    sever.sin_port = htons(port);
    sever.sin_addr.s_addr = htonl(INADDR_ANY);
    int opt = 1;
    // setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int ret = bind(sfd, (const struct sockaddr *)&sever, sizeof(sever));
    if (ret == -1)
    {
        sys_error("bind()");
    }
    ret = listen(sfd, 64);
    if (ret == -1)
    {
        sys_error("listen()");
    }
    int n = 0;
    int csize = sizeof(client);
    printf("1");
    fsm_t *fsm = (fsm_t *)malloc(sizeof(fsm_t) * MAX_CLIENTS / 2);
    while (1)
    {
        while (1)
        {
            int i;
            int newfd = accept(sfd, (struct sockaddr *)&client, &csize);
            for (i = 0; i < MAX_CLIENTS; i++)
            {
                if (cfd[i] == 0)
                {
                    cfd[i] = newfd;
                    printf("Accepted new connection from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                    break;
                }
            }
            if (i == MAX_CLIENTS)
            {
                printf("Max clients reached. Connection rejected.\n");
                close(newfd);
                continue;
            }
        }
    }
    return 0;
}