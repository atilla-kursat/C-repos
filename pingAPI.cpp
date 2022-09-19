#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <WinSock2.h>
#include <WinSock.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>

void setwindows();
void allocmemory(const char* instring, int port);
void bind();
void send(char* instring);
bool ping();
WSADATA wsa;
struct sockaddr_in server;
int s = -1;
char* datapack[20];
using namespace std;


int main()
{   int selection;
    const char* cardaddress = "192.168.1.111";
    int port = 8;
    char data[20];
    uint8_t temparray[4];
    char formattedarray[15];
    int dotflag=0,j=0,temp=0;
    cout<<"welcome to pingAPI, enter what you want to accomplish \n 1-> Ping the card\n 2-> Make MCU ping the computer\n 3->Make MCU send current status \n 4->Make MCU ping a different address \n 5->Make MCU send UDP data to a different address\n";
    cin>>selection;

    switch (selection)
    {
    case 1:
        system("cls");
        int x;
        x = ping();
        if(x == 0){
            cout<<"Success!";
            getchar();
        }
        else{
            cout<<"Pinging was unsuccesful";
            getchar();
        }
        break;
    
    case 2:
        setwindows();
        allocmemory(cardaddress,port);
        bind();
        data[0] = 2;
        send(data);

        break;

    case 3:
        setwindows();
        allocmemory(cardaddress,port);
        bind();
        data[0] = 3;
        send(data);
        break;

    case 4:
    
    system("cls");
    data[0]=4;
    cout<<"enter the ip address you want to send a ping to";
    scanf("%d.%d.%d.%d",&temparray[0],&temparray[1],&temparray[2],&temparray[3]);
    for (int i = 0; i < 4; i++)
    {
        if(temparray[i]>255 || temparray[i]<0)
        {
            cout<<"No such ip exists, try again";
            getchar();
            exit(1);
        }
        data[1+i]=temparray[i];
    }
    setwindows();
    allocmemory(cardaddress,port);
    bind();
    send(data);
    break;

    case 5:
    system("cls");
    data[0]=5;
    cout<<"enter the ip address you want to send a UDP data to";
    scanf("%d.%d.%d.%d",&temparray[0],&temparray[1],&temparray[2],&temparray[3]);
     for (int i = 0; i < 4; i++)
    {
        if(temparray[i]>255 || temparray[i]<0)
        {
            cout<<"No such ip exists, try again";
            getchar();
            exit(1);
        }
        data[1+i]=temparray[i];
    }
    setwindows();
    allocmemory(cardaddress,port);
    bind();
    send(data);
    break;

    default:

        cout<<"select an item from menu!";
        getchar();
        break;
    }


}


void setwindows(){

        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("\nError: Windows socket subsytsem could not be initialized. Error Code: %d. Exiting..\n", WSAGetLastError());
        getchar();
        exit(1);
    }


        if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)    {
        printf("Error: Could not create socket: %s. Exiting..\n", strerror(errno));
        getchar();
        exit(1);
    }

}

void allocmemory(const char* instring, int port){

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr(instring); 
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

}

void bind(){
    if ( bind(s, (const struct sockaddr *)&server, sizeof(server)) < 0 ) 
    { 
        cout<<"bind failed"; 
        getchar();
        exit(1); 
    } 
}

void send(char* instring){

 sendto(s, (const char *)instring, strlen(instring), 0, (const struct sockaddr *) &server,  sizeof(server)); 
cout<<"data sent!";
getchar();
}

bool ping(){
    getchar();
    int x = system("ping 192.168.1.111");
    if (x==0){
    return 0;
    }
       else {
    return 1;
    }
}