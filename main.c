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

void print_db(struct myData *database, int total_students)
{
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

int main(int argc, char *argv[])
{
    struct myData *database = NULL;
    int total_students = 0;

    printf("Commands:\n");
    printf("-add [-age -name -year -course -day -month -byear]\n");
    printf("-del [NAME]\n");
    printf("-sort [-age -name -year -course -day -month -byear]\n");
    printf("-filter [-age -name -year -course -day -month -byear] [VALUE]\n");
    printf("-help\n");

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
    print_db(database, total_students);

    if (argc >= 2)
    {
        if (mystrcmp(argv[1], "-add") == 0)
        {
            int age = -1;
            char *name = NULL;
            int year = -1;
            char course[10] = {0};
            int day = -1, month = -1, byear = -1;

            for (int i = 2; i < argc; i++)
            {
                if (mystrcmp(argv[i], "-age") == 0 && i + 1 < argc)
                    age = myatoi(argv[++i]);
                else if (mystrcmp(argv[i], "-name") == 0 && i + 1 < argc)
                    name = argv[++i];
                else if (mystrcmp(argv[i], "-year") == 0 && i + 1 < argc)
                    year = myatoi(argv[++i]);
                else if (mystrcmp(argv[i], "-course") == 0 && i + 1 < argc)
                    mystrcpy(course, argv[++i]);
                else if (mystrcmp(argv[i], "-day") == 0 && i + 1 < argc)
                    day = myatoi(argv[++i]);
                else if (mystrcmp(argv[i], "-month") == 0 && i + 1 < argc)
                    month = myatoi(argv[++i]);
                else if (mystrcmp(argv[i], "-byear") == 0 && i + 1 < argc)
                    byear = myatoi(argv[++i]);
            }

            if (age == -1 || name == NULL || year == -1 ||
                course[0] == 0 || day == -1 || month == -1 || byear == -1)
            {
                printf("Required: -name -age -year -course -day -month -byear\n");
            }
            else
            {
                struct myData *new_db = malloc((total_students + 1) * sizeof(struct myData));
                for (int i = 0; i < total_students; i++) new_db[i] = database[i];
                free(database);
                database = new_db;

                database[total_students].age = age;
                database[total_students].name = malloc(mystrlen(name) + 1);
                mystrcpy(database[total_students].name, name);
                database[total_students].year = year;
                mystrcpy(database[total_students].course, course);
                database[total_students].bdate.day = day;
                database[total_students].bdate.month = month;
                database[total_students].bdate.year = byear;
                total_students++;

                printf("Student added:\n");
                print_db(database, total_students);
            }
        }

        else if (mystrcmp(argv[1], "-del") == 0 && argc == 3)
        {
            char *name = argv[2];
            int found = 0;

            for (int i = 0; i < total_students; i++)
            {
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
                    print_db(database, total_students);
                    break;
                }
            }

            if (!found)
            {
                printf("Not found.\n");
            }
        }

        else if (mystrcmp(argv[1], "-sort") == 0 && argc == 3)
        {
            if (mystrcmp(argv[2], "-age") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (database[i].age > database[j].age)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }
            else if (mystrcmp(argv[2], "-name") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (mystrcmp(database[i].name, database[j].name) > 0)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }
            else if (mystrcmp(argv[2], "-course") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (mystrcmp(database[i].course, database[j].course) > 0)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }
            else if (mystrcmp(argv[2], "-birthyear") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (database[i].bdate.year > database[j].bdate.year)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }
            else if (mystrcmp(argv[2], "-year") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (database[i].year > database[j].year)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }
            else if (mystrcmp(argv[2], "-day") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (database[i].bdate.day > database[j].bdate.day)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }
            else if (mystrcmp(argv[2], "-month") == 0)
            {
                for (int i = 0; i < total_students; i++)
                    for (int j = i + 1; j < total_students; j++)
                        if (database[i].bdate.month > database[j].bdate.month)
                        {
                            struct myData t = database[i];
                            database[i] = database[j];
                            database[j] = t;
                        }
            }

            print_db(database, total_students);
        }

        else if (mystrcmp(argv[1], "-filter") == 0 && argc == 4)
        {
            char *field = argv[2];
            char *value = argv[3];
            int found = 0;

            printf("filtered:\n");
            for (int i = 0; i < total_students; i++)
            {
                if (mystrcmp(field, "-name") == 0 && mystrcmp(database[i].name, value) == 0)
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
                else if (mystrcmp(field, "-course") == 0 && mystrcmp(database[i].course, value) == 0)
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
                else if (mystrcmp(field, "-age") == 0 && database[i].age == myatoi(value))
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
                else if (mystrcmp(field, "-year") == 0 && database[i].year == myatoi(value))
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
                else if (mystrcmp(field, "-day") == 0 && database[i].bdate.day == myatoi(value))
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
                else if (mystrcmp(field, "-month") == 0 && database[i].bdate.month == myatoi(value))
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
                else if (mystrcmp(field, "-byear") == 0 && database[i].bdate.year == myatoi(value))
                {
                    printf("%d %s %d %s %d %d %d\n",
                        database[i].age, database[i].name, database[i].year,
                        database[i].course, database[i].bdate.day,
                        database[i].bdate.month, database[i].bdate.year);
                    found = 1;
                }
            }

            if (!found)
            {
                printf("Not found.\n");
            }
            printf("\n");
        }

        else if (mystrcmp(argv[1], "-help") == 0)
        {
            printf("Commands:\n");
            printf("-add [-age -name -year -course -day -month -byear]\n");
            printf("-del [NAME]\n");
            printf("-sort [-age -name -year -course -day -month -byear]\n");
            printf("-filter [-age -name -year -course -day -month -byear] [VALUE]\n");
            printf("-help\n");
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
