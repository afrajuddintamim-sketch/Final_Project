#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <magic.h>
typedef struct {
    char file_username[50];
    char file_password[50];
    char username[50];
    char password[50];
} Sign_Up_Input;

void sign_Up(Sign_Up_Input *sign_up_input);
void Log_In(Sign_Up_Input *sign_up_input);

int main(void)
{
    int choice;
    Sign_Up_Input sign_up_input;
    int c;

    printf("================================================\n");
    printf("\tWELCOME TO GADGET FINDING SYSTEM\n");
    printf("================================================\n");

    while (1) {
        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {
        case 1:
            sign_Up(&sign_up_input);
            break;
        case 2:
            Log_In(&sign_up_input);
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    return 0;
}

void sign_Up(Sign_Up_Input *sign_up_input)
{
    system("clear || cls");
    printf("================================================\n");
    printf("\tSIGN UP FOR GADGET FINDING SYSTEM\n");
    printf("================================================\n");
    while (1) {
        printf("Enter Username: ");
        if (!fgets(sign_up_input->file_username, sizeof(sign_up_input->file_username), stdin)) {
            printf("Error reading username.\n");
            continue;
        }
        sign_up_input->file_username[strcspn(sign_up_input->file_username, "\n")] = '\0';

        if (strlen(sign_up_input->file_username) == 0) {
            printf("Username cannot be empty.\n");
            continue;
        }
        if (strlen(sign_up_input->file_username) < 5) {
            printf("Username must be at least 5 characters long.\n");
            continue;
        }
        if (strchr(sign_up_input->file_username, ' ') != NULL) {
            printf("Username cannot contain spaces.\n");
            continue;
        }


        char existing_user[50], existing_pass[50];
        FILE *check = fopen("sign_up.txt", "r");
        if (check != NULL) {
            int duplicate = 0;
            while (fscanf(check, "%s %s", existing_user, existing_pass) == 2) {
                if (strcmp(existing_user, sign_up_input->file_username) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            fclose(check);
            if (duplicate) {
                printf("Username already exists. Please choose another.\n");
                continue;
            }
        }
        break;
    }

    while (1) {
        printf("Enter Password: ");
        if (!fgets(sign_up_input->file_password, sizeof(sign_up_input->file_password), stdin)) {
            printf("Error reading password.\n");
            continue;
        }
        sign_up_input->file_password[strcspn(sign_up_input->file_password, "\n")] = '\0';

        if (strlen(sign_up_input->file_password) == 0) {
            printf("Password cannot be empty.\n");
            continue;
        }
        if (strlen(sign_up_input->file_password) < 8) {
            printf("Password must be at least 8 characters long.\n");
            continue;
        }
        if (strchr(sign_up_input->file_password, ' ') != NULL) {
            printf("Password cannot contain spaces.\n");
            continue;
        }
        break;
    }
    FILE *user_file = fopen("sign_up.txt", "a");
        if (user_file == NULL) {
         printf("Unable to save user information.\n");
            return;
        } 
    fprintf(user_file, "%s %s\n", sign_up_input->file_username,sign_up_input->file_password);
    fclose(user_file);
    printf("Sign-Up Successful! Now Log In to continue.\n");
                
}

void Log_In(Sign_Up_Input *sign_up_input)
{
    system("clear || cls");
    printf("================================================\n");
    printf("\tLOG IN TO GADGET FINDING SYSTEM\n");
    printf("================================================\n");
    while (1) {
        while (1) {
            printf("Enter Username: ");
            if (!fgets(sign_up_input->username, sizeof(sign_up_input->username), stdin)) {
                printf("Error reading username.\n");
                continue;
            }
            sign_up_input->username[strcspn(sign_up_input->username, "\n")] = '\0';
            if (strlen(sign_up_input->username) == 0) {
                printf("Username cannot be empty.\n");
                continue;
            }
            break;
        }

        while (1) {
            printf("Enter Password: ");
            if (!fgets(sign_up_input->password, sizeof(sign_up_input->password), stdin)) {
                printf("Error reading password.\n");
                continue;
            }
            sign_up_input->password[strcspn(sign_up_input->password, "\n")] = '\0';
            if (strlen(sign_up_input->password) == 0) {
                printf("Password cannot be empty.\n");
                continue;
            }
            break;
        }

        FILE *user_file = fopen("sign_up.txt", "r");
        if (user_file == NULL) {
            printf("No registered users found. Please sign up first.\n");
            return;
        }

        int found = 0;
        while (fscanf(user_file, "%s %s",sign_up_input->file_username,sign_up_input->file_password) == 2) {
            if (strcmp(sign_up_input->file_username, sign_up_input->username) == 0) {
                found = 1;
                if (strcmp(sign_up_input->file_password, sign_up_input->password) == 0)
                    found = 3;
                break;
            }
        }
        fclose(user_file);

        int success = 0;
        switch (found) {
        case 0:
            printf("No such user found. Please sign up first.\n");
            return;
        case 1:
            printf("Incorrect password. Please try again.\n");
            break;
        case 3:
            printf("Log In Successful! Welcome back, %s!\n", sign_up_input->username);
            success = 1;
            break;
        default:
            printf("An unexpected error occurred.\n");
            return;
        }

        if (success) break;
    }
    printf("Now you can access the gadget finding system features.\n");
}
