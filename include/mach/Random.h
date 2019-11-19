////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Random
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Random_h___
#define ___Random_h___

class Random
{
	mutable unsigned long holdrand;
public:
	Random();
	Random(unsigned long seed);
	Random(const Random& other);
	~Random();
public:
	Random& operator = (const Random& other);
public:
	int nextInt() const;
	int nextInt(int n) const;
	int nextInt(int min, int max) const;
	double nextDouble() const;
	double nextDouble(double n) const;
	double nextDouble(double min, double max) const;
};

#endif

