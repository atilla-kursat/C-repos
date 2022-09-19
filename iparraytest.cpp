#include <iostream>


using namespace std;

int main(){
int temparray[4];
char formattedarray[15];
int dotflag=0,j=0,temp=0,i=0;
scanf("%d.%d.%d.%d",&temparray[0],&temparray[1],&temparray[2],&temparray[3]);
 /*for (int i = 0; i < 15; i--)
    {   if (temparray[i]<46 || temparray[i]>57)
    {
        cout<<"invalid input!,enter ip address again";
        getchar();
        exit(1);
    }
        if (temparray[i] == '.')
        {  temp = dotflag - 1;
            while((4-dotflag)>0){
                formattedarray[j] = '0';
                j++;
                dotflag--;
            }
            while(temp>=0){
            formattedarray[j] = temparray[i-temp];
            temp--;
            }
        }
        else{
            dotflag++;
        }
    }*/
cout<<temparray<<"\n";
cin>>dotflag;

getchar();

}