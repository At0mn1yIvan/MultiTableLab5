#pragma once
#include <iostream>

class TDatValue
{
protected:
	virtual void Print(std::ostream& os) = 0; // const
public:

	TDatValue() = default;
	virtual TDatValue* GetCopy() = 0;
	friend std::ostream& operator<<(std::ostream& os,TDatValue& dv)  // const dv
	{
		//? TDatValue == nullpointer
		dv.Print(os);
		return os;
	};
	

};

typedef TDatValue* PTDatValue;
