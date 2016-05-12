__kernel void onlet(__global char* a,__global char* b,int w,int t)
{
    int id = get_global_id(0);
    int pos = id%(t+1);
    int let = id/(t+1);
    if(pos == 0)
        b[id] = ' ';
    else
    {
        b[id] = a[(w+1)*pos+let];
    }
}
