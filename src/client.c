#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <termios.h>

#define HOST "127.0.0.1"        // 根据你服务器的IP地址修改
#define PORT 6666                   // 根据你服务器进程绑定的端口号修改
//#define BUFFER_SIZ (4 * 1024)           // 4k的数据区域
#define BUFFER_SIZ 1           // 4k的数据区域


int main(void)
{
    struct termios oldt, newt;
    int ch;

    /* 获取当前终端设置 */
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    /* 将终端设置为不缓冲和不回显模式 */
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    int sockfd, ret;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZ];        //用于保存输入的文本

    // 创建套接字描述符
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create an endpoint for communication fail!\n");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(HOST);

    // 建立TCP连接
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
        printf("connect server fail...\n");
        close(sockfd);
        exit(1);
    }

    printf("connect server success...\n");
    printf("please enter some text: ");

    while (1) {
        ch = getchar();

        // printf("please enter some text: ");
        //fgets(buffer, BUFFER_SIZ, stdin);
        buffer[0]=ch;

        //输入了end，退出循环（程序）
        if(strncmp(buffer, "end", 3) == 0)
            break;

        write(sockfd, buffer, sizeof(buffer));
    }

    close(sockfd);
    exit(0);
}
