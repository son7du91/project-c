#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
    char id[20];
    char password[20];
    char status[10]; // active or inactive
    int locked; // 0: unlocked, 1: locked
} User;

User users[MAX_USERS];
int userCount = 0;
char adminPassword[20] = "admin123"; // Default admin password

void adminLogin(int* loggedIn) {
    char enteredPassword[20];

    printf("\n=====================================\n");
    printf("         *** ADMIN LOGIN ***         \n");
    printf("=====================================\n");
    printf("Enter admin password: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = 0;

    if (strcmp(enteredPassword, adminPassword) == 0) {
        printf("\nLogin successful!\n");
        *loggedIn = 1;
    } else {
        printf("\nIncorrect password. Try again.\n");
    }
}

void searchUserByID() {
    char userID[20];
    printf("\nEnter User ID to search: ");
    fgets(userID, sizeof(userID), stdin);
    userID[strcspn(userID, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, userID) == 0) {
            printf("\n+---------------------------------------------------------------------------------+\n");
            printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
                   "ID", "Name", "Phone", "Email", "Status");
            printf("+---------------------------------------------------------------------------------+\n");
            
            printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
                   users[i].id, 
                   users[i].name, 
                   users[i].phone, 
                   users[i].email, 
                   users[i].status);
                   
            printf("+---------------------------------------------------------------------------------+\n");

            // Hiển thị thông tin chi tiết thêm
            printf("\nDetailed Information:");
            printf("\n---------------------");
            printf("\nUser ID: %s", users[i].id);
            printf("\nFull Name: %s", users[i].name);
            printf("\nPhone Number: %s", users[i].phone);
            printf("\nEmail Address: %s", users[i].email);
            printf("\nAccount Status: %s", users[i].status);
            printf("\nAccount State: %s", users[i].locked ? "Locked" : "Unlocked");
            printf("\n---------------------\n");
            
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("\n+---------------------------------------------------------------------------------+\n");
        printf("                      No user found with ID: %-8s                               \n", userID);
        printf("+---------------------------------------------------------------------------------+\n");
    }
}

void addUserForAdmin() {
    if (userCount >= MAX_USERS) {
        printf("\nMaximum user limit reached.\n");
        return;
    }

    User newUser;
    sprintf(newUser.id, "USER%03d", userCount + 1);

    printf("\nGenerated User ID: %s\n", newUser.id);
    printf("Enter Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;

    printf("Enter Phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;

    printf("Enter Password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strcspn(newUser.password, "\n")] = 0;

    strcpy(newUser.status, "active");
    newUser.locked = 0;

    users[userCount++] = newUser;
    printf("\nUser added successfully.\n");
}

void lockUnlockUser() {
    char userID[20];
    printf("\nEnter User ID to lock/unlock: ");
    fgets(userID, sizeof(userID), stdin);
    userID[strcspn(userID, "\n")] = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, userID) == 0) {
            users[i].locked = !users[i].locked;
            // Update status based on lock state
            if (users[i].locked) {
                strcpy(users[i].status, "inactive");
            } else {
                strcpy(users[i].status, "active");
            }
            printf("\nUser %s has been %s.\n", users[i].name, users[i].locked ? "locked" : "unlocked");
            printf("Status changed to: %s\n", users[i].status);
            return;
        }
    }
    printf("\nNo user found with the ID %s.\n", userID);
}

void sortUsersByName() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (strcmp(users[i].name, users[j].name) > 0) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
    printf("\nUsers sorted by name successfully.\n");
}

void changeAdminPassword() {
    char newPassword[20];
    printf("\nEnter new admin password: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    newPassword[strcspn(newPassword, "\n")] = 0;

    strcpy(adminPassword, newPassword);
    printf("\nAdmin password changed successfully.\n");
}

void displayUsersForAdmin() {
    if (userCount == 0) {
        printf("\nNo users to display.\n");
        return;
    }

    printf("\n+---------------------------------------------------------------------------------+\n");
    printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
           "ID", "Name", "Phone", "Email", "Status");
    printf("+---------------------------------------------------------------------------------+\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
               users[i].id, 
               users[i].name, 
               users[i].phone, 
               users[i].email, 
               users[i].status);
    }

    printf("+---------------------------------------------------------------------------------+\n");
}

void adminMenu() {
    int choice;
    do {
        printf("\n=====================================\n");
        printf("          *** ADMIN MENU ***         \n");
        printf("=====================================\n");
        printf("[1] Display Users\n");
        printf("[2] Add User\n");
        printf("[3] Lock/Unlock User\n");
        printf("[4] Sort Users by Name\n");
        printf("[5] Change Admin Password\n");
        printf("[6] Search User by ID\n");
        printf("[0] Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }
        while (getchar() != '\n'); // Clear buffer after number input

        switch (choice) {
            case 1: displayUsersForAdmin(); break;
            case 2: addUserForAdmin(); break;
            case 3: lockUnlockUser(); break;
            case 4: sortUsersByName(); break;
            case 5: changeAdminPassword(); break;
            case 6: searchUserByID(); break;
            case 0: return;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    } while (1);
}

void displayMenu() {
    int choice;
    int loggedIn = 0;
    
    while (1) {
        printf("\n=====================================\n");
        printf("      *** BANK MANAGER SYSTEM ***    \n");
        printf("=====================================\n");
        printf("[1] Admin Login\n");
        printf("[0] Exit\n");
        printf("-------------------------------------\n");
        printf("Your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }
        while (getchar() != '\n'); // Clear buffer after number input

        switch (choice) {
            case 1:
                adminLogin(&loggedIn);
                if (loggedIn) {
                    adminMenu();
                }
                break;
            case 0:
                printf("\nGoodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

int main() {
    displayMenu();
    return 0;
}