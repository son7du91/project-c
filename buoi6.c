#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define FILE_PATH "C:\\BAITAPC\\test.c"

// Cấu trúc người dùng
typedef struct {
    char id[20];
    char name[50];
    char phone[15];
    char email[50];
    char password[20];
    char status[10]; // "active" or "inactive"
    int locked; // 0: not locked, 1: locked
} User;

User users[MAX_USERS];
int userCount = 0;
char adminPassword[20] = "admin123"; // Mật khẩu mặc định của admin

// Khai báo hàm
void saveUsersToFile();
void loadUsersFromFile();
void displayMenu();
void adminLogin();
void adminMenu();
void addUser();
void displayUsers();
void searchUserByName();
void searchUserByID();
void lockUnlockUserByID();
void sortUsersByName();
void changeAdminPassword();

// Lưu người dùng vào tệp
void saveUsersToFile() {
    FILE *file = fopen(FILE_PATH, "w");
    if (!file) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%d\n", 
                users[i].id, users[i].name, users[i].phone, users[i].email, 
                users[i].password, users[i].status, users[i].locked);
    }
    fclose(file);
}

// Tải người dùng từ tệp    
void loadUsersFromFile() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("No user data found.\n");
        return;
    }
    while (fscanf(file, "%19[^,],%49[^,],%14[^,],%49[^,],%19[^,],%9[^,],%d\n", 
                  users[userCount].id, users[userCount].name, users[userCount].phone, 
                  users[userCount].email, users[userCount].password, users[userCount].status, 
                  &users[userCount].locked) == 7) {
        userCount++;
        if (userCount >= MAX_USERS) break;
    }
    fclose(file);
}

// Hiển thị menu chính
void displayMenu() {
    int choice;
    while (1) {
        printf("\n*** Bank Manager System ***\n");
        printf("[1]. Admin login\n");
        printf("[0]. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xóa bộ đệm đầu vào

        switch (choice) {
            case 1: adminLogin(); break;
            case 0: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n"); break;
        }
    }
}

// Đăng nhập admin
void adminLogin() {
    char password[20];
    printf("Enter admin password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Xóa ký tự xuống dòng

    if (strcmp(password, adminPassword) == 0) {
        adminMenu();
    } else {
        printf("Incorrect password!\n");
    }
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        printf("\n*** Admin Menu ***\n");
        printf("[1] Display Users\n");
        printf("[2] Add User\n");
        printf("[3] Search User by Name\n");
        printf("[4] Search User by ID\n");
        printf("[5] Lock/Unlock User\n");
        printf("[6] Sort Users by Name\n");
        printf("[7] Change Admin Password\n");
        printf("[0] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Xóa bộ đệm đầu vào

        switch (choice) {
            case 1: displayUsers(); break;
            case 2: addUser(); break;
            case 3: searchUserByName(); break;
            case 4: searchUserByID(); break;
            case 5: lockUnlockUserByID(); break;
            case 6: sortUsersByName(); break;
            case 7: changeAdminPassword(); break;
            case 0: return;
            default: printf("Invalid choice. Try again.\n"); break;
        }
    } while (choice != 0);
}

// thêm người dùng mới
void addUser() {
    if (userCount >= MAX_USERS) {
        printf("User list is full!\n");
        return;
    }

    User newUser;
    printf("Enter ID: ");
    scanf("%s", newUser.id);
    printf("Enter Name: ");
    scanf("%s", newUser.name);
    printf("Enter Phone: ");
    scanf("%s", newUser.phone);
    printf("Enter Email: ");
    scanf("%s", newUser.email);
    printf("Enter Password: ");
    scanf("%s", newUser.password);

    strcpy(newUser.status, "active");
    newUser.locked = 0;

    users[userCount++] = newUser;
    saveUsersToFile();
    printf("User added successfully!\n");
}

// Hiển thị danh sách người dùng
void displayUsers() {
    printf("\nUser List:\n");
    for (int i = 0; i < userCount; i++) {
        printf("ID: %s, Name: %s, Phone: %s, Email: %s, Status: %s, Locked: %s\n",
               users[i].id, users[i].name, users[i].phone, users[i].email,
               users[i].status, users[i].locked ? "Yes" : "No");
    }
}

// tìm kiếm người dùng theo tên
void searchUserByName() {
    char searchName[50];
    printf("Enter name to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName)) {
            printf("ID: %s, Name: %s, Phone: %s, Email: %s, Status: %s, Locked: %s\n",
                   users[i].id, users[i].name, users[i].phone, users[i].email,
                   users[i].status, users[i].locked ? "Yes" : "No");
        }
    }
}

// tìm kiếm người dùng theo ID
void searchUserByID() {
    char searchID[20];
    printf("Enter ID to search: ");
    scanf("%s", searchID);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, searchID) == 0) {
            printf("ID: %s, Name: %s, Phone: %s, Email: %s, Status: %s, Locked: %s\n",
                   users[i].id, users[i].name, users[i].phone, users[i].email,
                   users[i].status, users[i].locked ? "Yes" : "No");
            return;
        }
    }
    printf("User not found.\n");
}

// Lock/Unlock người dùng theo ID
void lockUnlockUserByID() {
    char id[20];
    printf("Enter ID to lock/unlock: ");
    scanf("%s", id);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0) {
            users[i].locked = !users[i].locked;
            saveUsersToFile();
            printf("User %s has been %s.\n", id, users[i].locked ? "locked" : "unlocked");
            return;
        }
    }
    printf("User ID not found.\n");
}

// sắp xếp người dùng theo tên
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
    saveUsersToFile();
    printf("User list sorted by name.\n");
}

// thay đổi mật khẩu admin
void changeAdminPassword() {
    printf("Enter new admin password: ");
    scanf("%s", adminPassword);
    printf("Admin password changed successfully!\n");
}

// Hàm chính
int main() {
    loadUsersFromFile();
    displayMenu();
    return 0;
}
