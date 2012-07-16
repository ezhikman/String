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
	char* temp_s = new char[strlen(refcount->str)+1];
	strcpy(temp_s,refcount->str);

	refcount->ref_dec();
	
	refcount = new RefCounting(temp_s);
	delete temp_s;
}

int String::Size()
{
	return strlen(this->refcount->str);
}

SubString* String::substr(int dest, int shift)
{
	if((shift+dest)>strlen(refcount->str))
		return NULL;
	SubString* substring = new SubString(dest,shift,this);
	return substring;
}

String* operator+(const String& l_val,const String& r_val)//error
{
	char* temp_ch = new char[strlen(l_val.refcount->str)+strlen(r_val.refcount->str)];
	strcpy(temp_ch,l_val.refcount->str);
	strcat(temp_ch,r_val.refcount->str);

    String* temp_str = new String(temp_ch);
	delete temp_ch;

	return temp_str;
}

String& String::operator+=(const String& r_val)
{
	if(r_val.refcount->ref_count>1)
		this->AllocRef();
	strcat(this->refcount->str, r_val.refcount->str);
	return *this;
}

String& String::operator=(const String& r_val)
{
	if(r_val.refcount->ref_count>1)
		this->AllocRef();
	strcpy(this->refcount->str, r_val.refcount->str);
	return *this;
}

bool operator==(const String& l_val,const String& r_val)
{
	return ((strcmp(l_val.refcount->str,r_val.refcount->str)==0)?true:false);
}

bool operator!=(const String& l_val,const String& r_val)
{
	return ((strcmp(l_val.refcount->str,r_val.refcount->str)!=0)?true:false);
}

bool operator<=(const String& l_val,const String& r_val)
{
	if(strcmp(l_val.refcount->str,r_val.refcount->str) <=0)
		return true;
	return false;
}

bool operator>=(const String& l_val,const String& r_val)
{
	if(strcmp(l_val.refcount->str,r_val.refcount->str) >=0)
		return true;
	return false;
}

bool operator<(const String& l_val,const String& r_val)
{
	if(strcmp(l_val.refcount->str,r_val.refcount->str) < 0)
		return true;
	return false;
}

bool operator>(const String& l_val,const String& r_val)
{
	if(strcmp(l_val.refcount->str,r_val.refcount->str) > 0)
		return true;
	return false;
}

ostream& operator<<(ostream& os, const String& s)
{
	for(int i=0; i<strlen(s.refcount->str);i++)
		os<<s.refcount->str[i];
	os<<"."<<endl;
	return os;
}

istream& operator>>(istream& is, const String& s)
{
	for(int i=0; i<strlen(s.refcount->str);i++)
		is>>s.refcount->str[i];
	return is;
}

char String::operator[](int i) const
{
	return (i<=strlen(this->refcount->str)) ? this->refcount->str[i] : NULL;
}

char* String::c_str()
{
	if(this->refcount->str!=NULL)
		return this->refcount->str;
	return NULL;
}

