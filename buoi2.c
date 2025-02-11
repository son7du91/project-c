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
    char status[10];
} User;

User users[MAX_USERS];
int userCount = 0;
char adminPassword[] = "admin123";  // Mật khẩu admin mặc định

// Khai báo các hàm
void displayMenu();
void adminLogin();
void adminMenu();
void addUserForAdmin();
void displayUsersForAdmin();
void searchUserByName();
int isDuplicateUser(char *id, char *phone, char *email);

// Hiển thị menu chính
void displayMenu() {
    int choice;
    while (1) {
        printf("\n*** Bank Manager System ***\n");
        printf("[1]. Admin login\n");
        printf("[0]. Exit\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 0:
                printf("Exiting program...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Đăng nhập admin
void adminLogin() {
    char password[20];
    printf("\nEnter admin password: ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n");

    if (strcmp(password, adminPassword) == 0) {
        printf("Admin login successful!\n");
        adminMenu();
    } else {
        printf("Incorrect password! Try again.\n");
    }
}

// Menu dành cho admin
void adminMenu() {
    int choice;
    while (1) {
        printf("\n*** Admin Menu ***\n");
        printf("[1]. Display user list\n");
        printf("[2]. Add user\n");
        printf("[3]. Search user by name\n");
        printf("[0]. Logout\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                displayUsersForAdmin();
                break;
            case 2:
                addUserForAdmin();
                break;
            case 3:
                searchUserByName();
                break;
            case 0:
                printf("Admin logged out.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Kiểm tra trùng lặp thông tin người dùng
int isDuplicateUser(char *id, char *phone, char *email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0 || strcmp(users[i].phone, phone) == 0 || strcmp(users[i].email, email) == 0) {
            return 1; // Đã tồn tại
        }
    }
    return 0; // Không trùng
}

// Thêm người dùng cho admin
void addUserForAdmin() {
    if (userCount >= MAX_USERS) {
        printf("User list is full!\n");
        return;
    }

    User newUser;

    // Nhập thông tin người dùng
    printf("Enter user name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
    if (strlen(newUser.name) == 0) {
        printf("User name cannot be empty!\n");
        return;
    }

    printf("Enter phone number: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;
    if (strlen(newUser.phone) == 0) {
        printf("Phone number cannot be empty!\n");
        return;
    }

    printf("Enter email address: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;
    if (strlen(newUser.email) == 0) {
        printf("Email cannot be empty!\n");
        return;
    }

    printf("Enter user ID: ");
    fgets(newUser.id, sizeof(newUser.id), stdin);
    newUser.id[strcspn(newUser.id, "\n")] = 0;
    if (strlen(newUser.id) == 0) {
        printf("User ID cannot be empty!\n");
        return;
    }

    // Kiểm tra trùng lặp thông tin
    if (isDuplicateUser(newUser.id, newUser.phone, newUser.email)) {
        printf("User ID, phone number, or email already exists!\n");
        return;
    }

    // Thiết lập mật khẩu và trạng thái mặc định
    strcpy(newUser.password, "123456");
    strcpy(newUser.status, "Open");

    // Lưu vào danh sách
    users[userCount] = newUser;
    userCount++;

    printf("User added successfully!\n");
}

// Hiển thị danh sách người dùng
void displayUsersForAdmin() {
    if (userCount == 0) {
        printf("\nNo users found!\n");
        return;
    }
    printf("\nUser List:\n");
    printf("+------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-12s | %-25s | %-15s | %-10s |\n", "ID", "Name", "Phone", "Email", "User ID", "Status");
    printf("+------------------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < userCount; i++) {
        printf("| %-3d | %-20s | %-12s | %-25s | %-15s | %-10s |\n", i + 1, users[i].name, users[i].phone, users[i].email, users[i].id, users[i].status);
    }
    printf("--------------------------------------------------------------------------------------------------------\n");
}

// Tìm kiếm người dùng theo tên
void searchUserByName() {
    char searchName[50];
    printf("\nEnter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;
    printf("\nSearch Results:\n");
    printf("+------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-20s | %-12s | %-25s | %-15s | %-10s |\n", "ID", "Name", "Phone", "Email", "User ID", "Status");
    printf("+------------------------------------------------------------------------------------------------------+\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName)) {
            printf("| %-3d | %-20s | %-12s | %-25s | %-15s | %-10s |\n", i + 1, users[i].name, users[i].phone, users[i].email, users[i].id, users[i].status);
            found = 1;
        }
    }

    if (!found) {
        printf("No users found with the given name.\n");
    }
}

// Hàm main
int main() {
    displayMenu();
    return 0;
}

