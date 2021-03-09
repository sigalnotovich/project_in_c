#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"
#include "student.h"
#include "semester.h"
#include <assert.h>
#include "mtm_ex3.h"           
#include "grade_information.h"
struct student_s {
	char * first_name;
	char * last_name;
	long int  id;
	Set friends;  //set of id's
	Set my_request;
	Set request_to_me;
	List semesteres;
};
static StudentResult addRightStudentidToLeftStudentFriendSet(Student student1,
	Student student2);

long int* copyId(long int* id) {
	long int* copy = malloc(sizeof(long int));
	*copy = *id;
	return copy;
}

void freeId(long int* id) {
	assert(id);
	free(id);
}

//return -1 if  id1 is smaller that  id2
//return 0 if  id1 is equal to  id2
//return 1 if  id1 is bigger then  id2
int compareId(long int* id1, long int*  id2) {
	assert(id1);
	assert(id2);
	if (*id1 < *id2) {
		return -1;
	}
	if (*id1 == *id2) {
		return 0;
	}
	if (*id1 > *id2) {
		return 1;
	}
	return 2;
}

ListElement copySemesterElement(ListElement element) {
	return (ListElement)copySemester((Semester)element);
}

void freeSemesterElement(ListElement element) {
	destroySemester((Semester)element);
	return;
}

int commpareSemesterElement(ListElement element_one,
	ListElement element_two) {
	Semester  semester_one = (Semester)element_one;
	Semester  semester_two = (Semester)element_two;
	return compareSemester(semester_one, semester_two);
}

SetElement copyIdElement(SetElement element) {
	if (element == NULL) {
		return NULL;
	}
	long int* tmp = (long int*)element;
	return (SetElement)copyId(tmp);
}

void freeIdElement(SetElement element) {
	freeId((long int*)element);
}

int compareIdElement(SetElement element_first, SetElement element_second) {
	long int* tmp_first = (long int*)element_first;
	long int* tmp_second = (long int*)element_second;
	return compareId(tmp_first, tmp_second);
}

Student createStudent(long int id, char* first_name, char* last_name) {
	Student new_student = malloc(sizeof(*new_student));
	new_student->id = id;
	new_student->first_name = malloc((strlen(first_name) + 1) * sizeof(char));
	if (new_student->first_name == NULL) {
		freeStudent(new_student);
		return NULL;
	}
	strcpy(new_student->first_name, first_name);
	new_student->last_name = malloc((strlen(last_name) + 1) * sizeof(char));
	if (new_student->last_name == NULL) {
		freeStudent(new_student);
		return NULL;
	}
	strcpy(new_student->last_name, last_name);
	new_student->friends = setCreate(copyIdElement,
		freeIdElement, compareIdElement);
	new_student->my_request = setCreate(copyIdElement, freeIdElement,
		compareIdElement);
	new_student->request_to_me = setCreate(copyIdElement,
		freeIdElement, compareIdElement);
	if (new_student->friends == NULL || new_student->my_request == NULL ||
		new_student->request_to_me == NULL) {
		freeStudent(new_student);
		return NULL;
	}
	new_student->semesteres = listCreate(copySemesterElement,
		freeSemesterElement);
	if (new_student->semesteres == NULL) {
		freeStudent(new_student);
		return NULL;
	}
	return new_student;
}

int getId(Student student) {
	return student->id;
}

Student copyStudent(Student student) {
	Student new_student = createStudent(student->id, student->first_name,
		student->last_name);
	listDestroy(new_student->semesteres);
	new_student->semesteres = listCopy(student->semesteres);
	setDestroy(new_student->friends);
	new_student->friends = setCopy(student->friends);
	setDestroy(new_student->my_request);
	new_student->my_request = setCopy(student->my_request);
	setDestroy(new_student->request_to_me);
	new_student->request_to_me = setCopy(student->request_to_me);
	return new_student;
}

void freeStudent(Student student) {
	free(student->first_name);
	free(student->last_name);
	listDestroy(student->semesteres);
	setDestroy(student->friends);
	setDestroy(student->my_request);
	setDestroy(student->request_to_me);
	free(student);
}

//compare student by id number
//return -1 if student1 id is smaller that student2 id
//return 0 if student1 id is equal to student2 id
//return 1 if student1 id is bigger then student2 id
int compareStudent(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	if (student1->id < student2->id) {
		return -1;
	}
	if (student1->id == student2->id) {
		return 0;
	}
	if (student1->id > student2->id) {
		return 1;
	}
	return 2;
}

//check if stuudent 2 id is in student 1 friends
static bool checkIsFriend(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	long int id2 = getId(student2);
	long int *id2_p = &id2;
	bool result = setIsIn(student1->friends, id2_p);
	return result;
}

//helper function to void studentFriendRequest (int other_id);
//the fuction return true if the students are friend and false if they are not
//we need a way to check that the student is friends from both side sets
StudentResult checkIfStudentAllreadyFriends(Student student1,
	Student student2) {
	assert(student1);
	assert(student2);
	bool result = checkIsFriend(student1, student2);
	if (result == true) {
		assert(checkIsFriend(student2, student1) == true);
		return STD_ARE_FRIENDS;
	}
	assert(checkIsFriend(student2, student1) == false);
	return STD_ARE_NOT_FRIENDS;
}

//add each one id to the friend set of the other one:
//add student 2 to the set friends of student 1
//and add student 1 to the set friend of student 2
//return STD_OUT_OF_MEMORY if there is no memory left or memory problame
//return STD_ALREADY_FRIENDS if studentsallreadyfriends
//return STD_SUCCESS if success
StudentResult addToFriends(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	StudentResult result1 = addRightStudentidToLeftStudentFriendSet(student1,
		student2);
	if (result1 == STD_OUT_OF_MEMORY) {
		return STD_OUT_OF_MEMORY;
	}
	//add student 1 id  to friends of student 2
	StudentResult result2 = addRightStudentidToLeftStudentFriendSet(student2,
		student1);
	if (result2 == STD_OUT_OF_MEMORY) {
		return STD_OUT_OF_MEMORY;
	}
	if (result1 == STD_ALREADY_FRIENDS) {
		assert(result2 == STD_ALREADY_FRIENDS);
		return STD_ALREADY_FRIENDS;
	}
	if (result2 == STD_ALREADY_FRIENDS) {
		assert(result1 == STD_ALREADY_FRIENDS);
		return STD_ALREADY_FRIENDS;
	}
	return STD_SUCCESS;
}

//return STD_OUT_OF_MEMORY if there is no memory left or memory problame
//return STD_ALREADY_FRIENDS if the student2id is allready in student1
//friends set
//return STD_SUCCESS if success
static StudentResult addRightStudentidToLeftStudentFriendSet(Student student1,
	Student student2) {
	assert(student1);
	assert(student2);
	long int id2 = getId(student2);
	long int *id2_p = &id2;
	SetResult result = setAdd(student1->friends, id2_p);
	if (result == SET_OUT_OF_MEMORY) {
		return STD_OUT_OF_MEMORY;
	}
	if (result == SET_ITEM_ALREADY_EXISTS) {
		return STD_ALREADY_FRIENDS;
	}
	return STD_SUCCESS;
}

//change bool in this function to Result enum?
//add student 2 to the set my_request of student 1
//return something?

static StudentResult addToMyRequest(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	long int id = getId(student2);
	long int *id_p = &id;
	SetResult result = setAdd(student1->my_request, id_p);
	if (result == SET_OUT_OF_MEMORY) {
		return STD_OUT_OF_MEMORY;
	}
	return STD_SUCCESS;
}

//add student 2 to the set request to me of student 1
static StudentResult addToRequestToME(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	long int id = getId(student2);
	long int *id_p = &id;
	SetResult result = setAdd(student1->request_to_me, id_p);
	if (result == SET_OUT_OF_MEMORY) {
		return STD_OUT_OF_MEMORY;
	}
	return STD_SUCCESS;
}

//student 1 ask frendship form student 2
//return STD_OUT_OF_MEMORY if memory allocation failed
//return STD_SUCCESS if success
StudentResult addRequest(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	StudentResult result = addToMyRequest(student1, student2);
	if (result == STD_OUT_OF_MEMORY) {
		return result;
	}
	result = addToRequestToME(student2, student1);
	if (result == STD_OUT_OF_MEMORY) {
		return result;
	}
	return STD_SUCCESS;
}

static bool checkIfRightStudentIdIsInMyRequestOfLeftStudent(Student student1,
	Student student2) {
	assert(student1);
	assert(student2);
	long int id2 = getId(student2);
	long int *id2_p = &id2;
	bool result = setIsIn(student1->my_request, id2_p);
	return result;
}

static bool checkIfRightStudenIdIsInRequestToMeOfLeftStudent(Student student1,
	Student student2) {
	assert(student1);
	assert(student2);
	long int id2 = getId(student2);
	long int *id2_p = &id2;
	bool result = setIsIn(student1->request_to_me, id2_p);
	return result;
}

//check if there is allready the id of student 2 in my_request of student 1
//and assert that there is allready the id of student 1 in
//request to me student2
//checkIfRightStudentAllredyRequestLeftStudent
StudentResult checkIfAllreadyRequested(Student student1, Student student2) {
	bool result = checkIfRightStudentIdIsInMyRequestOfLeftStudent(student1,
		student2);
	bool result2 = checkIfRightStudenIdIsInRequestToMeOfLeftStudent(student2,
		student1);
	if (result == true) {
		assert(result2 == true);
		if (result2 == true) { // get over not used variable
			return STD_ALREADY_REQUESTED;
		}
	}
	assert(result2 == false);
	return STD_NOT_REQUESTED;
}

//remove student 2 from my request  of student1
StudentResult static removeFromMyRequest(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	long int id2 = getId(student2);
	long int *id2_p = &id2;
	SetResult result = setRemove(student1->my_request, id2_p);
	if (result == SET_ITEM_DOES_NOT_EXIST) {
		return STD_NOT_IN_MY_REQUEST;
	}
	return STD_SUCCESS;
}

//remove student 2 from request to me of student1
StudentResult static removeFromRequestToMe(Student student1,
	Student student2) {
	assert(student1);
	assert(student2);
	long int id2 = getId(student2);
	long int *id2_p = &id2;
	SetResult result = setRemove(student1->request_to_me, id2_p);
	if (result == SET_ITEM_DOES_NOT_EXIST) {
		return STD_NOT_IN_MY_REQUEST;
	}
	return	STD_SUCCESS;
}

//remove student 2 from my request of student 1  removeFromMyRequest
//remove student 1 from request to me of student 2 removeFromRequestToMe
StudentResult removeRequest(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	if (checkIfAllreadyRequested(student1, student2) == STD_NOT_REQUESTED) {
		return STD_NOT_REQUESTED;
	}
	removeFromMyRequest(student1, student2);
	removeFromRequestToMe(student2, student1);
	return STD_SUCCESS;
}

static StudentResult removeRightFromFriendsOfLeftStudent(Student student1,
	Student student2) {
	assert(student1);
	assert(student2);
	assert(student1->friends);
	long int id2 = getId(student2);
	long int * id2_p = &id2;
	SetResult result = setRemove(student1->friends, id2_p);
	if (result == SET_ITEM_DOES_NOT_EXIST) {
		return STD_ARE_NOT_FRIENDS;
	}
	return STD_SUCCESS;
}

//removes student1 from beeing a friend of student 2 and oposite
//remove student1 id from student 2 friends set
//remove student2 id from student 1 friend set
StudentResult removeFriend(Student student1, Student student2) {
	assert(student1);
	assert(student2);
	if (checkIfStudentAllreadyFriends(student1, student2) ==
		STD_ARE_NOT_FRIENDS) {
		return STD_ARE_NOT_FRIENDS;
	}
	removeRightFromFriendsOfLeftStudent(student1, student2);
	removeRightFromFriendsOfLeftStudent(student2, student1);
	return STD_SUCCESS;
}

bool addGradeToStudent(Student student, int semesterId,
	long int course_id, char* points, int grade) {
	//return 0 if fail, return 1 is success //new
	//check if we have semester if yes we add grade
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		if (getSemesterId(semesterIterator) == semesterId) {
			return addGrade(semesterIterator, course_id, points, grade);
		}
	}
	//insert new semester
	int result = addSemesterToStudent(student, semesterId);
	if (result == 0) {
		return 0;
	}
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		if (getSemesterId(semesterIterator) == semesterId) {
			return addGrade(semesterIterator, course_id, points, grade);
		}
	}
	return 0;
}

//return 0 if fail, return 1 is success
int addSemesterToStudent(Student student, int semesterId) {
	Semester new_semester = createSemester(semesterId);
	if (new_semester == NULL) {
		return 0;
	}
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		if (getSemesterId(semesterIterator) > semesterId) {
			ListResult result = listInsertBeforeCurrent(student->semesteres,
				(ListElement)new_semester);
			destroySemester(new_semester);
			if (result == LIST_SUCCESS) {
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	//the new semester is the bigest
	ListResult result = listInsertLast(student->semesteres,
		(ListElement)new_semester);
	destroySemester(new_semester);
	if (result == LIST_SUCCESS) {
		return 1;
	}
	else
	{
		return 0;
	}
}

void printStudent(Student student, FILE* output_channel) {
	mtmPrintStudentInfo(output_channel, student->id, student->first_name,
		student->last_name);
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		printSemester(semesterIterator, output_channel);
	}
	mtmPrintSummary(output_channel, totalPointsCoursesX2(student),
		failedPointsCoursesX2(student),
		effectivePointsCoursesX2(student), effectiveGradesCoursesX2(student));
	return;
}

//return 1 if course found 0 if not
int removeGradeFromeStudent(Student student, int semester,
	long int course_id) {
	assert(student != NULL);
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		if (getSemesterId(semesterIterator) == semester) {

			return removeGrade(semesterIterator, course_id);
		}
	}
	return 0;
}
Semester findSemesterByIndexInList(List semesterList, int index) {
	Semester tmp = (Semester)listGetFirst(semesterList);
	for (int i = 0; i < index - 1; i++) {
		tmp = (Semester)listGetNext(semesterList);
	}
	return tmp;
}
int findAndChangeLastSemesterCourseGrade(Student student,
	long int course_id, int new_grade) {
	int index = listGetSize(student->semesteres);
	int result = 0;
	for (int i = index; i >0; i--) {//go over the semesters list from the end
		Semester tmp = findSemesterByIndexInList(student->semesteres, i);
		result = findCourseLastGradeAndChange(tmp, course_id, new_grade);
		if (result == 1) {//found course grade in this semester
			return 1;
		}
	}
	return 0;
}
int totalPointsCoursesX2(Student student) {
	int sum = 0;
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		sum += totalPointsX2(semesterIterator);
	}
	return sum;
}

int failedPointsCoursesX2(Student student) {
	int sum = 0;
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		sum += failedPointsX2(semesterIterator);
	}
	return sum;
}

int effectivePointsCoursesX2(Student student) {
	int i = 0, j = 0, sum_points = 0;
	int* size_of_array = &i;
	int* current_index = &j;
	long int *course_id_array = arraySizeOfGradeOfStudent(student,
		size_of_array);
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		sum_points += effectivePointsOfSemesterArrayOfCourses(semesterIterator,
			course_id_array, current_index);
	}
	free(course_id_array);
	return sum_points;

}

long int *arraySizeOfGradeOfStudent(Student student, int* size) {
	LIST_FOREACH(Semester, semesterIterator, student->semesteres) {
		*(size) += sizeOfGradeInSemester(semesterIterator);
	}
	long int *array = malloc(sizeof(*array)*(*size));
	return array;

}

int effectiveGradesCoursesX2(Student student) {
	int i = 0, j = 0, sum_points = 0;
	int* size_of_array = &i;
	int* current_index = &j;
	long int *course_id_array = arraySizeOfGradeOfStudent(student,
		size_of_array);
	List tmp = listCreate(copySemesterElement, freeSemesterElement);
	LIST_FOREACH(Semester, iterator, student->semesteres) {
		listInsertFirst(tmp, (ListElement)iterator);
	}
	LIST_FOREACH(Semester, semesterIterator, tmp) {
		sum_points += effectiveGradesSemesterArrayOfCourses(semesterIterator,
			course_id_array, current_index);
	}
	listDestroy(tmp);
	free(course_id_array);
	return sum_points;
}

int printStudentClean(Student student, FILE* output_channel) {
	mtmPrintStudentInfo(output_channel, student->id, student->first_name,
		student->last_name);
	effectiveGradesCoursesCleanX2(student, output_channel);
	return 1;
}

static SetElement copyInformationElement(SetElement element) {
	return (SetElement)copyArray((information)element);
}

static void freeInformationElement(SetElement element) {
	freeArray((information)element);
	return;
}

static int comperInformationElement(SetElement element1, SetElement element2) {
	return comperArray((information)element1, (information)element2);
}

static int comperGradeInformationElement(SetElement element1,
	SetElement element2) {
	return comperArrayByGrade((information)element1, (information)element2);
}

static int comperGradeWorstInformationElement(SetElement element1,
	SetElement element2) {
	return comperArrayByGradeWorst((information)element1,
		(information)element2);
}

int effectiveGradesCoursesCleanX2(Student student, FILE* output_channel) {
	int i = 0, j = 0, k = 0, sum_of_points_grade = 0;
	int *sum_of_points = &k;
	int* size_of_array = &i;
	int* current_index = &j;
	long int *course_id_array = arraySizeOfGradeOfStudent(student,
		size_of_array);
	Set information_set = setCreate(copyInformationElement,
		freeInformationElement, comperInformationElement);
	List tmp = listCreate(copySemesterElement, freeSemesterElement);
	LIST_FOREACH(Semester, iterator, student->semesteres) {
		listInsertFirst(tmp, (ListElement)iterator);
	}
	LIST_FOREACH(Semester, semesterIterator, tmp) {

		sum_of_points_grade += GradesOfSemesterClean(semesterIterator,
			course_id_array, current_index, output_channel,
			sum_of_points, information_set);
	}
	SET_FOREACH(information, iterator, information_set) {
		int sigal = setGetSize(information_set); // ---
		mtmPrintGradeInfo(output_channel, getCourse(iterator),
			getPoints(iterator), getGadeInformation(iterator));
	}
	mtmPrintCleanSummary(output_channel, *sum_of_points, sum_of_points_grade);
	listDestroy(tmp);
	free(course_id_array);
	setDestroy(information_set);
	return *sum_of_points;
}
void printStudentBest(Student student, FILE* output_channel, int amount) {
	int i = 0, j = 0, k = 0, sum_of_points_grade = 0;
	int *sum_of_points = &k;
	int* size_of_array = &i;
	int* current_index = &j;
	long int *course_id_array = arraySizeOfGradeOfStudent(student,
		size_of_array);
	Set information_set = setCreate(copyInformationElement,
		freeInformationElement, comperGradeInformationElement);
	List tmp = listCreate(copySemesterElement, freeSemesterElement);
	LIST_FOREACH(Semester, iterator, student->semesteres) {
		listInsertFirst(tmp, (ListElement)iterator);
	}
	LIST_FOREACH(Semester, semesterIterator, tmp) {
		sum_of_points_grade += GradesOfSemesterClean(semesterIterator,
			course_id_array, current_index, output_channel, sum_of_points,
			information_set);
	}
	SET_FOREACH(information, iterator, information_set) {
		if (amount == 0) {
			break;
		}
		mtmPrintGradeInfo(output_channel, getCourse(iterator),
			getPoints(iterator), getGadeInformation(iterator));
		amount--;
	}
	listDestroy(tmp);
	free(course_id_array);
	setDestroy(information_set);
	return;
}

void printStudentWorst(Student student, FILE* output_channel, int amount) {
	int i = 0, j = 0, k = 0, sum_of_points_grade = 0;
	int *sum_of_points = &k;
	int* size_of_array = &i;
	int* current_index = &j;
	long int *course_id_array = arraySizeOfGradeOfStudent(student,
		size_of_array);
	Set information_set = setCreate(copyInformationElement,
		freeInformationElement, comperGradeWorstInformationElement);
	List tmp = listCreate(copySemesterElement, freeSemesterElement);
	LIST_FOREACH(Semester, iterator, student->semesteres) {
		listInsertFirst(tmp, (ListElement)iterator);
	}
	LIST_FOREACH(Semester, semesterIterator, tmp) {
		sum_of_points_grade += GradesOfSemesterClean(semesterIterator,
			course_id_array, current_index, output_channel, sum_of_points,
			information_set);
	}
	SET_FOREACH(information, iterator, information_set) {
		if (amount == 0) {
			break;
		}
		mtmPrintGradeInfo(output_channel, getCourse(iterator),
			getPoints(iterator), getGadeInformation(iterator));
		amount--;
	}
	listDestroy(tmp);
	free(course_id_array);
	setDestroy(information_set);
	return;
}

char *getStudentFirst(Student student) {
	return student->first_name;
}

char* getStudentLast(Student student) {
	return student->last_name;
}

//return grade
int findStudentBestGradeInCourse(long int course_id,
	Student student_iterator) {
	int curent_grade = 0;
	if (student_iterator == NULL) {
		return 0;
	}
	LIST_FOREACH(Semester, iterator, student_iterator->semesteres) {
		int grade = findBestGradeCourseInSemester(iterator, course_id);
		if (grade > curent_grade) {
			curent_grade = grade;
		}
	}
	return curent_grade;
}

int searchForGradeInCourseSemester(Student student, long int course_id) {
	int result = 0;
	LIST_FOREACH(Semester, iterator, student->semesteres) {
		result = searchForGradeInCourseGrade(iterator, course_id);
		if (result == 1) {
			return 1;
		}
	}
	return result;
}
Set newFriendSet(Student student_logged_in) {
	return student_logged_in->friends;
}