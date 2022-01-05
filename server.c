#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 100

int main()
{
    // 创建套接字
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定套接字
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("192.168.43.242");
    sockAddr.sin_port = htons(1234);
    bind(server_sock, (struct sockaddr *)&sockAddr, sizeof(sockAddr));

    // 进入监听状态
    listen(server_sock, 20);

    // 接受客户端请求
    struct sockaddr cltAddr;
    socklen_t nSize = sizeof(cltAddr);
    char buffer[BUF_SIZE] = {0};
    while (1)
    {
        // 阻塞直到客户端发来消息
        int client_sock = accept(server_sock, (struct sockaddr *)&cltAddr, &nSize);

        // 接受客户端消息
        int strLen = read(client_sock, buffer, BUF_SIZE);
        printf("Message form client: %s\n", buffer);

        // 给客户端回复消息
        printf("Input a string: \n");
        fgets(buffer, sizeof(buffer), stdin);
        write(client_sock, buffer, strLen);

        // 关闭套接字
        close(client_sock);
        // 重置缓冲区
        memset(buffer, 0, BUF_SIZE);
    }

    // 关闭套接字
    close(server_sock);
}
