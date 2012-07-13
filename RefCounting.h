#ifndef REF_COUNTING_H
#define REF_COUNTING_H

#pragma once

#include<vector>
#include"String.h"

class RefCounting
{
	char* str;
	int ref_count;
public:

	RefCounting();
	RefCounting(char);
	RefCounting(char*);

	void ref_inc();
	void ref_dec();

	~RefCounting();

	friend class String;
};

#endif