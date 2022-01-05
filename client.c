#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 100

int main(){
    // 创建套接字
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(9080);

    char bufSend[BUF_SIZE] = {0};
    char bufRecv[BUF_SIZE] = {0};

    while (1) {
        // 创建套接字
        int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        // 连接服务器
        connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));

        // 获取用户输入的字符串并发送给服务器
        printf("Input a string:");
        fgets(bufSend, sizeof(bufSend), stdin);
        send(sock, bufSend, BUF_SIZE, 0);

        //  接受服务器传回来的消息
        recv(sock, bufRecv, BUF_SIZE, 0);
        printf("Message form server: %s\n", bufRecv);

        // 重置缓冲区
        memset(bufSend, 0, BUF_SIZE);
        memset(bufRecv, 0, BUF_SIZE);

        // 关闭套接字
        close(sock);
    }

    return 0;
}
