#pragma once

#include <iostream>
#include "TDatValue.h"

typedef std::string TKey;

class TTabRecord : public TDatValue {

protected:
	
	TKey _key;
	PTDatValue _value;

	void Print(std::ostream& os) override { // const
		os << _key << " " << *_value;
	}

	void SetKey(const TKey& key) { _key = key; }
	void SetValue(PTDatValue value) { _value = value; }

public:
	TTabRecord(const TKey& key = "", PTDatValue value = nullptr) :
		_key(key), _value(value) {}


	TKey GetKey() { return _key; }
	PTDatValue GetValue() { return _value; }

	TTabRecord& operator=(const TTabRecord& other) {
		_key = other._key;
		_value = other._value;

		return *this;
	}

	bool operator==(const TTabRecord& other) {
		return _key == other._key;
	}

	bool operator<(const TTabRecord& other) {
		return _key < other._key;
	}

	bool operator>(const TTabRecord& other) {
		return _key > other._key;
	}

	PTDatValue GetCopy() override {
		return new TTabRecord(_key, _value);
	}

	friend class TScanTable;
	friend class TArrayTable;
};

typedef TTabRecord* PTTabRecord;