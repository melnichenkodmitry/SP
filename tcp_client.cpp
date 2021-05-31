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

int main (int argc, char * argv[])
{
    setlocale (LC_ALL, "Russian");
    int st = socket (AF_INET, SOCK_STREAM,0);
    if (st<0)
    {
        perror ("Ошибка. Невозможно вызвать сокет.");
        return -1;
    }

    struct sockaddr_in serv;
    int result;
    char buffer[128];
    serv.sin_family = AF_INET;
    serv.sin_port = htons (5555);
    serv.sin_addr.s_addr = inet_addr ("192.168.249.132");

    cout<<"Привет, это клиент!"<<endl;
    
    result = connect (st, (struct sockaddr *)&serv, sizeof(serv));
    if (result<0)
    {
        perror("Ошибка. Невозможно установить соединение с сервером (connect).");
        return -1;
    }

    fill_n (buffer,128,0);
    cout<<"Введите сообщение серверу: ";
    fgets(buffer,127,stdin);;

    result = send(st,buffer,sizeof(buffer),0);
    if (result<=0)
    {
        perror("Ошибка. Невозможно отправить данные.");
        return -1;
    }

    result = recv(st,buffer,sizeof(buffer),0);
    if (result<0)
    {
        perror("Ошибка. Невозможно получить данные.");
        return -1;
    }

    cout<<endl<<"Ответ получен"<<endl;
    cout<<"Сообщение от сервера: "<<buffer<<endl;

    close(st);
    return 0;
}
