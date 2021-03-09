//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
//#include <string.h>
//#include "test_utilities.h"
//#include "grade.h"
//
//
//static bool testcreateGrade() {
//	Grade grade = createGrade(90, 1, "1.5");
//	ASSERT_TEST(grade != NULL);
//	destroyGrade(grade);
//	return true;
//}
//
//
//static bool testcopyGrade() {
//	Grade grade = createGrade(90, 1, "1.5");
//	ASSERT_TEST(grade != NULL);
//	Grade new_grade = copyGrade(grade);
//	ASSERT_TEST(new_grade != NULL);
//	unsigned long int course_id = getCourseId(grade);
//	unsigned long int new_course_id= getCourseId(new_grade);
//	ASSERT_TEST(course_id == new_course_id);
//	int grade_num = getGrade(grade);
//	int new_grade_num = getGrade(new_grade);
//	ASSERT_TEST(grade_num = new_grade_num);
//	destroyGrade(grade);
//	destroyGrade(new_grade);
//	return true;
//}
//
//
//static bool testgetCourseId() {
//	unsigned long int course_id = 1234567;
//	Grade grade = createGrade(90, course_id, "1.5");
//	unsigned long int get_course_id = getCourseId(grade);
//	ASSERT_TEST(course_id == get_course_id);
//	destroyGrade(grade);
//	return true;
//}
//
//static bool testchangeGradeNumber() {
//	int grade_num = 90;
//	Grade grade = createGrade(grade_num,1,"1.5");
//	changeGradeNumber(grade, 99);
//	int new_grade = getGrade(grade);
//	ASSERT_TEST(new_grade == 99);
//	destroyGrade(grade);
//	return true;
//}
//
//static bool testmultiplyPoints() { 
//	Grade grade = createGrade(99, 1, "1.5");
//	int result = multiplyPoints(grade);
//	ASSERT_TEST(result == 3);
//	destroyGrade(grade);
//	return true;
//}
//
//
//static bool testgetGrade() {
//	int grade_num = 90;
//	Grade grade = createGrade(grade_num, 1, "1.5");
//	int get_grade = getGrade(grade);
//	ASSERT_TEST(get_grade == 90);
//	destroyGrade(grade);
//	return true;
//}
//
//int main() {
//	RUN_TEST(testcreateGrade);
//	RUN_TEST(testcopyGrade);
//	RUN_TEST(testgetCourseId);
//	RUN_TEST(testchangeGradeNumber);
//	RUN_TEST(testmultiplyPoints);
//	RUN_TEST(testgetGrade);
//	
//	return 0;
//}