#include <iostream>
#include <cstring>
#include "string.h"
#include "port.h"
#include "ip.h"
#include "input.h"

#define SUCCESS 0
#define ERROR -1
#define DOUBLE 2
#define FIRST_FIELD 0
#define SECOND_FIELD 1

using namespace std; 

/**
 * @brief The main function
 * @param argc - number of arguments
 * @param argv - array of the arguments - the rule is in argv[1]
 * @return 0 in SUCCESS and -1 on ERROR
 */	

int main(int argc, char **argv){

	//check if the input is valid
	if(check_args(argc, argv)){
		return ERROR;
	}

	//go over the rule and canceling the tab and the coma
	int field_length = (strlen(argv[SECOND_FIELD]) + 1);
	char *temp_string = new char[field_length];
	strcpy(temp_string, argv[SECOND_FIELD]);
	for(int i=0; i < field_length; i++){
		if((temp_string[i] == ',') || (temp_string[i] == '\t')){
			temp_string[i] = ' ';
		}
	}

	String curr_rule(temp_string); 
	delete[] temp_string;

	//split the current rule
	String *split_subs;
	size_t size = 0;
	curr_rule.trim().split("=" , &split_subs, &size);
	if(size != DOUBLE){
		delete[] split_subs;
		return ERROR;
	}

	//setting the field type from the first field and the rule from the second
	String field_type = split_subs[FIRST_FIELD].trim();
	String rule_actual = split_subs[SECOND_FIELD].trim();
	delete[] split_subs;

	//check which field type the tule is

	if(field_type.equals("src-port")){
		Port src_port(field_type);
		src_port.set_value(rule_actual);
		parse_input(src_port);
	}

	else if(field_type.equals("dst-port")){
		Port dst_port(field_type);
		dst_port.set_value(rule_actual);
		parse_input(dst_port);
	}

	else if(field_type.equals("src-ip")){
		Ip src_ip(field_type);
		src_ip.set_value(rule_actual);
		parse_input(src_ip);
	}

	else{
		Ip dst_ip(field_type);
		dst_ip.set_value(rule_actual);
		parse_input(dst_ip);
	}

	return 0;

}
