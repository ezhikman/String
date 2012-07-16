//#ifndef SUBSTRING_H
//#define SUBSTRING_H

#pragma once
#include"String.h"

class SubString
{
	String* str_parent;
	int dest;
	int shift;
public:

	SubString(int d,int s,String* st):dest(d),shift(s),str_parent(st){};

	SubString& operator=(char*);
	SubString& operator=(const String*);
	friend class String;
};

//#endif