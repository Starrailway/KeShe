//
// Created by Administrator on 24-4-15.
//

#ifndef KESHE_STUDENT_H
#define KESHE_STUDENT_H

#include <stdio.h>
#include <string.h>

#define NAME_LEN 32
#define ID_LEN 12
#define PASSWORD_LEN 50

#define admin "007"
#define adminpasswords "123456"

typedef struct Person {
    char ID[ID_LEN];
    char password[PASSWORD_LEN];
    char correctPassword[PASSWORD_LEN];
} Person;

typedef struct {
    Person s;
    char name[NAME_LEN];
    char gender[6];
    int age;
    char phone[13];
    char dormitoryLocation[11];
} Student;

#define MAX_STUDENTS 469
Student students[MAX_STUDENTS];
int studentCount = 0;

#include "DocProcess.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* 清空缓冲区 */
    }
}


void addStudent() {

    if (studentCount >= MAX_STUDENTS) {
        printf("数据已满，无法添加更多学生数据\n");
    }
    //password[strcspn(password, "\n")] = 0;

    printf("请输入学生姓名: ");
    fgets(students[studentCount].name, NAME_LEN + 1, stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = 0;

    printf("请输入学生性别:");
    fgets(students[studentCount].gender, sizeof(students[studentCount].gender), stdin);
    students[studentCount].gender[strcspn(students[studentCount].gender, "\n")] = 0;

    printf("请输入学生年龄:");
    scanf("%d", &students[studentCount].age);
    clear_input_buffer();

    printf("请输入学生宿舍地址:");
    fgets(students[studentCount].dormitoryLocation, sizeof(students[studentCount].dormitoryLocation), stdin);
    students[studentCount].dormitoryLocation[strcspn(students[studentCount].dormitoryLocation, "\n")] = 0;

    printf("请输入手机号:");
    fgets(students[studentCount].phone, sizeof(students[studentCount].phone), stdin);
    students[studentCount].phone[strcspn(students[studentCount].phone, "\n")] = 0;
}

void registerUser() {
    Student s1;

    printf("请输入用户名:");

    fgets(s1.s.ID, NAME_LEN, stdin);
    s1.s.ID[strcspn(s1.s.ID, "\n")] = 0; // 移除换行符

    while (1) {
        printf("请输入密码:");
        fgets(s1.s.password, PASSWORD_LEN, stdin);
        s1.s.password[strcspn(s1.s.password, "\n")] = 0; // 移除换行符
        printf("请再次确认密码:");

        fgets(s1.s.correctPassword, PASSWORD_LEN, stdin);
        s1.s.correctPassword[strcspn(s1.s.correctPassword, "\n")] = 0; // 移除换行符
        if (strcmp(s1.s.password, s1.s.correctPassword) == 0)break;
        else printf("两次密码不一致，请重新输入\n");
    }


    // 检查用户名是否已存在
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].s.ID, s1.s.ID) == 0) {
            printf("该用户名已被占用，请重新输入\n");
            system("pause");
            system("cls");
            return;
        }
    }

    // 添加新用户
    strcpy(students[studentCount].s.ID, s1.s.ID);
    strcpy(students[studentCount].s.correctPassword, s1.s.correctPassword);
    addStudent();
    studentCount++;
    printf("用户注册成功!\n");
    saveStudents();
    system("pause");
    system("cls");
}

char *loginUser() {
    char userID[NAME_LEN];
    char password[PASSWORD_LEN];
    printf("请输入用户名:");
    fgets(userID, NAME_LEN, stdin);
    userID[strcspn(userID, "\n")] = 0; // 移除字符串末尾的换行符
    printf("请输入密码: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0; // 移除字符串末尾的换行符
    if (strcmp(admin, userID) == 0 && strcmp(adminpasswords, password) == 0)
        return "007";
    else {
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].s.ID, userID) == 0 && strcmp(students[i].s.correctPassword, password) == 0) {
                printf("登录成功!\n");
                return students[i].name;
            }
        }
    }
    printf("用户名或密码错误，请重试\n");

    return "0";//
}

void showStudents() {
    printf("List of all students:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%d. 学生姓名：%s, 宿舍位置: %s, 手机号码: %s, 学号: %s, 性别: %s, 年龄: %d\n",
               i + 1,
               students[i].name,
               students[i].dormitoryLocation,
               students[i].phone,
               students[i].s.ID,
               students[i].gender,
               students[i].age);
    }
    printf("\n");
    system("pause");
    system("cls");
}

Student *searchStudent() {
    char ID[50];
    printf("请输入查找的用户名:");
    scanf("%11s", ID);
    printf("\n");
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].s.ID, ID) == 0) {
            printf("找到学生: 姓名： %s, 宿舍地址: %s, 手机号: %s, 学号: %s, 性别: %s, 年龄: %d\n",
                   students[i].name,
                   students[i].dormitoryLocation,
                   students[i].phone,
                   students[i].s.ID,
                   students[i].gender,
                   students[i].age
            );
            return &students[i];
        }
    }
    printf("没有找到学号为 %s 的学生\n", ID);
    system("pause");
    system("cls");
}

void ModifyStuInfor(Student *s0) {
    while (1) {
        int choice = 0;
        printf("\n******************\n");
        printf("** 修改学生信息 **\n");
        printf("* 1.修改密码     *\n");
        printf("* 2.修改姓名     *\n");
        printf("* 3.修改年龄     *\n");
        printf("* 4.修改性别     *\n");
        printf("* 5.修改联系方式 *\n");
        printf("* 6.修改宿舍地址 *\n");
        printf("* 7.返回         *\n");
        printf("******************\n");
        printf("请输入您的选择:");
        scanf("%d", &choice);
        clear_input_buffer();
        switch (choice) {
            case 1:
                // 使用 memset 清空整个字符串数组
                memset(s0->s.correctPassword, 0, sizeof(s0->s.correctPassword));
                printf("请输入新的密码：");
                fgets(s0->s.correctPassword, PASSWORD_LEN, stdin);
                s0->s.correctPassword[strcspn(s0->s.correctPassword, "\n")] = 0;
                break;
            case 2:
                memset(s0->name, 0, sizeof(s0->name));
                printf("请输入新的姓名：");
                fgets(s0->name, sizeof(s0->name), stdin);
                s0->name[strcspn(s0->name, "\n")] = 0;
                break;
            case 3:
                scanf("%d", &s0->age);
                clear_input_buffer();
                break;
            case 4:
                memset(s0->gender, 0, sizeof(s0->gender));
                printf("请输入新的年龄：");
                fgets(s0->gender, sizeof(s0->gender), stdin);
                s0->gender[strcspn(s0->gender, "\n")] = 0;
                break;
            case 5:
                memset(s0->phone, 0, sizeof(s0->phone));
                printf("请输入新的联系方式：");
                fgets(s0->phone, sizeof(s0->phone), stdin);
                s0->phone[strcspn(s0->phone, "\n")] = 0;
                break;
            case 6:
                memset(s0->dormitoryLocation, 0, sizeof(s0->dormitoryLocation));
                printf("请输入新的宿舍地址：");
                fgets(s0->dormitoryLocation, sizeof(s0->dormitoryLocation), stdin);
                s0->dormitoryLocation[strcspn(s0->dormitoryLocation, "\n")] = 0;
                break;
            case 7:
                return;
            default:
                printf("无效输入，请重新输入一个整数");
                break;
        }

    }


}

void removeStudent(char *ID) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].s.ID, ID) == 0) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++)
                students[j] = students[j + 1];

            studentCount--;
            printf("学生删除成功！\n");
            system("pause");
            system("cls");
            break;
        }
    }
    if (!found) {
        printf("未找到学生\n");
        system("pause");
        system("cls");
    }
}

void changePassword() {
    int j = 0;
    char userID[NAME_LEN];
    char password[PASSWORD_LEN];
    char correctPassword[PASSWORD_LEN];
    printf("请输入用户名:");
    fgets(userID, NAME_LEN, stdin);
    userID[strcspn(userID, "\n")] = 0; // 移除字符串末尾的换行符
    printf("请输入密码: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0; // 移除字符串末尾的换行符
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].s.ID, userID) == 0 && strcmp(students[i].s.correctPassword, password) == 0) {
            while (1) {
                j++;
                printf("请输入新密码:");
                fgets(password, PASSWORD_LEN, stdin);
                password[strcspn(password, "\n")] = 0; // 移除换行符
                printf("请再次确认新密码:");
                fgets(correctPassword, PASSWORD_LEN, stdin);
                correctPassword[strcspn(correctPassword, "\n")] = 0; // 移除换行符
                if (strcmp(password, correctPassword) == 0)break;
                else printf("两次密码不一致，请重新输入\n");
            }
            strcpy(students[i].s.correctPassword, correctPassword);
            if (strcmp(students[i].s.correctPassword, correctPassword) == 0) {
                printf("密码修改成功！\n");
                system("pause");
                system("cls");
            }
        }
    }
    if (j == 0) {
        printf("密码错误！\n");
        system("pause");
        system("cls");
    }
    return;
}


#endif //KESHE_STUDENT_H
