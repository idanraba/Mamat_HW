#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "linked-list.h"
#include "grades.h"

/* Define the const*/
enum {SUCCESS = 0 , ERROR = -1 , EXIST = 1 , MIN_GRADE = 0 , MAX_GRADE = 100};



/* Define the TOP ADT*/
struct grades {
	struct list *list_students;
};


/* Define the type of one student's data*/
struct student {
	char *name_student;
	unsigned int id_student;
	struct list *courses;
};

/* Define the type of course data*/
struct course {
	char *name_course;
	int grade_course;
};



/*Define the user function of the list_init function*/



/**
 * @brief User function, clones “element” to “output”. 
 *        In this case, clone a struct of -course- with his fields.
 * @param element The source element that need to copied 'course'.
 * @param output The destinetion of the copied element.
 * @returns Returns 0 on SUCCESS. or -1 in case of an ERROR.
 */
static int course_clone(void *element, void **output){
	
	if((element == NULL) || (output == NULL)){
		return ERROR;
	}

	/*casting*/
	struct course *source = (struct course*)element;
	struct course **clone = (struct course**)output;
	*clone = malloc(sizeof(struct course));

	if(*clone == NULL){
		free(*clone);
		return ERROR;
	} 

	/*process of cloning course */

	/* GRADE */
	(*clone)->grade_course = source->grade_course;

	/* NAME */
	char *name_string= malloc(sizeof(char)*(strlen(source->name_course)+1));
	if(name_string == NULL){
		free(name_string);
		return ERROR;
	}

	strcpy(name_string,source->name_course);
	(*clone)->name_course = name_string;

	
	return SUCCESS;
}



/**
 * @brief User function,that destroy “element” .
 *        In this case, destroy a struct of -course- with his fields.
 * @param element The source element that need to destroy - 'course'.
 * @note Always succeed
 */
static void course_destroy(void *element){

	if(element == NULL){
		return;
	}

	/*casting*/
	struct course *course_destroy = (struct course*)element;

	/*allocate the memory*/
	free(course_destroy->name_course);
	free(course_destroy);
}



/**
 * @brief User function,that destroy “element” .
 *        In this case, destroy a struct of -student- with his fields.
 * @param element The source element that need to destroy - 'student'.
 * @note Always succeed
 */
static void student_destroy(void *element){

	if(element == NULL){
		return;
	}

	/*casting*/
	struct student *student_destroy = (struct student*)element;

	/*allocate the memory*/
	list_destroy(student_destroy->courses);
	free(student_destroy->name_student);
	free(student_destroy);
}



/**
 * @brief User function, clones “element” to “output”. 
 *        In this case, clone a struct of -student- with his fields.
 * @param element The source element that need to copied 'student'.
 * @param output The destinetion of the copied element.
 * @returns Returns 0 on SUCCESS. or -1 in case of an ERROR.
 */
static int student_clone(void *element, void **output){
	
	if((element == NULL) || (output == NULL)){
		return ERROR;
	}

	/*casting*/
	struct student *source = (struct student*)element;
	struct student **clone = (struct student**)output;
	(*clone) = malloc(sizeof(struct student));

	if(*clone == NULL){
		free(*clone);
		return ERROR;
	} 

	/*process of cloning student */

	/* ID */
	(*clone)->id_student = source->id_student;

	/* NAME */
	char *name_string= malloc(sizeof(char)*(strlen(source->name_student)+1));
	if(name_string == NULL){
		free(name_string);
		return ERROR;
	}

	strcpy(name_string,source->name_student);
	(*clone)->name_student = name_string;

	/*list of courses*/
	/*setting 2 local vars - one for given element's course list, and the
	sec one for our clone - will use a user function to apply (list init)*/
	struct list *source_list = source->courses;
	struct list *clone_list = list_init(course_clone, course_destroy);
	/*if the list is not empty , we define iterator to the list head*/
	if(list_size(source_list)){
		
		struct iterator *course_iterator = list_begin(source_list);	
		if(course_iterator == NULL){
			student_destroy(clone);
			return ERROR;
		}

		/*define another variable , to copy the list of the given element 
		( course type ) with the iterator each element every iteration
		to the clone list*/
		struct course **clone_current_course;
		
		while(course_iterator){
			/*we define a pointer to the current iterator , then copy the 
			object itself to the helping var. at the end we push the objest
			 to the end of the list */
			struct course *current_course = list_get(course_iterator);
			int test_clone = course_clone(current_course,
										 (void*)&clone_current_course);

			if(test_clone == SUCCESS){
				int test_push_back = list_push_back(clone_list,
												 *clone_current_course);
				if(test_push_back == SUCCESS){
					list_next(course_iterator);
				}
				else{
					student_destroy(clone);
					return ERROR;
				}
			}
		}
	}	

	(*clone)->courses = clone_list;
	return SUCCESS;
}

/*Define the user function of the grades_add_student and grades_add_grade 
  function*/



/**
 * @brief Searcing if there a student with this id in grades - adt
 * @param grades - our TOP-ADT
 * @param id - the id of the  student
 * @returns a pointer to the student with the id, OR NULL if faild
 */
static struct student *search_student_id(struct grades *grades, int id){

	struct iterator *student_iterator = list_begin(grades->list_students);
	struct student *current_student;

	/*loop that go over the list of student in grades, and search if 
	  there is a student with the same id*/
	while(student_iterator){
		
		current_student = list_get(student_iterator);
		if(current_student->id_student == id){
			return current_student;
		}
		student_iterator = list_next(student_iterator);
		
	}

	return NULL;
}



/**
 * @brief Searcing if there a course with this name in list of student
 * @param current_student the adt that we search the course in him
 * @param name - the name of the  course
 * @returns a pointer to the course if exist, OR NULL if faild
 */
static struct course *search_course_name(struct student *current_student,
										 const char *name){

	struct iterator *course_iterator = list_begin(current_student->courses);
	struct course *current_course;

	/*loop that go over the list of courses in list of student, and search if 
	  there is a course with the same name*/
	while(course_iterator){
		
		current_course = list_get(course_iterator);
		if(!strcmp(current_course->name_course,name)){
			return current_course;
		}
		course_iterator = list_next(course_iterator);
		
	}

	return NULL;
}



/**
 * @brief create a new struct of student
 * @param name - the name of the new student
 * @param id - the id of the new student
 * @returns a pointer to the new student OR NULL if faild
 */
static struct student *create_student(const char *name, int id){

	struct student *new_student = malloc(sizeof(struct student));
	if(new_student == NULL){
		return NULL;
	}

	/*field of id*/
	new_student->id_student = id;

	/*field of name*/
	new_student->name_student =  malloc(sizeof(char)*(strlen(name)+1));

	if(new_student->name_student == NULL){
		free(new_student);
		return NULL;
	}

	strcpy(new_student->name_student, name);

	/*field of courses list*/
	struct list *current_list = list_init(course_clone, course_destroy);
	new_student->courses = current_list;


	return new_student;
}



/**
 * @brief create a new struct of course
 * @param name - the name of the new course
 * @param grade - the grade of the student in this course
 * @returns a pointer to the new course OR NULL if faild
 */
static struct course *create_course(const char *name, int grade){
	
	struct course *new_course = malloc(sizeof(struct course));
	if(new_course == NULL){
		return NULL;
	}

	/*field of grade*/
	new_course->grade_course = grade;

	/*field of name*/
	new_course->name_course =  malloc(sizeof(char)*(strlen(name)+1));

	if(new_course->name_course == NULL){
		free(new_course);
		return NULL;
	}

	strcpy(new_course->name_course, name);


	return new_course;
}



/*Define the grades.h function*/



/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, or NULL in case of an error
 */
struct grades* grades_init(){
	
	struct grades *top_adt = malloc(sizeof(struct grades));
	if (top_adt == NULL){
		free(top_adt);
		return NULL;
	} 
	top_adt -> list_students = list_init(student_clone, student_destroy);
	return top_adt;
}



/**
 * @brief Destroys "grades", de-allocate all memory!
 * @param grades, The element that we need to destroy, with his fields.
 */
void grades_destroy(struct grades *grades){

	if(grades == NULL){
		return;
	}

	list_destroy(grades->list_students);
	free(grades);
}



/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @param grades - our TOP-ADT
 * @param name - the name of the new student
 * @param id - the id of the new student
 * @returns 0 on success, OR -1 in error.
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){

	/*chack if "grades" is invalid, or a student with 
      the same "id" already exists in "grades" */
	if((grades == NULL)||(search_student_id(grades, id) != SUCCESS)){
		return ERROR;
	}

	struct student *new_student = create_student(name, id);
	if(new_student == NULL){
	 	student_destroy(new_student);
	 	return ERROR;
    }

	struct list *current_list = grades->list_students;
	if(list_push_back(current_list, new_student) == SUCCESS){
		student_destroy(new_student);
		return SUCCESS;
	} 
	else {
		student_destroy(new_student);
		return ERROR;
	}

}



/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

	/* check if the params are ok*/
	if( !(grades) || !(name) || (grade <= MIN_GRADE) || (grade >= MAX_GRADE)){

		return ERROR;
	}
		
	/*search the student in grades adt and check if not exist*/
	struct student *current_student = search_student_id(grades, id);
  	if(current_student == NULL){
  		return ERROR;
  	}

  	/*check if the course is already exist*/
  	if(search_course_name(current_student, name)){
  		return ERROR;
  	}

  	struct course *new_course = create_course(name, grade);
  	if(new_course == NULL){
  		return ERROR;
  	}
	
	struct list *current_list = current_student->courses;
	if(!list_push_back(current_list, new_course)){
		course_destroy(new_course);
		return SUCCESS;
	}
	else {
		return ERROR;
	}
	
}



/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out){

	if((grades == NULL) || (out == NULL)){
		out = NULL;
		return ERROR;
	}

	/*search the student in grades adt and check if not exist*/
	struct student *current_student = search_student_id(grades, id);
  	if(current_student == NULL){
  		out = NULL;
  		return ERROR;
  	}

  	char *name = malloc((sizeof(char))*
  						(strlen(current_student->name_student)+1));
  	if(name == NULL){
  		out = NULL;
  		return ERROR;
  	}

  	strcpy(name, current_student->name_student);
  	*out = name;

  	int num_of_courses = list_size(current_student->courses);
  	int sum = 0;
  	float avg;
  	if(num_of_courses == 0){
  		return (float)sum;
  	}
  	
  	struct iterator *course_iterator = list_begin(current_student->courses);
  	if(course_iterator == NULL){
  		out = NULL;
  		free(name);
  		return ERROR;
  	}

  	/*loop that go over the courses list*/
  	struct course *current_course;
  	while(course_iterator){
  		current_course = list_get(course_iterator);
  		sum += current_course->grade_course;
  		course_iterator = list_next(course_iterator);
  	}
  	
  	avg = (float)sum / num_of_courses;
  	return avg;

}



/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){

	if(grades == NULL){
		return ERROR;
	}

	/*search the student in grades adt and check if not exist*/
	struct student *current_student = search_student_id(grades, id);
  	if(current_student == NULL){
  		return ERROR;
  	}

  	struct iterator *course_iterator = list_begin(current_student->courses);
  	struct course *current_course;
  	char *current_name_course;
  	int current_grade;

  	printf("%s %d:", current_student->name_student, id);
  	/*loop that go over the courses list*/
  	while(course_iterator){
  		current_course = list_get(course_iterator);
  		current_name_course = current_course->name_course;
  		current_grade = current_course->grade_course;
  		printf(" %s %d",current_name_course, current_grade);

  		course_iterator = list_next(course_iterator);
  		if(course_iterator){
  			printf(",");
  		}
  	}

  	printf("\n");
  	return SUCCESS;

}



/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){

	if(grades == NULL){
		return ERROR;
	}

	struct iterator *student_iterator = list_begin(grades->list_students);
	struct student *current_student;

	/*loop that go over the students list*/
	while(student_iterator){
		current_student = list_get(student_iterator);
		grades_print_student(grades, current_student->id_student);
		student_iterator = list_next(student_iterator);
	}

	return SUCCESS;

}


