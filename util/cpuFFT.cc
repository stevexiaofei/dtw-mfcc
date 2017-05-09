#include<cmath>
#include<iostream>
#include<cstring>
#include"cpuFFT.h"
#include"util.h"
void CalcuCoes(int n,Complex* ptrCoes){
	for(int i=0;i<n/2;i++){
		float temp=Pai_2/float(n)*float(i);
		ptrCoes[i].real=cos(temp);
		ptrCoes[i].img=-sin(temp);
	 }
}

Complex add(Complex& ca,Complex& cb){
 	return Complex{ca.real+cb.real,ca.img+cb.img};
 }                                
Complex sub(Complex& ca,Complex& cb){
	return Complex(ca.real-cb.real,ca.img-cb.img);
}
Complex mul(Complex& ca,Complex& cb){
	return Complex{ca.real*cb.real-ca.img*cb.img,ca.img*cb.real+ca.real*cb.img};
}
float Squarevalue(Complex& C)
{
	return C.real*C.real+C.img*C.img;
}

void bufferfly(Complex& ca, Complex &cb,
	Complex& coes,Complex& c,Complex& d){
	Complex mulRes=mul(coes,cb);
	c=add(ca,mulRes);
    d=sub(ca,mulRes);             
}   
void cpuFFT(FtPat& input, FtPat& buffer,Complex* Coes,int log_N)
{
	
	unsigned int batch=input.batch;
	unsigned int length=input.length;
	Complex* data=input.data;
	Complex* bufferdata=buffer.data;

	for(unsigned int i=0;i<batch;i++)
	{
		Complex* tempPtr=data+i*length;
		Complex* tempbufferPtr=bufferdata+i*length;
		for(unsigned int j=0;j<length/2;j++)
		{
			unsigned int temp1=0;
			unsigned int temp2=0;
			unsigned int exchangindex1=j*2;
			unsigned int exchangindex2=j*2+1;
			for(int i=0;i<log_N;i++){
				temp1=(temp1<<1)|(exchangindex1>>i&0x00000001);
				temp2=(temp2<<1)|(exchangindex2>>i&0x00000001);
       		}
			tempbufferPtr[temp1]=tempPtr[exchangindex1];
			tempbufferPtr[temp2]=tempPtr[exchangindex2];
		}
	}
//#ifdef DEBUGE
//	printVComplex(bufferdata,batch*length,"exchanged data");

//#endif
	for(int i=0;i<batch;i++)
	{
		Complex* ptrArray[2]={bufferdata+i*length,data+i*length};
        unsigned int temp=0xFFFFFFFF;
		for(int j=0;j<log_N;j++,temp=temp<<1)
		{
			for(unsigned int Index=0;Index<length/2;Index++)
			{
				unsigned int Stat=j%2,revStat=1-Stat;
				unsigned int indexa=((Index&temp)<<1)|(Index&~temp);
            	unsigned int indexb=indexa|(1<<j);

//#ifdef DEBUGE
               // std::cout<<indexa<<"-"<<indexb<<std::endl;
//	int coesindex=(Index<<(log_N-1-j))&(length/2-1);
//				std::cout<<coesindex<<std::endl;
//#endif
				bufferfly(ptrArray[Stat][indexa],
						ptrArray[Stat][indexb],
				Coes[Index<<(log_N-1-j)&(length/2-1)],ptrArray[revStat][indexa],ptrArray[revStat][indexb]);
			}						  
		}
      
	}
}

void printVComplex(Complex* ptrC,int n,char* str)
{
	if(str!=NULL)
		std::cout<<str<<std::endl;
	for(int i=0;i<n;i++)
		std::cout<<ptrC[i]<<std::endl;
	std::cout<<std::endl;
}
void FFT(FtPat& input)
{
	Complex* Coes=new Complex[input.length/2];
	unsigned int log_N=log2(input.length);
    CalcuCoes(input.length,Coes);
    //printVComplex(Coes,input.length/2,"the coes array");	
	FtPat tempinput=input;
	tempinput.data=new Complex[input.batch*input.length];
    cpuFFT(input,tempinput,Coes,log_N);	
	
    if(log_N%2==0)
	{

		memcpy(input.data,tempinput.data,
					sizeof(Complex)*input.batch*input.length);
	}
	delete[] Coes;
	delete[] tempinput.data;
#ifdef DEBUGE
	printVComplex(input.data,input.batch*input.length,"FFT");
#endif
}

unsigned int getNpoint(int n)
{
	
	unsigned int index=(unsigned int)log2(n);
	return (n==exp2(index))? n:exp2(index+1);
}
void getFtEn(RFtPat& in)
{


	FtPat input{in.batch,getNpoint(in.length),NULL};
     
	std::cout<<"N:"<<getNpoint(in.length)<<std::endl;

	input.data=new Complex[input.batch*input.length];
	for(unsigned int i=0;i<input.batch;i++)
		for(unsigned int j=0;j<input.length;j++)
		{
			if(j<in.length)
				input.data[i*input.length+j]=Complex(in.data[i*in.length+j]);
			else
				input.data[i*input.length+j]=Complex(0);
		}
	
	FFT(input);

	for(unsigned int i=0;i<in.batch;i++)
		for(unsigned int j=0;j<in.length;j++)
		{
			in.data[i*in.length+j]=Squarevalue(input.data[i*input.length+j]);
		}

	delete[] input.data;
}

