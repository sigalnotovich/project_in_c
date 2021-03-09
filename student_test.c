//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
//#include <string.h>
//#include "test_utilities.h"
//#include "student.h"
//
//
//static bool StudentaddToFriendsTest();
//static bool StudentcheckIfFriendsAndIfRequestedTest();
//static bool studentChakeRemoveRequestTest();
//static bool StudentRemoveFromFriendsTest();
//
//
//
//static bool StudentcheckIfFriendsAndIfRequestedTest() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	Student student2 = createStudent(ida, first_namea, last_namea);
//	StudentResult result = checkIfStudentAllreadyFriends(student1, student2);
//	ASSERT_TEST(result == STD_ARE_NOT_FRIENDS);
//	result = addToFriends(student1, student2);
//	ASSERT_TEST(result == STD_SUCCESS);
//	result = checkIfStudentAllreadyFriends(student1, student2);
//	ASSERT_TEST(result == STD_ARE_FRIENDS);
//	//unfriend
//	result = addRequest(student1, student2);
//	result = checkIfAllreadyRequested(student1, student2);
//	ASSERT_TEST(result == STD_ALREADY_REQUESTED);
//	result = checkIfAllreadyRequested(student2, student1);
//	ASSERT_TEST(result == STD_NOT_REQUESTED);
//	freeStudent(student1);
//	freeStudent(student2);
//
//	return true;
//}
//
//static  bool studentChakeRemoveRequestTest() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	Student student2 = createStudent(ida, first_namea, last_namea);
//	StudentResult result = removeRequest(student1, student2);
//	ASSERT_TEST(result == STD_NOT_REQUESTED);
//	result = addRequest(student1, student2); //
//	result = removeRequest(student1, student2);
//	ASSERT_TEST(result == STD_SUCCESS);
//	result = removeRequest(student1, student2);
//	ASSERT_TEST(result == STD_NOT_REQUESTED);
//	freeStudent(student1);
//	freeStudent(student2);
//
//	return true;
//}
//
//
//static bool StudentRemoveFromFriendsTest() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	Student student2 = createStudent(ida, first_namea, last_namea);
//	StudentResult result = addToFriends(student1, student2);
//	ASSERT_TEST(result == STD_SUCCESS);
//	result = removeFriend(student1, student2);
//	ASSERT_TEST(result == STD_SUCCESS);
//	result = checkIfStudentAllreadyFriends(student1, student2);
//	ASSERT_TEST(result == STD_ARE_NOT_FRIENDS);
//	freeStudent(student1);
//	freeStudent(student2);
//	return true;
//}
//
//static bool StudentaddToFriendsTest() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	Student student2 = createStudent(ida, first_namea, last_namea);
//	StudentResult result = checkIfStudentAllreadyFriends(student1, student2);
//	ASSERT_TEST(result == STD_ARE_NOT_FRIENDS);
//	result = addToFriends(student1, student2);
//	ASSERT_TEST(result == STD_SUCCESS);
//	result = addToFriends(student1, student2);
//	ASSERT_TEST(result == STD_ALREADY_FRIENDS);
//	result = addToFriends(student2, student1);
//	ASSERT_TEST(result == STD_ALREADY_FRIENDS);
//	freeStudent(student1);
//	freeStudent(student2);
//	return true;
//}
//
//static bool testaddGradeToStudentAndremoveGradeFromeStudent() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	bool result = addGradeToStudent(student1, 1, 1234, "4.5", 98);
//	ASSERT_TEST(result == true);
//	removeGradeFromeStudent(student1, 1, 1234);
//	freeStudent(student1);
//	return true;
//}
//
//static bool testaddSemesterToStudent() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	int result = addSemesterToStudent(student1, 2);
//	ASSERT_TEST(result == 1);
//	freeStudent(student1);
//	return true;
//}
//
//static bool testfindAndChangeLastSemesterCourseGrade() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	int result = findAndChangeLastSemesterCourseGrade(student1, 1234, 98);
//	ASSERT_TEST(result == 0); //there is no such course
//	addGradeToStudent(student1, 1, 1234, "4.5", 92);
//	result = findAndChangeLastSemesterCourseGrade(student1, 1234, 98);
//	ASSERT_TEST(result == 1);//the course is exist
//	freeStudent(student1);
//	return true;
//}
//
//static bool testtotalPointsCoursesX2() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	addGradeToStudent(student1, 1, 1234, "4.5", 92);
//	addGradeToStudent(student1, 2, 12, "1.5", 92);
//	addGradeToStudent(student1, 3, 12345, "2", 92);
//	int result =  totalPointsCoursesX2(student1);
//	ASSERT_TEST(result == 16);
//	freeStudent(student1);
//	return true;
//}
//
//static bool testfailedPointsCoursesX2() {
//	int ids = 001;
//	char* first_names = "sigal";
//	char* last_names = "notovich";
//	Student student1 = createStudent(ids, first_names, last_names);
//	addGradeToStudent(student1, 1, 1234, "4.5", 20);
//	addGradeToStudent(student1, 2, 12, "1.5", 92);
//	addGradeToStudent(student1, 3, 12345, "2", 30);
//	int result = failedPointsCoursesX2(student1);
//	ASSERT_TEST(result == 13);
//	freeStudent(student1);
//	return true;
//}
//
//int main() {
//	RUN_TEST(StudentcheckIfFriendsAndIfRequestedTest);
//	RUN_TEST(studentChakeRemoveRequestTest);
//	RUN_TEST(StudentaddToFriendsTest);
//	RUN_TEST(StudentRemoveFromFriendsTest);
//	RUN_TEST(testaddGradeToStudentAndremoveGradeFromeStudent);
//	RUN_TEST(testaddSemesterToStudent);
//	RUN_TEST(testfindAndChangeLastSemesterCourseGrade);
//	RUN_TEST(testtotalPointsCoursesX2);
//	RUN_TEST(testfailedPointsCoursesX2);
//}