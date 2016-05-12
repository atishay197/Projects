#include<iostream>
#include<string.h>
#include<cstdio>
#include<stdlib.h>
#include<stdio.h>
#include<CL/cl.h>
#include<conio.h>
#define MAX_SOURCE_SIZE (0x100000)
#define size 1000

using namespace std;

int main()
{
    int a[100],n,i,m,b[100]={0};
    cout << "Enter matrix size : ";
    cin>>n;
    m = n*n;
    cout<<"Enter matrix elements :\n";
    for(i=0 ; i<m ; i++)
        cin>>a[i];

	FILE *fp = fopen("adder.cl", "r");
	char *source_str;
	size_t source_size;

	if(!fp)
	{
		cout<<"Failed in opening file\n";
		getch();
		exit(1);
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	 ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    cl_command_queue command_queue = clCreateCommandQueue(context,device_id,0,&ret);

    cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,m*sizeof(int),NULL,&ret);
    cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_READ_WRITE,m*sizeof(int),NULL,&ret);

    ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,m*sizeof(int),a,0,NULL,NULL);

	//Create Program from Kernel Source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);

	//Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    cout<<ret<<endl;
	    //Create the OpenCl Kernel
	cl_kernel kernel = clCreateKernel(program, "adder", &ret);
    cout<<ret<<endl;

    ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
    ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);
    ret = clSetKernelArg(kernel,2,sizeof(cl_mem),(void*)&n);
    cout<<ret<<endl;
    size_t global[2] = {n,n};
    size_t local[2] = {1,1};

    ret = clEnqueueNDRangeKernel(command_queue,kernel,2,NULL,global,local,0,NULL,NULL);
    ret = clFinish(command_queue);

    ret = clEnqueueReadBuffer(command_queue,b_mem_obj,CL_TRUE,0,m*sizeof(int),b,0,NULL,NULL);
    cout<<ret<<endl;

    for(i=0 ; i<m ; i++)
    {
        cout<<b[i]<<"\t";
        if((i+1)%n == 0)
            cout<<endl;
    }
	getch();
	return 0;
}


