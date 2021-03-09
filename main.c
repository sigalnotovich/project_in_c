//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "grade.h"
//#include "mtm_ex3.h"
//#include "student.h"
//#include "list.h"
//#include "set.h"
//#include "test_utilities.h"
//
////grade check
//bool gradeCheckPointsParameterTest();
//
//int main() {
//	RUN_TEST(gradeCheckPointsParameterTest);
//}
//
//bool gradeCheckPointsParameterTest() {
//	int grade_number = 98;
//	unsigned long int course_id = 12345;
//	char* points = "4.5";
//	//reateGrade(grade_number, course_id,  points);
//	int result = checkPointsParameter(points);
//	ASSERT_TEST(result == 1);
//	points = "4.0";
//	ASSERT_TEST(result == 1);
//	points = "4.5";
//	ASSERT_TEST(result == 1);
//	points = "4";
//	ASSERT_TEST(result == 1);
//	points = "4.1";
//	ASSERT_TEST(result == 0);
//	points = "4.2";
//	ASSERT_TEST(result == 0);
//	points = "4.3";
//	ASSERT_TEST(result == 0);
//	points = "4.4";
//	ASSERT_TEST(result == 0);
//	points = "4.6";
//	ASSERT_TEST(result == 0);
//	points = "4.7";
//	ASSERT_TEST(result == 0);
//	points = "4.8";
//	ASSERT_TEST(result == 0);
//	points = "4.9";
//	ASSERT_TEST(result == 0);
//	return true;
//}
//
////multiply grade for what is this function?
//
//bool gradeCreateGradeTest() {
//	unsigned long int  course_id = 123456;
//	char* points = "4.5";
//	int grade = 99;
//	createGrade(99, course_id, points);
//	destroyGrade(99);
//
//
//}