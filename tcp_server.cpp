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
    int st = socket(AF_INET, SOCK_STREAM, 0);
    if(st<0)
    {
        perror("Ошибка. Невозможно вызвать сокет.");
        return -1;
    }

    struct sockaddr_in serv;
    char buffer[128];
    int result;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5555);
    serv.sin_addr.s_addr = INADDR_ANY;

    cout<<"Привет, это сервер."<<endl;
    result = bind(st, (struct sockaddr *)&serv, sizeof(serv));
    if(result<0)
    {
        perror("Ошибка. Невозможно связать сокет с адресом (bind).");
        return -1;
    }

    if (listen(st,7))
    {
        perror("Ошибка. Невозможно перевести сокет в режим ожидания запросов (listen).");
        return -1;
    }

    int st_listen = accept(st,NULL,NULL);
    if (st_listen<0)
    {
        perror("Ошибка. Невозможно невозможно принять запрос (accept).");
        return -1;
    }

    fill_n(buffer,128,0);

    result = recv(st_listen,buffer, sizeof(buffer),0);
    if(result<0)
    {
        perror("Ошибка. Невозможно получить данные.");
        return -1;
    }

    cout << "Сообщение от клиента: " << buffer;
    cout<<endl<<"Введите сообщение клиенту: ";
    fill_n(buffer,128,0);
    fgets(buffer,127,stdin);

    result = send(st_listen,buffer,sizeof(buffer),0);
    if(result<0)
    {
        perror("Ошибка. Невозможно отправить данные.");
        return -1;
    }

    cout << endl << "Ответ отправлен" << endl;

    int opt = 1;
    setsockopt (st, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt (st_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    close(st);
    close(st_listen);
    return 0;
}
