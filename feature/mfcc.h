#pragma once
#include<string>
#include<cmath>
#include<vector>
#include"util/io.h"
#include"util/cpuFFT.h"
using namespace std;
namespace DTW{
struct mfccOpt{
	unsigned int framelen;
	unsigned int frameshift;
	unsigned int filternum;
	unsigned int fs;
	unsigned int lf;
	unsigned int numcep;
	unsigned int Nstep;
	float wavescale;
	float enagyscale;
	bool adddeltas;
	mfccOpt& operator=(const mfccOpt& other)
	{
		if(this==&other)
			return *this;
		framelen=other.framelen;
		frameshift=other.frameshift;
		filternum=other.filternum;
		fs=other.fs;
		lf=other.lf;
		Nstep=other.Nstep;
		numcep=other.numcep;
		wavescale=other.wavescale;
		enagyscale=other.enagyscale;
		adddeltas=other.adddeltas;
		return *this;
	};
	mfccOpt()
	{
	
	};
	mfccOpt(unsigned int c_framelen,
			unsigned int c_frameshift,
			unsigned int c_filternum,
			unsigned int c_fs,
			unsigned int c_lf,
			unsigned int c_numcep,
			unsigned int c_Nstep,
			float c_wavescale,
			float c_enagyscale,
			bool c_adddeltas
			):
					framelen(c_framelen),
					frameshift(c_frameshift),
					filternum(c_filternum),
					numcep(c_numcep),
					fs(c_fs),
					lf(c_lf),
					adddeltas(c_adddeltas),
					wavescale(c_wavescale),
					enagyscale(c_enagyscale),
					Nstep(c_Nstep)
			{};
};
class mfcc{
public:
	mfcc(mfccOpt& Opt);
	void getMfcc(string filename,std::vector<std::vector<float>>& ptrRes);    	
	~mfcc();
private:
	void inithanning();
	void initfiltercoes();
	float vectorSumReduce(float* V,int n);
	float mel2f(float mel){	return 700*(pow(10,mel/1125)-1);};
	float f2mel(float f){return 1125*log10(1+f/700);};
	void vectormul(float* ptr1,float*ptr2,int n );
	void vec2complex(Complex& C,float* ptr,int n);
	float *hanningCoes;
	mfccOpt mOpt;
	waveio<float> reader;
	short* filterCoes;
};
}
