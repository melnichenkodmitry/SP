#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <fstream>
#include <sys/wait.h>
using namespace std;

int freq = 0;
sem_t semaphore;
struct ttf_arg
{
    char *sent;
    char *tri;
};

void* findt(void *args)
{
    ttf_arg *arg = (ttf_arg*) args;
    string str = arg->sent;
    string trigram = arg->tri;
    int i = str.find (trigram,0);

    fstream to_file;
    to_file.open("input.txt", ios::out);
    while (i != string::npos)
    {
        i = str.find(trigram, i + 1);
        to_file<<"1"<<endl;
    }
    to_file.close();
    sem_post(&semaphore);
    return 0; 
}

void* count(void *args)
{
    sem_wait(&semaphore);
    fstream from_file;
    from_file.open("input.txt",ios::in);
    if (from_file)
    {
        string buf;
        while (getline(from_file, buf))
        {
            freq = freq + stoi(buf);
        }
    }
    from_file.close();
    return 0;
}

int main()
{
    int pos = 0, i = 0;
    string text, temp, trigram;

    setlocale (LC_ALL, "Russian");
    cout << "Введите текст:" << endl;
    getline(cin,text);

    cout << "Введите триграмму: " << endl;
    getline(cin,trigram);

    for (i=text.find(".", i++); i!= string::npos; i = text.find(".", i+1))
    {
        temp = text.substr(pos, i-pos);
        pos = i;

        char *arr_temp = new char[temp.length()];
        char *arr_trigram = new char[trigram.length()];
        strcpy(arr_temp, temp.c_str());
        strcpy(arr_trigram, trigram.c_str());
        pthread_t thread1;
        pthread_t thread2;

        ttf_arg arg;
        arg.sent = arr_temp;
        arg.tri = arr_trigram;
        sem_init(&semaphore, 0, 0);

        pthread_create(&thread1, NULL, findt, (void*) &arg);
        pthread_create(&thread2, NULL, count, NULL);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        sem_destroy(&semaphore);
        delete[] arr_temp;
        delete[] arr_trigram;
    }
    remove ("input.txt");
    cout << "\nЧастота '" << trigram << "' триграммы: " << freq << endl;
    return 0;

}
