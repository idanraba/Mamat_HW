#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN 1
#define MAX 100
#define PASS_GRADE 55
#define PRECENT 100
#define NEW_LINE 10

/*
* @brief: open the file , scan the grades, calculate the wanted values,
		 insert them in the output file.
*@param: argc - num of inserted arguments
*@param: argv - the pointers to the files in the input
*@return: will return 1 for error otherwise 0
*/
int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    FILE *grades = fopen(argv[1],"r");
    
    if (grades == NULL) {
    	fprintf(stderr, "Error opening the file of grades\n");
    	return 1;
    }
    
    

	int num_student = 0;
	int sum = 0;
	int min_student = MAX;
	int max_student = MIN;
	int total_pass = 0;
	int hist[MAX] = {0};
	int temp_grade = 0;

/*take input from the grades file, and calc unit*/
	while(fscanf(grades,"%d\n", &temp_grade) != EOF){
		
		min_student = (temp_grade < min_student) ? temp_grade : min_student;
		max_student = (temp_grade > max_student) ? temp_grade : max_student;
		total_pass  += (PASS_GRADE <= temp_grade ) ? 1 : 0;
		num_student++;
		hist[temp_grade - 1]++;
		sum += temp_grade;
	}

	if (fclose(grades) != 0){
		fprintf(stderr, "Error closing the file of grades\n");
		return 1;
	}	

	int half_student = (num_student +1) / 2;
	int temp_median = 0;
	int index = 0;
	/*find the median*/
	while(temp_median < half_student){
		temp_median += hist[index];
		index++;
	}

	int median = index;

	double avg = (double)sum / (double)num_student;
	double pass_precent =(double)total_pass * PRECENT / (double)num_student;

	FILE *culc = fopen(argv[2],"w");
    
    if (culc == NULL){
    	fprintf(stderr, "Error opening the file of calc\n");
    	return 1;
    }

    fprintf(culc, "num of students = %d\n", num_student );
    fprintf(culc, "avg = %.3f\n", avg);
    fprintf(culc, "the median is - %d\n", median);
    fprintf(culc, "max grade = %d, min grade = %d\n",
    	    max_student, min_student);
    fprintf(culc, "pass rate = %.2f%%\n", pass_precent);

    for (int i = 0; i < MAX; i++){
    	fprintf(culc, "%d", hist[i]);

    	if(((i+1) % NEW_LINE) == 0){
    		fprintf(culc, "\n");
    	}
    	else{
    		fprintf(culc, " ");
    	}
    }

    if (fclose(culc) != 0){
		fprintf(stderr, "Error closing the file of calc\n");
		return 1;
	} 


    return 0;
}
