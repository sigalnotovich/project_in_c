#ifndef GRADE
#define GRADE

typedef struct grade_s *Grade;

Grade createGrade(int grade_number, long int course_id, char* points);

void destroyGrade(Grade grade);

Grade copyGrade(Grade grade);

void printGrade(Grade grade);

long int getCourseId(Grade grade);

void changeGradeNumber(Grade grade, int new_grade);

int multiplyPoints(Grade grade);

int checkPointsParameter(char* points);

int getGrade(Grade grade);

#endif // !GRADE
