#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<assert.h>
#include"util.h"
using namespace std;

namespace DTW{
template<typename T>
class waveio{
private:
	FILE* fileID;
    int mframelength;
	int mframeshift;
	unsigned int mframes;
    T* data;
	short* buffer;
	bool isempty;
	bool isdone;
	float scale;
	bool Check(const WaveHeader& header);
	void vectorconvert(T* data,short* buffer,int n);
public:
	void setvalue(const string& filename,int framelength,
					int frameshift,bool readall,float cscale);
	bool Done()const;
	void Next();
    T* value();
	unsigned int frames();
	waveio();
    waveio(const string& filename,int framelength=256,
					int frameshift=128,bool readall=false,float cscale=0.025);
	~waveio(){
		if(data!=NULL) 
			delete[] data;
		if(fileID!=NULL)
			fclose(fileID);
		if(buffer!=NULL)
			delete[] buffer;
	};

};

}


namespace DTW{
template<typename T>
	waveio<T>::waveio(const string& filename,int framelength,
					int frameshift,bool readall,float cscale):scale(cscale),isempty(true){
		setvalue(filename,framelength,frameshift,readall,cscale);
		isempty=false;
	}
template<typename T>
	void waveio<T>::vectorconvert(T* data,short* buffer,int n)
	{
		for(int i=0;i<n;i++)
		{
				data[i]=static_cast<T>(buffer[i]*scale);
		}
	}
template<typename T>
	void waveio<T>::setvalue(const string& filename,int framelength,
					int frameshift,bool readall,float cscale)
	{
		
		if(isempty==false)
		{
							
			if(data!=NULL) 
				delete[] data;
			if(fileID!=NULL)
				fclose(fileID);
			if(buffer!=NULL)
				delete[] buffer;
		}
		isempty=false;
		WaveHeader header;
		scale=cscale;
		assert(filename.size()!=0&&"filename empty!!");
		fileID=fopen(filename.c_str(),"rb");
		//assert(errno==0&&"file open failed !");
		mframelength=framelength;
		mframeshift=frameshift;
	    fread(&header,sizeof(WaveHeader),1,fileID);
		assert(Check(header)==true&&"wave file format not correct"
						"please check");
		
	    	
		long loc=ftell(fileID);
		buffer=new short[framelength];
		mframes=0;
		while(fread(buffer,sizeof(short),framelength,fileID)==
								framelength){
			mframes++;
            fseek(fileID,-mframeshift*sizeof(short),SEEK_CUR);
		}
		isdone=(mframes==0)? true:false;

		fseek(fileID,loc,SEEK_SET);
		if(readall==true)
		{
			data=new T[mframes*framelength];
			T* cur=data;
			while(fread(buffer,sizeof(short),framelength,fileID)
							==framelength){
			    vectorconvert(cur,buffer,framelength);	
				cur=cur+framelength;
				fseek(fileID,-mframeshift*sizeof(short),SEEK_CUR);
				
			}
		}
		else
		{
			data=new T[framelength];
			fread(buffer,sizeof(short),framelength,fileID);
			vectorconvert(data,buffer,framelength);
		}

        
		
	
	}
template<typename T>
	waveio<T>::waveio()
	{
		fileID=NULL;
		mframelength=0;
		mframeshift=0;
		mframes=0;
		data=NULL;
		isempty=true;
		buffer=NULL;
	}

template<typename T>
	bool waveio<T>::Done()const
	{
		return isdone;
	}
template<typename T>
	unsigned int waveio<T>::frames()
	{
		return mframes;
	}
template<typename T>
	void waveio<T>::Next()
	{
	     fseek(fileID,-mframeshift*sizeof(short),SEEK_CUR);
		if(fread(buffer,sizeof(short),mframelength,
								fileID)==mframelength)
		{		
			isdone=false;
			vectorconvert(data,buffer,mframelength);
		}
		else
		{
			isdone=true;
		}
	}
template<typename T>
	T* waveio<T>::value()
	{
		return data;
	}
template<typename T>	
	bool waveio<T>::Check(const WaveHeader& header)
	{
	//TODO no Check ,always return true ;
	//maybe will complete in the future
		return true;
	}
}



