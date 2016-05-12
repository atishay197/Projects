__kernel void copy(__global char *a , __global char *b){
	int i = get_global_id(0);
	b[i]=a[i] ;
}

