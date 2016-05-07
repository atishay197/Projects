__kernel void copy(__global int *a , __global int *b)
{
	int i = get_global_id(0);
	int temp = a[i];
	int s[500];int j =0 ;
	while(temp!=0)
	{
		if(temp%2==0)
			s[j++]=0;
		else 
			s[j++]=1 ;
		temp = temp/2 ;
	}
	int n =j-1;
	b[i]=s[n];
	for(int k=n-1;k>-1;k--)
	   b[i]=b[i]*10+s[k];
}

