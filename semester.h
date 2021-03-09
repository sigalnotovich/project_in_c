#ifndef SEMESTER
#define SEMESTER
#include "grade.h"
#include "set.h"
#include <stdio.h>

typedef struct semester_s *Semester;

Semester createSemester(int id);

void destroySemester(Semester semester);

Semester copySemester(Semester semester);

int compareSemester(Semester semester_one, Semester semester_two);

int getSemesterId(Semester semester);

int addGrade(Semester semester, long int course_id, char* points, int grade);

void printSemester(Semester semester, FILE* output_channel);

int removeGrade(Semester semester, long int course_id);

int findCourseLastGradeAndChange(Semester semester, long int course_id,
	int new_grade);

int totalPointsX2(Semester semester);

int failedPointsX2(Semester semester);

int sizeOfGradeInSemester(Semester semester);

long int* arrayOfCoursesInSemester(Semester semester, int* index);

int effectivePointsX2(Semester semester);

int findLastGradeOfCourse(Semester semester, long int course_id);

int effectiveGradeSumX2(Semester semeser);

int findLastGradeCourseAndMultiplyWithGrade(Semester semester,
	long int course_id);

int effectivePointsOfSemesterArrayOfCourses(Semester semester,
	long int *new_array, int* index_in_array);

int effectiveGradesSemesterArrayOfCourses(Semester semester,
	long int *new_array, int* index_in_array);

int addGradeInsertInArray(int i, Semester semester, long int *array,
	int* index_in_array, long int *new_array);

int GradesOfSemesterClean(Semester semester, long int *new_array,
	int* index_in_array, FILE* output_channel, int *sum_of_points,
	Set information_set);

int findGradeById(Semester semester, long int course_id);

int findPointsByCourseId(Semester semester, long int course_id);

int findLastCountGradeCourseMultiplyGrade(Semester semester,
	long int course_id);

int findLastGradeOfCourseClean(Semester semester, long int course_id);

int findBestGradeCourseInSemester(Semester semester, long int course_id);

int searchForGradeInCourseGrade(Semester semester, long int course_id);

#endif // !SEMESTER