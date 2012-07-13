#ifndef  STRING_H
#define STRING_H

#pragma once

#include<iostream>
#include<vector>
#include"RefCounting.h"
#include"SubString.h"

class String 
{
	RefCounting* refcount;

public:

	String();
	String(String&);
	String(char*);
	String(char ch);

	void AllocRef();

	SubString& substr(int dest,int shift);

	int Size();

	friend String& operator+(const String&,const String&);

	String& operator+=(const String&);
	String& operator=(const String&);

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

#endif