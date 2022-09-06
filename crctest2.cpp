#include <stdio.h>
#include <zlib.h>
#include <iostream>

using namespace std;

int main(){
    int dummy;
char data[12];    
    for (int i = 0; i < 11; i++)
    {
        data[i] = '2';
    } 
const unsigned char *buf = (unsigned char *)data;
cout << buf;
cin>>dummy;

uLong crc = crc32(0L, Z_NULL, 0);


        crc = crc32(crc,buf,11);
    
    
    cout<<crc;
    cin>>dummy;

}