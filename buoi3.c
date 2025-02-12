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
    char status[10]; // Trạng thái người dùng: 'active' hoặc 'inactive'
} User;

User users[MAX_USERS];
int userCount = 0;
char adminPassword[] = "admin123"; // Mật khẩu admin mặc định

// Khai báo các hàm
void displayMenu();
void adminLogin();
void adminMenu();
void addUserForAdmin();
void displayUsersForAdmin();
void searchUserByName();
void searchUserByID();
int isDuplicateUser(char *id, char *phone, char *email);

// Hàm này chờ người dùng nhấn Enter để quay lại menu chính
void waitForUser() {
    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n');
}

// Hàm hiển thị danh sách người dùng cho admin
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

// Hàm tìm kiếm người dùng theo tên
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

// Hàm tìm kiếm người dùng theo ID
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

// Hàm kiểm tra trùng lặp người dùng
int isDuplicateUser(char *id, char *phone, char *email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0 || strcmp(users[i].phone, phone) == 0 || strcmp(users[i].email, email) == 0) {
            return 1; // Đã tồn tại
        }
    }
    return 0; // Không trùng
}

// Hàm thêm người dùng mới cho admin
void addUserForAdmin() {
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        waitForUser();
        return;
    }
    
    User newUser;

    // Tạo ID tự động tăng dần
    sprintf(newUser.id, "USER%03d", userCount + 1); // Ví dụ: USER001, USER002, USER003,...

    printf("\nGenerated User ID: %s\n", newUser.id);
    
    // Nhập thông tin người dùng khác
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
    
    users[userCount++] = newUser;
    printf("User added successfully.\n");
    waitForUser();
}

// Hàm đăng nhập admin
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

// Menu admin
void adminMenu() {
    int choice;
    
    do {
        // Hiển thị menu admin
        printf("\n*** Admin Menu ***\n");
        printf("[1]. Display user list\n");
        printf("[2]. Add user\n");
        printf("[3]. Search user by name\n");
        printf("[4]. Search user by ID\n");
        printf("[5]. Exit\n");
        printf("*** End of Menu ***\n");  // Thêm banner kết thúc menu

        // Nhập lựa chọn từ admin
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Loại bỏ ký tự không hợp lệ
            continue;
        }
        while (getchar() != '\n'); // Loại bỏ ký tự xuống dòng
        
        // Xử lý lựa chọn
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
            case 4: 
                searchUserByID(); 
                break;
            case 5: 
                printf("Exiting...\n");
                break;
            default: 
                printf("Invalid choice. Try again.\n"); 
                break;
        }
    } while (choice != 5);
}

// Hiển thị menu chính
void displayMenu() {
    int choice;
    
    while (1) {
        // Hiển thị menu chính
        printf("\n*** Bank Manager System ***\n");
        printf("[1]. Admin login\n");
        printf("[0]. Exit\n");
        printf("Your choice: ");
        
        // Xử lý lựa chọn của người dùng
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');  // Loại bỏ ký tự không hợp lệ
            continue;
        }
        while (getchar() != '\n');  // Loại bỏ ký tự xuống dòng
        
        // Xử lý lựa chọn
        switch (choice) {
            case 1:
                adminLogin();  // Gọi hàm đăng nhập admin
                break;
            case 0:
                printf("Exiting program...\n");  // Thoát chương trình
                return;
            default:
                printf("Invalid choice. Please try again.\n");  // Lựa chọn không hợp lệ
                break;
        }
    }
}

// Hàm main
int main() {
    displayMenu();  
    return 0;
}
