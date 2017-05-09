#include"util.h"
namespace DTW{
float EularDist(float* v1,float* v2,int n)
{
	float temp=0;
	for(int i=0;i<n;i++)
	{
		temp+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return sqrt(temp);
}
float DiscretCosDist(float* v1,float* v2,int n)
{
	float E1=0,E2=0,innerproduct=0;
	for(int i=0;i<n;i++)
	{
		E1+=v1[i]*v1[i];
		E2+=v2[i]*v2[i];
		innerproduct+=v1[i]*v2[i];
	}
	return (1-innerproduct/(sqrt(E1*E2)));
}
}
