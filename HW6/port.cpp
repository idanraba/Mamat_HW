#include "port.h"

#define FIRST_FIELD 0
#define SECOND_FIELD 1
#define FIELD_PORT 2
#define MIN_PORT 65535
#define MAX_PORT 65535

/**
 * @brief Constructor - Initiates Port from string pattern
 */	
Port::Port(String pattern) :
	Field(pattern){

	}

/**
 * @brief Destructor 
 */
Port::~Port(){}

/**
 * @brief setting the min and max value from the rule - range, 
 * @      and check if we can parsing it
 * @param rule - A String of the current rule - range with his fields
 * @return true if we can parsing the rule - range
 */	
bool Port::set_value(String val){

	String *split_subs;
	size_t size = 0;
	val.split("-" , &split_subs, &size);

	if(size != FIELD_PORT){
		delete[] split_subs;
		return false;
	}

	// import from the split the MIN and the MAX port
	min_val = split_subs[FIRST_FIELD].trim().to_integer();
	max_val = split_subs[SECOND_FIELD].trim().to_integer();
	delete[] split_subs;

	// check if the port is in the range that allowed 
	if((min_val <= max_val) && (MIN_PORT <= min_val) && (max_val <= MAX_PORT)){
		return true;
	}
	else{
		return false;
	}

}

/**
 * @brief check if the packet - port and the rule - range are same
 * @param packet - A String that we need to compare with the rule - range
 * @return true if the packet - port matches the rule - range
 */	
bool Port::match_value(String packet) const{

	int tmp_port = packet.trim().to_integer();
	if((min_val <= tmp_port) && (tmp_port <= max_val)){
		return true;
	}
	else{
		return false;
	}
}