__kernel void selection_string(__global char *A, __global char *B,__global int *l)
{
	int id=get_global_id(0);
	int startpos=0;
	for(int i=0;i<id;i++)
		startpos+=l[i];
	int endpos=startpos+l[id]-2;
	B[endpos+1]=' ';
	for(int i = startpos; i<=endpos; i++)
	{
		char data = A[i];
		int pos=0;
		for(int j=0;j<l[id]-1;j++)
		{
			if(A[j+startpos]<data || (A[j+startpos] == data && (j+startpos)<i))
				pos++;
		}

		B[pos+startpos]=data;
	}
}
