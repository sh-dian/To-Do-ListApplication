/*
    SECTION 02 - TO DO LIST APPLICATION
    1. SHARIFAH LYDIEANNA BINTI SYED SHAMSUDDIN (CB20050)
    2. AHMAD HILMAN BIN AHMAD BADRUDDIN (CB20093)
    3. WAN MUHAMMAD DZULKHAIRIE BIN WAN ZAHARI (CB20096)
    4. NURUL ATIKAH BINTI FADZIL HALMI (CB20133)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define SIZE 100
#define FALSE 0
#define TRUE 1

typedef struct ApplicationAccount //main structure 1
{
    char email[SIZE];
    char pass[SIZE];
    char username[SIZE];

}appValid;

typedef struct Calendar //main structure 2
{
    int month;
    int year;

}Calendar;

typedef struct DueDate
{
    int d;
    int m;
    int y;

}DueDate;

typedef struct ToDoList //main structure 3
{
    int count;
    char tList[SIZE];

    struct TaskInfo //nested structure 1
    {
        char tag[SIZE];
        char status[SIZE];
    }TaskInfo;

    DueDate due; //nested structure 2

    struct ToDoList *ptrNext;

}ToDoList;

ToDoList *front, *rear, *newPtr, *currentPtr;

//Function declaration
struct ApplicationAccount Account(appValid userAcc); //return structure 1
void Opening(appValid userAcc); //passing structure 1

struct Calendar getValueC(Calendar c); //return structure 2
struct Calendar getCalendar(Calendar c); //passing structure 2

void enqueueDefaultData();
void addToDo(Calendar c); //enqueue //passing structure 3
void deleteToDo(); //dequeue
void updateToDo(); //update linked list

void searchToDo(); //linear sequential search

void swapToDo(ToDoList *data_A, ToDoList *data_B); //swap for sorting
void sortToDo(); //bubble sort

void displayAll(); //display all list

void adjustCount();
void determineDay();

int main()
{
    //default data
    newPtr = (ToDoList*)malloc(sizeof(ToDoList));
    strcpy(newPtr->tList, "COMPLETE DSA PROJECT");
    strcpy(newPtr->TaskInfo.status, "NOT COMPLETED");
    strcpy(newPtr->TaskInfo.tag, "URGENT");
    newPtr->due.d = 21;
    newPtr->due.m = 1;
    newPtr->due.y = 2022;
    enqueueDefaultData(); //calling function

    newPtr = (ToDoList*)malloc(sizeof(ToDoList));
    strcpy(newPtr->tList, "MANDARIN TEST");
    strcpy(newPtr->TaskInfo.status, "COMPLETED");
    strcpy(newPtr->TaskInfo.tag, "NO TAG");
    newPtr->due.d = 24;
    newPtr->due.m = 1;
    newPtr->due.y = 2022;
    enqueueDefaultData(); //calling function

    newPtr = (ToDoList*)malloc(sizeof(ToDoList));
    strcpy(newPtr->tList, "STUDY HCI");
    strcpy(newPtr->TaskInfo.status, "NOT COMPLETED");
    strcpy(newPtr->TaskInfo.tag, "NO RUSH");
    newPtr->due.d = 25;
    newPtr->due.m = 1;
    newPtr->due.y = 2022;
    enqueueDefaultData(); //calling function

    newPtr = (ToDoList*)malloc(sizeof(ToDoList));
    strcpy(newPtr->tList, "COMPLETE SYLLABUS SUBJECT");
    strcpy(newPtr->TaskInfo.status, "NOT COMPLETED");
    strcpy(newPtr->TaskInfo.tag, "URGENT");
    newPtr->due.d = 28;
    newPtr->due.m = 1;
    newPtr->due.y = 2022;
    enqueueDefaultData(); //calling function

    Calendar cal;
    appValid userAcc;

    userAcc = Account(userAcc); //calling function
    Opening(userAcc); //calling function
    cal = getValueC(cal);

    int pick = 1;
    while(pick != 0) //To-Do List Menu
    {
        system("cls");
        printf("\t\t\t\t\t\t\t\t\t------- TO DO LIST MENU -------\n\n");
        printf("\t\t\t\t\t\t\t\t\t1. Create / Add To-Do List\n");
        printf("\t\t\t\t\t\t\t\t\t2. Delete To-Do List\n");
        printf("\t\t\t\t\t\t\t\t\t3. Update To-Do List\n");
        printf("\t\t\t\t\t\t\t\t\t4. Sort To-Do List\n");
        printf("\t\t\t\t\t\t\t\t\t5. Search To-Do List\n");
        printf("\t\t\t\t\t\t\t\t\t6. View To-Do List\n");
        printf("\t\t\t\t\t\t\t\t\t0. Exit Application\n");

        printf("\n\t\t\t\t\t\t\t\t\tPick your Choice: ");
        scanf("%i", &pick);
        pick = toupper(pick);

            switch(pick)
            {
                case 1: system("cls"); addToDo(cal); break;
                case 2: system("cls"); deleteToDo(); break;
                case 3: system("cls"); updateToDo(); break;
                case 4: system("cls"); sortToDo(); break;
                case 5: system("cls"); searchToDo();break;
                case 6: system("cls"); displayAll(); printf("\n\n"); system("pause"); break;
                default: system("cls"); printf("\n\n\t\t\t\t\t\t\t ------------- THANKYOU %s! SEE YOU SOON! -------------\n\n", userAcc.username); break;
            }
    }

    return 0;
}
//Function Definition - First interface
struct ApplicationAccount Account(appValid userAcc)
{
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tEMAIL: ");
    scanf(" %[^\n]s", userAcc.email);

    printf("\t\t\t\t\t\t\t\t\tPASSWORD: ");
    scanf(" %[^\n]s", userAcc.pass);

    printf("\n\t\t\t\t\t\t\t USERNAME WILL BE DISPLAY AT THE OPENING AND EXIT APPLICATION^^\n");
    printf("\n\t\t\t\t\t\t\t\t\tUSERNAME: ");
    scanf(" %[^\n]s", userAcc.username);

    return userAcc;
}

void Opening(appValid user)
{
    system("clear||@cls");
    printf("\033[33;1m");
    printf("\n\n\t\t\t\t\t\t ------------- HI %s! WELCOME TO YOUR TO-DO LIST APPLICATION -------------\n", user.username);

    time_t t;
    time(&t);

    printf("\n\t\t\t\t\t\t\t\t\t %s", ctime(&t));
    printf("\n\t\t\t\t\t\t\t\t\t Email: %s", user.email);
    printf("\n\t\t\t\t\t\t\t\t\t User: %s", user.username);

}
//Function Definition - obtain value from user to determine calendar
struct Calendar getValueC(Calendar c)
{
    do
    {
        printf("\n\n\t\t\t\t\t\t\t\tEnter Year for Calendar: ");
        scanf("%d", &c.year);

    }while(c.year < 1);

    do
    {
        printf("\t\t\t\t\t\t\t\tEnter Month for Calendar: ");
        scanf("%d", &c.month);

    }while(c.month < 1 || c.month >12);

    return c; //return structure 1
}
//Function Definition - condition to display calendar
struct Calendar getCalendar(Calendar c)
{
    printf("\033[33;1m");

    int i = 1;
    int day;
    int leap;
    int count;
    int xcount;

    if(c.month == 4 || c.month == 6 || c.month == 9 || c.month == 11)
    {
        day = 30;
    }

        if(c.year %4 == 0 && c.year %100 != 0 || c.year % 400 == 0)
        {
            if(c.month == 2)
            {
                day = 29;
            }
        }
        else
        {
            if(c.month == 2)
            {
                day = 28;
            }
        }

        if(c.month == 1 || c.month == 3 || c.month == 5 || c.month == 7 || c.month == 8 || c.month == 10 || c.month == 11)
            day = 31;

        leap = ((c.year-1)/4) - ((c.year-1)/100) + ((c.year-1)/400);
        long int dp = ((c.year -1)*3651) + leap;

        switch(c.month)
        {
            case 1: dp += 31;
            case 2: dp += 30;
            case 3: dp += 28;
            case 4: dp += 30;
            case 5: dp += 31;
            case 6: dp += 30;
            case 7: dp += 31;
            case 8: dp += 31;
            case 9: dp += 30;
            case 10: dp += 31;
            case 11: dp += 30;
            case 12: dp += 31;
        }

        printf("\n\t\t\t\t\t\t\t\t         SUN MON TUE WED THU FRI SAT");

        switch(dp%7)
        {
            case 1: count = 4;
                    break;
            case 2: count = 8;
                    break;
            case 3: count = 12;
                    break;
            case 4: count = 16;
                    break;
            case 5: count = 20;
                    break;
            case 6: count = 24;
                    break;
            default: break;
        }

        printf("\n");
        xcount = count;

        while(xcount > 0)
        {
            printf("    ");
            --xcount;
        }

        while(day >= i)
        {
            if(count %28 == 0)
                printf("\n\t\t\t\t\t\t\t\t        ");

            printf("%3d ",i);
            i++;
            count += 4;
        }
}
//Function Definition - Add Default to-do list into system
void enqueueDefaultData()
{
    newPtr->ptrNext = NULL;

    if(front == NULL)
    {
        front = newPtr;
        rear = newPtr;
        newPtr->count =1;
    }
    else
    {
        rear->ptrNext = newPtr;
        rear = newPtr;
    }

    adjustCount(); //calling function
}
//Function Definition - Add New to-do list into system
void addToDo(Calendar c) //enqueue
{
    char x, y;
    int status, tag;

    printf("\n\t\t\t\t\t\t\t\t\t1. CREATE / ADD TO DO LIST\n");

    while(1)
    {
        printf("\n\t\t\t\t\t\t\t\tADD TASK? [y/n] : ");
        scanf(" %c", &x);

            if(x == 'n' || x == 'N')
            {
                break;
            }

        newPtr = (ToDoList*)malloc(sizeof(ToDoList));
        printf("\n\t\t\t\t\t\t\t\tENTER TASK: ");
        scanf(" %[^\n]s", newPtr->tList);

        printf("\t\t\t\t\t\t\t\tTAG - [1]URGENT [2]NO RUSH [3]NO TAG: ");
        scanf("%d", &tag);

            if(tag == 1)
            {
                strcpy(newPtr->TaskInfo.tag, "URGENT");
            }
            else if(tag == 2)
            {
                strcpy(newPtr->TaskInfo.tag, "NO RUSH");
            }
            else
            {
                strcpy(newPtr->TaskInfo.tag, "NO TAG");
            }

        strcpy(newPtr->TaskInfo.status,"NOT COMPLETED");

        printf("\n\t\t\t\t\t\t\t\tIF TASK HAVE NO DUE, ENTER TODAY DATE\n");
        getCalendar(c); //Calling Function
        printf("\n\n\t\t\t\t\t\t\t\tENTER DUE DATE: ");
        scanf("%d/%d/%d", &newPtr->due.d, &newPtr->due.m, &newPtr->due.y);

        newPtr->ptrNext = NULL;
        if(front == NULL)
        {
            front = newPtr;
            rear = newPtr;
            newPtr->count = 1;
        }
        else
        {
            rear->ptrNext = newPtr;
            rear = newPtr;
        }

        adjustCount(); //Calling Function
    }

    printf("\n\n\n");
    displayAll(); //Calling Function
    printf("\n\n");
    system("pause");
}
//Function Definition - Delete to-do list from system
void deleteToDo() //dequeue
{
    currentPtr = front;

    if(front == NULL)
    {
        printf("\t\t\t\t\t\t\t\t\tNothing to be deleted");
    }
    else
    {
        front = front ->ptrNext;
        free(currentPtr);
        adjustCount(); //Calling Function

        printf("\n\n\n");
        displayAll(); //Calling Function
        printf("\n\t\t\t\t\t\t\t\t\tTo Do List Deleted");
    }

    printf("\n\n");
    system("pause");
}
//Function Definition - display all to-do list
void displayAll()
{
    printf("\n\t\t\t\t\t\t\t\t\t6. VIEW TO DO LIST\n");

    if(front == NULL)
    {
        printf("\t\t\t\t\t\t\t\t\tYou haven't add any to-do list yet ^^\n");
    }
    else
    {
        currentPtr = front;
        printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
        printf("\t\t\t\t| NUM |            TO-DO LIST [TASK]        |    TAG   |      STATUS     |     DUE    |    DAY   |\n");
        printf("\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

        do
        {
            printf("\t\t\t\t|%3d  | %-35s | %-8s | %-15s |  %d/%d/%d | ", currentPtr->count, currentPtr->tList, currentPtr->TaskInfo.tag, currentPtr->TaskInfo.status , currentPtr->due.d, currentPtr->due.m, currentPtr->due.y);
            determineDay(); //Calling Function
            printf("  |\n");
            currentPtr = currentPtr->ptrNext;
        }while(currentPtr != NULL);

        printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
    }
}
//Function Definition - Fix counting number
void adjustCount()
{
    int count = 1;
    newPtr = front;

    while(newPtr != NULL)
    {
        newPtr->count = count;
        count++;
        newPtr = newPtr->ptrNext;
    }
}
//Function Definition - Determine day for the input date of to-do list
void determineDay()
{
    int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char* day[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    int d = currentPtr->due.d;
    int m = currentPtr->due.m;
    int y = currentPtr->due.y;

    if(y %4 == 0 && (y %100 != 0 || y %400 == 0))
        month[1] = 29;

    if(y < 1900 || m < 1 || m > 12 || d < 1 || d > month[m - 1])
    {
        printf("This is an invalid date.\n");
    }
    else
    {
        for(int i = 1900; i < y; i++)
            if(i %4 == 0 && (i %100 != 0 || i %400 == 0))
                d += 366;
            else
                d+= 365;

        for(int i = 0; i < m-1; i++)
            d += month[i];

        printf("%s", day[d %7]);
    }
}
//Function Definition
void swapToDo(ToDoList *data_A, ToDoList *data_B) //swap for sorting
{
    int tempDate;
    char tempStatus[SIZE],tempList[SIZE], tempTag[SIZE];

    strcpy(tempStatus, data_B->TaskInfo.status);
    strcpy(data_B->TaskInfo.status, data_A->TaskInfo.status);
    strcpy(data_A->TaskInfo.status, tempStatus);

    strcpy(tempList, data_B->tList);
    strcpy(data_B->tList, data_A->tList);
    strcpy(data_A->tList, tempList);

        tempDate = data_B->due.d;
        data_B->due.d = data_A->due.d;
        data_A->due.d = tempDate;

        tempDate = data_B->due.m;
        data_B->due.m = data_A->due.m;
        data_A->due.m = tempDate;

        tempDate = data_B->due.y;
        data_B->due.y = data_A->due.y;
        data_A->due.y = tempDate;

    strcpy(tempTag, data_B->TaskInfo.tag);
    strcpy(data_B->TaskInfo.tag, data_A->TaskInfo.tag);
    strcpy(data_A->TaskInfo.tag, tempTag);
}
//Function Definition - sorting to-do list based on choices
void sortToDo() //bubble sort
{
    int x, swapped;
    struct ToDoList *ptrFirst;
    struct ToDoList *ptrSecond = NULL;

    printf("\n\t\t\t\t\t\t\t\t\t4. SORT TO DO LIST\n");
    printf("\n\t\t\t\t\t\t\t\tSORT BY [1]STATUS [2]TAG [3]DATE : ");
    scanf("%d", &x);

    if(x == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tSORT BY STATUS\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tEMPTY LIST, NOTHING CAN BE SORTED");
        }
        else
        {
            do{
                swapped = FALSE;
                ptrFirst = front;

                while(ptrFirst->ptrNext != ptrSecond)
                {
                    if(strcmp(ptrFirst->TaskInfo.status, ptrFirst->ptrNext->TaskInfo.status)<0)
                    {
                        swapToDo(ptrFirst, ptrFirst->ptrNext);
                        swapped = TRUE;
                    }

                    ptrFirst = ptrFirst->ptrNext;
                }
                ptrSecond = ptrFirst;
            }while(swapped == TRUE);
        }

    }
    else if(x == 2)
    {
        printf("\n\t\t\t\t\t\t\t\t\tSORT BY TAG\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tEMPTY LIST, NOTHING CAN BE SORTED");
        }
        else
        {
            do{
                swapped = FALSE;
                ptrFirst = front;

                while(ptrFirst->ptrNext != ptrSecond)
                {
                    if(strcmp(ptrFirst->TaskInfo.tag, ptrFirst->ptrNext->TaskInfo.tag)<0)
                    {
                        swapToDo(ptrFirst, ptrFirst->ptrNext);
                        swapped = TRUE;
                    }

                    ptrFirst = ptrFirst->ptrNext;
                }
                ptrSecond = ptrFirst;
            }while(swapped == TRUE);
        }

    }
    else if(x == 3)
    {
        printf("\n\t\t\t\t\t\t\t\t\tSORT BY DATE\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tEMPTY LIST, NOTHING CAN BE SORTED");

        }
        else
        {
            do{
                swapped = FALSE;
                ptrFirst = front;

                while(ptrFirst->ptrNext != ptrSecond)
                {
                    if(ptrFirst->due.y > ptrFirst->ptrNext->due.y)
                    {
                        swapToDo(ptrFirst, ptrFirst->ptrNext);
                        swapped = TRUE;
                    }
                    else
                    {
                        if(ptrFirst->due.y == ptrFirst->ptrNext->due.y)
                        {
                            if(ptrFirst->due.m > ptrFirst->ptrNext->due.m)
                            {
                                swapToDo(ptrFirst, ptrFirst->ptrNext);
                                swapped = TRUE;
                            }
                            else
                            {
                                if(ptrFirst->due.m == ptrFirst->ptrNext->due.m)
                                {
                                    if(ptrFirst->due.d > ptrFirst->ptrNext->due.d)
                                    {
                                        swapToDo(ptrFirst, ptrFirst->ptrNext);
                                        swapped = TRUE;
                                    }
                                }
                            }

                        }
                    }

                    ptrFirst = ptrFirst->ptrNext;
                }
                ptrSecond = ptrFirst;
            }while(swapped == TRUE);
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\tSORRY CHOICE INVALID");
    }

    printf("\n\n");
    displayAll(); //Calling Function
    printf("\nDONE SORT");
    printf("\n\n");
    system("pause");
}
//Function Definition - search to-do list based on categories
void searchToDo() //linear search
{
    int x,key;
    char searchStatus[SIZE], searchTag[SIZE];

    printf("\n\t\t\t\t\t\t\t\t\t5. SEARCH TO DO LIST\n");
    printf("\n\t\t\t\t\t\t\t\tSEARCH BY [1]STATUS [2]TAG : ");
    scanf("%d", &x);

    if(x == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tSEARCH BY STATUS\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tLIST EMPTY");
        }
        else
        {
            printf("\n\t\t\t\t\t\t\tENTER SEARCH KEY [1]NOT COMPLETED [2]COMPLETED : ");
            scanf("%d", &key);

                if(key == 1)
                {
                    strcpy(searchStatus, "NOT COMPLETED");
                }
                else if(key == 2)
                {
                    strcpy(searchStatus, "COMPLETED");
                }
                else
                {
                    printf("KEYWORD INVALID");
                }
            currentPtr = front;

            while(currentPtr->ptrNext != NULL)
            {
                if(strcmp(currentPtr->TaskInfo.status, searchStatus)==0)
                {
                    printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                    //Display Information Based on Search Key
                    printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
                    printf("\t\t\t\t| NUM |            TO-DO LIST [TASK]        |    TAG   |      STATUS     |     DUE    |    DAY   |\n");
                    printf("\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

                    do
                    {
                        if(strcmp(currentPtr ->TaskInfo.status, searchStatus)==0)
                        {
                            printf("\t\t\t\t|%3d  | %-35s | %-8s | %-15s |  %d/%d/%d | ", currentPtr->count, currentPtr->tList, currentPtr->TaskInfo.tag, currentPtr->TaskInfo.status , currentPtr->due.d, currentPtr->due.m, currentPtr->due.y);
                            determineDay(); //Calling Function
                            printf("  |\n");
                        }
                        currentPtr = currentPtr ->ptrNext;

                    }while(currentPtr != NULL);

                    printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

                    printf("\n\n");
                    system("pause");

                    return;
                }
                else
                {
                    currentPtr = currentPtr ->ptrNext;
                }
            }

            if(strcmp(currentPtr->TaskInfo.status, searchStatus)==0)
            {
                printf("\n\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                //Display Information Based on Search Key
                printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
                printf("\t\t\t\t| NUM |            TO-DO LIST [TASK]        |    TAG   |      STATUS     |     DUE    |    DAY   |\n");
                printf("\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

                do
                {
                    if(strcmp(currentPtr ->TaskInfo.status, searchStatus)==0)
                    {
                        printf("\t\t\t\t|%3d  | %-35s | %-8s | %-15s |  %d/%d/%d | ", currentPtr->count, currentPtr->tList, currentPtr->TaskInfo.tag, currentPtr->TaskInfo.status , currentPtr->due.d, currentPtr->due.m, currentPtr->due.y);
                        determineDay(); //Calling Function
                        printf("  |\n");
                    }
                    currentPtr = currentPtr ->ptrNext;

                }while(currentPtr != NULL);

                printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

            }
            else
            {
                printf("\nNO TO-DO LIST FOUND");
            }
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\tSEARCH BY TAG\n");

        if(front == NULL)
        {
            printf("LIST EMPTY");
        }
        else
        {
            printf("\n\t\t\t\t\t\t\tENTER SEARCH KEY [1]URGENT [2]NO RUSH [3]NO TAG : ");
            scanf("%d", &key);

                if(key == 1)
                {
                    strcpy(searchTag, "URGENT");
                }
                else if(key == 2)
                {
                    strcpy(searchTag, "NO RUSH");
                }
                else if(key == 3)
                {
                    strcpy(searchTag, "NO TAG");
                }
                else
                {
                    printf("\t\t\t\t\t\t\t\tKEYWORD INVALID");
                }
            currentPtr = front;

            while(currentPtr->ptrNext != NULL)
            {
                if(strcmp(currentPtr->TaskInfo.tag, searchTag)==0)
                {
                    printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                    //Display Information Based on Search Key
                    printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
                    printf("\t\t\t\t| NUM |            TO-DO LIST [TASK]        |    TAG   |      STATUS     |     DUE    |    DAY   |\n");
                    printf("\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

                    do
                    {
                        if(strcmp(currentPtr ->TaskInfo.tag, searchTag)==0)
                        {
                            printf("\t\t\t\t|%3d  | %-35s | %-8s | %-15s |  %d/%d/%d | ", currentPtr->count, currentPtr->tList, currentPtr->TaskInfo.tag, currentPtr->TaskInfo.status , currentPtr->due.d, currentPtr->due.m, currentPtr->due.y);
                            determineDay(); //Calling Function
                            printf("  |\n");
                        }
                        currentPtr = currentPtr ->ptrNext;

                    }while(currentPtr != NULL);

                    printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

                    printf("\n\n");
                    system("pause");

                    return;
                }
                else
                {
                    currentPtr = currentPtr ->ptrNext;
                }
            }

            if(strcmp(currentPtr->TaskInfo.tag, searchTag)==0)
            {
                printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                //Display Information Based on Search Key
                printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
                printf("\t\t\t\t| NUM |            TO-DO LIST [TASK]        |    TAG   |      STATUS     |     DUE    |    DAY   |\n");
                printf("\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");

                do
                {
                    if(strcmp(currentPtr ->TaskInfo.tag, searchTag)==0)
                    {
                        printf("\t\t\t\t|%3d  | %-35s | %-8s | %-15s |  %d/%d/%d | ", currentPtr->count, currentPtr->tList, currentPtr->TaskInfo.tag, currentPtr->TaskInfo.status , currentPtr->due.d, currentPtr->due.m, currentPtr->due.y);
                        determineDay(); //Calling Function
                        printf("  |\n");
                    }
                    currentPtr = currentPtr ->ptrNext;

                }while(currentPtr != NULL);

                printf("\n\t\t\t\t+-----+-------------------------------------+----------+-----------------+------------+----------+\n");
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\tNO TO-DO LIST FOUND");
            }
        }
    }

    printf("\n\n");
    system("pause");
}
//Function Definition - update to-do list
void updateToDo() //update linked list
{
    int x,key;
    char searchStatus[SIZE], searchTag[SIZE];

    int status, tag;

    printf("\n\t\t\t\t\t\t\t\t\t3. UPDATE TO DO LIST\n");
    printf("\n\t\t\t\t\t\t\t\tUPDATE BY [1]STATUS [2]TAG [3]A TASK: ");
    scanf("%d", &x);

    if(x == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tUPDATE BY STATUS\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tLIST EMPTY");
        }
        else
        {
            displayAll(); //Calling Function
            printf("\n\t\t\t\t\t\t\t\t\tENTER TASK NUMBER: ");
            scanf(" %d", &key);

            currentPtr = front;

            while(currentPtr->ptrNext != NULL)
            {
                if(currentPtr->count == key)
                {
                    printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                    printf("\n\t\t\t\t\t\t\tENTER NEW STATUS [1]NOT COMPLETED [2]COMPLETED: ");
                    scanf("%d", &status);

                    if(status == 1)
                    {
                        strcpy(currentPtr->TaskInfo.status, "NOT COMPLETED");
                    }
                    else
                    {
                        strcpy(currentPtr->TaskInfo.status, "COMPLETED");
                    }

                    displayAll(); //Calling Function

                    printf("\n\n");
                    system("pause");

                    return;
                }
                else
                {
                    currentPtr = currentPtr ->ptrNext;
                }
            }

            if(currentPtr->count == key)
            {
                printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                printf("\n\t\t\t\t\t\t\tENTER NEW STATUS [1]NOT COMPLETED [2]COMPLETED: ");
                scanf("%d", &status);

                if(status == 1)
                {
                    strcpy(currentPtr->TaskInfo.status, "NOT COMPLETED");
                }
                else
                {
                    strcpy(currentPtr->TaskInfo.status, "COMPLETED");
                }

                displayAll(); //Calling Function
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\t\tNO TO-DO LIST FOUND");
            }
        }
    }
    else if(x == 2)
    {
        printf("\n\t\t\t\t\t\t\t\t\tUPDATE BY TAG\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tLIST EMPTY");
        }
        else
        {
            displayAll(); //Calling Function
            printf("\n\t\t\t\t\t\t\t\t\tENTER TASK NUMBER: ");
            scanf("%d", &key);

            currentPtr = front;

            while(currentPtr->ptrNext != NULL)
            {
                if(currentPtr->count == key)
                {
                    printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                    printf("\n\t\t\t\t\t\t\tENTER NEW TAG [1]URGENT [2]NO RUSH [3]NO TAG: ");
                    scanf("%d", &tag);

                    if(tag == 1)
                    {
                        strcpy(currentPtr->TaskInfo.tag, "URGENT");
                    }
                    else if(tag == 2)
                    {
                        strcpy(currentPtr->TaskInfo.tag, "NO RUSH");
                    }
                    else
                    {
                        strcpy(currentPtr->TaskInfo.tag, "NO TAG");
                    }

                    displayAll(); //Calling Function

                    printf("\n\n");
                    system("pause");

                    return;
                }
                else
                {
                    currentPtr = currentPtr ->ptrNext;
                }
            }

            if(currentPtr->count == key)
            {
                printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                printf("\n\t\t\t\t\t\t\t\tENTER NEW TAG [1]URGENT [2]NO RUSH [3]NO TAG: ");
                scanf("%d", &tag);

                if(tag == 1)
                {
                    strcpy(currentPtr->TaskInfo.tag, "URGENT");
                }
                else if(tag == 2)
                {
                    strcpy(currentPtr->TaskInfo.tag, "NO RUSH");
                }
                else
                {
                    strcpy(currentPtr->TaskInfo.tag, "NO TAG");
                }

                displayAll(); //Calling Function

                printf("\n\n");
                system("pause");

                return;
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\t\tNO TO-DO LIST FOUND");
            }
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\tUPDATE A TASK\n");

        if(front == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\tLIST EMPTY");
        }
        else
        {
            displayAll(); //Calling Function
            printf("\n\t\t\t\t\t\t\t\t\tENTER TASK NUMBER: ");
            scanf("%d", &key);

            currentPtr = front;

            while(currentPtr->ptrNext != NULL)
            {
                if(currentPtr->count == key)
                {
                    printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                    printf("\n\t\t\t\t\t\t\tENTER NEW UPDATE TASK: ");
                    scanf(" %[^\n]", currentPtr->tList);

                        printf("\n\t\t\t\t\t\t\tENTER NEW TAG [1]URGENT [2]NO RUSH [3]NO TAG: ");
                        scanf("%d", &tag);

                        if(tag == 1)
                        {
                            strcpy(currentPtr->TaskInfo.tag, "URGENT");
                        }
                        else if(tag == 2)
                        {
                            strcpy(currentPtr->TaskInfo.tag, "NO RUSH");
                        }
                        else
                        {
                            strcpy(currentPtr->TaskInfo.tag, "NO TAG");
                        }

                        printf("\n\t\t\t\t\t\t\tENTER NEW STATUS [1]NOT COMPLETED [2]COMPLETED: ");
                        scanf("%d", &status);

                        if(status == 1)
                        {
                            strcpy(currentPtr->TaskInfo.status, "NOT COMPLETED");
                        }
                        else
                        {
                            strcpy(currentPtr->TaskInfo.status, "COMPLETED");
                        }

                        printf("\n\n\t\t\t\t\t\t\t\tENTER NEW DUE DATE: ");
                        scanf("%d/%d/%d", &currentPtr->due.d, &currentPtr->due.m, &currentPtr->due.y);

                    displayAll(); //Calling Function

                    printf("\n\n");
                    system("pause");

                    return;
                }
                else
                {
                    currentPtr = currentPtr ->ptrNext;
                }
            }

            if(currentPtr->count == key)
            {
                printf("\n\t\t\t\t\t\t\t\t\tTO DO LIST FOUND!!\n");

                    printf("\n\t\t\t\t\t\t\tENTER NEW UPDATE TASK: ");
                    scanf(" %[^\n]", currentPtr->tList);

                        printf("\n\t\t\t\t\t\t\tENTER NEW TAG [1]URGENT [2]NO RUSH [3]NO TAG: ");
                        scanf("%d", &tag);

                        if(tag == 1)
                        {
                            strcpy(currentPtr->TaskInfo.tag, "URGENT");
                        }
                        else if(tag == 2)
                        {
                            strcpy(currentPtr->TaskInfo.tag, "NO RUSH");
                        }
                        else
                        {
                            strcpy(currentPtr->TaskInfo.tag, "NO TAG");
                        }

                        printf("\n\t\t\t\t\t\t\tENTER NEW STATUS [1]NOT COMPLETED [2]COMPLETED: ");
                        scanf("%d", &status);

                        if(status == 1)
                        {
                            strcpy(currentPtr->TaskInfo.status, "NOT COMPLETED");
                        }
                        else
                        {
                            strcpy(currentPtr->TaskInfo.status, "COMPLETED");
                        }

                        printf("\n\n\t\t\t\t\t\t\t\tENTER NEW DUE DATE: ");
                        scanf("%d/%d/%d", &currentPtr->due.d, &currentPtr->due.m, &currentPtr->due.y);

                    displayAll(); //Calling Function

                printf("\n\n");
                system("pause");

                return;
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\t\tNO TO-DO LIST FOUND");
            }
        }
    }

    printf("\n\n");
    system("pause");
}
