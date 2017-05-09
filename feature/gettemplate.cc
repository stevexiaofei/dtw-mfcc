#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <vector>
#include <fstream>

#include"mfcc.h"
#include"util/featureIO.h"

using namespace std;
using namespace DTW;

void getfilelist(const char* dir_name,vector<string>& filelist);
int main(int argc,char** argv)
{

	if((argc!=3))
	{
		cout<<"arg error!"<<endl;
		exit(1);
	}
	char* dir_name=argv[1];
	char* out_dir=argv[2];
	vector<string> filelist;
	getfilelist(dir_name,filelist);
	mfccOpt opt(400,//framelength
				200,//frameshift
				26,//filterbins
				16000,//fs
				100,
				12,//number os ceps
				2,
				0.001,
				0.1,//enagyscale
				true
		);
	mfcc ceptrum(opt);
	vector<vector<float>> ceps;

/////////////////////////////file write////////////////////////
	string tags("MFCC");
	featHeader header(tags,39,filelist.size());
	string outfile=string(out_dir);
	featWriter<float> featwrite(outfile.c_str(),header);
	fstream fout;
	outfile=outfile+".scp";
	fout.open(outfile,fstream::out);
		


////////////////////////////////////////////////////////////////
	int i=0;
	itemHeader itemhead;

	string strdir(dir_name);
	string temp;
	for(auto& it:filelist)
	{
		cout<<"processing:"<<filelist[i]<<endl<<endl;
		temp=strdir+"/"+filelist[i];
		ceptrum.getMfcc(temp,ceps);
		cout<<"finish !"<<"count: "<<i<<"  "<<filelist[i]<<endl;
		itemhead=itemHeader(i,ceps.size());
		featwrite.write(itemhead,ceps);
		ceps.clear();

		fout<<filelist[i].substr(0,filelist[i].find("_"))<<endl;
		i++;

	}
	
	//for(vector<float>& item:ceps)
	//{
	//	for(float& ite:item)
	// 	{
	//		cout<<ite<<" ";
	//	}
	//	cout<<endl;
	//}

}

void getfilelist(const char* dir_name,vector<string>& filelist)
{
	if( NULL == dir_name )
	{  
		cout<<" dir_name is null ! "<<endl;  
		return;  
	}  
	struct stat s;  
	lstat( dir_name , &s );  
	if( ! S_ISDIR( s.st_mode ) )  
	{  
		cout<<"dir_name is not a valid directory !"<<endl;  
		return;  
	}        
	struct dirent * filename;    // return value for readdir()  
	DIR * dir;                   // return value for opendir()  
	dir = opendir(dir_name);  
	if( NULL == dir )  
	{  
		cout<<"Can not open dir "<<dir_name<<endl;  
		return;
	}  
	cout<<"Successfully opened the dir !"<<endl; 
	while( (filename = readdir(dir))!= NULL)  
	{  
		if( strcmp(filename->d_name,".")==0||strcmp(filename->d_name,"..")== 0) 
		continue;  
		string temp=string(filename ->d_name);
		filelist.push_back(temp);
	}  

}
