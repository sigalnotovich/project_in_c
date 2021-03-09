//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "course_manager.h"
//#include "mtm_ex3.h"
////#include "list.h"
////#include "set.h"
//#include "test_utilities.h"
//
//
////course manager adars functions check
//
//bool courseMangareGradeSheetAddTest();
//bool courseMangareGradeSheetRemoveTest();
//bool courseManagerGradeSheetUpdateTest();
//
//int main() {
//	RUN_TEST(courseMangareGradeSheetAddTest);
//	RUN_TEST(courseMangareGradeSheetRemoveTest);
//	RUN_TEST(courseManagerGradeSheetUpdateTest);
//}
//
//
//bool courseMangareGradeSheetAddTest() {
//course_manager manager = createCourseManager();
//int id = 001;
//char* first_name = "sigal";
//char* last_name = "notovich";
//int semester = 2017;
//unsigned long int  course_id = 123456;
//char* points = "4.5";
//int grade = 99;
//CourseManagerResult result =  gradeSheetAdd(semester,course_id,points,grade,manager);
//ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//result = studentAdd(id,first_name,last_name,manager);
//ASSERT_TEST(result == MNG_SUCCESS);
//result = studentLogin(id, manager);
//ASSERT_TEST(result == MNG_SUCCESS);
//semester = -2010;
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//semester = 3010;
//course_id = 10000000001; //greater then milion
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//course_id = -2233452;
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//course_id = 4567;
//points = "4.2";
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//points = "3.9";
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//points = "5.0";
//grade = 103;
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//grade = -5;
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//grade = 99;
//points = "4.2";
//result = gradeSheetAdd(semester, course_id, points, grade, manager);
//ASSERT_TEST(result == MNG_SUCCESS);
//	destroyCourseManager(manager);
//	return true;
//}
//
//bool courseMangareGradeSheetRemoveTest() {
//	course_manager manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int semester = 2017;
//	unsigned long int  course_id = 123456;
//	char* points = "4.5";
//	int grade = 99;
//	CourseManagerResult result = gradeSheetRemove(semester, course_id, manager);
//	ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//	result = studentAdd(id, first_name, last_name, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentLogin(id, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	 result = gradeSheetRemove(semester, course_id, manager);
//	 ASSERT_TEST(result == MNG_COURSE_DOES_NOT_EXIST);
//	 result = gradeSheetAdd(semester, course_id, points, grade, manager);
//	 ASSERT_TEST(result == MNG_SUCCESS);
//	 grade = 80;
//	 result = gradeSheetAdd(semester, course_id, points, grade, manager);
//	 ASSERT_TEST(result == MNG_SUCCESS);
//	  result = gradeSheetRemove(semester, course_id, manager);
//	  ASSERT_TEST(result == MNG_SUCCESS);
//	  result = gradeSheetRemove(semester, course_id, manager);
//	  ASSERT_TEST(result == MNG_SUCCESS);
//	  result = gradeSheetRemove(semester, course_id, manager);
//	  ASSERT_TEST(result == MNG_COURSE_DOES_NOT_EXIST);
//	  destroyCourseManager(manager);
//	  return true;
//}
//
//bool courseManagerGradeSheetUpdateTest() { //to do
//	course_manager manager = createCourseManager();
//
//	destroyCourseManager(manager);
//	return true;
//}