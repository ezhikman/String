#include"SubString.h"

SubString& SubString::operator=(char* chp)
{
	str_parent->AllocRef();

	if (this==NULL)
		return;
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
	