#include <stdio.h>
#include <string.h>
typedef struct {
    char username[50];
    char password[50];
} User;
void sign_in(User *user);
int main(void)
{
    printf("Welcome to the Sign-In Page!\n");
    printf("Please enter your username and password to sign in.\n");
    User user;
    sign_in(&user);
    return 0;
}
void sign_in(User *user)
{
    while (1){
   
    printf("Enter Username: ");
    if(!fgets(user->username, sizeof(user->username), stdin)) {
        printf("Error reading username.\n");
        continue;
    }
    else if(strlen(user->username) == 1) {
        printf("Username cannot be empty.\n");
        continue;
    }
    else if(strlen(user->username) < 5) {
        printf("Username must be at least 5 characters long.\n");
        continue;
    }
    else if(strchr(user->username, ' ') != NULL) {
        printf("Username cannot contain spaces.\n");
        continue;
    }
    user->username[strcspn(user->username, "\n")] = '\0'; // Remove newline character
    break;
}
    while(1) {
    printf("Enter Password: ");
    if(!fgets(user->password, sizeof(user->password), stdin)) {
        printf("Error reading password.\n");
        continue;;
    }
    else if(strlen(user->password) == 1) {
        printf("Password cannot be empty.\n");
        continue;
    }
    else if(strlen(user->password) < 8) {
        printf("Password must be at least 8 characters long.\n");
        continue;;
    }
    else if(strchr(user->password, ' ') != NULL) {
        printf("Password cannot contain spaces.\n");
        continue;;
    }
    user->password[strcspn(user->password, "\n")] = '\0'; // Remove newline character
    break;
    }
    printf("Sign-In Successful! Welcome, %s!\n", user->username);
}
