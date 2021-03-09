#include "grade_information.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
struct information_s {
	long int course_id;
	int pointsx2;
	int grade;
	int semester;
};

//create a set of array size  that include course id, grade, points
//the set will be in order of courses id and semester number
information creatArray(long int course_id, int points,
	int grade, int semester) {
	information new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}
	new->course_id = course_id;
	new->grade = grade;
	new->pointsx2 = points;
	new->semester = semester;
	return new;
}

information copyArray(information array) {
	information new = creatArray(array->course_id, array->pointsx2,
		array->grade, array->semester);
	return new;
}

void freeArray(information array) {
	free(array);
	return;
}

int comperArray(information array1, information array2) {
	if (array1->course_id == array2->course_id) {
		if (array1->semester > array2->semester) {
			return 1;
		}
		else {
			if (array1->semester == array2->semester) {
				return 0;
			}
			else {
				return -1;
			}
		}
	}
	else {
		if (array1->course_id > array2->course_id) {
			return 1;
		}
		else {
			return -1;
		}
	}
}

long int getCourse(information information) {
	return information->course_id;
}

int getSemester(information information) {
	return information->semester;
}

int getGadeInformation(information information) {
	return information->grade;
}

int getPoints(information information) {
	return information->pointsx2;
}

int comperArrayByGrade(information array1, information array2) {
	if (array1->grade == array2->grade) {
		if (array1->semester == array2->semester) {
			if (array1->course_id == array2->course_id) {
				return 0;
			}
			else {
				if (array1->course_id > array2->course_id) {
					return 1;
				}
				else {
					return -1;
				}
			}
		}
		else {
			if (array1->semester > array2->semester) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	else {
		if (array1->grade > array2->grade) {
			return -1;
		}
		else {
			return 1;
		}
	}
}

int comperArrayByGradeWorst(information array1, information array2) {
	if (array1->grade == array2->grade) {
		if (array1->semester == array2->semester) {
			if (array1->course_id == array2->course_id) {
				return 0;
			}
			else {
				if (array1->course_id > array2->course_id) {
					return 1;
				}
				else {
					return -1;
				}
			}
		}
		else {
			if (array1->semester > array2->semester) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	else {
		if (array1->grade > array2->grade) {
			return 1;
		}
		else {
			return -1;
		}
	}
}