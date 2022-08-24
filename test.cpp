#include <iostream>

using namespace std;

int main()
{   
    string selection;
    int s=1,selection1;
    cout<<"Kürsatin Ahsen Seyma için yazdigi programa hosgediniz. Kimlik dogrulamasi icin lütfen dünyadaki en önemli tarihi giriniz\n";
    
    while(s==1)
    {
    cin>>selection;
    if (selection=="06.02")
    {   
        cout<<"Hosgeldin Ahsen Seyma!\n Kursatin dusuncelerinden olusan bu programda seni sasirtabilecek bir kac bilgi yer almakta. Hangi bilgiyi ogrenmek istedigini secer misin";
        s=0;
    }
    
    cout<<"yanlis tarih girdiniz\n";
    }
    
    while(s==0){
    cout<<"1. Kursatin seni ne kadar sevdigini gormek icin\n 2. Senin adin anildiginda Kürsatin aklina gelen ilk sey \n 3. Kürsat seni gordugunde aklindan gecen dusunceler";
    cin>>selection1;
    if (selection1==1)
    {
        while (s==0)
        {
            cout<<"Cok ";
        }
        
    }
    if (selection1==2)
    {
        cout<<"aşk";
    }

    if(selection1==3)
    {
        cout<<"huzur";
    }    

    }

}
