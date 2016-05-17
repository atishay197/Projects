__kernel void copy(__global char *a , __global char *b){
	int i = get_global_id(0);
	b[i]=a[i]+ 32  ;
	if(a[i] == '\0' || a[i] > 91) 
		b[i]=a[i];
}

