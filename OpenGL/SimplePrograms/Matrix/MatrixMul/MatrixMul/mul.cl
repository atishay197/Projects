__kernel void multiply(__global int *a , __global int *b, __global int *c,int wa , int wb)
{
	int col = get_global_id(0);
	int row = get_global_id(1);
	int sum =0 ;
	int i;
	for(i=0;i<wa;i++)
	{
		sum+=a[wa*row+i]*b[i*wb+col];
	}
	c[row*wb+col]=sum;
}

