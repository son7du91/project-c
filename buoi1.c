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
void addUserForAdmin();  // Hàm thêm người dùng từ menu Admin
void displayUsersForAdmin();  // Hiển thị danh sách người dùng từ menu Admin

// Hiển thị menu chính
void displayMenu() {
    int choice;
    while (1) {
        printf("\n*** Bank Manager System ***\n");
        printf("1. Admin login\n");  // Đổi thành "1" cho đăng nhập admin
        printf("0. Exit\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Xóa bộ nhớ đệm để tránh lỗi lặp vô hạn
            continue;
        }
        while (getchar() != '\n'); // Xóa bộ nhớ đệm để tránh lỗi fgets()
        switch (choice) {
            case 1:
                adminLogin();  // Đăng nhập admin
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
        adminMenu();  // Hiển thị menu admin
    } else {
        printf("Incorrect password! Try again.\n");
    }
}

// Menu dành cho admin
void adminMenu() {
    int choice;
    while (1) {
        printf("\n*** Admin Menu ***\n");
        printf("1. Display user list\n");  // Hiển thị danh sách người dùng
        printf("2. Add user\n");  // Thêm người dùng
        printf("0. Logout\n");  // Đăng xuất
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Xóa bộ nhớ đệm
            continue;
        }
        while (getchar() != '\n'); // Xóa bộ nhớ đệm
        switch (choice) {
            case 1:
                displayUsersForAdmin();  // Hiển thị danh sách người dùng cho admin
                break;
            case 2:
                addUserForAdmin();  // Thêm người dùng cho admin
                break;
            case 0:
                printf("Admin logged out.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Hiển thị danh sách người dùng cho admin
void displayUsersForAdmin() {
    if (userCount == 0) {
        printf("\nNo users found!\n");
        return;
    }
    printf("\nUser List:\n");
    printf("---------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-12s | %-25s | %-15s | %-10s |\n", "ID", "Name", "Phone", "Email", "User ID", "Status");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < userCount; i++) {
        printf("| %-3d | %-20s | %-12s | %-25s | %-15s | %-10s |\n", i + 1, users[i].name, users[i].phone, users[i].email, users[i].id, users[i].status);
    }
    printf("---------------------------------------------------------------\n");
}

// Thêm người dùng cho admin
void addUserForAdmin() {
    if (userCount >= MAX_USERS) {
        printf("User list is full!\n");
        return;
    }

    // Nhập tên người dùng
    printf("Enter user name: ");
    fgets(users[userCount].name, sizeof(users[userCount].name), stdin);
    users[userCount].name[strcspn(users[userCount].name, "\n")] = 0;  // Xóa dấu xuống dòng nếu có

    // Nhập số điện thoại
    printf("Enter phone number: ");
    fgets(users[userCount].phone, sizeof(users[userCount].phone), stdin);
    users[userCount].phone[strcspn(users[userCount].phone, "\n")] = 0;  // Xóa dấu xuống dòng nếu có
    
    // Nhập email
    printf("Enter email address: ");
    fgets(users[userCount].email, sizeof(users[userCount].email), stdin);
    users[userCount].email[strcspn(users[userCount].email, "\n")] = 0;  // Xóa dấu xuống dòng nếu có

    // Nhập ID người dùng
    printf("Enter user ID: ");
    fgets(users[userCount].id, sizeof(users[userCount].id), stdin);
    users[userCount].id[strcspn(users[userCount].id, "\n")] = 0;  // Xóa dấu xuống dòng nếu có

    // Đặt mật khẩu và trạng thái mặc định
    strcpy(users[userCount].password, "123456");  // Mật khẩu mặc định
    strcpy(users[userCount].status, "Open");     // Trạng thái mặc định

    printf("User added successfully!\n");
    userCount++;
}

// Hàm main
int main() {
    displayMenu();
    return 0;
}
