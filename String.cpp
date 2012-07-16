#include"String.h"
#include<cstdlib>

using namespace std;

String::String()
{
	refcount = new RefCounting();
	//cout<<"default constructor";
}

String::String(String& temp_str)
{
	refcount = temp_str.refcount;
	refcount->ref_inc();
	//cout<<"copy constructor";
}

String::String(char* chp)
{
	refcount = new RefCounting(chp);
	//cout<<"char* constructor";
}

String::String(char ch)
{
	refcount = new RefCounting(ch);
	//cout<<"char constructor";
}

String::~String()
{
	refcount->ref_dec();
	//cout<<"destructor";
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

/*String& operator+(const String& l_val,const String& r_val)//error
{
	char* temp_ch = new char[strlen(l_val.refcount->str)+strlen(r_val.refcount->str)];
	strcpy(temp_ch,l_val.refcount->str);
	strcat(temp_ch,r_val.refcount->str);

    String* temp_str = new String(temp_ch);
	delete temp_ch;

	return *temp_str;
}*/

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

/////////////////////////////////////////////////

RefCounting::RefCounting()
{
	str = new char(0);
	ref_count = 1;
}

RefCounting::RefCounting(char* chp)
{
	str = new char[strlen(chp)+1];
	strcpy(str,chp);
	ref_count = 1;
}

RefCounting::RefCounting(char ch)
{
	str = new char[2];
	str[0] = ch;
	str[1] = '\0';
	ref_count = 1;
}

void RefCounting::ref_inc()
{
	this->ref_count++;
}

void RefCounting::ref_dec()
{
	this->ref_count--;
	if(ref_count==0)
		delete str;
}

/////////////////////////////////////////////////////////

SubString& SubString::operator=(char* chp)
{
	str_parent->AllocRef();

	char* first_piece = new char [dest];
	char* second_piece = new char [strlen(chp)];
	char* third_piece = new char [strlen(str_parent->c_str())-(shift+dest)];

	memcpy(first_piece,str_parent->refcount->str,dest);
	strcpy(second_piece, chp);
	memcpy(third_piece,&(str_parent[dest+shift+1]),strlen(str_parent->c_str())-(shift+dest));

	strcat(first_piece,second_piece);
	strcat(first_piece,third_piece);

	delete str_parent->refcount->str;
	str_parent->refcount->str = first_piece;

	return *this;
} 
	
