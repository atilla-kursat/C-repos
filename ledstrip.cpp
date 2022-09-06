#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <zlib.h>


using namespace std;

uint8_t result[4];
char packet[18];
char readfile[1];
HANDLE hComm;
char ComPortName[] = "\\\\.\\COM8";
bool status;
DWORD dwEventMask;
char temp;
DWORD numberofbytes;
DCB dcb;
COMMTIMEOUTS timeouts;
bool receive_data();


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
    WriteFile(hComm,instring,18,&numbytes_ok,NULL);
    /*receive_data();
    if(!readfile[1]){
        cout<<"\ncorrupted data was sent, trying again...";
        WriteFile(hComm,instring,18,&numbytes_ok,NULL);
    }
    else{
        cout<<"\n successful transmission";
    }
    */
    return 0;
}

void combinedata(char* data){
int checksum=0;
int j=1;
packet[0] = 75;//start of file
for (int i = 0; i < 11; i++)//data packet and checksum calc
{
    packet[j]=data[i];
    checksum+=data[i];
    j++;
}
packet[j]=checksum;//storing checksum
for (int i = 0; i < 4; i++)//storing crc value
{
    j++;
    packet[j] = result[i];
}
packet[j+1] = 85;//end of file


}



bool receive_data(){
LPDWORD numbytes_ok;

if(!ReadFile(hComm,readfile,1,numbytes_ok,NULL))
   { cout<<"reading error";
    return 1;}


    return 0;

    
}


void crc_calc(char* input){
     
char data[12];
 
int n = 0;   
    for (int i = 0; i < 11; i++)
    {
        data[i] = input[i]+48;
    } 
const unsigned char *buf = (unsigned char *)data;


uLong crc = crc32(0L, Z_NULL, 0);


 crc = crc32(crc,buf,11);
 cout<< "\n" <<crc << "\n";
for (int i = 0; i < 4; i++)
{

    result[i] = (crc >> n) & 0xFF;
    n+=8;
}

   

   
}




int main(){



char select[17];
for (int i = 0; i < 18; i++)
{
    select[i]='k';
}

char datafile[11];
int colorint;
int j=0;
char jchar;

cout<< "welcome to the led control program \n enter which leds you want to control with a comma in  between (enter a for all):";
cin>> select;

if(select[0]=='a')
    {   
        for (int i = 0; i < 16; i+=2)
        { 
        
              
          select[i]=j+48;
          j++;
        }
        
       
    }


portman();


for (int i=0; i<16; i+=2){
    if (select[i] != 'k')
    {
        datafile[0]= select[i]-48;
        cout<<"enter value of green for led number "<<select[i]<<" ==> ";
        cin>> colorint;
        while (colorint>255 | colorint<0){

            cout<<"incorrect entry, try again";
            cin>>colorint;
        }
        while(colorint>=100)
        {
            datafile[1]++;
            colorint-=100;
        }
        while(colorint>=10)
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
        while(colorint>=100)
        {
            datafile[4]++;
            colorint-=100;
        }
        while(colorint>=10)
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
        while(colorint>=100)
        {
            datafile[7]++;
            colorint-=100;
        }
        while(colorint>=10)
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
        datafile[10]=colorint;
        crc_calc(datafile);
        combinedata(datafile);
        send_data(packet);

        for (int i = 0; i < 12; i++)
        {
            datafile[i]=0;
        }
        
        

    }
    else{
        datafile[0]=8;
        i=17;
        sleep(1);
        crc_calc(datafile);
        combinedata(datafile);
        send_data(packet);
        
    }
    
    


}








}