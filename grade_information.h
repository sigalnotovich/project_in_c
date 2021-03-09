#ifndef INFORMATION
#define INFORMATION

typedef struct information_s *information;

information creatArray(long int course_id, int points, int grade,
	int semester);

information copyArray(information array);

void freeArray(information array);

int comperArray(information array1, information array2);


long int getCourse(information information);

int getSemester(information information);

int getGadeInformation(information information);

int getPoints(information information);

int comperArrayByGrade(information array1, information array2);

int comperArrayByGradeWorst(information array1, information array2);

#endif // !INFORMATION