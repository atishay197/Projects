__kernel void getsum(__global int *a, __global int *rowsum, __global int* colsum, int row , int col)
{
	int i=get_global_id(0);
	int j=get_global_id(1);
	rowsum[i]=0;
	colsum[j]=0;
	for(int p=0;p<col;p++)
		rowsum[i]+=a[i*col+p];
	for(int p=0;p<row;p++)
		colsum[j]+=a[p*col+j];
}