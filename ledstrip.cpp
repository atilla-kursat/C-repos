#include <iostream>
#include <stdio.h>
#include <windows.h>


using namespace std;

HANDLE hComm;
char ComPortName[] = "\\\\.\\COM8";
bool status;
DWORD dwEventMask;
char temp;
DWORD numberofbytes;
DCB dcb;
COMMTIMEOUTS timeouts;

void portman(){

  hComm = CreateFile( ComPortName,                  
                            GENERIC_READ | GENERIC_WRITE, 
                            0,                            
                            0,                      
                            OPEN_EXISTING,                
                            0,                            
                            0);  

 if(hComm == INVALID_HANDLE_VALUE){
    cout<<"Cannot open port!";
    exit(6);                       
 }        
dcb.BaudRate = CBR_9600;
dcb.ByteSize = 8;
dcb.Parity = NOPARITY;
dcb.StopBits = ONESTOPBIT;
dcb.DCBlength = sizeof(dcb);
if(!SetCommState(hComm,&dcb))
{
    cout<<"Cannot get a response";
    exit(7);

}
    timeouts.ReadIntervalTimeout = 200; 
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 0;
if (!SetCommTimeouts(hComm, &timeouts)){
    cout<<"cannot set timeouts";
    exit(8);

}

}


bool send_data(char* instring){
DWORD numbytes_ok;   
    if(!WriteFile(hComm,instring,11,&numbytes_ok,NULL));
{
    cout<<"writing error   sent number:"<< numbytes_ok;
    return 1;
}

    

return 0;
}

bool receive_data(){
LPDWORD numbytes_ok;
char readfile[50];
if(!ReadFile(hComm,readfile,sizeof(readfile),numbytes_ok,NULL))
   { cout<<"reading error";
    return 1;}

    return 0;

    
}

int main(){



char select[17] = {9};
char datafile[11] = {0};
int colorint;
int j=0;
char jchar;

cout<< "welcome to the led control program \n enter which leds you want to control with a comma in  between (enter a for all):";
cin>> select;

if(select[0]=='a')
    {   
        for (int i = 0; i < 17; i+=2)
        { 
        
              
          select[i]=j+48;
          j++;
        }
        
       
    }


portman();

for (int i=0; i<17; i+=2){
    if (!select[i]==9)
    {
        datafile[0]= select[i]-48;
        cout<<"enter value of green for led number "<<select[i]<<" ==> ";
        cin>> colorint;
        while (colorint>255 | colorint<0){

            cout<<"incorrect entry, try again";
            cin>>colorint;
        }
        while(colorint>100)
        {
            datafile[1]++;
            colorint-=100;
        }
        while(colorint>10)
        {
            datafile[2]++;
            colorint-=10;
        }
        while(colorint>0)
        {
            datafile[3]++;
            colorint--;
        }

        cout<<"enter value of red for led number "<<select[i]<<" ==> ";
        cin>> colorint;
        while (colorint>255 | colorint<0){

            cout<<"incorrect entry, try again";
            cin>>colorint;
        }
        while(colorint>100)
        {
            datafile[4]++;
            colorint-=100;
        }
        while(colorint>10)
        {
            datafile[5]++;
            colorint-=10;
        }
        while(colorint>0)
        {
            datafile[6]++;
            colorint--;
        }


        cout<<"enter value of blue for led number "<<select[i]<<" ==> ";
        cin>> colorint;
        while (colorint>255 | colorint<0){

            cout<<"incorrect entry, try again";
            cin>>colorint;
        }
        while(colorint>100)
        {
            datafile[7]++;
            colorint-=100;
        }
        while(colorint>10)
        {
            datafile[8]++;
            colorint-=10;
        }
        while(colorint>0)
        {
            datafile[9]++;
            colorint--;
        }

        cout<<"enter brigthness 1 for lowest 4 for highest==>";
        cin>> colorint;
        while (colorint>4 | colorint<0){

            cout<<"incorrect entry, try again";
            cin>>colorint;
        }
        datafile[10]=colorint+48;

        send_data(datafile);

        for (int i = 0; i < 12; i++)
        {
            datafile[i]='0';
        }
        
        

    }
    


}








}