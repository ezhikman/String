//#ifndef REF_COUNTING_H
//#define REF_COUNTING_H

#pragma once

#include<vector>
#include"String.h"

class RefCounting
{
	char* str;
	int ref_count;
public:

	friend class String;
	friend class SubString;

	RefCounting();
	RefCounting(char);
	RefCounting(char*);

	void ref_inc();
	void ref_dec();

	friend String* operator+(const String&,const String&);

	friend bool operator==(const String& l_val,const String& r_val);
	friend bool operator!=(const String&,const String&);
	friend bool operator<=(const String&,const String&);
	friend bool operator>=(const String&,const String&);
	friend bool operator<(const String&,const String&);
	friend bool operator>(const String&,const String&);

	friend std::ostream& operator<<(std::ostream&,const String&);
	friend std::istream& operator>>(std::istream&,const String&);

	~RefCounting();
};

//#endif