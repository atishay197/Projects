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

	char str1[100];
	char str2[100];
	int i = 0, j = 0, l = 0;

	printf("Enter a string:\n");
	gets(str1);
	int len = strlen(str1);
	cout<<"length : "<<len<<endl;
	FILE *fp = fopen("string.cl", "r");
	char *source_str;
	size_t source_size;

	if(!fp)
	{
		cout<<"Failed";
		getch();
		//exit(1);
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

	//Create Command Queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	//Create Memory Buffers on the Device for each Vector
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char), NULL, &ret);


	//Copy the lists A and B to respective Memory Buffers
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(char), str1, 0 ,NULL, NULL);

	//Create Program from Kernel Source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
    cout<<ret<<endl;
	//Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	//Create the OpenCl Kernel
	cl_kernel kernel = clCreateKernel(program, "Reverse", &ret);

	//Set the args of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&len);


	//Execute the OpenCL Kernel on the list
	size_t global_item_size = len;		//Process the entire list
	size_t local_item_size = 1;			//Process in groups of 64

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);
	ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, len*(sizeof(char)), str2, 0, NULL, NULL);

	str2[len] = '\0';
	cout<<"Done\n";
	cout<<"Reversed String:\n"<<str2;

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	getch();
	return 0;
}


