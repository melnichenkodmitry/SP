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

using namespace std;

int main(int argc, char * argv[])
{
    setlocale (LC_ALL, "Russian");
    int st = socket (AF_INET, SOCK_DGRAM,0);
    if (st<0)
    {
        perror("Ошибка. Невозможно вызвать сокет.");
        return -1;
    }

    struct sockaddr_in serv, cli;
    char buf[128];
    unsigned int len = sizeof(cli);
    int res;

    serv.sin_family = AF_INET;
    serv.sin_port = htons (6666);
    serv.sin_addr.s_addr = INADDR_ANY;

    cout<<"Привет, это сервер!"<<endl;

    res = bind(st, (struct sockaddr *)&serv, sizeof(serv));
    if (res<0)
    {
        perror("Ошибка. Невозможно связать сокет с адресом (bind).");
        return -1;
    }

    fill_n(buf,128,0);
    res = recvfrom(st,buf,128,0,(struct sockaddr *)&cli, &len);
    if (res<0)
    {
        perror("Ошибка. Невозможно получить данные.");
        return -1;
    }

    cout<<"Сообщение от клиента: "<<buf;
    cout<<endl<<"Введите сообщение клиенту: ";
    fill_n(buf,128,0);
    fgets(buf,127,stdin);

    res = sendto (st,buf,128,0,(struct sockaddr *)&cli, sizeof(cli));
    if (res<0)
    {
        perror("Ошибка. Невозможно отправить данные.");
        return -1;
    }

    cout<<endl<<"Ответ отправлен"<<endl;
    close(st);
    return 0;
}
