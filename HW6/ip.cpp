#include "ip.h"

#define FIRST_FIELD 0
#define SECOND_FIELD 1
#define THIRD_FIELD 2
#define FOURTH_FIELD 3
#define SHIFT_BYTE 8
#define SHIFT_TWO_BYTE 16
#define SHIFT_THREE_BYTE 24
#define FIELD_MASK 2
#define TOTAL_BITS 32


/**
 * @brief Constructor - Initiates Ip from string pattern
 */	
Ip::Ip(String pattern) :
	Field(pattern){

	}

/**
 * @brief Destructor 
 */
Ip::~Ip(){}	


/**
 * @brief Convert the ip with 4 fields to one unsigned int ip
 * @param ip_src The ip with the 4 fields
 * @return The unsigned int ip with one field
 */	
unsigned int Ip::legal_ip(String ip_src) const{ 

	unsigned int new_ip = 0;

	String *split_subs;
	size_t size = 0;
	ip_src.split("." , &split_subs, &size);  //split the src ip to one num

	//setting the fields
	int first_field = split_subs[FIRST_FIELD].trim().to_integer();
	int second_field = split_subs[SECOND_FIELD].trim().to_integer();
	int third_field = split_subs[THIRD_FIELD].trim().to_integer();
	int fourth_field = split_subs[FOURTH_FIELD].trim().to_integer();

	// merg the 4 field to one unsigned int
	new_ip = (first_field << SHIFT_THREE_BYTE) | 
			(second_field << SHIFT_TWO_BYTE) |
			(third_field << SHIFT_BYTE) | (fourth_field);

	delete[] split_subs;
	return new_ip;		

}

/**
 * @brief setting the ip and mask field from the rule, 
 * @      and check if we can parsing it
 * @param rule - A String of the current rule with his fields
 * @return true if we can parsing the rule
 */	
bool Ip::set_value(String val){
	
	String *split_subs;
	size_t size = 0;
	val.split("/" , &split_subs, &size);

	if(size != FIELD_MASK){
		delete[] split_subs;
		return false;
	}

	// import from the split the mask and the tmp ip
	unsigned int tmp_ip = legal_ip(split_subs[FIRST_FIELD].trim());
	mask_length = split_subs[SECOND_FIELD].trim().to_integer();
	delete[] split_subs;

	//make ip rule with mask
	if(mask_length == 0){
		ip_rule = 0;
	}
	else{
		ip_rule = tmp_ip >> ( TOTAL_BITS - mask_length);
	}
	return true;
}

/**
 * @brief check if the packet - ip and the rule are same
 * @param packet - A String that we need to compare with the rule
 * @return true if the packet - ip matches the rule
 */	
bool Ip::match_value(String packet) const{

	unsigned int tmp_ip = legal_ip(packet.trim());
	unsigned int matched;
	if(mask_length == 0){
		matched = 0;
	}
	else{
		matched = tmp_ip >> ( TOTAL_BITS - mask_length);
	}


	if(matched == ip_rule){
		return true;
	}
	else{
		return false;
	}
	

}