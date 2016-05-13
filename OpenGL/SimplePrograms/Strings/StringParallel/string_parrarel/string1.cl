__kernel void Reverse(__global char* a, __global char* b, __global int* l)
{
	int k=0,sum=0,j=0,len;	
	int i = get_global_id(0);

	for(j=0;j<i;j++)
	    sum=sum+l[j]+1;
	len=l[i];
	for(k=0;k<len;k++)
	{
		b[sum+len-k-1]=a[sum+k];
	}
   	b[sum+len]='  ';	  
}
