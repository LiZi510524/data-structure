#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define MAX_SIZE 100

typedef int Status; // 状态码
typedef struct {
    char date[11];   // 日期格式: YYYY-MM-DD
    char time[6];    // 时间格式: HH:MM
    char addr[50];   // 地点
    float temp;      // 温度
    float humi;      // 湿度
} Home;

typedef struct HomeNode {
    Home data;                     // 结点的数据域
    struct HomeNode *next;         // 结点的指针域
} HomeNode, *HomeList;

int length = 0; // 链表长度

// 创建智能家居系统链表
void CreateHomeList(HomeList *L) {
    *L = (HomeNode *)malloc(sizeof(HomeNode));
    (*L)->next = NULL; // 建立一个带头结点的空链表
    length = 0;
}

// 插入数据
Status InsertHomeData(HomeList L, int i, Home e) {
    if (i < 1 || i > length + 1) return ERROR; // 检查位置合法性

    HomeNode *p = L;
    int j;
    for (j = 0; j < i - 1; j++) {
        p = p->next; // 找到第i-1个结点
    }

    HomeNode *s = (HomeNode *)malloc(sizeof(HomeNode)); // 创建新结点
    s->data = e; // 赋值
    s->next = p->next; // 将新结点插入
    p->next = s;
    length++;
    return OK;
}

// 按值查找
HomeNode* LocateHome(HomeList L, char *date, char *time, char *addr) {
    HomeNode *p = L->next;
    while (p != NULL) {
        if (strcmp(p->data.date, date) == 0 && strcmp(p->data.time, time) == 0 && strcmp(p->data.addr, addr) == 0) {
            return p; // 找到结点
        }
        p = p->next; // 指向下一个结点
    }
    return NULL; // 未找到
}

// 按日期删除
Status DeleteByDate(HomeList L, char *date) {
    HomeNode *p = L;
    HomeNode *q;

    while (p->next != NULL && strcmp(p->next->data.date, date) != 0) {
        p = p->next; // 找到待删除结点的前驱
    }

    if (p->next == NULL) return ERROR; // 未找到

    q = p->next; // 保存被删结点的地址
    p->next = q->next; // 删除结点
    free(q); // 释放内存
    length--;
    return OK;
}

// 显示链表
void DisplayList(HomeList L) {
    HomeNode *p = L->next;
    printf("%-12s %-6s %-20s %-6s %-6s\n", "日期", "时间", "地点", "温度", "湿度");
    while (p) {
        printf("%-12s %-6s %-20s %-6.2f %-6.2f\n", p->data.date, p->data.time, p->data.addr, p->data.temp, p->data.humi);
        p = p->next;
        p = p->next;
    }
}

int main() {
    Home myhome;
    HomeList hL;
    char date[11], time[6], addr[50], delDate[11];
    int choosenum;

    CreateHomeList(&hL);
    printf("智能家居链表创建成功\n");
	
	choosenum=-1;
    while (choosenum!=0) {
        printf("\n1. 输入\n2. 显示\n3. 查找\n4. 插入\n5. 删除\n0. 退出\n选择操作: ");
        scanf("%d", &choosenum);
        switch (choosenum) {
            case 1:
                printf("请输入参数表:\n日期(yyyy-mm-dd): ");
                scanf("%s", myhome.date);
                printf("时间（hh:mm）：");
                scanf("%s", myhome.time);
                printf("地点：");
                scanf("%s", myhome.addr);
                printf("温度：");
                scanf("%f", &myhome.temp);
                printf("湿度：");
                scanf("%f", &myhome.humi);
                InsertHomeData(hL, 1, myhome);
                printf("数据插入成功！\n");
                break;
            case 2:
                DisplayList(hL);
                break;
            case 3:
                printf("请输入查找条件:\n日期(yyyy-mm-dd): ");
                scanf("%s", date);
                printf("时间（hh:mm）：");
                scanf("%s", time);
                printf("地点：");
                scanf("%s", addr);
                HomeNode *found = LocateHome(hL, date, time, addr);
                if (found) {
                    printf("找到记录: %s %s %s %.2f %.2f\n", found->data.date, found->data.time, found->data.addr, found->data.temp, found->data.humi);
                } else {
                    printf("未找到记录！\n");
                }
                break;
            case 4:
                printf("请输入插入位置: ");
                int pos;
                scanf("%d", &pos);
                InsertHomeData(hL, pos, myhome);
                break;
            case 5:
                printf("请输入要删除的日期信息: ");
                scanf("%s", delDate);
                if (DeleteByDate(hL, delDate) == OK) {
                    printf("删除成功!\n");
                } else {
                    printf("删除失败!\n");
                }
                break;
            case 0:
                free(hL); // 释放链表内存
                return 0;
            default:
                printf("无效的选择！\n");
        }
    }

    return 0;
}


