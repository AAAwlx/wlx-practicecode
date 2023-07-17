#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024

int main()
{
    int server_socket, client_sockets[MAX_CLIENTS];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // 创建服务器套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    // 绑定服务器地址到套接字
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(server_socket, 5) == -1)
    {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for connections...\n");

    // 初始化客户端套接字数组
    memset(client_sockets, 0, sizeof(client_sockets));
    int n = 0;
    while (1)
    {
        // 接受新的客户端连接
        while (n<=MAX_CLIENTS)
        {
            int new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
            if (new_socket == -1)
            {
                perror("Failed to accept");
                exit(EXIT_FAILURE);
            }
            else
            {
                
                n++;
                printf("%d\n",n);
            }
            if (n <= MAX_CLIENTS)
            {
                int i;
                for (i = 0; i < MAX_CLIENTS; i++)
                {
                    if (client_sockets[i] == 0)
                    {
                        client_sockets[i] = new_socket;
                        printf("Accepted new connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                        break;
                    }
                }
            }
            else
            {
                
                printf("Max clients reached. Connection rejected.\n");
                close(new_socket);
                break;
            }
            
        }
        // 接收和处理客户端数据
        /*
        memset(buffer, 0, BUFFER_SIZE);
         int bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0);
         if (bytes_received > 0) {
             printf("Received data from %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
         } else if (bytes_received == 0) {
             printf("Connection closed by %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
             close(new_socket);
             client_sockets[i] = 0;
         } else {
             perror("Failed to receive data");
             close(new_socket);
             client_sockets[i] = 0;
         }
        */
    }

    // 关闭服务器套接字
    close(server_socket);

    return 0;
}
