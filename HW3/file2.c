//file2.c
#include <stdio.h>
#include <stdlib.h>
#include "file2.h"
#include "file4.h"
int file2_function(){
	printf("This is file2_function()\n");
	file4_function();
	return 0;
}
