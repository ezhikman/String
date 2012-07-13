#include"String.h"
#include<cstdlib>
#include<string.h>

using namespace std;

String::String()
{
	refcount = new RefCounting();
}

String::String(String& temp_str)
{
	refcount = temp_str.refcount;
	refcount->ref_inc();
}

String::String(char* chp)
{
	refcount = new RefCounting(chp);
}

String::String(char ch)
{
	refcount = new RefCounting(ch);
}

String::~String()
{
	refcount->ref_dec();
}

void String::AllocRef()
{
	refcount->ref_dec();
	refcount = new RefCounting(refcount->str);
}

int String::Size()
{
	return strlen(this->refcount->str);
}

SubString& String::substr(int dest, int shift)
{
	SubString* substring = new SubString;
}

String& operator+(const String&,const String& r_val)
{
	
}

String& String::operator+=(const String&)
{
	this->AllocRef();
}

String& String::operator=(const String& r_val)
{
	this->AllocRef();
}

bool operator==(const String& l_val,const String& r_val)
{
	return ((strcmp(l_val.str,r_val.str)==0)?true:false);
}

bool operator!=(const String& l_val,const String& r_val)
{
	return ((strcmp(l_val.str,r_val.str)!=0)?true:false);
}

bool operator<=(const String& l_val,const String& r_val)
{

}

bool operator>=(const String& l_val,const String& r_val)
{

}

bool operator<(const String& l_val,const String& r_val)
{

}

bool operator>(const String& l_val,const String& r_val)
{

}

ostream& operator<<(ostream& os, const String&)
{

}

istream& operator>>(istream& is, const String&)
{

}

char String::operator[](int) const
{

}

char* String::c_str()
{
	if(str!=NULL)
		return str;
	return NULL;
}

