__kernel void Reverse(__global char* a, __global char* b,int l)
{
	int i = get_global_id(0);
	b[i] = a[l-i-1];
	b[l-i-1] = a[i];
	
}
