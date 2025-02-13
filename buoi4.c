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
char adminPassword[] = "admin123"; // Default admin password

// Function declarations
void displayMenu();
void adminLogin();
void adminMenu();
void addUserForAdmin();
void displayUsersForAdmin();
void searchUserByName();
void searchUserByID();
int isDuplicateUser(char *id, char *phone, char *email);
void waitForUser();
void lockUnlockUserByID();
void sortUsersByName();

// Wait for user to press Enter to return to the menu
void waitForUser() {
    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n');  // Ensure input is complete before continuing
}

// Display users for admin
void displayUsersForAdmin() {
    if (userCount == 0) {
        printf("No users to display.\n");
        waitForUser();
        return;
    }
    
    printf("\n+----------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-12s | %-25s | %-10s |\n", "ID", "Name", "Phone", "Email", "Status");
    printf("+----------------------------------------------------------------------------------+\n");
    
    for (int i = 0; i < userCount; i++) {
        printf("| %-3d | %-20s | %-12s | %-25s | %-10s |\n", i + 1, users[i].name, users[i].phone, users[i].email, users[i].status);
    }
    
    printf("+----------------------------------------------------------------------------------+\n");
    waitForUser();
}

// Search for users by name
void searchUserByName() {
    char searchName[50];
    printf("\nEnter user name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;
    printf("\n+----------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-12s | %-25s | %-10s |\n", "ID", "Name", "Phone", "Email", "Status");
    printf("+----------------------------------------------------------------------------------+\n");
    
    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName)) {
            printf("| %-3d | %-20s | %-12s | %-25s | %-10s |\n", i + 1, users[i].name, users[i].phone, users[i].email, users[i].status);
            found = 1;
        }
    }
    
    if (!found) {
        printf("| %-70s |\n", "No user found with the given name.");
    }
    printf("+----------------------------------------------------------------------------------+\n");
    waitForUser();
}

// Search for users by ID
void searchUserByID() {
    char searchID[20];
    printf("\nEnter user ID to search: ");
    fgets(searchID, sizeof(searchID), stdin);
    searchID[strcspn(searchID, "\n")] = 0;

    int found = 0;
    printf("\n+----------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-12s | %-25s | %-10s |\n", "ID", "Name", "Phone", "Email", "Status");
    printf("+----------------------------------------------------------------------------------+\n");
    
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, searchID) == 0) {
            printf("| %-3d | %-20s | %-12s | %-25s | %-10s |\n", i + 1, users[i].name, users[i].phone, users[i].email, users[i].status);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("| %-70s |\n", "No user found with the given ID.");
    }
    printf("+----------------------------------------------------------------------------------+\n");
    waitForUser();
}

// Check if user with the same ID, phone or email already exists
int isDuplicateUser(char *id, char *phone, char *email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0 || strcmp(users[i].phone, phone) == 0 || strcmp(users[i].email, email) == 0) {
            return 1; // Duplicate exists
        }
    }
    return 0; // No duplicate
}

// Add a new user for admin
void addUserForAdmin() {
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        waitForUser();
        return;
    }
    
    User newUser;

    // Auto-generate user ID
    sprintf(newUser.id, "USER%03d", userCount + 1); // Example: USER001, USER002, USER003,...

    printf("\nGenerated User ID: %s\n", newUser.id);
    
    // Get user details
    printf("Enter Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
    
    printf("Enter Phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;
    
    printf("Enter Email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;
    
    strcpy(newUser.status, "active");
    newUser.locked = 0;  // User is unlocked by default
    
    users[userCount++] = newUser;
    printf("User added successfully.\n");
    waitForUser();
}

// Admin login
void adminLogin() {
    char enteredPassword[20];
    printf("Enter admin password: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = 0;
    
    if (strcmp(enteredPassword, adminPassword) == 0) {
        printf("Login successful!\n");
        adminMenu();
    } else {
        printf("Incorrect password. Try again.\n");
        waitForUser();
    }
}

// Lock/unlock user by ID
void lockUnlockUserByID() {
    char userID[20];
    printf("\nEnter user ID to lock/unlock: ");
    fgets(userID, sizeof(userID), stdin);
    userID[strcspn(userID, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, userID) == 0) {
            found = 1;
            if (users[i].locked == 0) {
                users[i].locked = 1;
                printf("User %s is now locked.\n", users[i].name);
            } else {
                users[i].locked = 0;
                printf("User %s is now unlocked.\n", users[i].name);
            }
            break;
        }
    }
    
    if (!found) {
        printf("No user found with the ID %s.\n", userID);
    }
    
    waitForUser();
}

// Sort users by name
void sortUsersByName() {
    int choice;
    printf("\nChoose sort order:\n");
    printf("[1]. Ascending\n");
    printf("[2]. Descending\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');  // Clear input buffer

    if (choice == 1) {
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].name, users[j].name) > 0) {
                    User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("Users sorted in ascending order by name.\n");
    } else if (choice == 2) {
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].name, users[j].name) < 0) {
                    User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("Users sorted in descending order by name.\n");
    } else {
        printf("Invalid choice.\n");
    }

    displayUsersForAdmin();
}

// Admin menu
void adminMenu() {
    int choice;
    
    do {
        // Display admin menu
        printf("\n*** Admin Menu ***\n");
        printf("[1]. Display user list\n");
        printf("[2]. Add user\n");
        printf("[3]. Search user by name\n");
        printf("[4]. Search user by ID\n");
        printf("[5]. Lock/Unlock user\n");
        printf("[6]. Sort users by name\n");
        printf("[7]. Exit\n");
        printf("*** End of Menu ***\n");

        // Get admin choice
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer
        
        // Handle menu choice
        switch (choice) {
            case 1: displayUsersForAdmin(); break;
            case 2: addUserForAdmin(); break;
            case 3: searchUserByName(); break;
            case 4: searchUserByID(); break;
            case 5: lockUnlockUserByID(); break;
            case 6: sortUsersByName(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n"); break;
        }
    } while (choice != 7);
}

// Main menu
void displayMenu() {
    int choice;
    
    while (1) {
        // Main menu
        printf("\n*** Bank Manager System ***\n");
        printf("[1]. Admin login\n");
        printf("[0]. Exit\n");
        printf("Your choice: ");
        
        // Get user choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');  // Remove invalid input
            continue;
        }
        while (getchar() != '\n');  // Clear newline
        
        // Handle choice
        switch (choice) {
            case 1: adminLogin(); break;
            case 0: printf("Exiting program...\n"); return;
            default: printf("Invalid choice. Try again.\n"); break;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}