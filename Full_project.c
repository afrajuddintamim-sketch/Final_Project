#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
    #define CLEAR "cls"
    #define strcasecmp _stricmp
#else
    #define CLEAR "clear"
#endif

#define MAX_ITEMS 200

typedef struct {
    char file_username[50];
    char file_password[50];
    char username[50];
    char password[50];
    int success;
} Sign_Up_Input;
typedef struct {
    char type[10];
    char name[50];
    int price;
    int feature; 
    int feature2;
} product_information;

product_information items[MAX_ITEMS];
int count = 0;

void sign_Up_interface(Sign_Up_Input *sign_up_input);
void sign_Up(Sign_Up_Input *sign_up_input);
void Log_In(Sign_Up_Input *sign_up_input);
void gadget_interface(void);

void makeUpperCase(char *word);
void clearLeftoverInput(void);
void printDashes(int howMany);

void featureLabels(const char *type,char *label1,char *label2,int  *featureCount);

void loadFromFile(void);
void saveToFile(void);

void addProduct(void);
void deleteProduct(void);
void showAllByType(void);

int compareByPrice(const void *a, const void *b);

void searchProducts(void);

/* ------------------------------------------------------------------ */
int main(void)
{
    Sign_Up_Input sign_up_input = {0};

    sign_Up_interface(&sign_up_input);

    if (sign_up_input.success)
        gadget_interface();

    return 0;
}

/* ------------------------------------------------------------------ */
void sign_Up_interface(Sign_Up_Input *sign_up_input)
{
    int choice, c;

    while (1) {
        system(CLEAR);

        printf("================================================\n");
        printf("\tWELCOME TO GADGET FINDING SYSTEM\n");
        printf("================================================\n");
        printf("- Username must be at least 5 characters long.\n");
        printf("- Password must be at least 8 characters long.\n\n");

        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {

        case 1:
            sign_Up(sign_up_input);
            printf("Press Enter to continue...");
            getchar();
            break;

        case 2:
            Log_In(sign_up_input);
            if (sign_up_input->success)
                return;
            break;

        case 3:
            printf("Exiting...\n");
            return;

        default:
            printf("Invalid choice.\n");
        }
    }
}

/* ------------------------------------------------------------------ */
void sign_Up(Sign_Up_Input *sign_up_input)
{
    system(CLEAR);

    printf("================================================\n");
    printf("\tSIGN UP\n");
    printf("================================================\n");

    while (1) {
        printf("Enter Username: ");

        fgets(sign_up_input->file_username,
              sizeof(sign_up_input->file_username),
              stdin);

        sign_up_input->file_username[
            strcspn(sign_up_input->file_username, "\n")
        ] = '\0';

        if (strlen(sign_up_input->file_username) < 5) {
            printf("Username too short.\n");
            continue;
        }

        if (strchr(sign_up_input->file_username, ' ') != NULL) {
            printf("Username cannot contain spaces.\n");
            continue;
        }

        FILE *check = fopen("sign_up.txt", "r");
        int duplicate = 0;

        if (check != NULL) {
            char user[50], pass[50];
            while (fscanf(check, "%49s %49s", user, pass) == 2) {
                if (strcmp(user, sign_up_input->file_username) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            fclose(check);
        }

        if (duplicate) {
            printf("Username already exists.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Password: ");

        fgets(sign_up_input->file_password,
              sizeof(sign_up_input->file_password),
              stdin);

        sign_up_input->file_password[
            strcspn(sign_up_input->file_password, "\n")
        ] = '\0';

        if (strlen(sign_up_input->file_password) < 8) {
            printf("Password too short.\n");
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
        printf("Could not save user.\n");
        return;
    }

    fprintf(user_file,
            "%s %s\n",
            sign_up_input->file_username,
            sign_up_input->file_password);

    fclose(user_file);

    printf("Sign Up Successful!\n");
}

/* ------------------------------------------------------------------ */
void Log_In(Sign_Up_Input *sign_up_input)
{
    system(CLEAR);

    printf("================================================\n");
    printf("\tLOG IN\n");
    printf("================================================\n");

    int attempts = 0;

    while (attempts < 3) {

        printf("Enter Username: ");
        fgets(sign_up_input->username,
              sizeof(sign_up_input->username), stdin);
        sign_up_input->username[
            strcspn(sign_up_input->username, "\n")] = '\0';

        printf("Enter Password: ");
        fgets(sign_up_input->password,
              sizeof(sign_up_input->password), stdin);
        sign_up_input->password[
            strcspn(sign_up_input->password, "\n")] = '\0';

        FILE *user_file = fopen("sign_up.txt", "r");

        if (user_file == NULL) {
            printf("No users found.\n");
            return;
        }

        int found = 0;

        while (fscanf(user_file,
                      "%49s %49s",
                      sign_up_input->file_username,
                      sign_up_input->file_password) == 2)
        {
            if (strcmp(sign_up_input->username,
                       sign_up_input->file_username) == 0)
            {
                found = 1;
                if (strcmp(sign_up_input->password,
                           sign_up_input->file_password) == 0)
                    found = 2;
                break;
            }
        }

        fclose(user_file);

        if (found == 2) {
            printf("Login Successful!\n");
            sign_up_input->success = 1;
            return;
        }
        else if (found == 1)
            printf("Wrong password.\n");
        else
            printf("Username not found.\n");

        attempts++;
    }

    printf("Too many failed attempts.\n");
}

/* ------------------------------------------------------------------ */
void gadget_interface(void)
{
    loadFromFile();

    int choice;

    while (1) {
        system(CLEAR);

        printf("\n");
        printf("==================================================\n");
        printf("              SMART GADGET FINDER\n");
        printf("==================================================\n");
        printf("1. Search Gadget\n");
        printf("2. Show Gadgets\n");
        printf("3. Add Product\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearLeftoverInput();
            printf("Invalid input.\n");
            continue;
        }

        clearLeftoverInput();

        switch (choice) {
        case 1: searchProducts(); break;
        case 2: showAllByType();  break;
        case 3: addProduct();     break;
        case 4: deleteProduct();  break;
        case 5:
            printf("Goodbye!\n");
            return;
        default:
            printf("Invalid choice.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }
}

/* ------------------------------------------------------------------ */
void makeUpperCase(char *word)
{
    while (*word) {
        *word = toupper((unsigned char)*word);
        word++;
    }
}

void clearLeftoverInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printDashes(int howMany)
{
    for (int i = 0; i < howMany; i++)
        putchar('-');
    putchar('\n');
}

void featureLabels(const char *type,char *label1,char *label2,int  *featureCount)
{
    if (strcmp(type, "TV") == 0) {
        strcpy(label1, "Screen Size (inches)");
        strcpy(label2, "");
        *featureCount = 1;
    }
    else if (strcmp(type, "PHONE") == 0) {
        strcpy(label1, "RAM (GB)");
        strcpy(label2, "ROM (GB)");
        *featureCount = 2;
    }
    else if (strcmp(type, "CAMERA") == 0) {
        strcpy(label1, "Megapixels");
        strcpy(label2, "");
        *featureCount = 1;
    }
    else {
        strcpy(label1, "Feature");
        strcpy(label2, "");
        *featureCount = 1;
    }
}


void loadFromFile(void)
{
    FILE *file = fopen("Gadget_info.txt", "r");

    if (file == NULL) {
        printf("No saved products found.\n");
        return;
    }

    count = 0;

    while (count < MAX_ITEMS &&
           fscanf(file,
                  "%9s %49s %d %d %d",
                  items[count].type,
                  items[count].name,
                  &items[count].price,
                  &items[count].feature,
                  &items[count].feature2) == 5)
    {
        makeUpperCase(items[count].type);
        count++;
    }

    fclose(file);
}

void saveToFile(void)
{
    FILE *file = fopen("Gadget_info.txt", "w");

    if (file == NULL) {
        printf("Could not save file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file,
                "%s %s %d %d %d\n",
                items[i].type,
                items[i].name,
                items[i].price,
                items[i].feature,
                items[i].feature2);
    }

    fclose(file);
}

void addProduct(void)
{
    if (count >= MAX_ITEMS) {
        printf("Storage full.\n");
        return;
    }

    product_information p;
    memset(&p, 0, sizeof(p));

    char label1[100], label2[100];
    int  featureCount;

    printf("\n--- Add Product ---\n");

    /* --- type --- */
    while (1) {
        printf("Type (TV/PHONE/CAMERA): ");
        scanf("%9s", p.type);
        clearLeftoverInput();
        makeUpperCase(p.type);

        if (strcmp(p.type, "TV")     == 0 ||
            strcmp(p.type, "PHONE")  == 0 ||
            strcmp(p.type, "CAMERA") == 0)
            break; 
        printf("Invalid type.\n");
    }

    /* --- name --- */
    printf("Product Name: ");
    scanf("%49s", p.name);
    clearLeftoverInput();

    /* --- price --- */
    while (1) {
        printf("Price: ");
        if (scanf("%d", &p.price) == 1 && p.price > 0) {
            clearLeftoverInput();
            break;
        }
        clearLeftoverInput();
        printf("Invalid price.\n");
    }

    /* --- feature(s) ---
       FIX: Loop now uses break (not return) so the product is saved.
            feature2 is read for PHONE; 0 is stored for other types.   */
    featureLabels(p.type, label1, label2, &featureCount);

    while (1) {
        printf("%s: ", label1);
        if (scanf("%d", &p.feature) == 1 && p.feature > 0) {
            clearLeftoverInput();

            if (featureCount == 2) {
                /* PHONE: also ask for ROM */
                while (1) {
                    printf("%s: ", label2);
                    if (scanf("%d", &p.feature2) == 1 && p.feature2 > 0) {
                        clearLeftoverInput();
                        break;
                    }
                    clearLeftoverInput();
                    printf("Invalid value.\n");
                }
            }

            break;  /* FIX: was 'return', which skipped saving */
        }
        clearLeftoverInput();
        printf("Invalid value.\n");
    }

    items[count++] = p;
    saveToFile();
    printf("Product added successfully.\n");
}


void deleteProduct(void)
{
    char targetName[50];

    printf("Enter product name to delete: ");
    scanf("%49s", targetName);
    clearLeftoverInput();

    int foundAt = -1;

    for (int i = 0; i < count; i++) {
        if (strcasecmp(items[i].name, targetName) == 0) {
            foundAt = i;
            break;
        }
    }

    if (foundAt == -1) {
        printf("Product not found.\n");
        return;
    }

    for (int i = foundAt; i < count - 1; i++)
        items[i] = items[i + 1];

    count--;
    saveToFile();
    printf("Product deleted.\n");
}

void showAllByType(void)
{
    char label1[100], label2[100];
    int  featureCount;
    char type[10];
    while (1){
    printf("Enter product type to display (TV/PHONE/CAMERA): ");
    scanf("%9s", type);
    makeUpperCase(type);           /* FIX: was missing in original */
    clearLeftoverInput();
  
    if (strcmp(type, "TV")     == 0 ||
        strcmp(type, "PHONE")  == 0 ||
        strcmp(type, "CAMERA") == 0)
    {
      break;  
    }
    printf("Invalid type.\n");
}

    featureLabels(type, label1, label2, &featureCount);

    printf("\n--- %s PRODUCTS ---\n", type);

    if (featureCount == 2)
        printf("%-25s %-12s %-10s %-10s\n", "Name", "Price", label1, label2);
    else
        printf("%-25s %-12s %-10s\n", "Name", "Price", label1);

    printDashes(55);

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(items[i].type, type) == 0) {
            if (featureCount == 2)
                printf("%-25s %-12d %-10d %-10d\n",
                       items[i].name, items[i].price,
                       items[i].feature, items[i].feature2);
            else
                printf("%-25s %-12d %-10d\n",
                       items[i].name, items[i].price, items[i].feature);
            found++;
        }
    }

    if (!found)
        printf("No products found.\n");
}

int compareByPrice(const void *a, const void *b)
{
    return ((product_information *)a)->price -
           ((product_information *)b)->price;
}

void searchProducts(void){
    int budget;
    int wantedFeature;
    int wantedFeature2 = 0;
    int tolerance;

    char type[10];

    char label1[100];
    char label2[100];

    int featureCount;

    printf("Enter product type to search (TV/PHONE/CAMERA): ");

    scanf("%9s", type);

    makeUpperCase(type);

    clearLeftoverInput();

    if (strcmp(type, "TV") != 0 &&
        strcmp(type, "PHONE") != 0 &&
        strcmp(type, "CAMERA") != 0)
    {
        printf("Invalid type.\n");
        return;
    }

    featureLabels(type, label1, label2, &featureCount);

    printf("\n--- Search %s ---\n", type);


    while (1) {

        printf("Maximum Budget: ");

        if (scanf("%d", &budget) == 1 &&
            budget > 0)
        {
            clearLeftoverInput();
            break;
        }

        clearLeftoverInput();

        printf("Invalid budget.\n");
    }


    while (1) {

        printf("Desired %s: ", label1);

        if (scanf("%d", &wantedFeature) == 1 &&
            wantedFeature > 0)
        {
            clearLeftoverInput();
            break;
        }

        clearLeftoverInput();

        printf("Invalid feature.\n");
    }


    if (featureCount == 2) {

        while (1) {

            printf("Desired %s: ", label2);

            if (scanf("%d", &wantedFeature2) == 1 &&
                wantedFeature2 > 0)
            {
                clearLeftoverInput();
                break;
            }

            clearLeftoverInput();

            printf("Invalid feature.\n");
        }
    }

    while (1) {

        printf("Tolerance (+/-): ");

        if (scanf("%d", &tolerance) == 1 &&
            tolerance >= 0)
        {
            clearLeftoverInput();
            break;
        }

        clearLeftoverInput();

        printf("Invalid tolerance.\n");
    }

    product_information results[MAX_ITEMS];

    int resultCount = 0;

    for (int i = 0; i < count; i++) {

        int typeMatch =
            strcmp(items[i].type, type) == 0;

        int priceOkay =
            items[i].price <= budget;

        int featureOkay =
            abs(items[i].feature - wantedFeature)
            <= tolerance;

        if (featureCount == 2) {

            featureOkay =
                featureOkay &&
                abs(items[i].feature2 - wantedFeature2)
                <= tolerance;
        }

        if (typeMatch && priceOkay && featureOkay) {

            results[resultCount++] = items[i];
        }
    }


    if (resultCount == 0) {

        printf("No matching products found.\n");
        return;
    }

    qsort(results,resultCount,sizeof(product_information),compareByPrice);

    system(CLEAR);
    printf("\n--- RESULTS ---\n");

    if (featureCount == 2)
    {
        printf("%-25s %-12s %-15s %-15s\n","Name","Price",label1,label2);
    }
    else
    {
        printf("%-25s %-12s %-15s\n",
               "Name",
               "Price",
               label1);
    }

    printDashes(70);

    for (int i = 0; i < resultCount; i++) {

        if (featureCount == 2)
        {
            printf("%-25s %-12d %-15d %-15d\n",
                   results[i].name,
                   results[i].price,
                   results[i].feature,
                   results[i].feature2);
        }
        else
        {
            printf("%-25s %-12d %-15d\n",
                   results[i].name,
                   results[i].price,
                   results[i].feature);
        }
    }

    printDashes(70);
}
