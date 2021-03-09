//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
//#include <string.h>
//#include "semester.h"
//#include "test_utilities.h"
//
//static bool testcreateSemester();
//static bool testcopySemester();
//static bool testcompareSemester();
//static bool testgetSemesterId();
//static bool testaddGrade();
//static bool testfindCourseLastGradeAndChange();
//static bool testtotalPointsX2();
//static bool testfailedPointsX2();
//static bool testsizeOfGradeInSemester();
//static bool testfindLastGradeOfCourseAndMultiplyWithGrade();
//static bool testfindGradeById();
//static bool testfindPointsByCourseId();
//static bool testfindLastCountGradeOfCourseAndMultiplyWithGrade();
//static bool testfindLastGradeOfCourseClean();
//static bool testfindBestGradeCourseInSemester();
//
//
//static bool testcreateSemester() {
//	Semester semester = createSemester(3);
//	ASSERT_TEST(semester != NULL);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testcopySemester() {
//	int semester_id = 2;
//	Semester semester = createSemester(semester_id);
//	Semester copy_semester = copySemester(semester);
//	int copy_semester_id = getSemesterId(copy_semester);
//	ASSERT_TEST(copy_semester_id == semester_id);
//	destroySemester(semester);
//	destroySemester(copy_semester);
//	return true;
//}
//
//static bool testcompareSemester() { 
//	int semester_id1 = 2;
//	int semester_id2 = 2;
//	Semester semester1 = createSemester(semester_id1);
//	Semester semester2 = createSemester(semester_id2);
//	int compare = compareSemester(semester1, semester2);
//	ASSERT_TEST(compare == 0);
//	destroySemester(semester1);
//	destroySemester(semester2);
//	semester_id1 = 2;
//	semester_id2 = 3;
//	semester1 = createSemester(semester_id1);
//	semester2 = createSemester(semester_id2);
//	compare = compareSemester(semester1, semester2);
//	ASSERT_TEST(compare <0);
//	destroySemester(semester1);
//	destroySemester(semester2);
//	semester_id1 = 3;
//	semester_id2 = 2;
//	semester1 = createSemester(semester_id1);
//	semester2 = createSemester(semester_id2);
//	compare = compareSemester(semester1, semester2);
//	ASSERT_TEST(compare > 0);
//	destroySemester(semester1);
//	destroySemester(semester2);
//	return true;
//}
//
//static bool testgetSemesterId() {
//	Semester semester = createSemester(3);
//	int semster_id = getSemesterId(semester);
//	ASSERT_TEST(semster_id == 3);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testaddGrade() {
//	Semester semester = createSemester(3);
//	int result = addGrade(semester, 1, "4.5", 98);
//	ASSERT_TEST(result == 1);
//	destroySemester(semester);
//	return true;
//}
//
//
//static bool testfindCourseLastGradeAndChange() {
//	Semester semester = createSemester(3);
//	addGrade(semester, 1234, "4.5", 98);
//	int result = findCourseLastGradeAndChange(semester, 1234, 80);
//	ASSERT_TEST(result == 1);
//	//check the new grade
//	result = findCourseLastGradeAndChange(semester, 12, 82);
//	ASSERT_TEST(result == 0);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testtotalPointsX2() {
//	Semester semester = createSemester(3);
//	addGrade(semester, 1234, "4.5", 98);
//	addGrade(semester, 1234, "1.5", 98);
//	addGrade(semester, 1234, "1", 98);
//	addGrade(semester, 1234, "3.0", 98);
//	int total = totalPointsX2(semester);
//	ASSERT_TEST(total == 20);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testfailedPointsX2() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 1234, "4.5", 45);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 98);
//	int total = failedPointsX2(semester);
//	ASSERT_TEST(total == 11);
//	return true;
//}
//
//static bool testsizeOfGradeInSemester() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 1234, "4.5", 45);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 98);
//	int total = sizeOfGradeInSemester(semester);
//	ASSERT_TEST(total == 4);
//	return true;
//}
//
//
//
//static bool testfindLastGradeOfCourseAndMultiplyWithGrade() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 1234, "4.5", 42);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 90);
//	int result = findLastGradeCourseAndMultiplyWithGrade(semester, 1234);
//	ASSERT_TEST(result == 180*3);
//	result = findLastGradeCourseAndMultiplyWithGrade(semester, 123);
//	ASSERT_TEST(result == 98*2*1.5);
//	result = findLastGradeCourseAndMultiplyWithGrade(semester, 12345);
//	ASSERT_TEST(result == 0);
//	destroySemester(semester);
//	return true;
//}
//
//
//static bool testfindGradeById() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 1234, "4.5", 42);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 80);
//	addGrade(semester, 1234, "3.0", 90);
//	int result = findGradeById(semester,1234);
//	ASSERT_TEST(result == 90);
//	result = findGradeById(semester,123);
//	ASSERT_TEST(result == 98);
//	result = findGradeById(semester, 12345);
//	ASSERT_TEST(result == 0);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testfindPointsByCourseId() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 80);
//	addGrade(semester, 1234, "3.0", 90);
//	int result = findPointsByCourseId(semester, 1234);
//	ASSERT_TEST(result == 6);
//	result = findPointsByCourseId(semester, 123);
//	ASSERT_TEST(result == 3);
//	result = findPointsByCourseId(semester, 12345);
//	ASSERT_TEST(result == 0);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testfindLastCountGradeOfCourseAndMultiplyWithGrade() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 80);
//	addGrade(semester, 1234, "3.0", 50);
//	int result = findLastCountGradeCourseMultiplyGrade(semester, 123);
//	ASSERT_TEST(result == 3 * 98);
//	result = findLastCountGradeCourseMultiplyGrade(semester, 12345);
//	ASSERT_TEST(result == -1);
//	result = findLastCountGradeCourseMultiplyGrade(semester, 1234);
//	ASSERT_TEST(result == -1);
//	destroySemester(semester);
//	return true;
//}
//
//static bool testfindLastGradeOfCourseClean() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 1234, "3.0", 80);
//	addGrade(semester, 1234, "3.0", 50);
//	int result = findLastGradeOfCourseClean(semester, 123);
//	ASSERT_TEST(result == 3);
//	result = findLastGradeOfCourseClean(semester, 12345);
//	ASSERT_TEST(result == 0);
//	result = findLastGradeOfCourseClean(semester, 1234);
//	ASSERT_TEST(result == 0);
//	destroySemester(semester);
//		return true;
//}
//
//static bool testfindBestGradeCourseInSemester() {
//	Semester semester = createSemester(2);
//	addGrade(semester, 123, "1.5", 98);
//	addGrade(semester, 12345, "1", 10);
//	addGrade(semester, 12345, "1", 70);
//	addGrade(semester, 1234, "3.0", 80);
//	addGrade(semester, 1234, "3.0", 60);
//	int result = findBestGradeCourseInSemester(semester, 567);
//	ASSERT_TEST(result == 0);
//	result = findBestGradeCourseInSemester(semester, 1234);
//	ASSERT_TEST(result == 80);
//	result = findBestGradeCourseInSemester(semester, 12345);
//	ASSERT_TEST(result == 70);
//	result = findBestGradeCourseInSemester(semester, 123);
//	ASSERT_TEST(result == 98);
//	return true;
//}
//
//
//int main() {
//	RUN_TEST(testcreateSemester);
//	RUN_TEST(testcopySemester);
//	RUN_TEST(testcompareSemester);
//	RUN_TEST(testgetSemesterId);
//	RUN_TEST(testaddGrade);
//	RUN_TEST(testfindCourseLastGradeAndChange);
//	RUN_TEST(testtotalPointsX2);
//	RUN_TEST(testfindGradeById);
//	RUN_TEST(testfailedPointsX2);
//	RUN_TEST(testsizeOfGradeInSemester);
//	RUN_TEST(testfindPointsByCourseId);
//	RUN_TEST(testfindLastCountGradeOfCourseAndMultiplyWithGrade);
//	RUN_TEST(testfindLastGradeOfCourseAndMultiplyWithGrade);
//	RUN_TEST(testfindLastGradeOfCourseClean);
//	RUN_TEST(testfindBestGradeCourseInSemester);
//	return 0;
//}