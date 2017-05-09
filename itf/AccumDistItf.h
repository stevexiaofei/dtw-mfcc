
namespace DTW{

class AccumDistItf{

struct Pattern{
	unsigned short m;
	unsigned short n;
};
public:
	AccumDistItf(const Pattern c_Pat,float* cptr_DistMat,
					float* cptr_LocalDist):
			Pat(c_Pat),ptrDistMat(cptr_DistMat),
			ptrLocalDist(cptr_LocalDist){}
	~AccumDistItf(){}
	virtual void InitDist(unsigned int initdepth)=0;
	virtual float ComputeAccumDist()=0;
private:
	virtual void  SetCurAccumDist(unsigned short i,unsigned short j)=0;
	Pattern Pat;
	float* ptrDistMat;
	float* ptrLocalDist;
	bool NeedTrace;//TODO
	
};
}
