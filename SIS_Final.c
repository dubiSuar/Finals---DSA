#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for Student
struct Student {
    int StudentNumber;
    char firstName[50];
    char middleName[50];
    char lastName[50];
    int age;
    char year[10];
    char email[50];
    char sex[10];
    char course[50];
    struct Student* next;
};

// Functions for program - add,remove, search, etc;
void addStudent(struct Student** head, int studentNumber);
void displayStudents(struct Student* head);
int authenticateAdmin(char* adminName, char* adminPass);
void enterStudentDetails(struct Student* student);
void displayStudentsInTable(struct Student* head);
void searchStudent(struct Student* head, int studentNumber);
void deleteStudent(struct Student** head, int studentNumber); // New function prototype
void userLogin(struct Student* head);
void enrollCourse(struct Student* head, int studentNumber);

//File handling Functionsd
void saveStudentsToFile(struct Student* head);
struct Student* loadStudentsFromFile();


// Function menus here.
int displayMenu();
void titleInfo();
void adminLogin();

int main()
{
    int choice;
    struct Student* studentList = NULL;

    //file handling, loading saved data; to check baka hindi ulit gumagana
     studentList = loadStudentsFromFile();

    do {
        choice = displayMenu();

        switch (choice) {
        case 1:
            userLogin(studentList);
            break;
        case 2:
            adminLogin(&studentList);
            break;
        case 0:
            printf("\n Logging Out.....");
        default:
            printf("Logged Out Successfully!");
            break;
        }
    } while (choice != 0);

    saveStudentsToFile(studentList);

    printf("Program has Terminated Successfully!\n");

    return 0;
}

int displayMenu() {
    int choice;

    titleInfo();
    printf("\n\t|----------------------|");
    printf("\n\t| Select Login :       |");
    printf("\n\t| [1] USER             |");
    printf("\n\t| [2] ADMINISTRATOR    |");
    printf("\n\t| [0] LOGOUT           |");
    printf("\n\t|----------------------|");
    printf("\n SELECT: ");
    scanf("%d", &choice);

    return choice;
}

void titleInfo() {
    printf("==========================================");
    printf("\n======= STUDENT INFORMATION SYSTEM =======");
    printf("\n========================================");
}

void userLogin(struct Student* head) {
    char userName[20];
    char userPass[20];
    int authenticationFailed = 0;

    do {
        printf("\n\t|----------------------|");
        printf("\n\t|---- USER LOGIN ------|");
        printf("\n\t| ENTER USER NAME      |");
        printf("\n\t|----------------------|");
        printf("\n USER NAME: ");
        scanf("%s", userName);

        printf("\n\t|----------------------|");
        printf("\n\t| ENTER PASSWORD       |");
        printf("\n\t|----------------------|");
        printf("\n PASSWORD : ");
        scanf("%s", userPass);

        if (strcmp(userName, "user") == 0 && strcmp(userPass, "user123") == 0) {
            printf("\nAuthentication Successful! Welcome, %s!\n", userName);

            int userChoice;

            do {
                printf("\n\t|--------------------------|");
                printf("\n\t|       USER MENU          |");
                printf("\n\t| [1] Search Student      |");
                printf("\n\t| [2] Enroll Course       |");
                printf("\n\t| [0] Logout              |");
                printf("\n\t|--------------------------|");
                printf("\n SELECT: ");
                scanf("%d", &userChoice);

                switch (userChoice) {
                    case 1: {
                        int studentNumber;
                        printf("\n\t|-------------------------|");
                        printf("\n\t|   SEARCH STUDENT        |");
                        printf("\n\t| Enter Student Number    |");
                        printf("\n\t|-------------------------|");
                        printf("\n STUDENT TO BE SEARCHED : ");
                        scanf("%d", &studentNumber);
                        searchStudent(head, studentNumber);
                        break;
                    }
                    case 2: {
                        int studentNumber;
                        printf("\n\t|------------------------|");
                        printf("\n\t|    ENROLL COURSE        |");
                        printf("\n\t| Enter Student Number   |");
                        printf("\n\t|------------------------|");
                        printf("\n STUDENT TO ENROLL : ");
                        scanf("%d", &studentNumber);
                        enrollCourse(head, studentNumber);
                        break;
                    }
                    case 0:
                        printf("\nLogging out...\n");
                        break;
                    default:
                        printf("Invalid choice! Please select again.\n");
                        break;
                }

            } while (userChoice != 0);

            authenticationFailed = 0; // Reset authentication failure flag
        } else {
            printf("\nAuthentication Failed! Invalid username or password.\n");
            authenticationFailed = 1; // Set authentication failure flag
        }
    } while (authenticationFailed);
}


int authenticateAdmin(char* adminName, char* adminPass) {
    const char* correctAdminName = "admin";
    const char* correctAdminPass = "admin123";

    if (strcmp(adminName, correctAdminName) == 0 && strcmp(adminPass, correctAdminPass) == 0) {
        return 1;
    }

    return 0;
}
void adminLogin(struct Student** studentList) {
    char adminName[20];
    char adminPass[20];

    printf("\n\t|-----------------------|");
    printf("\n\t|  --- ADMIN LOGIN ---  |");
    printf("\n\t| ENTER ADMIN USER NAME |");
    printf("\n\t|-----------------------|");
    printf("\n USER NAME: ");
    scanf("%s", adminName);

    printf("\n\t|-----------------------|");
    printf("\n\t| ENTER ADMIN PASSWORD  |");
    printf("\n\t|-----------------------|");
    printf("\n PASSWORD : ");
    scanf("%s", adminPass);

    if (authenticateAdmin(adminName, adminPass)) {
        printf("\nAuthentication Successful! Welcome, %s!\n", adminName);

        int adminChoice;

        do {
            printf("\n\t|-------------------------|");
            printf("\n\t|   ADMINISTRATOR MENU   |");
            printf("\n\t| [1] Add Student        |");
            printf("\n\t| [2] Display Students   |");
            printf("\n\t| [3] Search Student     |");
            printf("\n\t| [4] Delete Student     |"); 
            printf("\n\t| [0] Logout             |");
            printf("\n\t|-------------------------|");
            printf("\n SELECT: ");
            scanf("%d", &adminChoice);

            switch (adminChoice) {
            case 1: {
                int studentNumber;
                printf("\n\t|----------------------|");
                printf("\n\t|  --- ADD STUDENT --- |");
                printf("\n\t| ADD STUDENT NUMBER   |");
                printf("\n\t|----------------------|");
                printf("\n ENTER : ");
                scanf("%d", &studentNumber);
                addStudent(studentList, studentNumber);
                break;
            }
            case 3: {
                int studentNumber;
                printf("\n\t|-------------------------|");
                printf("\n\t|   SEARCH STUDENT        |");
                printf("\n\t| Enter Student Number    |");
                printf("\n\t|-------------------------|");
                printf("\n STUDENT TO BE SEARCHED : ");
                scanf("%d", &studentNumber);
                searchStudent(*studentList, studentNumber);
                break;
            }
            case 2:
                displayStudentsInTable(*studentList);
                break;
            case 4: {
                int studentNumber;
                printf("\n\t|-------------------------|");
                printf("\n\t|   DELETE STUDENT        |");
                printf("\n\t| Enter Student Number    |");
                printf("\n\t|-------------------------|");
                printf("\n STUDENT TO BE DELETED : ");
                scanf("%d", &studentNumber);
                deleteStudent(studentList, studentNumber);
                break;
            }
            case 0:
                printf("\nLogging out...\n");
                break;
            default:
                printf("Invalid choice! Please select again.\n");
                break;
            }

        } while (adminChoice != 0);
    } else {
        printf("\nAuthentication Failed! Invalid username or password.\n");
    }
}

void addStudent(struct Student** head, int studentNumber) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

    if (!newStudent) {
        printf("\n Memory allocation failed for adding student.");
        return;
    }

    newStudent->StudentNumber = studentNumber;
    newStudent->next = *head;

    printf("\nEnter details for Student %d:\n", studentNumber);
    enterStudentDetails(newStudent);

    *head = newStudent;

    printf("\n Student No. %d has been successfully added!\n", studentNumber);
}

void enterStudentDetails(struct Student* student) {

    char course[30];

    printf("First Name: ");
    scanf("%s", student->firstName);

    fflush(stdin);

    printf("Middle Name: ");
    scanf("%s", student->middleName);

    fflush(stdin);

    printf("Last Name: ");
    scanf("%s", student->lastName);

    fflush(stdin);

    printf("Age: ");
    scanf("%d", &student->age);

    fflush(stdin);

    printf("Year Level:");
    scanf(" %s", &student->year);

    fflush(stdin);

    printf("Email: ");
    scanf("%s", student->email);

    fflush(stdin);

    printf("Sex: ");
    scanf("%s", student->sex);

    fflush(stdin);

    printf("Course: ");
    scanf(" %[^\n]", student->course);

}

void searchStudent(struct Student* head, int studentNumber) {
    // Search for the student
    while (head != NULL) {
        if (head->StudentNumber == studentNumber) {
            // Display student details in a table format
            printf("\n=== STUDENT DETAILS ===\n");
            printf("| %-15s | %-30s | %-5s | %-5s | %-10s | %-30s | %-30s |\n", "Student ID", "Name", "Age", "Year", "Sex", "Email", "Course");
            printf("|-----------------|--------------------------------|-------|-------|------------|--------------------------------|--------------------------------|\n");

            char nameBuffer[150];  // Buffer for concatenated name
            strcpy(nameBuffer, head->firstName);
            strcat(nameBuffer, " ");
            strcat(nameBuffer, head->middleName);
            strcat(nameBuffer, " ");
            strcat(nameBuffer, head->lastName);

            char emailBuffer[50];  // Buffer for email
            strcpy(emailBuffer, head->email);

            printf("| %-15d | %-30s | %-5d | %-5s | %-10s | %-30s | %-30s |\n",
                   head->StudentNumber,
                   nameBuffer,
                   head->age,
                   head->year,
                   head->sex,
                   emailBuffer,
                   head->course);

            return; // Exit the function after displaying the student details
        }
        head = head->next;
    }

    // If the loop completes, the student was not found
    printf("\nStudent with ID %d not found.\n", studentNumber);
}

void displayStudentsInTable(struct Student* head) {
    // Display all students' details in a table format
    printf("\n=== STUDENT DETAILS ===\n");
    printf("| %-15s | %-30s | %-5s | %-5s | %-10s | %-30s | %-30s |\n", "Student ID", "Name", "Age", "Year", "Sex", "Email", "Course");
    printf("|-----------------|--------------------------------|-------|-------|------------|--------------------------------|--------------------------------|\n");

    while (head != NULL) {
        char nameBuffer[150];  // Buffer for concatenated name
        strcpy(nameBuffer, head->firstName);
        strcat(nameBuffer, " ");
        strcat(nameBuffer, head->middleName);
        strcat(nameBuffer, " ");
        strcat(nameBuffer, head->lastName);

        char emailBuffer[50];  // Buffer for email
        strcpy(emailBuffer, head->email);

        printf("| %-15d | %-30s | %-5d | %-5s | %-10s | %-30s | %-30s |\n",
               head->StudentNumber,
               nameBuffer,
               head->age,
               head->year,
               head->sex,
               emailBuffer,
               head->course);

        head = head->next;
    }
}

void deleteStudent(struct Student** head, int studentNumber) {
    struct Student* temp = *head;
    struct Student* prev = NULL;

    if (temp != NULL && temp->StudentNumber == studentNumber) {
        *head = temp->next;
        free(temp);
        printf("\nStudent with ID %d has been deleted successfully.\n", studentNumber);
        return;
    }

    while (temp != NULL && temp->StudentNumber != studentNumber) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nStudent with ID %d not found.\n", studentNumber);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\nStudent with ID %d has been deleted successfully.\n", studentNumber);
}

void enrollCourse(struct Student* head, int studentNumber) {
    struct Student* current = head;

    // Find the student by student number
    while (current != NULL) {
        if (current->StudentNumber == studentNumber) {
            printf("\nEnter Course to Enroll for Student %d: ", studentNumber);
            scanf(" %[^\n]", current->course); // Enroll the student in a course
            printf("\nStudent No. %d has been enrolled in the course: %s\n", studentNumber, current->course);
            return;
        }
        current = current->next;
    }

    // If the student was not found
    printf("\nStudent with ID %d not found.\n", studentNumber);
}

void displayCourseTable() 
{
    printf("|-------------------------------------------------------------------------|\n");
    printf("| Course ID |       Course Name                     |\n");
    printf("|-------------------------------------------------------------------------|\n");
    printf("|   IIT406  | Computer Programming 3                                      |\n");
    printf("|   IIT404  | Data Structures and Algorithms                              |\n");
    printf("|   ITS404  | Computer Architecture, Organization and Logic Design        |\n");
    printf("|   IIT408  | Operating System                                            |\n");
    printf("|   ITS401  | Networking 1                                                |\n");
    printf("|   GE11    | Readings in Philippine History                              |\n");
    printf("|   GE4     | Life and Works of Rizal                                     |\n");
    printf("|   PE3     | Physical Education 3                                        |\n");
    printf("|   RE3     | Religious Education 3                                       |\n");
    printf("|-------------------------------------------------------------------------|\n");
}



/*
FOR FILE HADNLING
TO DO:
    - DOUBLE CHECK IF GUMAGANA
    - PRINTTING PROBLEM: PRINTING EXCESS CHARACTERS
*/

//saving student data - to check
void saveStudentsToFile(struct Student* head)
{
    FILE* file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing: student_data.txt\n");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%d %s %s %s %d %s %s %s %s\n",
                head->StudentNumber,
                head->firstName,
                head->middleName,
                head->lastName,
                head->age,
                head->year,
                head->email,
                head->sex,
                head->course);

        head = head->next;
    }

    fclose(file);
}


//loading students from file rito
struct Student* loadStudentsFromFile()
{
    struct Student* head = NULL;
    FILE* file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("No existing data found. Starting with an empty student list.\n");
        return head;
    }

    char lineBuffer[150];   // Buffer for reading a line from the file
                            // TO STUDY TO ^^^
    while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL) {
        struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
        if (!newStudent) {
            printf("\n Memory allocation failed for adding student.");
            fclose(file);
            return head;
        }

        if (sscanf(lineBuffer, "%d %s %s %s %d %s %s %s %s",
                   &newStudent->StudentNumber,
                   newStudent->firstName,
                   newStudent->middleName,
                   newStudent->lastName,
                   &newStudent->age,
                   newStudent->year,
                   newStudent->email,
                   newStudent->sex,
                   newStudent->course) != 9) {
            free(newStudent);
            continue;
        }

        newStudent->next = head;
        head = newStudent;
    }

    fclose(file);
    return head;
}


