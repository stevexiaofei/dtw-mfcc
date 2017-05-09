#include<iostream>
#include<vector>
#include"mfcc.h"
using namespace DTW;
int main()
{
	mfccOpt opt(400,//framelength
				125,//frameshift
				26,//filterbins
				16000,//fs
				290,
				12,//number os ceps
				2,
				0.001,
				10,
				true
			);
	mfcc ceptrum(opt);
	vector<vector<float>> ceps;
	ceptrum.getMfcc(
					//"/home/xiao/B12_384.wav"
					"/home/xiao/data/template/accelerate_1.wav",ceps);
	for(vector<float>& item:ceps)
	{
		for(float& ite:item)
		{
			cout<<ite<<" ";
		}
		cout<<endl;
	}
	return 0;
}
