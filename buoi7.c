#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100 // Số lượng người dùng tối đa
#define USER_FILE "user.bin" // Tên tệp để lưu trữ thông tin người dùng

// Định nghĩa cấu trúc User (Người dùng)
typedef struct {
    char name[50]; // Tên người dùng
    char phone[15]; // Số điện thoại người dùng
    char email[50]; // Email người dùng
    char id[20]; // ID người dùng
    char password[20]; // Mật khẩu người dùng
    char status[10]; // Trạng thái tài khoản: active (hoạt động) hoặc inactive (không hoạt động)
    int locked; // Trạng thái tài khoản: 0 - mở khóa, 1 - khóa
} User;

User users[MAX_USERS]; // Mảng lưu trữ thông tin người dùng
int userCount = 0; // Số lượng người dùng hiện tại
char adminPassword[20] = "admin123"; // Mật khẩu mặc định của quản trị viên

// Hàm tải người dùng từ tệp
void loadUsersFromFile() {
    FILE* file = fopen(USER_FILE, "rb"); // Mở tệp để đọc ở chế độ nhị phân
    if (file != NULL) {
        fread(&userCount, sizeof(int), 1, file); // Đọc số lượng người dùng từ tệp
        fread(users, sizeof(User), userCount, file); // Đọc dữ liệu người dùng từ tệp
        fclose(file); // Đóng tệp
    }
}

// Hàm lưu người dùng vào tệp
void saveUsersToFile() {
    FILE* file = fopen(USER_FILE, "wb"); // Mở tệp để ghi ở chế độ nhị phân
    if (file != NULL) {
        fwrite(&userCount, sizeof(int), 1, file); // Ghi số lượng người dùng vào tệp
        fwrite(users, sizeof(User), userCount, file); // Ghi dữ liệu người dùng vào tệp
        fclose(file); // Đóng tệp
    }
}

// Hàm đăng nhập quản trị viên
void adminLogin(int* loggedIn) {
    char enteredPassword[20];

    printf("\n=====================================\n");
    printf("         *** ADMIN LOGIN ***         \n");
    printf("=====================================\n");
    printf("Enter admin password: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin); // Nhận mật khẩu từ người dùng
    enteredPassword[strcspn(enteredPassword, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    if (strcmp(enteredPassword, adminPassword) == 0) { // So sánh mật khẩu nhập vào với mật khẩu quản trị viên
        printf("\nLogin successful!\n");
        *loggedIn = 1; // Đặt trạng thái đăng nhập thành công
    } else {
        printf("\nIncorrect password. Please try again.\n");
    }
}

// Hàm tìm kiếm người dùng theo ID
void searchUserByID() {
    char userID[20];
    printf("\nEnter User ID to search: ");
    fgets(userID, sizeof(userID), stdin); // Nhận ID người dùng từ người dùng
    userID[strcspn(userID, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    int found = 0;
    for (int i = 0; i < userCount; i++) { // Duyệt qua mảng người dùng
        if (strcmp(users[i].id, userID) == 0) { // So sánh ID người dùng với ID nhập vào
            printf("\n+---------------------------------------------------------------------------------------+\n");
            printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
                   "ID", "Name", "Phone", "Email", "Status");
            printf("+---------------------------------------------------------------------------------------+\n");
            printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
                   users[i].id, 
                   users[i].name, 
                   users[i].phone, 
                   users[i].email, 
                   users[i].status);
            printf("+---------------------------------------------------------------------------------------+\n");

            found = 1; // Đặt trạng thái tìm thấy người dùng
            break;
        }
    }
    
    if (!found) { // Nếu không tìm thấy người dùng
        printf("\n+---------------------------------------------------------------------------------------+\n");
        printf("                      No user found with ID: %-8s                               \n", userID);
        printf("+---------------------------------------------------------------------------------------+\n");
    }
}

// Hàm tìm kiếm người dùng theo tên
void searchUserByName() {
    char userName[50];
    printf("\nEnter User Name to search: ");
    fgets(userName, sizeof(userName), stdin); // Nhận tên người dùng từ người dùng
    userName[strcspn(userName, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    int found = 0;
    printf("\n+---------------------------------------------------------------------------------------+\n");
    printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
           "ID", "Name", "Phone", "Email", "Status");
    printf("+---------------------------------------------------------------------------------------+\n");

    for (int i = 0; i < userCount; i++) { // Duyệt qua mảng người dùng
        if (strcasecmp(users[i].name, userName) == 0) { // So sánh không phân biệt hoa thường tên người dùng
            printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
                   users[i].id, 
                   users[i].name, 
                   users[i].phone, 
                   users[i].email, 
                   users[i].status);

            printf("+---------------------------------------------------------------------------------------+\n");

            // Hiển thị thông tin chi tiết
            printf("\nDetailed Information:");
            printf("\n---------------------");
            printf("\nUser ID: %s", users[i].id);
            printf("\nFull Name: %s", users[i].name);
            printf("\nPhone Number: %s", users[i].phone);
            printf("\nEmail Address: %s", users[i].email);
            printf("\nAccount Status: %s", users[i].status);
            printf("\nAccount State: %s", users[i].locked ? "Locked" : "Unlocked");
            printf("\n---------------------\n");

            found = 1; // Đặt trạng thái tìm thấy người dùng
        }
    }
    
    if (!found) { // Nếu không tìm thấy người dùng
        printf("\n+---------------------------------------------------------------------------------------+\n");
        printf("                      No user found with Name: %-20s                               \n", userName);
        printf("+---------------------------------------------------------------------------------------+\n");
    }
}

// Hàm thêm người dùng mới
void addUserForAdmin() {
    if (userCount >= MAX_USERS) { // Kiểm tra xem đã đạt giới hạn người dùng chưa
        printf("\nMaximum user limit reached.\n");
        return;
    }

    User newUser;
    sprintf(newUser.id, "USER%03d", userCount + 1); // Tự động tạo ID người dùng

    printf("\nGenerated User ID: %s\n", newUser.id);
    printf("Enter Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin); // Nhận tên người dùng
    newUser.name[strcspn(newUser.name, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    printf("Enter Phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin); // Nhận số điện thoại
    newUser.phone[strcspn(newUser.phone, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    printf("Enter Email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin); // Nhận email
    newUser.email[strcspn(newUser.email, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    strcpy(newUser.password, newUser.phone); // Đặt mật khẩu mặc định là số điện thoại
    strcpy(newUser.status, "active"); // Đặt trạng thái tài khoản là hoạt động
    newUser.locked = 0; // Đặt trạng thái tài khoản là mở khóa

    users[userCount++] = newUser; // Thêm người dùng mới vào mảng và tăng số lượng người dùng
    saveUsersToFile(); // Lưu thông tin người dùng vào tệp
    printf("\nUser added successfully. Default password is the phone number.\n");
}

// Hàm xóa người dùng
void deleteUser() {
    char userID[20];
    printf("\nEnter User ID to delete: ");
    fgets(userID, sizeof(userID), stdin); // Nhận ID người dùng từ người dùng
    userID[strcspn(userID, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    for (int i = 0; i < userCount; i++) { // Duyệt qua mảng người dùng
        if (strcmp(users[i].id, userID) == 0) { // So sánh ID người dùng với ID nhập vào
            for (int j = i; j < userCount - 1; j++) { // Dịch chuyển các phần tử sau người dùng bị xóa
                users[j] = users[j + 1];
            }
            userCount--; // Giảm số lượng người dùng
            saveUsersToFile(); // Lưu thông tin người dùng vào tệp
            printf("\nUser with ID %s has been deleted successfully.\n", userID);
            return;
        }
    }
    printf("\nNo user found with ID %s.\n", userID);
}

// Hàm xóa tất cả người dùng
void deleteAllUsers() {
    userCount = 0; // Đặt lại số lượng người dùng là 0
    saveUsersToFile(); // Lưu thông tin người dùng vào tệp
    printf("\nAll users have been deleted successfully.\n");
}

// Hàm khóa/mở khóa người dùng
void lockUnlockUser() {
    char userID[20];
    printf("\nEnter User ID to lock/unlock: ");
    fgets(userID, sizeof(userID), stdin); // Nhận ID người dùng từ người dùng
    userID[strcspn(userID, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    for (int i = 0; i < userCount; i++) { // Duyệt qua mảng người dùng
        if (strcmp(users[i].id, userID) == 0) { // So sánh ID người dùng với ID nhập vào
            users[i].locked = !users[i].locked; // Chuyển đổi trạng thái khóa/mở khóa
            // Cập nhật trạng thái dựa trên trạng thái khóa
            if (users[i].locked) {
                strcpy(users[i].status, "inactive");
            } else {
                strcpy(users[i].status, "active");
            }
            saveUsersToFile(); // Lưu thông tin người dùng vào tệp
            printf("\nUser %s has been %s.\n", users[i].name, users[i].locked ? "locked" : "unlocked");
            printf("Status changed to: %s\n", users[i].status);
            return;
        }
    }
    printf("\nNo user found with ID %s.\n", userID);
}

// Hàm sắp xếp người dùng theo tên
void sortUsersByName() {
    for (int i = 0; i < userCount - 1; i++) { // Duyệt qua mảng người dùng
        for (int j = i + 1; j < userCount; j++) { // So sánh từng cặp người dùng
            if (strcmp(users[i].name, users[j].name) > 0) { // So sánh tên người dùng
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
    saveUsersToFile(); // Lưu thông tin người dùng vào tệp
    printf("\nUsers sorted by name successfully.\n");
}

// Hàm thay đổi mật khẩu quản trị viên
void changeAdminPassword() {
    char newPassword[20];
    printf("\nEnter new admin password: ");
    fgets(newPassword, sizeof(newPassword), stdin); // Nhận mật khẩu mới từ người dùng
    newPassword[strcspn(newPassword, "\n")] = 0; // Loại bỏ ký tự xuống dòng

    strcpy(adminPassword, newPassword); // Cập nhật mật khẩu quản trị viên
    saveUsersToFile(); // Lưu thông tin người dùng vào tệp
    printf("\nAdmin password changed successfully.\n");
}

// Hàm hiển thị người dùng cho quản trị viên
void displayUsersForAdmin() {
    if (userCount == 0) { // Kiểm tra xem có người dùng nào không
        printf("\nNo users to display.\n");
        return;
    }

    printf("\n+---------------------------------------------------------------------------------------+\n");
    printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
           "ID", "Name", "Phone", "Email", "Status");
    printf("+---------------------------------------------------------------------------------------+\n");

    for (int i = 0; i < userCount; i++) { // Duyệt qua mảng người dùng
        printf("| %-8s | %-20s | %-12s | %-25s | %-8s |\n", 
               users[i].id, 
               users[i].name, 
               users[i].phone, 
               users[i].email, 
               users[i].status);
    }

    printf("+---------------------------------------------------------------------------------------+\n");
}

// Menu quản trị viên
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
        printf("[7] Search User by Name\n");
        printf("[8] Delete User\n");
        printf("[9] Delete All Users\n");
        printf("[0] Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { // Kiểm tra xem đầu vào có phải là số không
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Xóa bộ nhớ đệm
            continue;
        }
        while (getchar() != '\n'); // Xóa bộ nhớ đệm sau khi nhập số

        switch (choice) {
            case 1: displayUsersForAdmin(); break; // Hiển thị người dùng
            case 2: addUserForAdmin(); break; // Thêm người dùng
            case 3: lockUnlockUser(); break; // Khóa/Mở khóa người dùng
            case 4: sortUsersByName(); break; // Sắp xếp người dùng theo tên
            case 5: changeAdminPassword(); break; // Thay đổi mật khẩu quản trị viên
            case 6: searchUserByID(); break; // Tìm kiếm người dùng theo ID
            case 7: searchUserByName(); break; // Tìm kiếm người dùng theo tên
            case 8: deleteUser(); break; // Xóa người dùng
            case 9: deleteAllUsers(); break; // Xóa tất cả người dùng
            case 0: return; // Thoát
            default: printf("\nInvalid choice. Please try again.\n");
        }
    } while (1);
}

// Menu chính
void displayMenu() {
    int choice;
    int loggedIn = 0;
    
    while (1) {
        printf("\n=====================================\n");
        printf("      *** BANK MANAGEMENT SYSTEM ***    \n");
        printf("=====================================\n");
        printf("[1] Admin Login\n");
        printf("[0] Exit\n");
        printf("-------------------------------------\n");
        printf("Your choice: ");
        
        if (scanf("%d", &choice) != 1) { // Kiểm tra xem đầu vào có phải là số không
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Xóa bộ nhớ đệm
            continue;
        }
        while (getchar() != '\n'); // Xóa bộ nhớ đệm sau khi nhập số

        switch (choice) {
            case 1:
                adminLogin(&loggedIn); // Đăng nhập quản trị viên
                if (loggedIn) {
                    adminMenu(); // Hiển thị menu quản trị viên nếu đăng nhập thành công
                }
                break;
            case 0:
                printf("\nGoodbye!\n");
                saveUsersToFile(); // Lưu thông tin người dùng vào tệp
                exit(0); // Thoát chương trình
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

// Hàm chính
int main() {
    loadUsersFromFile(); // Tải người dùng từ tệp
    displayMenu(); // Hiển thị menu chính
    return 0;
}