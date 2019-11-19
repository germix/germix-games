////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FadingHandler
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___FadingHandler_h___
#define ___FadingHandler_h___

class FadingHandler
{
	double				time;
	bool				inverted;
	double				maxTime;
	int					minValue;
	int					maxValue;
	int					currentValue;
	int					initialValue;
public:
	FadingHandler(double maxTime, int maxValue);
	FadingHandler(double maxTime, int maxValue, bool inverted);
	FadingHandler(double maxTime, int minValue, int maxValue, bool inverted);
	~FadingHandler();
public:
	void reset(bool inv = false);
	bool update(double dt);
	inline int value() const { return currentValue; }
	inline bool isInverted() const { return inverted; }
};

#endif
