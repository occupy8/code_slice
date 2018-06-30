#ifndef _VARIANT_H
#define _VARIANT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#define Timestamp struct tm

typedef enum _VariantType {
	V_NULL = 1,
	V_UNDEFINED = 2,
	V_BOOL = 3,
	V_INT8 = 4,
	V_INT16 = 5,
	V_INT32 = 6,
	V_INT64 = 7,
	V_UINT8 = 8,
	V_UINT16 = 9,
	V_UINT32 = 10,
	V_UINT64 = 11,
	V_DOUBLE = 12,
	_V_NUMERIC = 13,
	V_TIMESTAMP = 14,
	V_DATE = 15,
	V_TIME = 16,
	V_STRING = 17,
	V_TYPED_MAP = 18,
	V_MAP = 19,
	V_BYTEARRAY = 20 
} VariantType;

struct VariantMap {
	string typeName;
	map<string, Variant> children;
	bool isArray;

	VariantMap(VariantMap & variantMap) {
		typeName = variantMap.typeName;
		children = variantMap.children;
		isArray = variantMap.isArray;
	}

	VariantMap() {
		isArray = false;
	}
};

class DLLEXP Variant {
private:
	VariantType _type;

	union {
		bool b;
		int8_t i8;
		int16_t i16;
		int32_t i32;
		int64_t i64;
		uint8_t ui8;
		uint16_t ui16;
		uint32_t ui32;
		uint64_t ui64;
		double d;
		Timestamp *t;
		string *s;
		VariantMap *m;
	} _value;
public:
	Variant();
	Variant(const Variant &val);

	Variant(const bool &val);
	Variant(const int8_t &val);
	Variant(const int16_t &val);
	Variant(const int32_t &val);
	Variant(const int64_t &val);
	Variant(const uint8_t &val);
	Variant(const uint16_t &val);
	Variant(const uint32_t &val);
	Variant(const uint64_t &val);
	Variant(const double &val);

	Variant(const Timestamp &time);
	Variant(const uint16_t year, const uint8_t month, const uint8_t day);
	Variant(const uint8_t hour, const uint8_t min, const uint8_t sec, const uint16_t m);
	Variant(const uint16_t year, const uint8_t month, const uint8_t day,
			const uint8_t hour, const uint8_t min, const uint8_t sec, const uint16_t m);

	Variant(const char *pValue);
	Variant(const string &value);
	Variant(const uint8_t *pValue, uint32_t len);

	virtual ~Variant();

	void Reset(bool isUndefined = false);

	Variant & operator=(const Variant &val);
	Variant & operator=(const bool &val);
	Variant & operator=(const int8_t &val);
	Variant & operator=(const int16_t &val);
	Variant & operator=(const int32_t &val);
	Variant & operator=(const int64_t &val);
	Variant & operator=(const uint8_t &val);
	Variant & operator=(const uint16_t &val);
	Variant & operator=(const uint32_t &val);
	Variant & operator=(const uint64_t &val);
	Variant & operator=(const double &val);

	Variant & operator=(const Timestamp &val);

	Variant & operator=(const char *pVal);
	Variant & operator=(const string &val);

	operator VariantType();
	operator bool();
	operator int8_t();
	operator int16_t();
	operator int32_t();
	operator int64_t();
	operator uint8_t();
	operator uint16_t();
	operator uint32_t();
	operator uint64_t();
	operator double();
	operator Timestamp();
	operator string();

	Variant & operator[](const string &key);
	Variant & operator[](const char *key);
	Variant & operator[](const uint32_t &key);
	Variant & operator[](Variant &key);
	Variant & GetValue(string key, bool caseSensitive);

	bool operator==(const Variant &value) const;
	bool operator!=(const Variant &value) const;
	bool operator==(const char *pValue) const;
	bool operator!=(const char *pValue) const;
	bool operator==(const string &value) const;
	bool operator!=(const string &value) const;
	bool operator==(const VariantType value) const;
	bool operator!=(const VariantType value) const;
};


#endif
