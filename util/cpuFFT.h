#pragma once
#include<string>
#include"util.h"
#include<iostream>
//TODO chang float to a tempdata;
struct Complex{
	float real;
	float img;
	Complex(float creal,float cimg)
	{
		real=creal;
		img=cimg;
	};
	Complex(float realvalue)
	{
		real=realvalue;
		img=0;
	};
	Complex(){Complex(0);};
	friend std::ostream& operator<<(std::ostream& os,
					const Complex& C)
	{
		os<<" [R:"<<C.real<<","<<"L:"<<C.img<<"] ";
		return os;
	};
    
};

extern Complex add(Complex& ca,Complex& cb);                                
Complex sub(Complex& ca,Complex& cb);
Complex mul(Complex& ca,Complex& cb);
void bufferfly(Complex& ca, Complex &cb,
Complex* coes,Complex& c,Complex& b);    

float Squarevalue(Complex& C);

void printVComplex(Complex* ptrC,int n,char* str=NULL);                                     
unsigned int getNpoint(int n);
	
 
struct FFTpatern{                                                    
	unsigned int batch;                                   
	unsigned int length;
    Complex* data;
};
struct realFFTpatern{
	unsigned int batch;
	unsigned int length;
	float* data;
};
typedef FFTpatern FtPat;  
typedef realFFTpatern RFtPat;
void CalcuCoes(int n,Complex* ptrCoes);      

void FFT(FtPat& in); 
void getFtEn(RFtPat& in);
void cpuFFT(FtPat& FtIn,FtPat& buffer,Complex* Coes,int log_N); 
