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
#include <pthread.h>
#include "../include/get_video.h"
#include "../include/main.h"


int main()
{
    pthread_t thread; // 用于存放线程标识符的变量
    // 创建并启动摄像头捕获线程
    struct termios oldt, newt;
    int ch;
    int sockfd, ret;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZ];        //用于保存输入的文本


    /* 获取当前终端设置 */
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    /* 将终端设置为不缓冲模式 */
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


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
    printf("Please enter your command: ");

    while (1) {
        ch = getchar();
        buffer[0]=ch;
        

        if(ch=='v')
        {
            //如果键盘输入v，则创建新线程，在新线程中使用opencv开启摄像头，避免阻塞
            int result = pthread_create(&thread,NULL,get_video,NULL);
            if (result != 0) {  
                fprintf(stderr, "Error: Failed to create capture thread.\n");
                return 1;
            }
        }
        write(sockfd, buffer, sizeof(buffer));

    }

    close(sockfd);
    pthread_join(thread, NULL);
    printf("Main thread: Capture thread has finished.\n");
    exit(0);
}
