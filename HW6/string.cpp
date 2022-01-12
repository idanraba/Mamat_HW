#include "string.h"
#include <stddef.h>
#include <iostream>
#include <cstring>


	/**
     * @brief Initiates an empty string
     */
    String::String(){
    	
    	data = new char[1];
    	data[0] = '\0';
    	length = 0;

    }

	/**
     * @brief Initiates string from other string
     */
    String::String(const String &str){
    	
    	if(!str.data){                  //check if str is empty
    		data = new char[1];
    		data[0] = '\0';
    		length = 0;
    	}
    	else{
    		length = str.length;
    		data = new char[length +1];
    		strcpy(data, str.data);
    	}
    	
    	
    }
	/**
     * @brief Initiates a string from char array
     */
    String::String(const char *str){

    	if(!str){                 //check if str is empty
    		length = 0;
    		data = new char[1];
    		data[0] = '\0';
    	}
    	else{
    		length = strlen(str);
    		data = new char[length +1];
    		strcpy(data, str);
    	}
    	

    }   

	/**
     * @brief Destructor a String
     */
    String::~String(){

    	delete[] data;

    }

	/**
     * @brief Changes this from String
     */
    String& String:: operator=(const String &rhs){

    	
    	if(!rhs.data){           //check if rhs is empty
    		delete[] data;
	       	length = 0;
	       	data = new char[1];
	       	data[0] = '\0';
	       	return *this;
    	}
       

       if(this == &rhs){
       	return *this;
       }
       else{
       	delete[] data;
       	length = rhs.length;
       	data = new char[length +1];
       	strcpy(data, rhs.data); 
       	return *this;
       } 

	}

	/**
     * @brief Changes this from char array
     */
    String& String:: operator=(const char *str){

    	if(!str){                  //check if str is empty
    		delete[] data;
	       	length = 0;
	       	data = new char[1];
	       	data[0] = '\0';
	       	return *this;
    	}


    	length = strlen(str);
	    if((!strcmp(str,data)) && (length == strlen(str))){
	     	return *this;
	       }
	    else{
	       	delete[] data;
	       	length = strlen(str);
	       	data = new char[length +1];
	       	strcpy(data, str); 
	       	return *this;
	       } 

	}

	/**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool String::equals(const String &rhs) const{

    	if(!rhs.data){                //check if rhs is empty
    		bool equal = (length ? false : true);
    		return equal;
    	}

    	if((!strcmp(rhs.data,data)) && (length == rhs.length)){
	     	return true;
	       } 
	    else{
	    	return false;
	       } 

    }

    	

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
    	
    	if(!rhs){                   //check if rhs is empty
    		bool equal = (length ? false : true);
    		return equal;
    	}

    	if((!strcmp(rhs,data)) && (length == strlen(rhs))){
	     	return true;
	       } 
	    else{
	    	return false;
	       }  

    }


    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void String::split(const char *delimiters, String **output, size_t *size) 
    					const{

    	int tmp_num_string = 0, index_clone = 0, index_string = 0;
    	int length_deli = strlen(delimiters);
    	char clone_string[length + 1];

    	if((!delimiters) || (!data)|| (!size)){
    		return;
    	}

    	strcpy(clone_string, data);

    	for(int i=0; i < (int)length; i++){
    		for(int j=0; j < length_deli; j++){
    			if(data[i] == delimiters[j]){
    				clone_string[i] = '\0';
    				tmp_num_string++;
    			}
    		}
    	}

    	*size = tmp_num_string + 1;

    	if(!output){
    		return;
    	}

    	*output = new String[*size];

    	for(int i=0; i < (int)length; i++){
    		for(int j=0; j < length_deli; j++){
    			if(data[i] == delimiters[j]){
    				(*output)[index_string++] = 
    				String(&clone_string[index_clone]);
    				index_clone = i + 1;
    			}
    		}
    	}

    	(*output)[index_string] = String(&clone_string[index_clone]);

    	return;				

    }

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const{

    	return atoi(data);

    }


    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const{

    	int i = 0, space_lead = 0, space_trail = 0;
    	int length_int = (int)length;

    	while(data[i] == ' '){
    		space_lead++;
    		i++;
    	}

    	if(data[i] == '\0'){
    		return String();
    	}

    	i = length_int - 1;
    	while(data[i] == ' '){
    		space_trail++;
    		i--;
    	}

    	int new_length = length_int - space_lead - space_trail;
    	char new_string[new_length + 1];

    	for(int i = 0; i < new_length; i++){
    		new_string[i] = data[space_lead + i];
    	}
    	new_string[new_length] = '\0';

    	return String(new_string);

    }

    



