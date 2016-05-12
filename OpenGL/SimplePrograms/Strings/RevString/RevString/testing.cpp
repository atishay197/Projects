#include<iostream>
#include<string.h>
#include<cstdio>
#include<stdlib.h>
#include<stdio.h>
#include<CL/cl.h>
#include<conio.h>
#define MAX_SOURCE_SIZE (0x100000)
#define size 1000
using namespace std;

char a[100],b[100];

void onlet(int id,int w,int t)
{
   // int id = get_global_id(0);
    printf("ID : %d :: ",id);
    int pos = (id+1)%(t+1);
    int let = id/(t+1);
    if(pos == 0)
    {
        b[id] = ' ';
        printf("\n");
    }
    else
    {
        printf("inputing %d: %c\n",id,a[(w+1)*(pos-1)+let]);
        b[id] = a[(w+1)*pos+let];
    }
}

int main()
{
    int n,i,w=0,t;
    cout<<"Enter String : ";
    gets(a);
    n = strlen(a);
    while(a[w] != ' ')
        w++;
    cout<<a<<endl;
    t = (n+1)/(w+1);
    printf("String : %d\nWord : %d\nTotal : %d\n",n,w,t);
    for(i=0 ; i<=n ; i++)
        onlet(i,w,t);
    printf("Output : %s\n",b);
}
