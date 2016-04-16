#include <bits/stdc++.h>
using namespace std;

int main()
{
	int count = 0,lcount=0;
	FILE *fp;
    int c,prev,pprev;
    fp = fopen("new22.tr", "r");
    fstream myfile;
    myfile.open ("final22.tr");
    while((c = fgetc(fp)) != EOF) 
    {
    	if(c == '\n')
    		lcount++;
    	if(lcount<7)
    		continue;
    	if(lcount==7)
    	{
    		lcount++;
    		continue;
    	}
    	if (c == ' ')
    		count++;
    	if(count > 8)
    	{
    		while((c = fgetc(fp)) != '\n') 
    		count = 0;
    	}
        if(c == 'M' && prev == '\n')
        {
            while((c = fgetc(fp)) != '\n')
                count = 0;
        }
    	if (c == '\n')
    		count = 0;
        if (c != '[' && c != ']' && c != '_' && !(c == ' ' && prev == ' '))
        	myfile<<(char)c;
        prev = c;
        pprev = prev;
    }
    fclose(fp);
    myfile.close();
}
