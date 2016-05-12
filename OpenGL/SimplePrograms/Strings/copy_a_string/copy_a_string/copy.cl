__kernel void copy(__global char *a , __global char* b){
	int i =0 ;
	while(a[i]!='\0')
    {
		b[i]= a[i];
       i++;
    }
	b[i]='\0';
}

