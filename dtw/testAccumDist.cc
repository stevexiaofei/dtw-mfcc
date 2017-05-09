#include<iostream>

#include"AccumDist.h"
using namespace std;

void unitTest()
{
	
	using namespace DTW;
	typedef AccumDist::Pattern Pattern;

	float localdist[6][5]={
	{0,  0,  1,  1,  1},
	{1,  1,  0,  1,  1},
	{1,  1,  1,  0.1,  1},
	{1,  1,  1,  0  ,1},
	{1,  1,  1,  0,  0},
	{0,  1,  1,  1,  0}
	};
	float* distmat=new float[36];
	AccumDist accumdist(Pattern(6,5),distmat,&localdist[0][0]);
	cout<<accumdist.ComputeAccumDist()<<endl;
	cout<<accumdist.ComputeAccumDist(AccumDist::AccumPathB)<<endl;
	cout<<accumdist.ComputeAccumDist(AccumDist::AccumPathC)<<endl;
    delete[] distmat;	
}

int main()
{
	unitTest();	
	return 0;
}

