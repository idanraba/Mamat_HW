#ifndef PORT_H
#define PORT_H


#include "string.h"
#include "field.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

class Port : public Field {
private:
	int min_val;
	int max_val;

public:

	/**
     * @brief Constructor - Initiates Port from string pattern
     */		
	Port(String pattern);

	/**
     * @brief Destructor 
     */	
	~Port();

	/**
     * @brief setting the min and max value from the rule - range, 
     * @      and check if we can parsing it
     * @param rule - A String of the current rule - range with his fields
     * @return true if we can parsing the rule - range
     */	
	bool set_value(String val);

	/**
     * @brief check if the packet - port and the rule - range are same
 	 * @param packet - A String that we need to compare with the rule - range
 	 * @return true if the packet - port matches the rule - range
     */	
	bool match_value(String packet) const;


};

#endif

