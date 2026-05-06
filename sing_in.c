#include <stdio.h>
#include <string.h>
typedef struct {
    char username[50];
    char password[50];
}Sign_Up_Input;
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
    while (1)
    {
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

        switch (choice)
        {
        case 1:
            sign_Up(&sign_up_input);
            {
                FILE *user_file = fopen("sign_up.txt", "a");
                if (user_file == NULL) {
                    printf("Unable to save user information.\n");
                } else {
                    fprintf(user_file, "Username: %s, Password: %s\n",
                            sign_up_input.username, sign_up_input.password);
                    fclose(user_file);
                    printf("Sign-Up Successful! Welcome, %s!\n", sign_up_input.username);
                }
            }
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
        if (strlen(sign_up_input->username) < 5) {
            printf("Username must be at least 5 characters long.\n");
            continue;
        }
        if (strchr(sign_up_input->username, ' ') != NULL) {
            printf("Username cannot contain spaces.\n");
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
        if (strlen(sign_up_input->password) < 8) {
            printf("Password must be at least 8 characters long.\n");
            continue;
        }
        if (strchr(sign_up_input->password, ' ') != NULL) {
            printf("Password cannot contain spaces.\n");
            continue;
        }
        break;
    }
}
void Log_In(Sign_Up_Input *sign_up_input)
{
    char username[50];
    char password[50];

    while (1) {
        printf("Enter Username: ");
        if (!fgets(username, sizeof(username), stdin)) {
            printf("Error reading username.\n");
            return;
        }
        username[strcspn(username, "\n")] = '\0';
        if (strlen(username) == 0) {
            printf("Username cannot be empty.\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Enter Password: ");
        if (!fgets(password, sizeof(password), stdin)) {
            printf("Error reading password.\n");
            return;
        }
        password[strcspn(password, "\n")] = '\0';
        if (strlen(password) == 0) {
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
    while (fscanf(user_file, "Username: %49[^,], Password: %49[\n]", sign_up_input->username, sign_up_input->password) == 2) {
        if (strcmp(sign_up_input->username, username) == 0 && strcmp(sign_up_input->password, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(user_file);

    if (found) {
        printf("Log In Successful! Welcome back, %s!\n", username);
    } else {
        printf("Invalid username or password.\n");
    }
}
