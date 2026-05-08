#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct {
    char file_username[50];
    char file_password[50];
    char username[50];
    char password[50];
    int choice;
    int c;
    int success;
} Sign_Up_Input;
typedef struct {
        int choice;
        char gadget_name[50];
        char gadget_description[200];
}gadget_information;
void sign_Up_interface(Sign_Up_Input *sign_up_input);
void sign_Up(Sign_Up_Input *sign_up_input);
void Log_In(Sign_Up_Input *sign_up_input);
void gadget_interface(gadget_information *gadget_info);

int main(void)
{
    Sign_Up_Input sign_up_input;
    gadget_information gadget_info;
    sign_Up_interface(&sign_up_input);
    gadget_interface(&gadget_info);


    return 0;
}
void sign_Up_interface(Sign_Up_Input *sign_up_input)
{
    system(CLEAR);
    printf("================================================\n");
    printf("\tSIGN UP FOR GADGET FINDING SYSTEM\n");
    printf("================================================\n");
    printf("Please follow the instructions to create your account.\n");
    printf("- Username must be at least 5 characters long and cannot contain spaces.\n");
    printf("- Password must be at least 8 characters long and cannot contain spaces.\n");
    printf("Let's get started!\n");
        while (1) {
        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &sign_up_input->choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while ((sign_up_input->c = getchar()) != '\n' && sign_up_input->c != EOF);
            continue;
        }
        while ((sign_up_input->c = getchar()) != '\n' && sign_up_input->c != EOF);

        switch (sign_up_input->choice) {
        case 1:
            sign_Up(&sign_up_input);
            break;
        case 2:
            Log_In(&sign_up_input);
            if(sign_up_input->success)
            return;
            else break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
}
}
void sign_Up(Sign_Up_Input *sign_up_input)
{
    system(CLEAR);
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
    fprintf(user_file, "%s %s\n", sign_up_input->file_username, sign_up_input->file_password);
    fclose(user_file);
    printf("Sign-Up Successful! Now Log In to continue.\n");
}
void Log_In(Sign_Up_Input *sign_up_input)
{
    system(CLEAR);
    printf("================================================\n");
    printf("\tLOG IN TO GADGET FINDING SYSTEM\n");
    printf("================================================\n");

    int attempts = 0;  // ✅ outside the loop — persists across iterations

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
        while (fscanf(user_file, "%s %s",
                      sign_up_input->file_username,
                      sign_up_input->file_password) == 2) {
            if (strcmp(sign_up_input->file_username, sign_up_input->username) == 0) {
                found = 1;
                if (strcmp(sign_up_input->file_password, sign_up_input->password) == 0)
                    found = 3;
                break;
            }
        }
        fclose(user_file);

        switch (found) {
        case 0:
            printf("Invalid username. Please try again.\n");
            attempts++;
            break;
        case 1:
            printf("Incorrect password. Please try again.\n");
            attempts++;
            break;
        case 3:
            printf("Log In Successful! Welcome back, %s!\n", sign_up_input->username);
            sign_up_input->success = 1;
            break;
        default:
            printf("An unexpected error occurred.\n");
            return;
        }

        if (attempts >= 3) {
            printf("Too many failed attempts. Please try again later.\n");
            return;
        }
        if (sign_up_input->success) break;
    }
    printf("Now you can access the gadget finding system features.\n");
}
