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

int main(int argc, char *argv[]) 
{
    struct myData *database = NULL;
    int total_students = 0;

    printf("Commands:\n");
    printf("add [AGE NAME YEAR COURSE DAY MONTH BYEAR]\n");
    printf("del [NAME]\n");
    printf("sort_age\n");
    printf("sort_name\n");
    printf("sort_birthyear\n");
    printf("sort_course\n");
    printf("help\n");


    FILE *fp = fopen("database.txt", "r");
    if (fp) 
    {
        while (1) 
        {
            int age, year, day, month, byear;
            char tempname[50], course[10];
            int res = fscanf(fp, "%d %49s %d %9s %d %d %d",
                &age, tempname, &year, course, &day, &month, &byear);
            if (res != 7) break;

            struct myData *new_db = malloc((total_students + 1) * sizeof(struct myData));
            for (int i = 0; i < total_students; i++) new_db[i] = database[i];
            free(database);
            database = new_db;

            int len = mystrlen(tempname) + 1;
            database[total_students].name = malloc(len);
            mystrcpy(database[total_students].name, tempname);
            mystrcpy(database[total_students].course, course);
            database[total_students].age = age;
            database[total_students].year = year;
            database[total_students].bdate.day = day;
            database[total_students].bdate.month = month;
            database[total_students].bdate.year = byear;

            total_students++;
        }
        fclose(fp);
    }

    printf("\ndatabase:\n");
    for (int i = 0; i < total_students; i++)
    {
        printf("%d %s %d %s %d %d %d\n",
            database[i].age,
            database[i].name,
            database[i].year,
            database[i].course,
            database[i].bdate.day,
            database[i].bdate.month,
            database[i].bdate.year);
    }
    printf("\n");

    if (argc >= 2) 
    {
        if (mystrcmp(argv[1], "add") == 0 && argc == 9) 
        {
            struct myData *new_db = malloc((total_students + 1) * sizeof(struct myData));
            for (int i = 0; i < total_students; i++) new_db[i] = database[i];
            free(database);
            database = new_db;

            database[total_students].age = myatoi(argv[2]);
            database[total_students].name = malloc(mystrlen(argv[3]) + 1);
            mystrcpy(database[total_students].name, argv[3]);
            database[total_students].year = myatoi(argv[4]);
            mystrcpy(database[total_students].course, argv[5]);
            database[total_students].bdate.day = myatoi(argv[6]);
            database[total_students].bdate.month = myatoi(argv[7]);
            database[total_students].bdate.year = myatoi(argv[8]);
            total_students++;

            printf("Student added:\n");
            for (int i = 0; i < total_students; i++)
            {
                printf("%d %s %d %s %d %d %d\n",
                    database[i].age,
                    database[i].name,
                    database[i].year,
                    database[i].course,
                    database[i].bdate.day,
                    database[i].bdate.month,
                    database[i].bdate.year);
            }
            printf("\n");
        }
        else if (mystrcmp(argv[1], "del") == 0 && argc == 3) 
        {
            char *name = argv[2];
            int found = 0;
            for (int i = 0; i < total_students; i++) {
                if (mystrcmp(database[i].name, name) == 0) 
                {
                    free(database[i].name);
                    for (int j = i; j < total_students - 1; j++)
                    {
                        database[j] = database[j + 1];
                    }
                    total_students--;
                    found = 1;
                    printf("Deleted %s.\n", name);
                    for (int i = 0; i < total_students; i++)
                    {
                        printf("%d %s %d %s %d %d %d\n",
                            database[i].age,
                            database[i].name,
                            database[i].year,
                            database[i].course,
                            database[i].bdate.day,
                            database[i].bdate.month,
                            database[i].bdate.year);
                    }
                    printf("\n");

                    break;
                }
            }
            if (!found) 
            {
                printf("Not found.\n");
            }
        }
        else if (mystrcmp(argv[1], "sort_age") == 0) 
        {
            for (int i = 0; i < total_students; i++)
            {
                for (int j = i + 1; j < total_students; j++)
                {
                    if (database[i].age > database[j].age) 
                    {
                        struct myData tmp = database[i];
                        database[i] = database[j];
                        database[j] = tmp;
                    }
                }
            }    
            printf("Sorted by age:\n");
            for (int i = 0; i < total_students; i++)
            {
                printf("%d %s %d %s %d %d %d\n",
                    database[i].age,
                    database[i].name,
                    database[i].year,
                    database[i].course,
                    database[i].bdate.day,
                    database[i].bdate.month,
                    database[i].bdate.year);
            }
            printf("\n");
        }

        else if (mystrcmp(argv[1], "sort_name") == 0)
        {
            for (int i = 0; i < total_students; i++)
            {    for (int j = i + 1; j < total_students; j++)
                {
                    if (mystrcmp(database[i].name, database[j].name) > 0)
                    {
                        struct myData tmp = database[i];
                        database[i] = database[j];
                        database[j] = tmp;
            }   }   }
            printf("Sorted by name:\n");
            for (int i = 0; i < total_students; i++)
            {
                printf("%d %s %d %s %d %d %d\n",
                    database[i].age,
                    database[i].name,
                    database[i].year,
                    database[i].course,
                    database[i].bdate.day,
                    database[i].bdate.month,
                    database[i].bdate.year);
            }
            printf("\n");

        }

        else if (mystrcmp(argv[1], "sort_birthyear") == 0)
        {
            for (int i = 0; i < total_students; i++)
            {    
                for (int j = i + 1; j < total_students; j++)
                {
                    if (database[i].bdate.year > database[j].bdate.year)
                    {
                        struct myData tmp = database[i];
                        database[i] = database[j];
                        database[j] = tmp;
                    }
                }
            }
            printf("Sorted by birthyear:\n");
            for (int i = 0; i < total_students; i++)
            {
                printf("%d %s %d %s %d %d %d\n",
                    database[i].age,
                    database[i].name,
                    database[i].year,
                    database[i].course,
                    database[i].bdate.day,
                    database[i].bdate.month,
                    database[i].bdate.year);
            }
            printf("\n");
        }


        else if (mystrcmp(argv[1], "sort_course") == 0)
        {
            for (int i = 0; i < total_students; i++)
            {
                for (int j = i + 1; j < total_students; j++)
                {
                    if (mystrcmp(database[i].course, database[j].course) > 0)
                    {
                        struct myData tmp = database[i];
                        database[i] = database[j];
                        database[j] = tmp;
                    }
                }
            }
            printf("Sorted by course:\n");
            for (int i = 0; i < total_students; i++)
            {
                printf("%d %s %d %s %d %d %d\n",
                    database[i].age,
                    database[i].name,
                    database[i].year,
                    database[i].course,
                    database[i].bdate.day,
                    database[i].bdate.month,
                    database[i].bdate.year);
            }
            printf("\n");
        }


        else if (mystrcmp(argv[1], "help") == 0)
        {
            printf("Commands:\n");
            printf("add [AGE NAME YEAR COURSE DAY MONTH BYEAR]\n");
            printf("del [NAME]\n");
            printf("sort_age\n");
            printf("sort_name\n");
            printf("sort_birthyear\n");
            printf("sort_course\n");
            printf("help\n");
        }
    }

    fp = fopen("database.txt", "w");
    if (!fp) 
    {
        printf("File write error.\n");
        for (int i = 0; i < total_students; i++)
        {
            free(database[i].name);
        }
        free(database);
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
    {
        free(database[i].name);
    }
    free(database);

    return 0;
}
