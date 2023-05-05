#pragma once
#include "TTabRecord.h"
#include "TDatCom.h"
#define TAB_OK 0
#define TAB_EMPTY -101
#define TAB_FULL -102
#define TAB_NO_RECORD -103
#define TAB_REC_DOUBLE -104
#define TAB_NO_MEM -105


class TTable: public TDatCom {
protected:
	size_t DataCount; //  ол-во записей
	size_t Efficiency; // Ёффективность
public:
	TTable() : DataCount(0), Efficiency(0) {}
	virtual ~TTable() {} // убрали virtual, и на что это повли€ет?
	size_t GetDataCount() const { return DataCount; }
	size_t GetEfficiency() const { return Efficiency; }

	bool isEmpty() const { return DataCount == 0; }
	virtual bool isFull() const = 0;

	virtual PTDatValue FindRecord(TKey key) = 0;
	virtual bool InsertRecord(TKey key, PTDatValue value) = 0; // передача value по ссылке
	virtual void DeleteRecord(TKey key) = 0;

	// »тератор
	virtual int Reset() = 0;
	virtual int IsTabEnded() const = 0;
	virtual int GoNext() = 0;
	virtual TKey GetKey() const = 0;
	virtual PTDatValue GetValuePTR() const = 0;


	friend std::ostream& operator<<(std::ostream& out, TTable& table) {
		for (table.Reset(); !table.IsTabEnded(); table.GoNext())
		{
			out << "Key: " << table.GetKey() << "\t\t\t Value: " << *table.GetValuePTR() << std::endl;
		}
		return out;
	}
};