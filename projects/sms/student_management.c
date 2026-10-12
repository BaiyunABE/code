#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "students.dat"

// 学生结构体
typedef struct {
    int id;                 // 学号
    char name[50];          // 姓名
    int age;                // 年龄
    char gender[10];        // 性别
    char className[50];     // 班级
    float score;            // 成绩
} Student;

// 全局变量
Student students[MAX_STUDENTS];
int studentCount = 0;

// 函数声明
void initSystem();
void saveToFile();
void loadFromFile();
void showMenu();
void addStudent();
void deleteStudent();
void modifyStudent();
void searchStudent();
void displayAll();
void displayStudent(Student stu);
void clearInputBuffer();
void waitForEnter();  // 跨平台等待
void clearScreen();   // 跨平台清屏

int main() {
    initSystem();
    
    while (1) {
        showMenu();
        printf("请选择操作（0-7）: ");
        char choice = getchar();
        clearInputBuffer();
        
        switch (choice) {
            case '1':
                addStudent();
                break;
            case '2':
                deleteStudent();
                break;
            case '3':
                modifyStudent();
                break;
            case '4':
                searchStudent();
                break;
            case '5':
                displayAll();
                break;
            case '6':
                saveToFile();
                printf("数据已保存到文件！\n");
                waitForEnter();
                break;
            case '7':
                loadFromFile();
                printf("数据已从文件加载！\n");
                waitForEnter();
                break;
            case '0':
                printf("感谢使用学生管理系统，再见！\n");
                saveToFile();
                return 0;
            default:
                printf("无效的选择，请重新输入！\n");
                waitForEnter();
        }
    }
    
    return 0;
}

// 初始化系统
void initSystem() {
    // 尝试从文件加载数据
    FILE *file = fopen(FILENAME, "rb");
    if (file != NULL) {
        fread(&studentCount, sizeof(int), 1, file);
        fread(students, sizeof(Student), studentCount, file);
        fclose(file);
        printf("成功加载 %d 条学生记录\n", studentCount);
    }
}

// 保存到文件
void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("无法打开文件进行保存！\n");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
}

// 从文件加载
void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("找不到数据文件！\n");
        return;
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
}

// 显示菜单
void showMenu() {
    clearScreen();
    printf("=================================\n");
    printf("     学生管理系统\n");
    printf("=================================\n");
    printf("1. 添加学生\n");
    printf("2. 删除学生\n");
    printf("3. 修改学生信息\n");
    printf("4. 查找学生\n");
    printf("5. 显示所有学生\n");
    printf("6. 保存数据到文件\n");
    printf("7. 从文件加载数据\n");
    printf("0. 退出系统\n");
    printf("=================================\n");
}

// 添加学生
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("学生数量已达上限，无法添加！\n");
        waitForEnter();
        return;
    }
    
    Student newStudent;
    printf("\n--- 添加学生 ---\n");
    
    // 输入学号
    printf("请输入学号: ");
    if (scanf("%d", &newStudent.id) != 1) {
        printf("输入无效！\n");
        clearInputBuffer();
        waitForEnter();
        return;
    }
    clearInputBuffer();
    
    // 检查学号是否已存在
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id) {
            printf("学号 %d 已存在！\n", newStudent.id);
            waitForEnter();
            return;
        }
    }
    
    // 输入其他信息
    printf("请输入姓名: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    
    printf("请输入年龄: ");
    scanf("%d", &newStudent.age);
    clearInputBuffer();
    
    printf("请输入性别(男/女): ");
    fgets(newStudent.gender, sizeof(newStudent.gender), stdin);
    newStudent.gender[strcspn(newStudent.gender, "\n")] = 0;
    
    printf("请输入班级: ");
    fgets(newStudent.className, sizeof(newStudent.className), stdin);
    newStudent.className[strcspn(newStudent.className, "\n")] = 0;
    
    printf("请输入成绩: ");
    scanf("%f", &newStudent.score);
    clearInputBuffer();
    
    // 添加到数组
    students[studentCount] = newStudent;
    studentCount++;
    
    printf("学生添加成功！\n");
    waitForEnter();
}

// 删除学生
void deleteStudent() {
    if (studentCount == 0) {
        printf("没有学生记录！\n");
        waitForEnter();
        return;
    }
    
    printf("\n--- 删除学生 ---\n");
    int id;
    printf("请输入要删除的学生学号: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("未找到学号为 %d 的学生！\n", id);
        waitForEnter();
        return;
    }
    
    // 显示要删除的学生信息
    printf("找到以下学生，确认删除？\n");
    displayStudent(students[foundIndex]);
    printf("确认删除？(y/n): ");
    char confirm = getchar();
    clearInputBuffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        // 删除学生：将后面的元素前移
        for (int i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("学生删除成功！\n");
    } else {
        printf("取消删除操作。\n");
    }
    
    waitForEnter();
}

// 修改学生信息
void modifyStudent() {
    if (studentCount == 0) {
        printf("没有学生记录！\n");
        waitForEnter();
        return;
    }
    
    printf("\n--- 修改学生信息 ---\n");
    int id;
    printf("请输入要修改的学生学号: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("未找到学号为 %d 的学生！\n", id);
        waitForEnter();
        return;
    }
    
    printf("找到学生，当前信息：\n");
    displayStudent(students[foundIndex]);
    printf("\n请输入新的信息（直接按回车保留原值）:\n");
    
    // 修改姓名
    printf("姓名[%s]: ", students[foundIndex].name);
    char temp[50];
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(students[foundIndex].name, temp);
    }
    
    // 修改年龄
    printf("年龄[%d]: ", students[foundIndex].age);
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        students[foundIndex].age = atoi(temp);
    }
    
    // 修改性别
    printf("性别[%s]: ", students[foundIndex].gender);
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(students[foundIndex].gender, temp);
    }
    
    // 修改班级
    printf("班级[%s]: ", students[foundIndex].className);
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(students[foundIndex].className, temp);
    }
    
    // 修改成绩
    printf("成绩[%.2f]: ", students[foundIndex].score);
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        students[foundIndex].score = atof(temp);
    }
    
    printf("学生信息修改成功！\n");
    waitForEnter();
}

// 查找学生
void searchStudent() {
    if (studentCount == 0) {
        printf("没有学生记录！\n");
        waitForEnter();
        return;
    }
    
    printf("\n--- 查找学生 ---\n");
    printf("1. 按学号查找\n");
    printf("2. 按姓名查找\n");
    printf("请选择查找方式: ");
    char choice = getchar();
    clearInputBuffer();
    
    if (choice == '1') {
        int id;
        printf("请输入学号: ");
        scanf("%d", &id);
        clearInputBuffer();
        
        int found = 0;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].id == id) {
                printf("\n找到学生：\n");
                displayStudent(students[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("未找到学号为 %d 的学生！\n", id);
        }
    } else if (choice == '2') {
        char name[50];
        printf("请输入姓名: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        
        int found = 0;
        for (int i = 0; i < studentCount; i++) {
            if (strstr(students[i].name, name) != NULL) {
                if (!found) {
                    printf("\n找到以下学生：\n");
                }
                displayStudent(students[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("未找到姓名为 %s 的学生！\n", name);
        }
    } else {
        printf("无效的选择！\n");
    }
    
    waitForEnter();
}

// 显示所有学生
void displayAll() {
    if (studentCount == 0) {
        printf("没有学生记录！\n");
        waitForEnter();
        return;
    }
    
    printf("\n--- 所有学生信息 ---\n");
    printf("===============================================================\n");
    printf("学号\t姓名\t\t年龄\t性别\t班级\t\t成绩\n");
    printf("===============================================================\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t", students[i].id);
        printf("%-10s\t", students[i].name);
        printf("%d\t", students[i].age);
        printf("%s\t", students[i].gender);
        printf("%-10s\t", students[i].className);
        printf("%.2f\n", students[i].score);
    }
    printf("===============================================================\n");
    printf("共 %d 名学生\n", studentCount);
    
    waitForEnter();
}

// 显示单个学生信息
void displayStudent(Student stu) {
    printf("-----------------------------------\n");
    printf("学号：%d\n", stu.id);
    printf("姓名：%s\n", stu.name);
    printf("年龄：%d\n", stu.age);
    printf("性别：%s\n", stu.gender);
    printf("班级：%s\n", stu.className);
    printf("成绩：%.2f\n", stu.score);
    printf("-----------------------------------\n");
}

// 清空输入缓冲区
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 跨平台等待用户按回车
void waitForEnter() {
    printf("\n按回车键继续...");
    clearInputBuffer();
}

// 跨平台清屏
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}