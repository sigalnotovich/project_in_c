#include "grade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
struct grade_s {
	int grade;
	long int course_id;
	char* points;
};

//return 0 if uncorrect 1 is correct
int checkPointsParameter(char* points) {
	int last_number = strlen(points) - 1;
	if (points[strlen(points) - 2] == '.') {
		if (points[last_number] != '0' && (points[last_number] != '5')) {
			return 0;
		}
		for (int i = 0; i < (strlen(points) - 2); i++) {
			if (points[i] > '9' || points[i] < '0') {
				return 0;
			}
		}
		return 1;
	}
	else {
		for (int i = 0; i < strlen(points); i++) {
			if (points[i] > '9' || points[i] < '0') {
				return 0;
			}
		}
	}
	return 1;
}

int multiplyPoints(Grade grade) {
	int tmp = 0;
	int last_number = strlen(grade->points) - 1;
	if (grade->points[strlen(grade->points) - 2] == '.') {//xxx.x
		if (grade->points[last_number] == '0') {//xxxx.0
			for (int i = 0; i < (strlen(grade->points) - 2); i++) {
				tmp += (grade->points[i] - '0');
				tmp *= 10;
			}
			tmp /= 10;
			return (tmp * 2);
		}
		else {//xxxx.5
			for (int i = 0; i < (strlen(grade->points) - 2); i++) {
				tmp += (grade->points[i] - '0');
				tmp *= 10;
			}
			tmp /= 10;
			tmp *= 2;
			return ++tmp;
		}
	}
	else {///xxx
		for (int i = 0; i < strlen(grade->points); i++) {
			tmp += (grade->points[i] - '0');
			tmp *= 10;
		}
		tmp /= 10;
		return (tmp * 2);
	}
}

Grade createGrade(int grade_number, long int course_id, char* points) {
	assert(points != NULL);
	Grade new_grade = malloc(sizeof(*new_grade));
	if (new_grade == NULL) {
		return NULL;
	}
	new_grade->course_id = course_id;
	new_grade->grade = grade_number;
	new_grade->points = malloc(sizeof(*points)*(strlen(points) + 1));
	strcpy(new_grade->points, points);
	return new_grade;
}

void destroyGrade(Grade grade) {
	if (grade == NULL) {
		return;
	}
	if (grade->points == NULL) {
		free(grade);
		return;
	}
	free(grade->points);
	free(grade);
	return;
}

//copy grade to new_grade(empty)
Grade copyGrade(Grade grade) {
	assert(grade != NULL);
	return createGrade(grade->grade, grade->course_id, grade->points);
}

void printGrade(Grade grade) {
	printf("grad:%d course_id:%lu points:%s\n", grade->grade,
		grade->course_id, grade->points);
	return;
}

long int getCourseId(Grade grade) {
	return grade->course_id;
}

void changeGradeNumber(Grade grade, int new_grade) {
	grade->grade = new_grade;
	return;
}

int getGrade(Grade grade) {
	return grade->grade;
}
