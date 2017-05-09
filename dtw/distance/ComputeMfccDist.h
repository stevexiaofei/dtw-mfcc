#pragma once
#include<vector>
#include<iostream>

#include"util/util.h"
#include"itf/ComputeLocalDist.h"
namespace DTW{


using namespace std;
class ComputeMfccDist{

typedef vector<vector<float>> Squence;
private:
	DistanFunc distancefunc;   
public:

	ComputeMfccDist(DistanFunc c_func):distancefunc(c_func){}
	~ComputeMfccDist();
	virtual float ComputeDist(Squence& squenceM,Squence& squenceN,unsigned short i,unsigned short j)const;

	void getlocalMat(Squence& squenceM,Squence& squenceN,float* localMat);

};
ComputeMfccDist::~ComputeMfccDist(){}
float ComputeMfccDist::ComputeDist(Squence& squenceM,Squence& squenceN,unsigned short i,unsigned short j)const
{
	return distancefunc(squenceM[i].data(),squenceN[j].data(),squenceM[i].size());
}
void ComputeMfccDist::getlocalMat(Squence& squenceM,Squence& squenceN,float* localMat)
{
	for(unsigned int i=0;i<squenceM.size();i++)
	{
		for(unsigned int j=0;j<squenceN.size();j++)
		{
			localMat[i*squenceN.size()+j]=ComputeDist(squenceM,squenceN,i,j);			
		}


	}

}

}
