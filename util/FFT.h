struct Complex{
	float real;
	float img;
};
__device__ __host__ Complex add(Complex& ca,Complex& cb){
	return Complex{ca.real+cb.real,ca.img+cb.img};
};
 __device__ __host__ Complex sub(Complex& ca,Complex& cb){
	return Complex(ca.real-cb.real,ca.img-cb.img);
};
 __device__ __host__ Complex mul(Complex& ca,Complex& cb){
	return Complex{ca.real*cb.real-ca.img*cb.img,ca.img*cb.real+ca.real*cb.img};
};
__device__ __host__ void bufferfly(Complex& ca, Complex &cb, 
				Complex& coes,Complex& c,Complex& d){
	  Complex mulRes=mul(coes,cb);
      c=add(ca,mulRes);
	  d=sub(ca,mulRes);
};

struct FFTpatern{
	unsigned int batch;
	unsigned int length;
	Complex* data;
};
typedef FFTpatern FtPat;
void CalcuCoes(int n,Complex* ptrCoes);
extern "C"{
void FFT(FtPat& in);
void FFT(FtPat& FtIn,Ftpat& FtOut);
};

