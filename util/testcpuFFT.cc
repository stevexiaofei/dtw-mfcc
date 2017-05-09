#include<iostream>
#include<cmath>
#include"cpuFFT.h"

void unitTest()
{
	RFtPat testpat;
	testpat.batch=2;
	testpat.length=31;
	testpat.data=new float[testpat.length*testpat.batch];
	for(int i=0;i<testpat.batch;i++)
	{
		for(int j=0;j<testpat.length;j++)
			testpat.data[i*testpat.length+j]=cos(j);
	}

	std::cout<<std::endl;
	getFtEn(testpat);
#ifdef DEBUGE	
	for(int i=0;i<testpat.length*testpat.batch;i++)
		std::cout<<testpat.data[i]<<std::endl;
#endif
	delete[] testpat.data;
}
int main()
{
	unitTest();	
	return 0;
}
