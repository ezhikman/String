#include"String.h"
//#include<cstdlib>

using namespace std;

String::String()
{
	refcount = new RefCounting();
	cout<<"default constructor"<<endl;
}

String::String(String& temp_str)
{
	refcount = temp_str.refcount;
	refcount->ref_inc();
	cout<<"copy constructor"<<endl;
}

String::String(char* chp)
{
	refcount = new RefCounting(chp);
	cout<<"char* constructor"<<endl;
}

String::String(char ch)
{
	refcount = new RefCounting(ch);
	cout<<"char constructor"<<endl;
}

String::~String()
{
	this->refcount->ref_dec();
	if(this->refcount->ref_count==0)
		delete refcount;
	cout<<"destructor - success"<<endl;
}

void String::AllocRef()
{
	RefCounting* tmp = refcount;

	refcount = new RefCounting(refcount->str);

	tmp->ref_dec();
}

int String::Size()
{
	return strlen(this->refcount->str);
}

SubString& String::substr(int dest, int shift)
{
	if((shift+dest)<strlen(refcount->str))
	{
		SubString* substring = new SubString(dest,shift,this);
		return *substring;
	}
}

String& operator+(const String& l_val,const String& r_val)//error
{
	char* new_char = new char[strlen(l_val.refcount->str)+strlen(r_val.refcount->str)+1];
	new_char[0]='\0';
	strcat(new_char,l_val.refcount->str);
	strcat(new_char,r_val.refcount->str);
	String* new_String = new String(new_char);
	delete new_char;
	return *new_String;
}

String& String::operator+=(const String& r_val)
{
	if(this->refcount->ref_count>1)
		this->AllocRef();
	*this=*this+r_val;
	return *this;
}

String& String::operator=(const String& r_val)
{
	if(*this==r_val)
		return *this;

	if(this->refcount->ref_count>1)
		this->AllocRef();

	delete this->refcount;

	this->refcount = r_val.refcount;

	if(this->refcount->ref_count>1)
		this->refcount->ref_inc();

	return *this;
}

String& String::operator=(const char* chp)
{
	if(strcmp(this->refcount->str,chp)==0)
		return *this;
	if(this->refcount->ref_count>1)
		this->AllocRef();

	delete[] this->refcount->str;
	this->refcount->str = new  char[strlen(chp)+1];
	this->refcount->str[0]='\0';
	strncpy(this->refcount->str, chp, strlen(chp));
	this->refcount->str[strlen(chp)]='\0';
	
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
	os<<".";
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
	str[0]='\0';
	strncpy(str,chp,strlen(chp)+1);
	ref_count = 1;
}

RefCounting::RefCounting(char ch)
{
	str = new char[2];
	str[0] = ch;
	str[1] = '\0';
	ref_count = 1;
}

RefCounting::RefCounting(RefCounting& ref)
{
	str = new char [strlen(ref.str)];
	strncpy(str,ref.str,strlen(ref.str));
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
		delete[] str;
	return;
}

RefCounting::~RefCounting()
{
	this->ref_dec();
}

/////////////////////////////////////////////////////////



SubString& SubString::operator=(const String& r_val)
{
	*this=r_val.refcount->str;
	return *this;
}

SubString& SubString::operator=(const char* chp)
{
	if(str_parent->refcount->ref_count>1)
		str_parent->AllocRef();

	char* first_piece = new char [dest+1];                                     
	first_piece[0]='\0';
	char* second_piece = new char [strlen(chp)+1];                              
	second_piece[0]='\0';
	char* third_piece = new char [strlen(str_parent->c_str())-(shift+dest)+1]; 
	third_piece[0]='\0';
	char* pie = new char [strlen(str_parent->c_str())-shift+strlen(chp)+1];
	pie[0]='\0';

	strncpy(first_piece,str_parent->refcount->str,dest);
	first_piece[dest]='\0';
	strncpy(second_piece, chp, strlen(chp)+1);
	memcpy(third_piece,&(str_parent->c_str()[dest+shift]),strlen(str_parent->c_str())-(shift+dest)+1);

	strcat(pie,first_piece);
	strcat(pie,second_piece);
	strcat(pie,third_piece);

	delete[] str_parent->refcount->str;
	
	this->str_parent->refcount->str = pie;

	delete[] third_piece;
	delete[] second_piece;	
	delete[] first_piece;

	return *this;
} 
	
