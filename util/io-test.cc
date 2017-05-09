
#include<iostream>
#include"io.h"
using namespace DTW;
#define FRAMELEN 24
#define FRAMESHIFT 12

bool Unittest(){

	waveio<float> reader("/home/xiao/data/empty.wav",FRAMELEN,FRAMESHIFT,true);
	int i=0;
	std::cout<<"Total frames: "<<reader.frames()<<std::endl;
	float* tempptr=reader.value();
	for(int i=0;i<48;i++)
		std::cout<<*(tempptr++)<<std::endl;
	reader.setvalue("/home/xiao/B12_384.wav",FRAMELEN,FRAMESHIFT,true,1);
	std::cout<<"Total frames: "<<reader.frames()<<std::endl;
	tempptr=reader.value();
	for(int i=0;i<48;i++)
		std::cout<<*(tempptr++)<<std::endl;

	//for(;!reader.Done();reader.Next(),i++)
//	{
//		for(short* cur=reader.value();cur!=reader.value()+FRAMELEN;cur++)
//			std::cout<<*cur<<std::endl;
//		std::cout<<std::endl;
//		if(i==3)
//			break;
//	}
	std::cout<<std::endl;
//	for(;!reader.Done();reader.Next()){
 //		for(const short& item:reader.value())
 //			std::cout<<item<<" ";
 //		std::cout<<std::endl;
 //	}
    return true;
}
int main(){
	Unittest();
}

