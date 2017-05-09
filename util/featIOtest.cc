#include<iostream>
#include<vector>
#include<string>
#include"featureIO.h"

using namespace std;
using namespace DTW;

void unitTest()
{
	string tags("MFCC");
	featHeader header(tags,4,2);
	{
	cout<<"step 1"<<endl;			
	featWriter<float> featwrite("featfile",header);
	cout<<"step 2"<<endl;
	vector<vector<float>> item1={
	{1,2,3,4},
	{5,6,7,8},
	{5,4,3,2}};
	itemHeader itemheader1(0,3);

	vector<vector<float>> item2={
	{10,11,12,13},
	{5.1,4,3,-2}};
	itemHeader itemheader2(1,2);
	featwrite.write(itemheader1,item1);
	featwrite.write(itemheader2,item2);
	cout<<"step 3"<<endl;
	}
	cout<<"unittest";
	tags="";
	header=featHeader(tags,0,0);
	featReader<float> reader("featfile",header);
	cout<<header.featname_s6<<endl
			<<(unsigned int)header.dimframes<<endl
			<<(unsigned int)header.numitem<<endl;
  	itemHeader itemhead;
	vector<vector<float>> item;
	reader.read(itemhead,item);
	cout<<"itemID: "<<itemhead.itemID<<endl
			<<"numberframes: "<<itemhead.numframes<<endl;
	for(auto& its:item)
	{
		for(auto& it:its)
		{
			cout<<it<<" ";
		}
		cout<<endl;
	}





			
	
}
int  main()
{
	unitTest();
	return 0;
}
