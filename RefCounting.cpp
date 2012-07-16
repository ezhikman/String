#include"RefCounting.h"

RefCounting::RefCounting()
{
	str = new char(0);
	ref_count = 1;
}

RefCounting::RefCounting(char* chp)
{
	str = new char[strlen(chp)+1];
	memcpy(str,chp,strlen(chp));
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