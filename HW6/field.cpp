#include "field.h"
#include <iostream>
#include <cstring>

#define DOUBLE 2


Field::Field(String pattern) : 
	   pattern(pattern){}


Field::~Field(){}


bool Field::match(String packet){
	
	// vars for spliting and check if the return sub is empty 
	String *split_subs;
	size_t size = 0;
	// turnning the long packet into seperated string 
	packet.split(",=" , &split_subs, &size);
	if(!size){
		delete[] split_subs;
		return false;
	}

	bool matched = false;
	String temp_str;
	//check if the string - this (pattern) - matches one of the rules
	for(int i = 0; i < (int)size; i+= DOUBLE){
		temp_str = split_subs[i].trim();
		if(pattern.equals(temp_str)){
			matched = match_value(split_subs[i+1].trim());
			delete[] split_subs;
			return matched;
		}
	}
	delete[] split_subs;
	return matched;

}

	








