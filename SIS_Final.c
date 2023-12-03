
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student Structure
struct Student
{
    int StudentNumber;
    char firstName[50];
    char middleName[50];
    char lastName[50];
    int age;
    char year[10];
    char email[50];
    char sex[10];
    char course[50];
    struct Student *next;
};

// COURSES FUNCTION - modifying the courses through admin function here
void displayCoursesForStudent(struct Student *head, int studentNumber);
void addCourse(struct Student *current);
void removeCourse(struct Student *current);
void modifyCourse(struct Student *current);

// Functions for program - add,remove, search, etc;
void addStudent(struct Student **head, int studentNumber);
void displayStudents(struct Student *head);
int authenticateAdmin(char *adminName, char *adminPass);
void enterStudentDetails(struct Student *student);
void displayStudentsInTable(struct Student *head);
void searchStudent(struct Student *head, int studentNumber);
void modifyStudent(struct Student *head, int studentNumber);
void deleteStudent(struct Student **head, int studentNumber);
void userLogin(struct Student **head);
void enrollCourse(struct Student *head, int studentNumber);

// Fixed table to display courses for the student
void displayCourseTable();

// File Handling Functions
void saveStudentsToFile(struct Student *head);
struct Student *loadStudentsFromFile();

// Function menus
int displayMenu();
void titleInfo();
void adminLogin();

int main()
{
    int choice;
    struct Student *studentList = NULL;

    // Load saved student file - attach "student_data.txt" file always
    studentList = loadStudentsFromFile();

    do
    {
        choice = displayMenu();

        switch (choice)
        {
        case 1:
            userLogin(studentList);
            break;
        case 2:
            adminLogin(&studentList);
            break;
        case 0:
            printf("\n Logging Out.....");
            // FILE SAVING HERE
            saveStudentsToFile(studentList);
            break;
        default:
            printf("Logged Out Successfully!");
            break;
        }
    } while (choice != 0);

    printf("Program has Terminated Successfully!\n");

    return 0;
}

int displayMenu()
{
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

void titleInfo()
{
    printf("==========================================");
    printf("\n======= STUDENT INFORMATION SYSTEM =======");
    printf("\n========================================");
}

void userLogin(struct Student **head)
{
    char userName[20];
    char userPass[20];
    int authenticationFailed = 0;

    do
    {
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

        if (strcmp(userName, "user") == 0 && strcmp(userPass, "user123") == 0)
        {
            printf("\nAuthentication Successful! Welcome, %s!\n", userName);

            int userChoice;

            do
            {
                printf("\n\t|--------------------------|");
                printf("\n\t|       USER MENU          |");
                printf("\n\t| [1] Display Information  |");
                printf("\n\t| [2] Enroll Course/s      |");
                printf("\n\t| [0] Logout               |");
                printf("\n\t|--------------------------|");
                printf("\n SELECT: ");
                scanf("%d", &userChoice);

                switch (userChoice)
                {
                case 1:
                {
                    int studentNumber;
                    printf("\n\t|-------------------------|");
                    printf("\n\t|   Display Information   |");
                    printf("\n\t| Enter Student Number    |");
                    printf("\n\t|-------------------------|");
                    printf("\n ID to be displayed : ");
                    scanf("%d", &studentNumber);
                    searchStudent(head, studentNumber);
                    break;
                }
                case 2:
                {
                    int studentNumber;
                    printf("\n\t|------------------------|");
                    printf("\n\t|    ENROLL COURSE       |");
                    printf("\n\t| Enter Student Number   |");
                    printf("\n\t|------------------------|");
                    displayCourseTable();
                    printf("\n STUDENT TO ENROLL : ");
                    scanf("%d", &studentNumber);
                    enrollCourse(head, studentNumber);
                    break;
                }
                case 0:
                    saveStudentsToFile(*head);
                    printf("\nLogging out...\n");
                    break;
                default:
                    printf("Invalid choice! Please select again.\n");
                    break;
                }

            } while (userChoice != 0);

            authenticationFailed = 0;
        }
        else
        {
            printf("\nAuthentication Failed! Invalid username or password.\n");
            authenticationFailed = 1;
        }
    } while (authenticationFailed);
}

int authenticateAdmin(char *adminName, char *adminPass)
{
    // default credentials
    const char *correctAdminName = "admin";
    const char *correctAdminPass = "admin123";

    if (strcmp(adminName, correctAdminName) == 0 && strcmp(adminPass, correctAdminPass) == 0)
    {
        return 1;
    }

    return 0;
}
void adminLogin(struct Student **studentList)
{
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

    if (authenticateAdmin(adminName, adminPass))
    {
        printf("\nAuthentication Successful! Welcome, %s!\n", adminName);

        int adminChoice;
        int modifyStudentNumber;

        do
        {
            printf("\n\t|------------------------|");
            printf("\n\t|   ADMINISTRATOR MENU   |");
            printf("\n\t| [1] Add Student        |");
            printf("\n\t| [2] Display Students   |");
            printf("\n\t| [3] Search Student     |");
            printf("\n\t| [4] Delete Student     |");
            printf("\n\t| [5] Modify Information |");
            printf("\n\t| [0] Logout             |");
            printf("\n\t|------------------------|");
            printf("\n SELECT: ");
            scanf("%d", &adminChoice);

            switch (adminChoice)
            {
            case 1:
            {
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
            case 3:
            {
                int studentNumber;
                printf("\n\t|-------------------------|");
                printf("\n\t|   PERSONAL INFORMATION  |");
                printf("\n\t| Enter Student Number    |");
                printf("\n\t|-------------------------|");
                printf("\n STUDENT TO BE DISPLAYED : ");
                scanf("%d", &studentNumber);
                searchStudent(*studentList, studentNumber);
                break;
            }
            case 2:
                displayStudentsInTable(*studentList);
                break;
            case 4:
            {
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
            case 5:
            {
                printf("Enter Student Number to Modify: "); 
                scanf("%d", &modifyStudentNumber);
                modifyStudent(*studentList, modifyStudentNumber);
                break;
            }

            case 0:
                saveStudentsToFile(*studentList);
                printf("\nLogging out...\n");
                break;

            default:
                printf("Invalid choice! Please select again.\n");
                break;
            }

        } while (adminChoice != 0);
    }
    else
    {
        printf("\nAuthentication Failed! Invalid username or password.\n");
    }
}

void addStudent(struct Student **head, int studentNumber)
{
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));

    if (!newStudent)
    {
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

void enterStudentDetails(struct Student *student)
{

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

    printf("Courses Shall be Enrolled by the Student");
}

void modifyStudent(struct Student *head, int studentNumber)
{
    struct Student *current = head;

    while (current != NULL)
    {
        if (current->StudentNumber == studentNumber)
        {
            printf("\n=== MODIFY STUDENT ===\n");
            printf("| %-20s | %-40s |\n", "Field", "Current Value");
            printf("|----------------------|------------------------------------------|\n");
            printf("| %-20s | %-40d |\n", "Student ID", current->StudentNumber);
            printf("| %-20s | %-40s |\n", "Current First Name", current->firstName);
            printf("| %-20s | %-40s |\n", "Current Middle Name", current->middleName);
            printf("| %-20s | %-40s |\n", "Current Last Name", current->lastName);
            printf("| %-20s | %-40d |\n", "Current Age", current->age);
            printf("| %-20s | %-40s |\n", "Current Year", current->year);
            printf("| %-20s | %-40s |\n", "Current Email", current->email);
            printf("| %-20s | %-40s |\n", "Current Sex", current->sex);
            printf("| %-20s | %-40s |\n", "Current Course/s", current->course);
            printf("|----------------------|------------------------------------------|\n");

            // Clearing input buffers
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            // Get new values
            printf("Enter New First Name: ");
            fgets(current->firstName, sizeof(current->firstName), stdin);
            current->firstName[strcspn(current->firstName, "\n")] = '\0'; // Remove trailing newline

            printf("Enter New Middle Name: ");
            fgets(current->middleName, sizeof(current->middleName), stdin);
            current->middleName[strcspn(current->middleName, "\n")] = '\0';

            printf("Enter New Last Name: ");
            fgets(current->lastName, sizeof(current->lastName), stdin);
            current->lastName[strcspn(current->lastName, "\n")] = '\0';

            printf("Enter New Age: ");
            scanf("%d", &current->age);

            printf("Enter New Year: ");
            scanf("%s", current->year);

            // Clear input buffer after reading integers
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            printf("Enter New Email: ");
            fgets(current->email, sizeof(current->email), stdin);
            current->email[strcspn(current->email, "\n")] = '\0';

            printf("Enter New Sex: ");
            fgets(current->sex, sizeof(current->sex), stdin);
            current->sex[strcspn(current->sex, "\n")] = '\0';

            printf("Enter New Course(s) (comma-separated): ");
            fgets(current->course, sizeof(current->course), stdin);
            current->course[strcspn(current->course, "\n")] = '\0';

            printf("\nStudent information updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("\nStudent with ID %d not found.\n", studentNumber);
}

void searchStudent(struct Student *head, int studentNumber)
{
    // Search for the student
    while (head != NULL)
    {
        if (head->StudentNumber == studentNumber)
        {
            // Display student details in a table format
            printf("\n=== STUDENT DETAILS ===\n");
            printf("| %-15s | %-30s | %-5s | %-5s | %-10s | %-30s | %-30s |\n", "Student ID", "Name", "Age", "Year", "Sex", "Email", "Course");
            printf("|-----------------|--------------------------------|-------|-------|------------|--------------------------------|--------------------------------|\n");

            char nameBuffer[150]; // Buffer for concatenated name
            strcpy(nameBuffer, head->firstName);
            strcat(nameBuffer, " ");
            strcat(nameBuffer, head->middleName);
            strcat(nameBuffer, " ");
            strcat(nameBuffer, head->lastName);

            char emailBuffer[50]; // Buffer for email
            strcpy(emailBuffer, head->email);

            printf("| %-15d | %-30s | %-5d | %-5s | %-10s | %-30s | %-30s |\n",
                   head->StudentNumber,
                   nameBuffer,
                   head->age,
                   head->year,
                   head->sex,
                   emailBuffer,
                   head->course);

            return;
        }
        head = head->next;
    }

    printf("\nStudent with ID %d not found.\n", studentNumber);
}

void displayStudentsInTable(struct Student *head)
{
    printf("\n=== STUDENT DETAILS ===\n");
    printf("| %-15s | %-30s | %-5s | %-5s | %-10s | %-30s | %-30s |\n", "Student ID", "Name", "Age", "Year", "Sex", "Email", "Course");
    printf("|-----------------|--------------------------------|-------|-------|------------|--------------------------------|--------------------------------|\n");

    while (head != NULL)
    {
        char nameBuffer[150]; // Buffer for concatenated name
        strcpy(nameBuffer, head->firstName);
        strcat(nameBuffer, " ");
        strcat(nameBuffer, head->middleName);
        strcat(nameBuffer, " ");
        strcat(nameBuffer, head->lastName);

        char emailBuffer[50]; // Buffer for email
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

void deleteStudent(struct Student **head, int studentNumber)
{
    struct Student *temp = *head;
    struct Student *prev = NULL;

    if (temp != NULL && temp->StudentNumber == studentNumber)
    {
        *head = temp->next;
        free(temp);
        printf("\nStudent with ID %d has been deleted successfully.\n", studentNumber);
        return;
    }

    while (temp != NULL && temp->StudentNumber != studentNumber)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("\nStudent with ID %d not found.\n", studentNumber);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\nStudent with ID %d has been deleted successfully.\n", studentNumber);
}

void enrollCourse(struct Student *head, int studentNumber)
{
    struct Student *current = head;

    // Find the student by student number
    while (current != NULL)
    {
        if (current->StudentNumber == studentNumber)
        {
            printf("\nEnter Course to Enroll for Student %d: ", studentNumber);

            char newCourse[50];
            scanf(" %[^\n]", newCourse);

            // Check if the student already has courses
            if (strlen(current->course) > 0)
            {
                // Append the new course to the existing courses
                strcat(current->course, ", ");
                strcat(current->course, newCourse);
            }
            else
            {
                // If the student has no existing courses, set the new course directly
                strcpy(current->course, newCourse);
            }

            printf("\nStudent No. %d has been enrolled in the courses: %s\n", studentNumber, current->course);
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
    printf("|-------------------------------------------------------------------------|\n");
    printf("| Course ID |       Course Name                                           |\n");
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
*/

// saving student data - to check
void saveStudentsToFile(struct Student *head)
{
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file for writing: student_data.txt");
        return;
    }

    while (head != NULL)
    {
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

    if (fclose(file) != 0)
    {
        perror("Error closing file");
    }
}

// loading students from file rito
struct Student *loadStudentsFromFile()
{
    struct Student *head = NULL;
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL)
    {
        perror("Error opening Student Information System for loading system: student_data.txt");
        printf("No existing data found. Starting an empty data list.\n");
        return head;
    }

    char lineBuffer[256];
    while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL)
    {
        struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
        if (!newStudent)
        {
            perror("Memory allocation failed for adding student");
            fclose(file);
            return head;
        }

        // Initialize the next pointer to NULL
        newStudent->next = NULL;

        if (sscanf(lineBuffer, "%d %s %s %s %d %s %s %s %s",
                   &newStudent->StudentNumber,
                   newStudent->firstName,
                   newStudent->middleName,
                   newStudent->lastName,
                   &newStudent->age,
                   newStudent->year,
                   newStudent->email,
                   newStudent->sex,
                   newStudent->course) != 9)
        {
            free(newStudent);
            continue;
        }

        newStudent->next = head;
        head = newStudent;
    }

    if (fclose(file) != 0)
    {
        perror("Error closing file");
    }

    return head;
}
