__kernel void sort(__global char *a , __global char *b,int size){
	int i = get_global_id(0);
	int pos=0,j=0,cnt=0;
	if (i<size)
	{
		for (j=0;j<size;j++)
		{
			if ((a[j]<a[i])||((a[j]==a[i])&&(j<i)))
				pos=pos+1;
		}
		b[pos]=a[i];
	}
}
