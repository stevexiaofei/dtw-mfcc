#pragma once
#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
namespace DTW{
//Pattern 	   *--*
//           	/ |
//        	   *  *
//
//i
class AccumDist;
typedef void (AccumDist::*SetAccumDistFunc)(unsigned short i,unsigned short j);
class AccumDist
{
public:
struct Pattern{
	unsigned short m;
	unsigned short n;
	Pattern(unsigned short cm,unsigned short cn)
	{
		m=cm;
		n=cn;
	}
};
struct Weight{
	float wl;
	float wm;
	float wr;
	Weight(float c_wl,float c_wm,float c_wr)
	{
			
	}
};
enum AccumPath{AccumPathA,AccumPathB,AccumPathC};



	AccumDist(Pattern c_pat,float* ptr_DistMat,
					const float* ptr_LocalDist):
					Pat(c_pat),
					ptrDistMat(ptr_DistMat),
					ptrLocalDist(ptr_LocalDist){}

	~AccumDist();


	float ComputeAccumDist(AccumPath accumPatern=AccumPathA);
    static void debugPrint(float*ptr,Pattern Pat);

private:
	 
 	void SetCurAccumDistA(unsigned short i,unsigned short j);
	void SetCurAccumDistB(unsigned short i,unsigned short j);
	void SetCurAccumDistC(unsigned short i,unsigned short j);
	void InitDist(unsigned int initdepth);

	Pattern Pat;
	float* ptrDistMat;
	const float* ptrLocalDist;
	bool NeedTrace;
}; 
void AccumDist::debugPrint(float*ptr,Pattern Pat)
{
	for(int i=Pat.m-1;i>=0;i--)
	{
		for(int j=0;j<Pat.n;j++)
		{
			std::cout<<std::setw(4)<<ptr[i*Pat.n+j];
		}
		std::cout<<std::endl;
	}
}
AccumDist::~AccumDist()
{
	;
}

///////////////////////////////////////////////////////////////////////////
#define WL 1
#define WM 2
#define WR 1
void AccumDist::SetCurAccumDistA(unsigned short i,unsigned short j)
{
	ptrDistMat[i*Pat.n+j]=std::min(ptrDistMat[i*Pat.n+j-1]+WL*ptrLocalDist[i*Pat.n+j],
					std::min(ptrDistMat[(i-1)*Pat.n+j-1]+WM*ptrLocalDist[i*Pat.n+j],
							ptrDistMat[(i-1)*Pat.n+j]+WR*ptrLocalDist[i*Pat.n+j]))
			;	
}
///////////////////////////////////////////
void AccumDist::SetCurAccumDistB(unsigned short i,unsigned short j)
{

	ptrDistMat[i*Pat.n+j]=std::min(ptrDistMat[(i-1)*Pat.n+j-2],std::min(ptrDistMat[(i-1)*Pat.n+j-1],ptrDistMat[(i-2)*Pat.n+j-1]))
			+ptrLocalDist[i*Pat.n+j];

//	std::cout<<"SetCurAccumDistB: "<<ptrDistMat[(i-1)*Pat.n+j-2]<<" "
//			<<ptrDistMat[(i-1)*Pat.n+j-1]<<" "
//			<<ptrDistMat[(i-2)*Pat.n+j-1]<<std::endl;
}
void AccumDist::SetCurAccumDistC(unsigned short i,unsigned short j)
{
	float lefttemp=0,righttemp=0;
	lefttemp=std::min(ptrDistMat[(i-1)*Pat.n+j-3]+ptrLocalDist[i*Pat.n+j-2],ptrDistMat[(i-1)*Pat.n+j-2])
			+ptrLocalDist[i*Pat.n+j-1];
	righttemp=std::min(ptrDistMat[(i-3)*Pat.n+j-1]+ptrLocalDist[(i-2)*Pat.n+j],ptrDistMat[(i-2)*Pat.n+j-1])
			+ptrLocalDist[(i-1)*Pat.n+j];
	ptrDistMat[i*Pat.n+j]=std::min(ptrDistMat[(i-1)*Pat.n+j-1],std::min(lefttemp,righttemp))
			+ptrLocalDist[i*Pat.n+j];
}
void AccumDist::InitDist(unsigned int initdepth)
{

	float temp=0;
	for(int i=0;i<Pat.m;i++)
	{	
		temp+=ptrLocalDist[i*Pat.n];
		ptrDistMat[i*Pat.n]=temp;
	}
	temp=ptrLocalDist[0];
	for(int i=1;i<Pat.n;i++)
	{
		temp+=ptrLocalDist[i];
		ptrDistMat[i]=temp;
	}
	for(int i=1;i<initdepth;i++)
	{
		for(int j=i;j<Pat.m;j++)
			SetCurAccumDistA(j,i);
		for(int j=i+1;j<Pat.n;j++)
			SetCurAccumDistA(i,j);
	}
	 
}
float AccumDist::ComputeAccumDist(AccumPath accumPatern)
{
	int initdepth=1;
	SetAccumDistFunc SetCurAccumDist=&AccumDist::SetCurAccumDistA;
	if(accumPatern==AccumPathB)
	{
		SetCurAccumDist=&AccumDist::SetCurAccumDistB;
		initdepth=2;
	}
	else if(accumPatern==AccumPathC)
	{
		SetCurAccumDist=&AccumDist::SetCurAccumDistC;
		initdepth=3;
	}
	InitDist(initdepth);
	int minlength=std::min(Pat.m,Pat.n);
	for(int i=initdepth;i<minlength-1;i++)
	{
		for(int j=i;j<Pat.m;j++)
			(this->*SetCurAccumDist)(j,i);
		for(int j=i+1;j<Pat.n;j++)
			(this->*SetCurAccumDist)(i,j);

	}
	int mh=minlength-1, nw=minlength-1;
	int* ptr_add=(Pat.m<Pat.n)? &nw:&mh;
	int abslen=abs(Pat.m-Pat.n);
	
	//debugPrint(ptrDistMat,Pat);
	std::cout<<abslen<<std::endl;
	std::cout<<mh<<" "<<nw<<std::endl;
	for(int i=-1;i<abslen;i++)
	{
			(this->*SetCurAccumDist)(mh,nw);
		(*ptr_add)++;
	}
	return ptrDistMat[Pat.m*Pat.n-1];
}


}
