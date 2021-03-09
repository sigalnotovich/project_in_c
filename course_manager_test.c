//#include <stdlib.h>
//#include <stdio.h>	
//#include <assert.h>
//#include <string.h>
//#include "test_utilities.h"
//#include "course_manager.h"
//
//
//static bool new_course_manager_test();
//static  bool addrequestTest();
//static bool HandleRequest1Test();
//static bool HandleRequest2Test();
//static bool HandleRequest3Test();
//static bool removeFriendTest1Test();
//static bool removeFriendTest2Test();
//static bool LogInLogOutTest();
//static bool AddAndRemoveStudentsFromManagerTest();
//
//
//static bool LogInLogOutTest() {
//	course_manager new_course_manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	studentAdd(id, first_name, last_name, new_course_manager);
//	CourseManagerResult result = studentLogin(-9999999, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentLogin(10000000001, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentLogin(3, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentLogin(id, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentLogin(id, new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_LOGGED_IN);
//	result = studentLogout(new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentLogout(new_course_manager);
//	ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//	destroyCourseManager(new_course_manager);
//	return  true;
//}
//
//
//static bool AddAndRemoveStudentsFromManagerTest() {
//	course_manager new_course_manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	CourseManagerResult result = studentAdd(id, first_name, last_name, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentAdd(id, NULL, last_name, new_course_manager);
//	ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//	result = studentAdd(id, first_name, NULL, new_course_manager);
//	ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//	result = studentAdd(-999999999, first_name, last_name, new_course_manager);
//	ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//	result = studentAdd(9999999999, first_name, last_name, new_course_manager);
//	ASSERT_TEST(result == MNG_INVALID_PARAMETERS);
//	result = studentRemove(-1, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentRemove(2, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	studentLogin(1, new_course_manager);
//	result = studentRemove(1, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentLogout(new_course_manager);
//	ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//	destroyCourseManager(new_course_manager);
//	return  true;
//}
//
//static bool HandleRequest1Test() {
//	course_manager new_course_manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	studentAdd(id, first_name, last_name, new_course_manager);
//	studentAdd(ida, first_namea, last_namea, new_course_manager);
//	CourseManagerResult result = studentHandleRequest(1, "fdsdf", new_course_manager);
//	ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//	result = studentHandleRequest(1, "accept", new_course_manager);
//	ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//	result = studentLogin(1, new_course_manager); //student 1 loged in
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentHandleRequest(2, "accept", new_course_manager); //not requested
//	ASSERT_TEST(result == MNG_NOT_REQUESTED);
//	result = studentHandleRequest(2, "reject", new_course_manager);
//	ASSERT_TEST(result == MNG_NOT_REQUESTED);
//	result = studentHandleRequest(2, "jkjk", new_course_manager);
//	ASSERT_TEST(result == MNG_NOT_REQUESTED);
//	result = studentHandleRequest(200, "accept", new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentHandleRequest(200, "jbjkjh", new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	//student asking from himself
//	result = studentHandleRequest(1, "accept", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	//student asking from himself
//	result = studentHandleRequest(1, "jbjkjh", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	//make students be friend:
//	result = studentFriendRequest(2, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	studentLogout(new_course_manager);
//	studentLogin(2, new_course_manager);//student 2 loged in
//	result = studentHandleRequest(1, "accept", new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	//try to accept request from allready friend student:
//	result = studentHandleRequest(1, "accept", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	//try to reject request from allready friend student:
//	result = studentHandleRequest(1, "reject", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	result = studentHandleRequest(1, "2efwesf", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	studentLogout(new_course_manager);
//	studentLogin(1, new_course_manager);
//	//student 1 loged in
//	result = studentHandleRequest(2, "accept", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	//try to reject request from allready friend student:
//	result = studentHandleRequest(2, "reject", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	result = studentHandleRequest(2, "2efwesf", new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	destroyCourseManager(new_course_manager);
//	return true;
//}
//
//static bool HandleRequest2Test() {
//	course_manager manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	studentAdd(id, first_name, last_name, manager);
//	studentAdd(ida, first_namea, last_namea, manager);
//	//make request from both sides and see what hapend
//	studentLogin(1, manager);
//	CourseManagerResult result = studentFriendRequest(2, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	studentLogout(manager);
//	studentLogin(2, manager);
//	result = studentFriendRequest(1, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentHandleRequest(1, "accept", manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	studentLogout(manager);
//	studentLogin(1, manager);
//	result = studentHandleRequest(2, "accept", manager);
//	//becouse request was deleted when handled by user which id =2:
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	destroyCourseManager(manager);
//	return true;
//}
//
//static bool HandleRequest3Test() {
//	course_manager manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	studentAdd(id, first_name, last_name, manager);
//	studentAdd(ida, first_namea, last_namea, manager);
//	studentLogin(1, manager);
//	CourseManagerResult result = studentFriendRequest(2, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	studentLogout(manager);
//	studentLogin(2, manager);
//	result = studentFriendRequest(1, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentHandleRequest(1, "reject", manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	studentLogout(manager);
//	studentLogin(1, manager);
//	result = studentHandleRequest(2, "accept", manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentHandleRequest(2, "accept", manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	destroyCourseManager(manager);
//	return true;
//}
//
//static bool removeFriendTest1Test() {
//	course_manager manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	studentAdd(id, first_name, last_name, manager);
//	studentAdd(ida, first_namea, last_namea, manager);
//	//make friends:
//	studentLogin(1, manager);
//	CourseManagerResult result = studentFriendRequest(2, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	studentLogout(manager);
//	studentLogin(2, manager);
//	result = studentHandleRequest(1, "accept", manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentFriendRequest(1, manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND);
//	result = studentUnfriend(1, manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentUnfriend(1, manager);
//	ASSERT_TEST(result == MNG_NOT_FRIEND);
//	destroyCourseManager(manager);
//	return true;
//}
//
//static bool removeFriendTest2Test() {
//	course_manager manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	studentAdd(id, first_name, last_name, manager);
//	studentAdd(ida, first_namea, last_namea, manager);
//	CourseManagerResult result = studentUnfriend(1, manager);
//	ASSERT_TEST(result == MNG_NOT_LOGGED_IN);
//	studentLogin(1, manager);
//	result = studentUnfriend(3000, manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentUnfriend(1, manager);
//	ASSERT_TEST(result == MNG_NOT_FRIEND);
//	result = studentUnfriend(2, manager);
//	ASSERT_TEST(result == MNG_NOT_FRIEND);
//	destroyCourseManager(manager);
//	return true;
//}
//
//static bool addrequestTest() {
//	course_manager new_course_manager = createCourseManager();
//	int id = 001;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	int ida = 002;
//	char* first_namea = "adar";
//	char* last_namea = "kaminski";
//	studentAdd(id, first_name, last_name, new_course_manager);
//	studentLogin(id, new_course_manager);
//	studentAdd(ida, first_namea, last_namea, new_course_manager);
//	CourseManagerResult result = studentFriendRequest(2, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentFriendRequest(2, new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_REQUESTED);
//	result = studentFriendRequest(1, new_course_manager);
//	ASSERT_TEST(result == MNG_ALREADY_FRIEND); //assking from himself
//	result = studentFriendRequest(3, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	//check if students actually friends
//	destroyCourseManager(new_course_manager);
//	return true;
//}
//
//
//static bool new_course_manager_test() {
//	course_manager new_course_manager = createCourseManager();
//	int id = 001;
//	int id2 = 002;
//	char* first_name = "sigal";
//	char* last_name = "notovich";
//	CourseManagerResult result = studentAdd(id, first_name, last_name, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	result = studentLogin(id2, new_course_manager);
//	ASSERT_TEST(result == MNG_STUDENT_DOES_NOT_EXIST);
//	result = studentLogin(id, new_course_manager);
//	ASSERT_TEST(result == MNG_SUCCESS);
//	destroyCourseManager(new_course_manager);
//	return true;
//}
//
//
//
//int main() {
//	RUN_TEST(new_course_manager_test);
//	RUN_TEST(AddAndRemoveStudentsFromManagerTest);
//	RUN_TEST(LogInLogOutTest);
//	RUN_TEST(addrequestTest);
//	RUN_TEST(HandleRequest1Test);
//	RUN_TEST(HandleRequest2Test);
//	RUN_TEST(HandleRequest3Test);
//	RUN_TEST(removeFriendTest1Test);
//	RUN_TEST(removeFriendTest2Test);
//}