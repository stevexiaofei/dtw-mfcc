#include<iostream>
#include<fstream>
#include<vector>
#include<assert.h>

#include"util/featureIO.h"
#include"distance/ComputeMfccDist.h"
#include"distance/util.h"
#include"AccumDist.h"

using namespace std;
using namespace DTW;
typedef AccumDist::Pattern Pattern;
int main()
{
	fstream In_template,In_test;
	In_template.open("/home/xiao/data/template/template.feat.scp",fstream::in);
	In_test.open("/home/xiao/data/test/test.feat.scp",fstream::in);
    vector<string> templatelist,testlist;
	string tempstr;
	while(In_template>>tempstr)
		templatelist.push_back(tempstr);
	
	while(In_test>>tempstr)
		testlist.push_back(tempstr);
	featHeader templateHeader("",0,0);
	featHeader testHeader("",0,0);
	featReader<float> templatereader("/home/xiao/data/template/template.feat",templateHeader);
	featReader<float> testreader("/home/xiao/data/test/test.feat",testHeader);
////////////////////////////////////////////////////////
	cout<<templateHeader.featname_s6<<endl
			<<(int)templateHeader.dimframes<<endl
			<<(int)templateHeader.numitem<<endl;
///////////////////////////////////////////////////////////////
	vector<vector<vector<float>>> templates;
	templates.resize(templateHeader.numitem);
	int i=0;
	itemHeader itemhead;
	vector<vector<float>> temp;
	while(i<templateHeader.numitem)
	{
		templatereader.read(itemhead,temp);
		assert(i==itemhead.itemID);	
		templates[i].swap(temp);
		i++;
		cout<<itemhead.numframes<<endl;
	}
/////////////////////////////////////////////////////////////
	//ComputeMfccDist computedist(EularDist); 
	ComputeMfccDist computedist(DiscretCosDist); 
	i=0;
	int rightcount=0;
	while(i<testHeader.numitem)
	{
		testreader.read(itemhead,temp);
		vector<float> globaldist;
		for(int j=0;j<templates.size();j++)
		{
			float* ptr=new float[temp.size()*templates[j].size()];
			cout<<"template frames:"<<templates[j].size()<<" "<<"test frames:"<<temp.size()<<endl<<endl;
			float* accumWeight=new float[temp.size()*templates[j].size()];
			computedist.getlocalMat(templates[j],temp,ptr);

			{
				AccumDist accumdist(Pattern(templates[j].size(),temp.size()),accumWeight,ptr);
				globaldist.push_back(accumdist.ComputeAccumDist(AccumDist::AccumPathA));
			} 	 
			delete[] ptr;
			delete[] accumWeight;
		}
		string str=templatelist[std::distance(globaldist.begin(),
						std::min_element(globaldist.begin(),globaldist.end()))];
		cout<<"test case:"<<i<<endl;
		cout<<"the predict is: "<<str<<endl;
		cout<<"this item is: "<<testlist[i]<<endl;
		
		if(strcmp(str.c_str(),testlist[i].c_str())==0)
			rightcount++;
		for(auto&it:globaldist)
			cout<<it<<" ";
		cout<<endl<<endl<<endl;
		i++;
	}
	for(auto& it:templatelist)
		cout<<it<<endl;;
	cout<<"the ASR rate is:"<<(rightcount/float(testlist.size()))<<endl;
	//for(auto& items:templates[1])
	//{
	//	for(auto& it:items)
	//	{
	//		cout<<it<<" ";
	//	}
	//	cout<<endl;
	//}
	return 0;
}
