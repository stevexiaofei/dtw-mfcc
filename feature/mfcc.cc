#include<cmath>
#include<vector>
#include<assert.h>
#include"mfcc.h"
#include"util/util.h"
#include"util/cpuFFT.h"
namespace DTW{

mfcc::mfcc(mfccOpt& Opt)
{
	mOpt=Opt;
	hanningCoes=new float[mOpt.framelen];
	filterCoes=new short[mOpt.filternum+2];
	inithanning();
	initfiltercoes();
}
mfcc::~mfcc()
{
	delete[] hanningCoes;
	delete[] filterCoes;
}
void mfcc::inithanning()
{
	int FrmLen=mOpt.framelen;
	for(int i=0;i<mOpt.framelen;i++)
		hanningCoes[i]=
	    (float)(0.54-0.46*cos((float)i*Pai_2/(float)(FrmLen-1)));
}
void mfcc::initfiltercoes()
{
	float bandwidth=(f2mel(8000)-f2mel(mOpt.lf))/(mOpt.filternum+1);
	std::cout<<"f2mel(8000): "<<f2mel(8000)<<std::endl
			<<"f2mel(mOpt.lf): "<<f2mel(mOpt.lf)<<std::endl
			<<"bandwidth: "<<bandwidth<<std::endl;
	for(int i=0;i<mOpt.filternum+2;i++)
	{
		filterCoes[i]=mel2f(f2mel(mOpt.lf)+i*bandwidth)/mOpt.fs*
				getNpoint(mOpt.framelen);
		std::cout<<filterCoes[i]<<" ";
	}

}
void mfcc::vectormul(float*ptr1,float*ptr2,int n)
{
	for(int i=0;i<n;i++)
	{
		ptr1[i]=ptr1[i]*ptr2[i];
	}
}
float  mfcc::vectorSumReduce(float* V,int n)
{
	float sum=0;
	for(int i=0;i<n;i++)
		sum+=V[i];
	return sum;
}
void mfcc::getMfcc(string filename,std::vector<std::vector<float>>& ptrRes)
{
	reader.setvalue(filename,mOpt.framelen,mOpt.frameshift,true,
					mOpt.wavescale);
	RFtPat fftInput{reader.frames(),mOpt.framelen,reader.value()};	
      
	getFtEn(fftInput);
    std::cout<<"frames: "<<reader.frames()<<"mfcc::getMfcc()"<<std::endl;
    float* En=fftInput.data;
/////////////////////////////////////////////////
//	for(int i=0;i<fftInput.batch;i++)
//	{
//		for(int j=0;j<fftInput.length;j++)
//		{
//			std::cout<<En[i*fftInput.length+j]<<" ";
//		}
//		std::cout<<std::endl;
//	}
//////////////////////////////////////////////////
	float* Hk=new float[mOpt.filternum*reader.frames()];
	float* frameEnagy=new float[reader.frames()];
	unsigned int npoint=getNpoint(fftInput.length);
	for(int i=0;i<reader.frames();i++)
	{
		for(int j=1;j<mOpt.filternum+1;j++)
		{
			Hk[i*mOpt.filternum+j-1]=0;
			for(int k=filterCoes[j-1];k<=filterCoes[j];k++)
			{
					Hk[i*mOpt.filternum+j-1]+=
			(float)(k-filterCoes[j-1])/
			(float)(filterCoes[j]-filterCoes[j-1])*
				En[i*mOpt.framelen+k];

			}
			for(int k=filterCoes[j];k<=filterCoes[j+1];k++)
				 Hk[i*mOpt.filternum+j-1]+=
			(filterCoes[j+1]-k)/(filterCoes[j+1]-filterCoes[j])*
				En[i*mOpt.framelen+k];	
		}
		frameEnagy[i]=mOpt.enagyscale*log10(vectorSumReduce(En+i*fftInput.length,npoint/2));
	}
//////////////////////////////
// 	for(int i=0;i<reader.frames();i++)
//	{
//		for(int j=0;j<mOpt.filternum;j++)
//		{
//			std::cout<<Hk[i*mOpt.filternum+j]<<" ";
//		}
//		std::cout<<std::endl;
//	}
/////////////////////////////////////////
	assert(&ptrRes!=NULL);
	ptrRes.resize(reader.frames());
	for(int i=0;i<reader.frames();i++)
	{
		ptrRes[i].resize(mOpt.numcep,0);
		for(int j=0;j<mOpt.numcep;j++)
		{
			for(int k=0;k<mOpt.filternum;k++)
			{
				ptrRes[i][j]=log10(Hk[i*mOpt.filternum+k])*
						cos((Pai*j*(k-0.5))/mOpt.filternum);		
			}
			
		}
		ptrRes[i].push_back(frameEnagy[i]);
	}

	delete[] Hk;
	delete[] frameEnagy; 

	float N2=0;
	for(int i=1;i<=mOpt.Nstep;i++)
		N2+=2*i*i;
	vector<float> temp1(mOpt.numcep+1);
	for(int i=0;i<reader.frames();i++ )
	{
		if(i<mOpt.Nstep||((reader.frames()-i)<mOpt.Nstep+1))
		{	
			temp1.assign(mOpt.numcep+1,0.0);
		}
		else
		{
			for(int j=0;j<mOpt.numcep+1;j++)
			{
				temp1[j]=0;
				for(int k=1;k<=mOpt.Nstep;k++)
					temp1[j]+=k*(ptrRes[i+k][j]-ptrRes[i-k][j]);
				temp1[j]/=N2;
			}
		}
		ptrRes[i].insert(ptrRes[i].end(),temp1.begin(),temp1.end());
	}
	int firstdeltas=(mOpt.numcep+1);
 	if(mOpt.adddeltas==true)
	{
		for(int i=0;i<reader.frames();i++)
		{
			if(i<mOpt.Nstep||((reader.frames()-i)<mOpt.Nstep+1))
			{
				temp1.assign(mOpt.numcep+1,0.0);
			}
			else
			{
				for(int j=0;j<mOpt.numcep+1;j++)
				{
					temp1[j]=0;
					for(int k=1;k<=mOpt.Nstep;k++)
						temp1[j]+=k*(ptrRes[i+k][j+firstdeltas]-
										ptrRes[i-k][j+firstdeltas]);
					temp1[j]/=N2;
				}
			}
			ptrRes[i].insert(ptrRes[i].end(),temp1.begin(),
							temp1.end());
		}
	}
	//add deltas
      		
}
}//namespace DTW
