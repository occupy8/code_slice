#include "variant.h"
#include <string.h>

#define FOR_MAP(m,k,v,i) for(map< k , v >::iterator i=(m).begin();i!=(m).end();i++)
#define MAP_KEY(i) ((i)->first)
#define MAP_VAL(i) ((i)->second)

int is_leap(unsigned y) {
	y += 1900;
	return (y % 4) == 0 && ((y % 100) != 0 || (y % 400) == 0);
}

time_t timegm(struct tm *tm) {
	static const unsigned ndays[2][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};
	time_t res = 0;
	int i;

	for (i = 70; i < tm->tm_year; ++i)
		res += is_leap(i) ? 366 : 365;

	for (i = 0; i < tm->tm_mon; ++i)
		res += ndays[is_leap(tm->tm_year)][i];
	res += tm->tm_mday - 1;
	res *= 24;
	res += tm->tm_hour;
	res *= 60;
	res += tm->tm_min;
	res *= 60;
	res += tm->tm_sec;
	return res;
}

Variant::Variant() {
	_type = V_NULL;
	memset(&_value, 0, sizeof (_value));
}

Variant::Variant(const Variant &val) {
	InternalCopy(val);
}

Variant::Variant(const bool &val) {
	_type = V_BOOL;
	memset(&_value, 0, sizeof (_value));
	_value.b = val;
}

Variant::Variant(const int8_t &val) {
	_type = V_INT8;
	memset(&_value, 0, sizeof (_value));
	_value.i8 = val;
}

Variant::Variant(const int16_t &val) {
	_type = V_INT16;
	memset(&_value, 0, sizeof (_value));
	_value.i16 = val;
}

Variant::Variant(const int32_t &val) {
	_type = V_INT32;
	memset(&_value, 0, sizeof (_value));
	_value.i32 = val;
}

Variant::Variant(const int64_t &val) {
	_type = V_INT64;
	memset(&_value, 0, sizeof (_value));
	_value.i64 = val;
}

Variant::Variant(const uint8_t &val) {
	_type = V_UINT8;
	memset(&_value, 0, sizeof (_value));
	_value.ui8 = val;
}

Variant::Variant(const uint16_t &val) {
	_type = V_UINT16;
	memset(&_value, 0, sizeof (_value));
	_value.ui16 = val;
}

Variant::Variant(const uint32_t &val) {
	_type = V_UINT32;
	memset(&_value, 0, sizeof (_value));
	_value.ui32 = val;
}

Variant::Variant(const uint64_t &val) {
	_type = V_UINT64;
	memset(&_value, 0, sizeof (_value));
	_value.ui64 = val;
}

Variant::Variant(const double &val) {
	_type = V_DOUBLE;
	memset(&_value, 0, sizeof (_value));
	_value.d = val;
}

Variant::Variant(const Timestamp &val) {
	_type = V_TIMESTAMP;
	memset(&_value, 0, sizeof (_value));
	_value.t = new Timestamp;
	*_value.t = val;
	NormalizeTs();
}

Variant::Variant(const uint16_t year, const uint8_t month, const uint8_t day) {
	_type = V_DATE;
	memset(&_value, 0, sizeof (_value));
	_value.t = new Timestamp;
	memset(_value.t, 0, sizeof (Timestamp));
	_value.t->tm_year = year - 1900;
	_value.t->tm_mon = month - 1;
	_value.t->tm_mday = day;
	_value.t->tm_hour = 0;
	_value.t->tm_min = 0;
	_value.t->tm_sec = 0;
	NormalizeTs();
}

Variant::Variant(const uint8_t hour, const uint8_t min, const uint8_t sec, const uint16_t m) {
	_type = V_TIME;
	memset(&_value, 0, sizeof (_value));
	_value.t = new Timestamp;
	memset(_value.t, 0, sizeof (Timestamp));
	_value.t->tm_year = 70;
	_value.t->tm_mon = 0;
	_value.t->tm_mday = 1;
	_value.t->tm_hour = hour;
	_value.t->tm_min = min;
	_value.t->tm_sec = sec;
	NormalizeTs();
}

Variant::Variant(const uint16_t year, const uint8_t month, const uint8_t day,
		const uint8_t hour, const uint8_t min, const uint8_t sec, const uint16_t m) {
	_type = V_TIMESTAMP;
	memset(&_value, 0, sizeof (_value));
	_value.t = new Timestamp;
	memset(_value.t, 0, sizeof (Timestamp));
	_value.t->tm_year = year - 1900;
	_value.t->tm_mon = month - 1;
	_value.t->tm_mday = day;
	_value.t->tm_hour = hour;
	_value.t->tm_min = min;
	_value.t->tm_sec = sec;
	NormalizeTs();
}

Variant::Variant(const char *pVal) {
	_type = V_STRING;
	memset(&_value, 0, sizeof (_value));
	_value.s = new string(pVal);
}

Variant::Variant(const string &val) {
	_type = V_STRING;
	memset(&_value, 0, sizeof (_value));
	_value.s = new string(val);
}

Variant::Variant(const uint8_t *pVal, uint32_t len) {
	_type = V_BYTEARRAY;
	memset(&_value, 0, sizeof (_value));
	_value.s = new string((const char*)pVal, (size_t)len);
}

Variant::~Variant() {
	Reset();
}

void Variant::Reset(bool isUndefined) {
	switch (_type) {
		case V_DATE:
		case V_TIME:
		case V_TIMESTAMP:
		{
			delete _value.t;
			break;
		}
		case V_BYTEARRAY:
		case V_STRING:
		{
			delete _value.s;
			break;
		}
		case V_MAP:
		case V_TYPED_MAP:
		{
			delete _value.m;
			break;
		}
		default:
		{
			break;
		}
	}
	if (isUndefined)
		_type = V_UNDEFINED;
	else
		_type = V_NULL;
	memset(&_value, 0, sizeof (_value));
}

Variant& Variant::operator=(const Variant &val) {
	Reset();
	InternalCopy(val);
	return *this;
}

Variant& Variant::operator=(const bool &val) {
	Reset();
	_type = V_BOOL;
	_value.b = val;
	return *this;
}

Variant& Variant::operator=(const int8_t &val) {
	Reset();
	_type = V_INT8;
	_value.i8 = val;
	return *this;
}

Variant& Variant::operator=(const int16_t &val) {
	Reset();
	_type = V_INT16;
	_value.i16 = val;
	return *this;
}

Variant& Variant::operator=(const int32_t &val) {
	Reset();
	_type = V_INT32;
	_value.i32 = val;
	return *this;
}

Variant& Variant::operator=(const int64_t &val) {
	Reset();
	_type = V_INT64;
	_value.i64 = val;
	return *this;
}

Variant& Variant::operator=(const uint8_t &val) {
	Reset();
	_type = V_UINT8;
	_value.ui8 = val;
	return *this;
}

Variant& Variant::operator=(const uint16_t &val) {
	Reset();
	_type = V_UINT16;
	_value.ui16 = val;
	return *this;
}

Variant& Variant::operator=(const uint32_t &val) {
	Reset();
	_type = V_UINT32;
	_value.ui32 = val;
	return *this;
}

Variant& Variant::operator=(const uint64_t &val) {
	Reset();
	_type = V_UINT64;
	_value.ui64 = val;
	return *this;
}

Variant& Variant::operator=(const double &val) {
	Reset();
	_type = V_DOUBLE;
	_value.d = val;
	return *this;
}

Variant& Variant::operator=(const Timestamp &val) {
	Reset();
	_type = V_TIMESTAMP;
	_value.t = new Timestamp;
	*_value.t = val;
	NormalizeTs();
	return *this;
}

Variant& Variant::operator=(const char *pVal) {
	Reset();
	_type = V_STRING;
	_value.s = new string(pVal);
	return *this;
}

Variant& Variant::operator=(const string &val) {
	Reset();
	_type = V_STRING;
	_value.s = new string(val);
	return *this;
}

Variant::operator VariantType() {
	return _type;
}

#define OPERATOR_DEF(ctype) \
Variant::operator ctype() {\
    switch (_type) {\
        case V_NULL:\
        case V_UNDEFINED:\
        {\
            return 0;\
        }\
        case V_BOOL:\
        {\
            return (ctype) _value.b;\
        }\
        case V_INT8:\
        {\
            return (ctype) _value.i8;\
        }\
        case V_INT16:\
        {\
            return (ctype) _value.i16;\
        }\
        case V_INT32:\
        {\
            return (ctype) _value.i32;\
        }\
        case V_INT64:\
        {\
            return (ctype) _value.i64;\
        }\
        case V_UINT8:\
        {\
            return (ctype) _value.ui8;\
        }\
        case V_UINT16:\
        {\
            return (ctype) _value.ui16;\
        }\
        case V_UINT32:\
        {\
            return (ctype) _value.ui32;\
        }\
        case V_UINT64:\
        {\
            return (ctype) _value.ui64;\
        }\
        case V_DOUBLE:\
        {\
            return (ctype) _value.d;\
        }\
        case V_TIMESTAMP:\
        case V_DATE:\
        case V_TIME:\
        case V_STRING:\
        case V_TYPED_MAP:\
        case V_MAP:\
        default:\
        {\
            ASSERT("Cast failed: %s", STR(ToString()));\
            return 0;\
        }\
    }\
}

OPERATOR_DEF(int8_t);
OPERATOR_DEF(int16_t);
OPERATOR_DEF(int32_t);
OPERATOR_DEF(int64_t);
OPERATOR_DEF(uint8_t);
OPERATOR_DEF(uint16_t);
OPERATOR_DEF(uint32_t);
OPERATOR_DEF(uint64_t);
OPERATOR_DEF(double);

Variant::operator bool() {
	switch (_type) {
		case V_NULL:
		case V_UNDEFINED:
		{
			return false;
		}
		case V_BOOL:
		{
			return _value.b;
		}
		case V_INT8:
		case V_INT16:
		case V_INT32:
		case V_INT64:
		case V_UINT8:
		case V_UINT16:
		case V_UINT32:
		case V_UINT64:
		case V_DOUBLE:
		{
			bool result = false;
			result |= (_value.i8 != 0);
			result |= (_value.i16 != 0);
			result |= (_value.i32 != 0);
			result |= (_value.i64 != 0);
			result |= (_value.ui8 != 0);
			result |= (_value.ui16 != 0);
			result |= (_value.ui32 != 0);
			result |= (_value.ui64 != 0);
			return result;
		}
		case V_TIMESTAMP:
		case V_DATE:
		case V_TIME:
		case V_STRING:
		case V_TYPED_MAP:
		case V_MAP:
		default:
		{
			ASSERT("Cast to bool failed: %s", STR(ToString()));
			return false;
		}
	}
}

Variant::operator Timestamp() {
	if ((_type == V_DATE)
			|| (_type == V_TIME)
			|| (_type == V_TIMESTAMP)) {
		return *_value.t;
	} else {
		ASSERT("Cast to struct tm failed: %s", STR(ToString()));
		Timestamp temp = Timestamp_init;
		return temp;
	}
}

Variant::operator string() {
	switch (_type) {
		case V_BOOL:
		{
			return _value.b ? "true" : "false";
		}
		case V_INT8:
		case V_INT16:
		case V_INT32:
		{
			return format("%d", this->operator int32_t());
		}
		case V_INT64:
		{
			return format("%"PRId64, this->operator int64_t());
		}
		case V_UINT8:
		case V_UINT16:
		case V_UINT32:
		{
			return format("%u", this->operator uint32_t());
		}
		case V_UINT64:
		{
			return format("%"PRIu64, this->operator uint64_t());
		}
		case V_DOUBLE:
		{
			return format("%.3f", this->operator double());
		}
		case V_TIMESTAMP:
		{
			char tempBuff[24] = {0};
			return string(tempBuff, strftime(tempBuff, 24, "%Y-%m-%dT%H:%M:%S.000", _value.t));
		}
		case V_DATE:
		{
			char tempBuff[24] = {0};
			return string(tempBuff, strftime(tempBuff, 24, "%Y-%m-%d", _value.t));
		}
		case V_TIME:
		{
			char tempBuff[24] = {0};
			return string(tempBuff, strftime(tempBuff, 24, "%H:%M:%S.000", _value.t));
		}
		case V_BYTEARRAY:
		case V_STRING:
		{
			return *_value.s;
		}
		case V_NULL:
		case V_UNDEFINED:
		case V_TYPED_MAP:
		case V_MAP:
		default:
		{
			// Change ASSERT to FATAL to avoid crash
			FATAL("Cast to string failed: %s", STR(ToString()));
			return "";
		}
	}
}

Variant& Variant::operator[](const string &key) {
	if ((_type != V_TYPED_MAP)
			&& (_type != V_MAP)
			&& (_type != V_NULL)
			&& (_type != V_UNDEFINED)) {
				assert(0);
	}
	if ((_type == V_NULL) || (_type == V_UNDEFINED)) {
		_type = V_MAP;
		_value.m = new VariantMap;
	}
	map<string, Variant>::iterator i = _value.m->children.find(key);
	if (i == _value.m->children.end()) {
		return (_value.m->children[key] = Variant());
	} else {
		return i->second;
	}
}

Variant& Variant::operator[](const char *key) {
	return operator[](string(key));
}

Variant& Variant::operator[](const uint32_t &key) {
	char temp[11];
	sprintf(temp, "0x%08"PRIx32, key);
	return operator[](temp);
}

Variant& Variant::operator[](Variant &key) {
	switch (key._type) {
		case V_INT8:
		case V_INT16:
		case V_INT32:
		case V_UINT8:
		case V_UINT16:
		case V_UINT32:
		{
			char temp[11];
			sprintf(temp, "0x%08"PRIx32, (uint32_t) key);
			return operator[](temp);
		}
		case V_STRING:
		{
			return operator[](*key._value.s);
		}
		default:
		{
			assert(0);
			break;
		}
	}
}

Variant &Variant::GetValue(string key, bool caseSensitive) {
	if (caseSensitive) {
		return (*this)[key];
	} else {

		FOR_MAP(*this, string, Variant, i) {
			if (lowerCase(MAP_KEY(i)) == lowerCase(key))
				return MAP_VAL(i);
		}

		return (*this)[key];
	}
}

bool Variant::operator==(const Variant &value) const {
	if (this == &value)
		return true;
	if (_type != value._type) {
		if (((_type == V_NULL) && (value._type == V_UNDEFINED))
				|| ((_type == V_UNDEFINED) && (value._type == V_NULL)))
			return true;
		return false;
	}
	switch (_type) {
		case V_BOOL:
			return _value.b == value._value.b;
		case V_INT8:
			return _value.i8 == value._value.i8;
		case V_INT16:
			return _value.i16 == value._value.i16;
		case V_INT32:
			return _value.i32 == value._value.i32;
		case V_INT64:
			return _value.i64 == value._value.i64;
		case V_UINT8:
			return _value.ui8 == value._value.ui8;
		case V_UINT16:
			return _value.ui16 == value._value.ui16;
		case V_UINT32:
			return _value.ui32 == value._value.ui32;
		case V_UINT64:
			return _value.ui64 == value._value.ui64;
		case V_DOUBLE:
			return _value.d == value._value.d;
		case V_TIMESTAMP:
			return (_value.t->tm_year == value._value.t->tm_year)
					&& (_value.t->tm_mon == value._value.t->tm_mon)
					&& (_value.t->tm_mday == value._value.t->tm_mday)
					&& (_value.t->tm_hour == value._value.t->tm_hour)
					&& (_value.t->tm_min == value._value.t->tm_min)
					&& (_value.t->tm_sec == value._value.t->tm_sec)
					&& (_value.t->tm_isdst == value._value.t->tm_isdst)
					;
		case V_DATE:
			return (_value.t->tm_year == value._value.t->tm_year)
					&& (_value.t->tm_mon == value._value.t->tm_mon)
					&& (_value.t->tm_mday == value._value.t->tm_mday)
					;
		case V_TIME:
			return (_value.t->tm_hour == value._value.t->tm_hour)
					&& (_value.t->tm_min == value._value.t->tm_min)
					&& (_value.t->tm_sec == value._value.t->tm_sec)
					&& (_value.t->tm_isdst == value._value.t->tm_isdst)
					;
		case V_BYTEARRAY:
		case V_STRING:
			return *_value.s == *value._value.s;
		case V_TYPED_MAP:
			if (_value.m->typeName != value._value.m->typeName)
				return false;
		case V_MAP:
		{
			if (_value.m->children.size() != value._value.m->children.size())
				return false;
			map<string, Variant>::iterator found;

			FOR_MAP(_value.m->children, string, Variant, i) {
				found = value._value.m->children.find(MAP_KEY(i));
				if (found == value._value.m->children.end())
					return false;
				if (MAP_VAL(i) != MAP_VAL(found))
					return false;
			}
			return true;
		}
		case V_NULL:
		case V_UNDEFINED:
			return true;
		default:
		{
			ASSERT("Invalid variant type: %d", _type);
			return false;
		}
	}
}

bool Variant::operator!=(const Variant &value) const {
	return !(*this == value);
}

bool Variant::operator==(const char *pValue) const {
	if (_type == V_STRING)
		return *_value.s == pValue;
	return false;
}

bool Variant::operator!=(const char *pValue) const {
	return !(*this == pValue);
}

bool Variant::operator==(const string &value) const {
	if (_type == V_STRING)
		return *_value.s == value;
	return false;
}

bool Variant::operator!=(const string &value) const {
	return !(*this == value);
}

bool Variant::operator==(const VariantType value) const {
	if (value == _V_NUMERIC) {
		return (_type == V_INT8)
				|| (_type == V_INT8)
				|| (_type == V_INT16)
				|| (_type == V_INT32)
				|| (_type == V_INT64)
				|| (_type == V_UINT8)
				|| (_type == V_UINT16)
				|| (_type == V_UINT32)
				|| (_type == V_UINT64)
				|| (_type == V_DOUBLE);
	} else {
		return _type == value;
	}
}

bool Variant::operator!=(const VariantType value) const {
	return !(*this == value);
}

void Variant::InternalCopy(const Variant &val) {
	_type = val._type;
	memset(&_value, 0, sizeof (_value));
	switch (val._type) {
		case V_DATE:
		case V_TIME:
		case V_TIMESTAMP:
		{
			_value.t = new Timestamp(*val._value.t);
			break;
		}
		case V_BYTEARRAY:
		case V_STRING:
		{
			_value.s = new string(*val._value.s);
			break;
		}
		case V_MAP:
		case V_TYPED_MAP:
		{
			_value.m = new VariantMap(*val._value.m);
			break;
		}
		default:
		{
			memcpy(&_value, &val._value, sizeof (_value));
			break;
		}
	}
}

void Variant::NormalizeTs() {
	time_t val = timegm(_value.t);
	if (val < 0) {
		val = 0;
	}
}

