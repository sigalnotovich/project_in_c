#ifndef HW3_PART3_2_STUDENT_H
#define HW3_PART3_2_STUDENT_H
#include "semester.h"
#include <stdbool.h>
typedef struct student_s *Student;
typedef enum studentResult_t {
	STD_ARE_FRIENDS,
	STD_ARE_NOT_FRIENDS,
	STD_OUT_OF_MEMORY,
	STD_SUCCESS,
	STD_ALREADY_REQUESTED,
	STD_ALREADY_FRIENDS,
	STD_NOT_REQUESTED,
	STD_NOT_IN_MY_REQUEST,
	STD_NOT_IN_REQUEST_TO_ME
} StudentResult;

Student copyStudent(Student student);

void freeStudent(Student student);

int compareStudent(Student student1, Student student2);

Student createStudent(long int id, char* first_name, char* last_name);

int getId(Student student);

//helper function to CourseManagerResult student_friend_request (int other_id);
//the fuction return true if the students are friend		
StudentResult checkIfStudentAllreadyFriends(Student student1,
	Student student2);

//check if there is allready request from student1 to student 2;
StudentResult checkIfAllreadyRequested(Student student1, Student student2);

//remove student 2 from my request of student 1  removeFromMyRequest
//remove student 1 from request to me of student 2 removeFromRequestToMe
StudentResult removeRequest(Student student1, Student student2);

//removes student1 from beeing a friend of student 2 and oposite  
StudentResult removeFriend(Student student1, Student student2);

//add student 2 to the set friends of student 1
//and add student 1 to the set friend of student 2
StudentResult addToFriends(Student student1, Student student2);

//addToMyRequest() student 2 to student 1
//addToRequestToME() student 1 to student 2
StudentResult addRequest(Student student1, Student student2);

bool addGradeToStudent(Student student, int semester, long int course_id,
	char* points, int grade);

int addSemesterToStudent(Student student, int semester);

void printStudent(Student student, FILE* output_channel);

int removeGradeFromeStudent(Student student, int semester, long int course_id);

int findAndChangeLastSemesterCourseGrade(Student student, long int course_id,
	int new_grade);

int totalPointsCoursesX2(Student student);

int failedPointsCoursesX2(Student student);

int effectivePointsCoursesX2(Student student);

long int *arraySizeOfGradeOfStudent(Student student, int* size);

int effectiveGradesCoursesX2(Student student);

int printStudentClean(Student student, FILE* output_channel);

int effectiveGradesCoursesCleanX2(Student student, FILE* output_channel);

void printStudentBest(Student student, FILE* output_channel, int amount);

void printStudentWorst(Student student, FILE* output_channel, int amount);

char *getStudentFirst(Student student);

char* getStudentLast(Student student);

int findStudentBestGradeInCourse(long int course_id, Student student_iterator);

int searchForGradeInCourseSemester(Student student, long int course_id);

Set newFriendSet(Student student_logged_in);

#endif //HW3_PART3_2_STUDENT_H