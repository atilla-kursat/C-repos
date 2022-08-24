#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
int x;
cout<<"enter the desired width and length of array===> ";
cin>>x;
int arr1[x][x];

for (int i = 0; i < x; i++)
{
    for (int n = 0; n < x; n++)
    {   
        if (rand()%2==0)
        arr1[i][n] = 0;
        else
        arr1[i][n] = 1;
    }
    
}

for (int i = 0; i < x; i++)
{
    for (int n = 0; n < x; n++)
    {   
        cout<<arr1[i][n]<<" ";

    }
    cout<<"\n";
}
cin>>x;
return 0;
}