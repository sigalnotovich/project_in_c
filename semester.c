#include "semester.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h" 
#include <assert.h>
#include "mtm_ex3.h"             
#include "grade_information.h" 

struct semester_s {
	int id;
	List grades;
};

Semester copySemester(Semester semester) {
	assert(semester != NULL);
	Semester new_semester = createSemester(semester->id);
	listDestroy(new_semester->grades);
	new_semester->grades = listCopy(semester->grades);
	return new_semester;
}

int compareSemester(Semester semester_one, Semester semester_two) {
	assert(semester_one != NULL);
	assert(semester_two != NULL);
	if (semester_one->id > semester_two->id) {
		return 1;
	}
	else {
		if (semester_one->id == semester_two->id) {
			return 0;
		}
		else {
			return -1;
		}
	}
}

ListElement copyGradeElement(ListElement element) {
	Grade grade = (Grade)element;
	Grade new_grade = copyGrade(grade);
	if (new_grade == NULL) {
		return NULL;
	}
	return new_grade;
}

void freeGradeElement(ListElement element) {
	destroyGrade((Grade)element);
	return;
}

Semester createSemester(int id) {
	Semester new_semester = malloc(sizeof(*new_semester));
	if (new_semester == NULL) {
		return NULL;
	}
	new_semester->id = id;
	new_semester->grades = listCreate(copyGradeElement, freeGradeElement);
	return new_semester;
}

void destroySemester(Semester semester) {
	if (semester == NULL) {
		return;
	}
	listDestroy(semester->grades);
	free(semester);
	return;
}

int getSemesterId(Semester semester) {
	return semester->id;
}

//return 0 if fail, return 1 is success
int addGrade(Semester semester, long int course_id, char* points, int grade) {
	assert(points != NULL);
	assert(semester != NULL);
	Grade new_grade = createGrade(grade, course_id, points);
	if (new_grade == NULL) {
		return 0;
	}
	ListResult result = listInsertFirst(semester->grades,
		(ListElement)new_grade);
	destroyGrade(new_grade);
	if (result == LIST_SUCCESS) {
		return 1;
	}
	else {
		return 0;
	}
}
void printSemester(Semester semester, FILE* output_channel) {
	List tmp = listCreate(copyGradeElement, freeGradeElement);
	LIST_FOREACH(Grade, iterator, semester->grades) {
		listInsertFirst(tmp, (ListElement)iterator);
	}
	LIST_FOREACH(Grade, iterator, tmp) {
		mtmPrintGradeInfo(output_channel, getCourseId(iterator),
			multiplyPoints(iterator), getGrade(iterator));
	}
	mtmPrintSemesterInfo(output_channel, semester->id, totalPointsX2(semester),
		failedPointsX2(semester), effectivePointsX2(semester),
		effectiveGradeSumX2(semester));
	listDestroy(tmp);
	return;
}

int removeGrade(Semester semester, long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			listRemoveCurrent(semester->grades);
			return 1;
		}
	}
	return 0;
}

//return 1 if we found relevent course in this semester and change grade
int findCourseLastGradeAndChange(Semester semester, long int course_id,
	int new_grade) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			changeGradeNumber(gradeIterator, new_grade);
			return 1;
		}
	}
	return 0;
}

int totalPointsX2(Semester semester) {
	int point = 0;
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		point += multiplyPoints(gradeIterator);
	}
	return point;
}

int failedPointsX2(Semester semester) {
	int point = 0;
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getGrade(gradeIterator) < 55) {
			point += multiplyPoints(gradeIterator);
		}
	}
	return point;
}

int effectivePointsX2(Semester semester) {
	int  sum_of_points = 0;
	int tmp = 0;
	int* index = &tmp;
	long int *array = arrayOfCoursesInSemester(semester, index);
	if (array == NULL) {
		return -1;
	}
	for (int i = 0; i < *index; i++) {
		sum_of_points += findLastGradeOfCourse(semester, array[i]);
	}
	free(array);
	return sum_of_points;
}

int sizeOfGradeInSemester(Semester semester) {
	int sum = 0;
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		sum++;
	}
	return sum;
}

//this functiotion make array of courses in semester
long int* arrayOfCoursesInSemester(Semester semester, int* index) {
	int sum = sizeOfGradeInSemester(semester);
	int tmp = 0;
	long int grade_id = 0;
	long int *course_array = malloc(sizeof(*course_array)*sum);
	if (course_array == NULL) {
		return NULL;
	}
	for (int i = 0; i < sum; i++) {
		course_array[i] = 0;
	}
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		for (int i = 0; i < sum; i++) {
			grade_id = getCourseId(gradeIterator);
			if (grade_id == course_array[i]) {
				tmp = 1;//the course is alredy in the array
				break;
			}
		}
		if (tmp == 0) { //the course is not in array
			course_array[*index] = getCourseId(gradeIterator);
			(*index)++;
		}
		tmp = 0;
	}
	return course_array;
}

//return point of course that is valid
int findLastGradeOfCourse(Semester semester, long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			if (getGrade(gradeIterator) >= 55) {
				return multiplyPoints(gradeIterator);
			}
		}
	}
	return -1;
}

int effectiveGradeSumX2(Semester semester) {
	int   sum_points = 0;
	int tmp = 0;
	int* index = &tmp;
	long int *array = arrayOfCoursesInSemester(semester, index);
	if (array == NULL) {
		return -1;
	}
	for (int i = 0; i < *index; i++) {
		sum_points += findLastGradeCourseAndMultiplyWithGrade(semester,
			array[i]);
	}
	free(array);
	return sum_points;
}

//return point multipaly grade of course that is valid
int findLastGradeCourseAndMultiplyWithGrade(Semester semester,
	long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			if (getGrade(gradeIterator) >= 55) {
				return (multiplyPoints(gradeIterator)*getGrade(gradeIterator));
			}
		}
	}
	return 0;
}

int findLastCountGradeCourseMultiplyGrade(Semester semester,
	long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			if (getGrade(gradeIterator) >= 55) {
				return (multiplyPoints(gradeIterator)*getGrade(gradeIterator));
			}
			else {
				return -1;
			}
		}
	}
	return -1;
}

int effectivePointsOfSemesterArrayOfCourses(Semester semester,
	long int *new_array, int* index_in_array) {
	int  sum_of_points = 0;
	int tmp = 0, find_grade = 0;
	int* index = &tmp;
	long int *array = arrayOfCoursesInSemester(semester, index);
	if (array == NULL) {
		return -1;
	}
	for (int i = 0; i < *index; i++) {//going over array
		if (array[i] >= 390000) {//sport course so we allways count it
			find_grade = findLastGradeOfCourse(semester, array[i]);
			if (find_grade != -1) {
				sum_of_points += find_grade;
			}
			continue;
		}
		if ((*index_in_array) == 0) {
			find_grade = findLastGradeOfCourse(semester, array[i]);
			if (find_grade != -1) {
				sum_of_points += find_grade;
				//we found a course with pass grade
				//we add course id to new array
				new_array[*index_in_array] = array[i];
				(*index_in_array)++;
				continue;
			}
		}
		for (int j = 0; j < (*index_in_array); j++) {//going over new_array
			if (array[i] == new_array[j]) {
				break;
			}
			if (array[i] != new_array[j]) {
				if (j == (*index_in_array) - 1) {
					//the current course is not in new_array
					find_grade = findLastGradeOfCourse(semester, array[i]);

					if (findLastGradeOfCourse(semester, array[i]) != -1) {
						sum_of_points += find_grade;
						//we found a course with pass grade, we add course 
						//id to new array
						new_array[*index_in_array] = array[i];
						(*index_in_array)++;
					}
				}
			}
		}
	}
	free(array);
	return sum_of_points;
}

int effectiveGradesSemesterArrayOfCourses(Semester semester,
	long int *new_array, int* index_in_array) {//new
	int  sum_of_points = 0, tmp = 0;
	int* index = &tmp;
	long int *array = arrayOfCoursesInSemester(semester, index);
	if (array == NULL) {
		return -1;
	}
	for (int i = 0; i < *index; i++) {//going over array
		if (array[i] >= 390000) {//sport course so we allways count it
			sum_of_points += findLastGradeCourseAndMultiplyWithGrade(semester,
				array[i]);
			continue;
		}
		if ((*index_in_array) == 0) {
			sum_of_points += addGradeInsertInArray(i, semester, array,
				index_in_array, new_array);
		}
		for (int j = 0; j < (*index_in_array); j++) {//going over new_array
			if (array[i] == new_array[j]) {
				break;
			}
			if (array[i] != new_array[j]) {
				if (j == (*index_in_array) - 1) {
					//the current course is not in new_array
					sum_of_points += addGradeInsertInArray(i, semester, array,
						index_in_array, new_array);
				}
			}
		}
	}
	free(array);
	return sum_of_points;
}

int addGradeInsertInArray(int i, Semester semester, long int *array,
	int* index_in_array, long int *new_array) {
	if (findLastGradeCourseAndMultiplyWithGrade(semester, array[i]) != 0) {
		//we found a course with pass grade, we add course id to new array
		new_array[*index_in_array] = array[i];
		(*index_in_array)++;
	}
	return findLastGradeCourseAndMultiplyWithGrade(semester, array[i]);
}

int GradesOfSemesterClean(Semester semester, long int *new_array,
	int* index_in_array, FILE* output_channel, int *sum, Set information_set) {
	int  sum_points = 0, tmp = 0;
	int* index = &tmp;
	int jacob = 0; //---
	long int *array = arrayOfCoursesInSemester(semester, index);
	if (array == NULL) {
		return -1;
	}
	int sigal = setGetSize(information_set);//--
	for (int i = 0; i < *index; i++) {//going over array
		int hadar = setGetSize(information_set);//--
		if (array[i] >= 390000) {//sport course so we allways count it
			if (findLastCountGradeCourseMultiplyGrade(semester,
				array[i]) != -1) {
				sum_points += findLastCountGradeCourseMultiplyGrade(semester,
					array[i]);
			}
			(*sum) += findLastGradeOfCourseClean(semester, array[i]);
			if (findLastCountGradeCourseMultiplyGrade(semester,
				array[i]) != -1) {
				information new = creatArray(array[i],
					findPointsByCourseId(semester, array[i]),
					findGradeById(semester, array[i]), semester->id);
				setAdd(information_set, new);
				jacob++; //---
				if (sigal == 45) {
					printf("heloo");
				}
				freeArray(new);
			}
			continue;
		}
		if ((*index_in_array) == 0) {
			if (addGradeInsertInArray(i, semester, array,
				index_in_array, new_array) != -1) {
				sum_points += addGradeInsertInArray(i, semester,
					array, index_in_array, new_array);
			}
			(*sum) += findLastGradeOfCourseClean(semester, array[i]);
			if (findLastCountGradeCourseMultiplyGrade(semester,
				array[i]) != -1) {
				information new = creatArray(array[i],
					findPointsByCourseId(semester, array[i]),
					findGradeById(semester, array[i]), semester->id);
				setAdd(information_set, new);
				jacob++; //---
				if (sigal == 45) {
					printf("heloo");
				}
				freeArray(new);
			}
		}
		for (int j = 0; j < (*index_in_array); j++) {//going over new_array
			if (array[i] == new_array[j]) {
				break;
			}
			if (array[i] != new_array[j]) {
				if (j == (*index_in_array) - 1) {
					//the current course is not in new_array
					if (addGradeInsertInArray(i, semester,
						array, index_in_array, new_array) != -1) {
						sum_points += addGradeInsertInArray(i,
							semester, array, index_in_array, new_array);
					}
					(*sum) += findLastGradeOfCourseClean(semester, array[i]);
					if (findLastCountGradeCourseMultiplyGrade(semester,
						array[i]) != -1) {
						information new = creatArray(array[i],
							findPointsByCourseId(semester, array[i]),
							findGradeById(semester, array[i]), semester->id);
						setAdd(information_set, new);
						jacob++; //---
						if (sigal == 45) {
							printf("heloo");
						}
						freeArray(new);
					}
				}
			}
		}
	}
	free(array);
	return sum_points;
}

int findPointsByCourseId(Semester semester, long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			if (getGrade(gradeIterator) >= 55) {
				return (multiplyPoints(gradeIterator));
			}
		}
	}
	return 0;
}

int findGradeById(Semester semester, long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			if (getGrade(gradeIterator) >= 55) {
				return (getGrade(gradeIterator));
			}
		}
	}
	return 0;
}

//return points of effective course
int findLastGradeOfCourseClean(Semester semester, long int course_id) {
	LIST_FOREACH(Grade, gradeIterator, semester->grades) {
		if (getCourseId(gradeIterator) == course_id) {
			if (getGrade(gradeIterator) >= 55) {
				return multiplyPoints(gradeIterator);
			}
			else {
				return 0;
			}

		}
	}
	return 0;
}

int findBestGradeCourseInSemester(Semester semester, long int course_id) {
	int curent_grade = 0;
	LIST_FOREACH(Grade, iterator, semester->grades) {
		if (getGrade(iterator) > curent_grade) {
			if (getCourseId(iterator) == course_id) {
				curent_grade = getGrade(iterator);
			}
		}
	}
	return curent_grade;
}

// return 1 if ew found grade in course, 0 if not
int searchForGradeInCourseGrade(Semester semester, long int course_id) {
	LIST_FOREACH(Grade, iterator, semester->grades) {
		if (getCourseId(iterator) == course_id) {
			return 1;
		}

	}
	return 0;
}