//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "test_utilities.h"
//#include "grade_information.h"
//
//static bool testcreatArrayAndcomperArray() {
//	information new_information1 = creatArray(123, 4.5, 98, 1);
//	information new_information2 = creatArray(123, 4.5, 98, 1);
//	int result = comperArray(new_information1, new_information2);
//	ASSERT_TEST(result == 0);
//	information new_information3 = creatArray(12345, 4.5, 98, 1);
//	result = comperArray(new_information1, new_information3);
//	ASSERT_TEST(result == -1);
//	freeArray(new_information1);
//	freeArray(new_information2);
//	freeArray(new_information3);
//	return true;
//}
//
//static bool testcopyArray() {
//	information new_information1 = creatArray(123, 4.5, 98, 1);
//	information new_information2 = copyArray(new_information1);
//	int result = comperArray(new_information1, new_information2);
//	ASSERT_TEST(result == 0);
//	freeArray(new_information1);
//	freeArray(new_information2);
//	return true;
//}
//
//static bool testgetCourseAndgetSemesterAndgetGadeInformation() {
//	information new_information1 = creatArray(123, 4.5, 98, 1);
//	unsigned long int course_id =  getCourse(new_information1);
//	ASSERT_TEST(course_id == 123);
//	int semester = getSemester(new_information1);
//	ASSERT_TEST(semester == 1);
//	int grade = getGadeInformation(new_information1);
//	ASSERT_TEST(grade == 98);
//	freeArray(new_information1);
//	return true;
//}
//
//
//static bool testcomperArrayByGrade() {
//	information new_information1 = creatArray(123, 4.5, 98, 1);
//	information new_information2 = creatArray(123, 4.5, 89, 1);
//	int result = comperArrayByGrade(new_information1, new_information2);
//	ASSERT_TEST(result == -1);
//	 result = comperArrayByGrade(new_information2, new_information1);
//	ASSERT_TEST(result == 1);
//	result = comperArrayByGrade(new_information1, new_information1);
//	ASSERT_TEST(result == 0);
//	freeArray(new_information1);
//	freeArray(new_information2);
//	return true;
//}
//
//
//static bool testcomperArrayByGradeWorst() {
//	information new_information1 = creatArray(1234, 4.5, 98, 1);
//	information new_information2 = creatArray(123, 4.5, 98, 1);
//	int result = comperArrayByGradeWorst(new_information1,new_information2);
//	ASSERT_TEST(result ==1);
//	result = comperArrayByGradeWorst(new_information1, new_information1);
//	ASSERT_TEST(result ==0);
//	result = comperArrayByGradeWorst(new_information2, new_information1);
//	ASSERT_TEST(result ==-1);
//	freeArray(new_information1);
//	freeArray(new_information2);
//	return true;
//}
//int main() {
//	RUN_TEST(testcreatArrayAndcomperArray);
//	RUN_TEST(testcopyArray);
//	RUN_TEST(testgetCourseAndgetSemesterAndgetGadeInformation);
//	RUN_TEST(testcomperArrayByGrade);
//	RUN_TEST(testcomperArrayByGradeWorst);
//	return 0;
//}