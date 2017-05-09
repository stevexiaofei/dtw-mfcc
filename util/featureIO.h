#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
namespace DTW{

struct featHeader{
	string featname_s6;
	unsigned char dimframes;
	unsigned char numitem;
	featHeader(string c_featname,unsigned char c_dimframes,
					unsigned char c_numitem)
	{
		featname_s6=c_featname;
		dimframes=c_dimframes;
		numitem=c_numitem;
	}
	featHeader()
	{
	}
};
struct itemHeader{
	unsigned int itemID;
	unsigned int numframes;
	itemHeader(unsigned int c_itemID,unsigned int c_numberframes)
	{
		itemID=c_itemID;
		numframes=c_numberframes;
	}
	itemHeader()
	{}
};
		

template<typename T>
class featWriter{
typedef unsigned int uint;
public:


	featWriter(string filename,featHeader& header);
	void write(itemHeader& header,vector<vector<T>>& featSquence); 
private:
	std::ofstream writer;
	

};
template<typename T>
featWriter<T>::featWriter(string filename,featHeader& header):writer(filename.c_str(),std::ios::binary)
{
	char temp[6];
	
	strcpy(temp,header.featname_s6.c_str());
	writer.write(temp,6*sizeof(char));
	writer.write(reinterpret_cast<char*>(&header.dimframes),
					sizeof(char));
	writer.write(reinterpret_cast<char*>(&header.numitem),
					sizeof(char));
	
}
template<typename T>
void featWriter<T>::write(itemHeader& header,vector<vector<T>>& featSquence)
{
	writer.write(reinterpret_cast<char*>(&header),sizeof(itemHeader));
	for(int i=0;i<featSquence.size();i++)
	{
	   	 writer.write(reinterpret_cast<char*>(featSquence[i].data()),featSquence[i].size()*sizeof(T));	
	}
}
template<typename T>
class featReader{
public:
	featReader(string filename,featHeader& header);
	void read(itemHeader& header,vector<vector<T>>& featSquence);
private:
	std::ifstream reader;
	unsigned char dim;
};
template<typename T>
featReader<T>::featReader(string filename,featHeader& header):reader(filename.c_str(),std::ios::binary)
{
	char temp[6];
	reader.read(temp,6*sizeof(char));
	
	header.featname_s6=temp;
	reader.read(reinterpret_cast<char*>(&header.dimframes),sizeof(char));
	reader.read(reinterpret_cast<char*>(&header.numitem),sizeof(char));
	dim=header.dimframes;
}
template<typename T>
void featReader<T>::read(itemHeader& header,vector<vector<T>>& featSquence)
{
	reader.read(reinterpret_cast<char*>(&header),sizeof(itemHeader));
	featSquence.clear();
	featSquence.resize(header.numframes);
	for(int i=0;i<header.numframes;i++)
	{
		featSquence[i].resize(dim);
		reader.read(reinterpret_cast<char*>(featSquence[i].data()),dim*sizeof(T));

	}
}

}
