// GetAverage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#define INCORRECTFILE 1
#define BLANKFILE 2
#define BAD 1
#define MIDDLE 2
#define GOOD 3
#define EXCELENT 4
#define NAMELENGTH 50
typedef struct _Student
{
	char Name[NAMELENGTH];
	char Family[NAMELENGTH];
	float grade;
}Student;
int EnterGradesOfStudents();
int ComputeAverageOfStudents();
float ComputeAverage(float* grades, int gradesCount);
void PrintGrades(Student* students, int studentCount);
void ReadGradesFromRecords(Student* students, float* grades, int gradesCount);
int _tmain(int argc, _TCHAR* argv[])
{
	while(true)
	{
		int todo = -1;
		printf("\n\n\nif you want to enter grades please enter 1\n");
		printf("else if you want to compute average please enter 2\n");
		printf("else to exit please enter 0\n");
		scanf("%d", &todo);
		switch(todo)
		{
		case 1 : EnterGradesOfStudents();
			break;
		case 2 : ComputeAverageOfStudents();
			break;
		default :
			break;
		}
	}
	return 0;
}
int EnterGradesOfStudents()
{
	int studentCount = 0;
	Student students = {};
	printf("\nPlease Enter Number Of Student\n");
	scanf("%d", &studentCount);
	printf("\nPlease Enter Path of output file\n");
	char filePath [256];
	
	scanf("%s", filePath);
	FILE* file = fopen((const char*)filePath, "a");
	if(file)
	{
		fwrite(&studentCount, sizeof(int), 1, file);
		printf("\nPlease, First Enter Name then Family and finally enter grade of each Student:\n");
		for(int i = 0; i < studentCount; i++)
		{
			printf("\nName:");
			scanf("%s", students.Name);
			printf("\tFamily:");
			scanf("%s", students.Family);
			printf("\tGrade:");
			scanf("%f", &students.grade);
			fwrite(&students, sizeof(Student), 1, file);
		}
		fclose(file);
	}
	else
	{
		printf("\noutput file path is incorrect or this file is using by another program\n");
		return -1;
	}
	printf("\nTo Continue press any key");
	getchar();
	return 0;
}
int ComputeAverageOfStudents()
{
	char filePath [256];
	printf("please, enter address of input file as grades file\n");
	scanf("%s", filePath);
	FILE* file = fopen((const char*)filePath, "r");
	if(file)
	{
		Student* students = NULL;
		float *grades = NULL;
		int studentCount = 0;
		int gradesCount = 0;
		fread(&studentCount, sizeof(int), 1, file);
		gradesCount = studentCount;
		if(studentCount)
		{
			grades = (float*)malloc(sizeof(float) * gradesCount);
			students = (Student*)malloc(sizeof(Student) * studentCount);
			fread(students, sizeof(Student), gradesCount, file);
			PrintGrades(students, studentCount);
			ReadGradesFromRecords(students,grades, gradesCount);
			float average = ComputeAverage(grades, gradesCount);
			int level = -1;
			if(average < 10)
			{
				level = BAD;
			}
			else if(average < 15)
			{
				level = MIDDLE;
			}
			else if(average < 17)
			{
				level = GOOD;
			}
			else
			{
				level = EXCELENT;
			}
			switch(level)
			{
				case BAD: 
					printf("\n average of whole of students is : %f\n then level of this class is Bad\n", average);
					break;
				case MIDDLE: 
					printf("\n average of whole of students is : %f\n then level of this class is Middle\n", average);
					break;
				case GOOD:
					printf("\n average of whole of students is : %f\n then level of this class is Good\n", average);
					break;
				default:
					printf("\n average of whole of students is : %f\n then level of this class is Excelent\n", average);

			}

			fclose(file);
			free(students);
			free(grades);
		}
		else
		{
			printf("\nnumber of grades is zero, please try a gaint for a true file");
			fclose(file);
			return BLANKFILE;
		}
	}
	else
	{
		printf("\ninput file is incorrect or is not exist\n");
		getchar();
		return INCORRECTFILE;
	}
	printf("\nTo Continue press any key");
	getchar();
	return 0;
}
void ReadGradesFromRecords(Student* students, float* grades, int gradesCount)
{	
	for(int i = 0; i < gradesCount; i++)
	{
		grades[i] = students[i].grade;		
	}
}
void PrintGrades(Student* students, int studentCount)
{
	printf("\nGrades of Strudent are:\n");
	for(int i = 0; i < studentCount; i++)
	{
		printf("\nName: %s", students->Name);
		printf("\t\tFamily: %s", students->Family);
		printf("\t\tGrade: %f", students->grade);
		students++;
	}
}
float ComputeAverage(float* grades, int gradesCount)
{
	float sum = 0;
	for(int i = 0; i < gradesCount; i++)
	{
		sum += *grades;
		grades++;
	}
	return sum / gradesCount;
}
