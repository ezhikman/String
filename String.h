//#ifndef	STRING_H
//#define STRING_H

#pragma once

#include<iostream>
#include<string.h>

class RefCounting;
class SubString;

class String 
{
	RefCounting* refcount;

public:

	friend class SubString;

	String();
	String(String&);
	String(char*);
	String(char ch);

	void AllocRef();

	SubString& substr(int dest,int shift);

	int Size();

	friend String& operator+(const String&,const String&);//

	String& operator+=(const String&);
	String& operator=(const String&);
	String& operator=(const char*);

	friend bool operator==(const String&,const String&);
	friend bool operator!=(const String&,const String&);
	friend bool operator<=(const String&,const String&);
	friend bool operator>=(const String&,const String&);
	friend bool operator<(const String&,const String&);
	friend bool operator>(const String&,const String&);

	friend std::ostream& operator<<(std::ostream&,const String&);
	friend std::istream& operator>>(std::istream&,const String&);
	
	char operator[](int) const;
	char* c_str();

	~String();
};

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
	RefCounting(RefCounting&);

	void ref_inc();
	void ref_dec();

	friend String& operator+(const String&,const String&);

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

class SubString
{
	String* str_parent;
	int dest;
	int shift;
public:

	SubString(int d,int s,String* st):dest(d),shift(s),str_parent(st){};

	SubString& operator=(const char*);
	SubString& operator=(const String&);

	friend class String;
};

//#endif