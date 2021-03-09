#include "list.h"
#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>   
#include "course_manager.h"
#include "mtm_ex3.h"
MtmErrorCode switchErrorName(CourseManagerResult manager_result) {
	MtmErrorCode mtm_result;
	switch (manager_result) {
	case MNG_STUDENT_ALREADY_EXISTS:
		mtm_result = MTM_STUDENT_ALREADY_EXISTS;
		break;
	case MNG_INVALID_PARAMETERS:
		mtm_result = MTM_INVALID_PARAMETERS;
		break;
	case MNG_STUDENT_DOES_NOT_EXIST:
		mtm_result = MTM_STUDENT_DOES_NOT_EXIST;
		break;
	case MNG_ALREADY_LOGGED_IN:
		mtm_result = MTM_ALREADY_LOGGED_IN;
		break;
	case MNG_NOT_LOGGED_IN:
		mtm_result = MTM_NOT_LOGGED_IN;
		break;
	case MNG_ALREADY_FRIEND:
		mtm_result = MTM_ALREADY_FRIEND;
		break;
	case MNG_NOT_REQUESTED:
		mtm_result = MTM_NOT_REQUESTED;
		break;
	case MNG_NOT_FRIEND:
		mtm_result = MTM_NOT_FRIEND;
		break;
	case MNG_ALREADY_REQUESTED:
		mtm_result = MTM_ALREADY_REQUESTED;
		break;
	case MNG_OUT_OF_MEMORY:
		mtm_result = MTM_OUT_OF_MEMORY;
		break;
	case MNG_COURSE_DOES_NOT_EXIST:
		mtm_result = MTM_COURSE_DOES_NOT_EXIST;
		break;
	case MNG_SUCCESS:
		break;
	}
	return mtm_result;
}
//id is long int and can be less then 1000000000 (miliard)
//convert a word to long int format
long int convertFromCharToInt(char* word) {
	int lenght = strlen(word);
	int digit = -1;
	int sign = 1;
	long int number = 0;
	int i = 0;
	if (word[0] == '-') {
		sign = -1;
		i = 1;
	}
	while (i < lenght) {
		switch (word[i]) {
		case '0':
			digit = 0;
			break;
		case '1':
			digit = 1;
			break;
		case '2':
			digit = 2;
			break;
		case '3':
			digit = 3;
			break;
		case '4':
			digit = 4;
			break;
		case '5':
			digit = 5;
			break;
		case '6':
			digit = 6;
			break;
		case '7':
			digit = 7;
			break;
		case '8':
			digit = 8;
			break;
		case '9':
			digit = 9;
			break;
		}
		number = number * 10 + digit;
		i++;
		//number = number + digit * pow(10, lenght - i - 1);
	}
	number = number * sign;
	return number;
}

void findStudentFunction(char** array, course_manager manager) {
	CourseManagerResult mng_result;
	if (strcmp(array[1], "add") == 0) {
		mng_result = studentAdd(convertFromCharToInt(array[2]),
			array[3], array[4], manager);
	}
	if (strcmp(array[1], "remove") == 0) {
		mng_result = studentRemove(convertFromCharToInt(array[2]), manager);
	}
	if (strcmp(array[1], "login") == 0) {
		mng_result = studentLogin(convertFromCharToInt(array[2]), manager);
	}
	if (strcmp(array[1], "logout") == 0) {
		mng_result = studentLogout(manager);
	}
	if (strcmp(array[1], "friend_request") == 0) {
		mng_result = studentFriendRequest(convertFromCharToInt(array[2]),
			manager);
	}
	if (strcmp(array[1], "handle_request") == 0) {
		mng_result = studentHandleRequest(convertFromCharToInt(array[2]),
			array[3], manager);
	}
	if (strcmp(array[1], "unfriend") == 0) {
		mng_result = studentUnfriend(convertFromCharToInt(array[2]), manager);
	}
	//print error message:
	if (mng_result != MNG_SUCCESS) {
		MtmErrorCode mtm_result = switchErrorName(mng_result);
		mtmPrintErrorMessage(stderr, mtm_result);
	}
	return;
}

void findGradeFunction(char** array, course_manager manager) {
	CourseManagerResult mng_result;
	if (strcmp(array[1], "add") == 0) {
		mng_result = gradeSheetAdd(convertFromCharToInt(array[2]),
			convertFromCharToInt(array[3]),
			array[4], convertFromCharToInt(array[5]), manager);
	}
	if (strcmp(array[1], "remove") == 0) {
		mng_result = gradeSheetRemove(convertFromCharToInt(array[2]),
			convertFromCharToInt(array[3]), manager);
	}
	if (strcmp(array[1], "update") == 0) {
		mng_result = gradeSheetUpdate(convertFromCharToInt(array[2]),
			convertFromCharToInt(array[3]), manager);
	}
	//print error message:
	if (mng_result != MNG_SUCCESS) {
		MtmErrorCode mtm_result = switchErrorName(mng_result);
		mtmPrintErrorMessage(stderr, mtm_result);
	}
	return;
}

void findReportFunction(char** array, course_manager manager, FILE* input,
	FILE* output) {
	CourseManagerResult mng_result;
	if (strcmp(array[1], "full") == 0) {
		mng_result = reportFull(manager, output);
	}
	if (strcmp(array[1], "clean") == 0) {
		mng_result = reportClean(manager, output);
	}
	if (strcmp(array[1], "best") == 0) {
		mng_result = reportBest(convertFromCharToInt(array[2]),
			manager, output);
	}
	if (strcmp(array[1], "worst") == 0) {
		mng_result = reportWorst(convertFromCharToInt(array[2]),
			manager, output);
	}
	if (strcmp(array[1], "reference") == 0) {
		mng_result = reportReference(convertFromCharToInt(array[2]),
			convertFromCharToInt(array[3]), manager, output);
	}
	if (strcmp(array[1], "faculty_request") == 0) {
		mng_result = reportFacultyRequest(convertFromCharToInt(array[2]),
			array[3], manager, output);
	}
	//print error message:
	if (mng_result != MNG_SUCCESS) {
		MtmErrorCode mtm_result = switchErrorName(mng_result);
		mtmPrintErrorMessage(stderr, mtm_result);
	}
	return;
}

void findFunction(char** array, course_manager manager,
	FILE* input, FILE* output) {
	if (strcmp(array[0], "student") == 0) {
		findStudentFunction(array, manager);
	}
	else {
		if (strcmp(array[0], "grade_sheet") == 0) {
			findGradeFunction(array, manager);
		}
		else {// "report"
			findReportFunction(array, manager, input, output);
		}
	}
	return;
}

//this function remove all spaces in the  line
char* copyStringWithNoSpaces(char* string) {
	char last_one = 'z';
	int j = 0;
	char* new_string = malloc(strlen(string) + 1);
	int len = strlen(string);
	for (int i = 0; i < len - 1; i++) {
		char current = string[i];
		if ((j == 0) && (current == ' ')) {//first space
			continue;
		}
		if ((last_one == ' ') && (current == ' ')) {//middle space
			last_one = current;
			continue;
		}
		else {
			new_string[j] = current;
			j++;
			last_one = current;
		}
	}
	new_string[j] = '\0';
	return new_string;
}


int findNumberOfWord(char* string) {
	int count = 1;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == ' ') {
			count++;
		}
	}
	return count;
}
void destroyStringArray(char** new_string, int number_of_word) {
	for (int i = 0; i < number_of_word; i++) {
		free(new_string[i]);
	}
	free(new_string);
	return;
}
//turn a line into array of words
char** castStringToStringArray(char* string) {
	int index_word = 0, index_line = 0;
	char word[MAX_LEN] = "";
	int number_of_word = findNumberOfWord(string);
	char** new_string = malloc(sizeof(*new_string)*number_of_word);
	if (new_string == NULL) {
		return NULL;
	}
	//this loop go over each char in string and when we arrived	
	//the end of a word we allocat place for if in char** new_string
	for (int i = 0; i < strlen(string) + 1; i++) {
		if (string[i] == '\0') {
			word[index_word] = '\0';
			new_string[index_line] = malloc(sizeof(char)*(strlen(word) + 1));
			if (new_string[index_line] == NULL) {
				return NULL;
			}
			//we copy a word to new_string- end of line
			strcpy(new_string[index_line], word);
			break;
		}
		if (string[i] != ' ') {
			word[index_word] = string[i];
			index_word++;
		}
		else {
			word[index_word] = '\0';
			new_string[index_line] = malloc(sizeof(char)*(strlen(word) + 1));
			if (new_string[index_line] == NULL) {
				return NULL;
			}
			//we copy a word to new_string- we arrived char space
			strcpy(new_string[index_line], word);
			index_line++;
			for (int i = 0; i < index_word + 1; i++) {
				word[i] = 0;
			}
			index_word = 0;
		}
	}
	free(string);
	return new_string;
}

//get file and read line ny line
//each line will turn into array of words
void readFile(FILE* input, FILE* output) {
	char line[MAX_LEN] = "";
	course_manager manager = createCourseManager();
	while (fgets(line, MAX_LEN, input) != NULL) {
		char * new_line = copyStringWithNoSpaces(line);
		if (new_line == NULL) {
			mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
			return;
		}
		if (new_line[0] == '#' || strlen(new_line) == 1 ||
			strlen(new_line) == 0) {
			free(new_line);
			continue;
		}
		int number_of_word = findNumberOfWord(new_line);
		char** array = castStringToStringArray(new_line);

		//here we need to call a function to encode
		findFunction(array, manager, input, output);
		destroyStringArray(array, number_of_word);
	}
	destroyCourseManager(manager);
}

int main(int argc, char** argv) {
	FILE* input;
	FILE* output;
	// check the case we have 2 parameters
	if (argc == 3) {
		if (strcmp(argv[1], "-i") == 0) {
			//we have input file
			input = fopen(argv[2], "r");
			if (!input) {
				mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
				return 0;
			}
			output = stdout;
			readFile(input, output);
			fclose(input);
			fclose(output);
		}
		else {
			if (strcmp(argv[1], "-o") == 0) {
				//we have output file
				output = fopen(argv[2], "w");
				if (!output) {
					mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
					return 0;
				}
				input = stdin;
				readFile(input, output);
				fclose(input);
				fclose(output);
			}
			else {
				mtmPrintErrorMessage(stderr,
					MTM_INVALID_COMMAND_LINE_PARAMETERS);
				return 0;
			}
		}
	}
	else {
		//check if we  have 4 parameters
		if (argc == 5) {
			if (strcmp(argv[1], "i") == 0 && strcmp(argv[3], "o") == 0) { //changed

				//input = fopen(argv[2], "r");
				input = fopen("C:\\Users\\sigal\\files\\test1.txt", "r");
				if (!input) {
					mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
					return 0;
				}
				//output = fopen(argv[4], "w");
				output = fopen("C:\\Users\\sigal\\files\\tempout.txt", "w");
				if (!output) {
					mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
					return 0;
				}
				readFile(input, output);
				fclose(input);
				fclose(output);
			}
			else {
				if (strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0) {

					input = fopen(argv[4], "r");
					if (!input) {
						mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
						return 0;
					}
					output = fopen(argv[2], "w");
					if (!output) {
						mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
						return 0;
					}
					readFile(input, output);
					fclose(input);
					fclose(output);
				}
				else {
					mtmPrintErrorMessage(stderr,
						MTM_INVALID_COMMAND_LINE_PARAMETERS);
					return 0;
				}
			}
		}
		else {
			if (argc == 1) {
				output = stdout;
				input = stdin;
				readFile(input, output);
				fclose(input);
				fclose(output);
			}
			else {
				mtmPrintErrorMessage(stderr,
					MTM_INVALID_COMMAND_LINE_PARAMETERS);
				return 0;
			}
		}

	}
	return 0;
}