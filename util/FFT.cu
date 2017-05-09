#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>

#include<cuda_runtime.h>
#include<helper_cuda.h>
#include<vector_types.h>

#include"FFT.h"
#include"util.h"
void CalcuCoes(int n,Complex* ptrCoes){
	for(i=0;i<n/2;i++){
		float temp=2Pai/float(n)*float(i)
		ptrCoes[i].real=cos(temp);
		ptrCoes[i].img=-sin(temp);
	}	
}

__global__ void cudaFFT(FtPat input, FtPat buffer, 
				Complex* Coes,int log_N){
	unsigned int nsample=input.batch;
	unsigned int length=input.length;

	Complex* data=input.data+sampleIndex*  ;
	Complex* bufferdata=buffer.data;
	Complex* ptrArray[2]={bufferdata,data};

	unsigned int sampleIndex=blockIdx.y*blockDim.y+threadIdx.y;
	unsigned int Index= blockIdx.x*blockDim.x+threadIdx.x;
	{
		unsigned int temp1=0;
		unsigned int temp2=0;
	    unsigned int exchangindex1=Index*2;
		unsigned int exchangindex2=Index*2+1;
		for(int i=0;i<log_N;i++){
	   		temp1=(temp1<<1)|(exchangindex1>>i&0x00000001);
			temp2=(temp2<<1)|(exchangindex2>>i&0x00000001);
		}
		bufferdata[temp1]=data[exchangindex1];
		bufferdata[temp2]=data[exchangindex2];
	}
    for(int i=0,unsigned int temp=0xFFFFFFFF;i<log_N;
					i++,temp=temp<<1)
	{
		unsigned int Stat=i%2,revStat=1-Stat;
		unsigned int indexa=((Index&temp)<<1)|(Index&~temp)
		unsigned int indexb=indexa|(1<<i);
		bufferfly(ptrArray[Stat][indexa],ptrArray[Stat][indexb],
						Coes[Index/(i+1)],ptrArray[revStat][indexa],
						ptrArray[revStat][indexb]);


	}	
}
void FFT(Ftpat in){

	
	assert(npoint%2==0);
    
	Complex* h_Coes=new Complex[in.length/2];
	CalcuCoes(npoint,Coes);
	Complex* d_Coes;
	size_t size=sizeof(Complex)*in.length/2;
	cudaMalloc(&d_Coes, size);
	cudaMemcpy(d_Coes, h_Coes, size, cudaMemcpyHostToDevice);

	FtPat devFtPat=in,devFtPatBuffer=in;
    size_t size=sizeof(Complex)*in.length*in.nsample;
    cudaMalloc(&devFtPat.data, size);
	cudaMelloc(&devFtPatBuffer.data,size);

	cudaMemcpy(devFtPat.data, in.data ,size, 
					cudaMemcpyHostToDevice);

    cudaFFT<<<  , >>>(devFtPat,devFtPatbuffer,d_Coes,N);



}
