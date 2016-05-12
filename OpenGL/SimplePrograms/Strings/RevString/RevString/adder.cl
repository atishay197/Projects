__kernel void adder(__global int* a,__global int* b,int l)
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    int id = j*l + i;
    int adder = 0;
    if(i<l/2)
    {
        if(j<l/2)
            adder = 1;
        else
            adder = 3;
    }
    else
    {
        if(j<l/2)
            adder = 2;
        else
            adder = 4;
    }
    b[id] = a[id] + adder;
}
