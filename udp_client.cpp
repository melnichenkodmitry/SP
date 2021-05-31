#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char * argv[])
{
    setlocale (LC_ALL, "Russian");
    int st = socket(AF_INET, SOCK_DGRAM,0);
    if (st<0)
    {
        perror("Ошибка. Невозможно вызвать сокет.");
        return -1;
    }

    struct sockaddr_in serv;
    unsigned int len = sizeof(serv);
    char buf[128];
    int res;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(6666);
    serv.sin_addr.s_addr = inet_addr ( "192.168.249.132" );

    cout<<"Привет, это клиент!"<<endl;

    cout<<"Введите сообщение серверу: ";
    fill_n(buf,128,0);
    fgets(buf,127,stdin);

    res = sendto(st,buf,128,0,(struct sockaddr *)&serv,sizeof(serv));
    if (res<=0)
    {
        perror("Ошибка. Невозможно отправить данные.");
        return -1;
    }

    fill_n(buf,128,0);

    res = recvfrom(st,buf,128,0,(struct sockaddr *)&serv,&len);
    if (res<0)
    {
        perror("Ошибка. Невозможно получить данные.");
        return -1;
    }

    cout<<endl<<"Ответ получен"<<endl;
    cout<<"Сообщение от сервера: "<<buf<<endl;
    close(st);
    return 0;
}
