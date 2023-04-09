#pragma once
#define DATA_OK 0
#define DATA_ERROR -1

class TDatCom {
protected:
	int RetCode;
	int SetRetCode(int ret) { return RetCode = ret; }
public:
	TDatCom(): RetCode(DATA_OK) {}
	int GetRetCode() {
		int tmp = RetCode;
		RetCode = DATA_OK;
		return tmp;
	}
	virtual ~TDatCom() {}
};