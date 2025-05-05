#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

__global__ void vectorAddCUDA(int *a, int *b, int *c, int n)
{
    //a[],b[],c[] are arrays which are passed in function
    //every thread has unique index in gpu. dim->no. of thread per block, 
    //idx->id of block, threadidx->id of thread inside block 
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < n)
    { //if index is in range add elements of a and b and store in c
        c[idx] = a[idx] + b[idx];
    }
}

void vectorAddCPU(int *a, int *b, int *c ,int n)
{
    for (int i = 0; i < n; i++)
    { //runs on cpu
        c[i] = a[i]+ b[i];
        //for (int i=0;i<n;i++)
        //cout<<c[i]<< " ";
        //cout<<endl;
    }
}

__global__ void matrixMulCUDA(int *a, int *b, int *c, int n)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n)
    { 
        int sum=0;
        for(int k=0; k<n; k++)
        sum += a[row*n+k] * b[k*n +col];
        c[row*n + col]= sum;
    }
}

void matrixMulCPU(int *a, int*b, int* c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int sum =0;
            for (int k =0;k<n;k++)
            sum += a[i*n+k] * b[k*n+j];
            c[i*n+j]=sum;
        }
    }
}

int main()
{
    int vecSize = 1<< 24;   // 16 million (=2^24)
    int matrixSize = 1024; //1024x1024 matrix , 10^5

    int  *h_a = new int [vecSize]; //alocates memory on host 'a' by creating vector
    int  *h_b = new int [vecSize];
    int  *h_c_cpu = new int [vecSize]; 
    int  *h_c_gpu = new int [vecSize];

    for(int i=0; i<vecSize; i++)
    { // fills a and b with random nos b/w 0 and 99
        h_a[i]= rand() % 100;
        h_b[i]= rand() % 100;
    }

    auto start= high_resolution_clock::now();
    vectorAddCPU(h_a, h_b, h_c_cpu, vecSize);
    auto end= high_resolution_clock::now();
    duration<double> vaddcputime = end - start;
    cout<< "Vector Addition[CPU] time:" <<vaddcputime.count()<<"seconds"<<endl;

    //cudamalloc allocates memory on gpu
    //cudamemcpy copies data from cpu to gpu

    int *d_a , *d_b, *d_c; //device
    cudaMalloc(&d_a, vecSize * sizeof(int)); 
    cudaMalloc(&d_b, vecSize * sizeof(int));
    cudaMalloc(&d_c, vecSize * sizeof(int));

    cudaMemcpy(d_a, h_a, vecSize * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, vecSize * sizeof(int), cudaMemcpyHostToDevice);

    start = high_resolution_clock::now();
    vectorAddCUDA<<<(vecSize + 255)/256, 256>>>(d_a,d_b,d_c,vecSize); //performing addition on gpu
    cudaDeviceSynchronize();
    end= high_resolution_clock::now();
    duration<double> vaddgputime = end - start;
    cudaMemcpy(h_c_gpu, d_c, vecSize * sizeof(int), cudaMemcpyDeviceToHost);
    cout<< "Vector Addition[GPU] Time: "<<vaddgputime.count()<<"seconds"<<endl; 

    int *mat_a = new int[matrixSize * matrixSize]; //making matrix
    int *mat_b = new int[matrixSize * matrixSize];
    int *mat_c_cpu = new int[matrixSize * matrixSize];
    int *mat_c_gpu = new int[matrixSize * matrixSize];

    for(int i=0;i<matrixSize*matrixSize;i++)
    {
        mat_a[i]=rand()%100;
        mat_b[i]=rand()%100;
    }

    start=high_resolution_clock::now();
    matrixMulCPU(mat_a, mat_b, mat_c_cpu, matrixSize);
    end = high_resolution_clock::now();
    duration<double> mmulcpu = end -start;
    cout<< "Matrix Multiplication[CPU] Time: "<<mmulcpu.count()<<"seconds"<<endl;

    int *d_mata, *d_matb, *d_matc;
    cudaMalloc(&d_mata, vecSize * sizeof(int));
    cudaMalloc(&d_matb, vecSize * sizeof(int));
    cudaMalloc(&d_matc, vecSize * sizeof(int));
    cudaMemcpy(d_mata,mat_a,matrixSize*matrixSize*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_matb,mat_b,matrixSize*matrixSize*sizeof(int),cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16,16); //2D grid of blocks, 16X16 threads each block
    dim3 blocksPerGrid((matrixSize+15)/16, (matrixSize+15)/16);

    start= high_resolution_clock::now();
    matrixMulCUDA<<<blocksPerGrid, threadsPerBlock>>>(d_mata, d_matb, d_matc, matrixSize);
    cudaDeviceSynchronize();
    end= high_resolution_clock::now();
    duration <double> mmulgpu = end-start;
    cout<<"Matrix Multiplication[GPU] Time: "<<mmulgpu.count()<<"seconds"<<endl;

    delete[] h_a;
    delete[] h_b;
    delete[] h_c_cpu;
    delete[] h_c_gpu;
    delete[] mat_a;
    delete[] mat_b;
    delete[] mat_c_cpu;
    delete[] mat_c_gpu;
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    cudaFree(d_mata);
    cudaFree(d_matb);
    cudaFree(d_matc);

    return 0;
}