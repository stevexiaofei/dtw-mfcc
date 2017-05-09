namespace DTW{
class ComputeLocalDistItf{
public:
ComputeLocalDistItf(){}

~ComputeLocalDistItf(){}

virtual float ComputeDist(unsigned short i,unsigned short j)const=0;

};

}
