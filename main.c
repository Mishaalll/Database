#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

struct birthdate 
{
    int day;
    int month;
    int year;
};

struct myData 
{
    int age;
    char *name;
    int year;
    char course[10];
    struct birthdate bdate;
};

#define MAX_STUDENTS 100
struct myData database[MAX_STUDENTS];
int total_students = 0;

int main(int argc, char *argv[]) 
{
    FILE *fp = fopen("database.txt", "r");
    if (fp) 
    {
        total_students = 0;
        while (total_students < MAX_STUDENTS) 
        {
            database[total_students].name = malloc(50);
            int res = fscanf(fp, "%d %49s %d %9s %d %d %d",
                &database[total_students].age,
                database[total_students].name,
                &database[total_students].year,
                database[total_students].course,
                &database[total_students].bdate.day,
                &database[total_students].bdate.month,
                &database[total_students].bdate.year);
            if (res != 7) break;
            total_students++;
        }
        fclose(fp);
    }

    if (argc >= 2) 
    {
        if (mystrcmp(argv[1], "add") == 0 && argc == 9) 
        {
            if (total_students >= MAX_STUDENTS) 
            {
                printf("Database full.\n");
                goto save;
            }

            int age = atoi(argv[2]);
            char *name = argv[3];
            int year = atoi(argv[4]);
            char *course = argv[5];
            int day = atoi(argv[6]);
            int month = atoi(argv[7]);
            int byear = atoi(argv[8]);

            database[total_students].age = age;
            database[total_students].name = malloc(50);
            mystrcpy(database[total_students].name, name);
            mystrcpy(database[total_students].course, course);
            database[total_students].year = year;
            database[total_students].bdate.day = day;
            database[total_students].bdate.month = month;
            database[total_students].bdate.year = byear;
            total_students++;
        } 
        else if (mystrcmp(argv[1], "del") == 0 && argc == 3) 
        {
            char *name = argv[2];
            for (int i = 0; i < total_students; i++) 
            {
                if (mystrcmp(database[i].name, name) == 0) 
                {
                    free(database[i].name);
                    for (int j = i; j < total_students - 1; j++)
                        database[j] = database[j + 1];
                    total_students--;
                    break;
                }
            }
        }
        else if (mystrcmp(argv[1], "help") == 0)
        {
            printf("Available commands:\n");
            printf("  help                     - show this help message\n");
            printf("  add [AGE NAME YEAR COURSE DAY MONTH BYEAR] - add a new student\n");
            printf("  del [NAME]               - delete a student by name\n");
            printf("  sort_age                 - sort students by age\n");
        }
        else if (mystrcmp(argv[1], "sort_age") == 0) 
        {
            for (int i = 0; i < total_students; i++) 
            {
                for (int j = i + 1; j < total_students; j++) 
                {
                    if (database[i].age > database[j].age) 
                    {
                        struct myData temp = database[i];
                        database[i] = database[j];
                        database[j] = temp;
                    }
                }
            }
        } 
        else 
        {
            printf("Unknown command. Use 'help'.\n");
        }
    }

save:
    fp = fopen("database.txt", "w");
    if (!fp) 
    {
        printf("Cannot open file for writing.\n");
        return 1;
    }

    for (int i = 0; i < total_students; i++) 
    {
        fprintf(fp, "%d %s %d %s %d %d %d\n",
            database[i].age,
            database[i].name,
            database[i].year,
            database[i].course,
            database[i].bdate.day,
            database[i].bdate.month,
            database[i].bdate.year);
    }
    fclose(fp);

    for (int i = 0; i < total_students; i++)
        free(database[i].name);

    return 0;
}
