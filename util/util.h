#pragma once
#include<cmath>
namespace DTW{
#define Pai_2 6.28318531
#define Pai 3.1415926535

typedef float (*DistanFunc)(float* v1,float* v2,int n);



struct WaveHeader{
// RIFF block;
	int rID;
	int rLen;
	int wID;
// format blocks
	int fID;
	int flen;

	short formatTag;
	short nchannel;
	int nSamplesPerSec;
	int nAvgBytesPerSec;
	short nBlockAlign;
	short wBitsPerSample;
// data blocks
	int dID;
	int wSampleLength;
};

}

