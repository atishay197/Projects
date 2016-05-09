__kernel void trmat(__global int* a, __global int* b,int noOfCols)
{
	int row=get_global_id(0);
	int col=get_global_id(1);
	b[col*noOfCols+row]=a[row*noOfCols+col];

}