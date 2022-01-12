#ifndef IP_H
#define IP_H


#include "string.h"
#include "field.h"
#include <iostream>
#include <cstring>

class Ip : public Field {
private:
	unsigned int ip_rule;
	int mask_length;

	/**
     * @brief Convert the ip with 4 fields to one unsigned int
     * @param ip_src The ip with the 4 fields
     * @return The unsigned int ip with one field
     */	
	unsigned int legal_ip(String ip_src) const;

public:

	/**
     * @brief Constructor - Initiates Ip from string pattern
     */		
	Ip(String pattern);

	/**
     * @brief Destructor 
     */	

	~Ip();

	/**
     * @brief setting the ip and mask field from the rule, 
     * @      and check if we can parsing it
     * @param rule - A String of the current rule with his fields
     * @return true if we can parsing the rule
     */	
	bool set_value(String val);

	/**
     * @brief check if the packet - ip and the rule are same
     * @param packet - A String that we need to compare with the rule
     * @return true if the packet - ip matches the rule
     */	
	bool match_value(String packet) const;


};

#endif