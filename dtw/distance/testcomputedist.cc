#include<iostream>
#include<vector>

#include"util.h"
#include"ComputeMfccDist.h"
using namespace DTW;
void unitTest()
{
using namespace std;
	vector<vector<float>>s1{{1,2},{1,3},{1,1}},s2{{2,4},{2,6}};
	float* ptr=new float[6];
	ComputeMfccDist computedist(EularDist);
	computedist.getlocalMat(s1,s2,ptr);
	for(int i=2;i>=0;i--)
	{
		for(int j=0;j<2;j++)
		{
			cout<<ptr[i*2+j]<<" ";
		}
		cout<<endl;
	}
}
int main()
{
	unitTest();
}
