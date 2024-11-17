#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define MAX_SIZE 100

typedef int Status; // ״̬��
typedef struct {
    char date[11];   // ���ڸ�ʽ: YYYY-MM-DD
    char time[6];    // ʱ���ʽ: HH:MM
    char addr[50];   // �ص�
    float temp;      // �¶�
    float humi;      // ʪ��
} Home;

typedef struct HomeNode {
    Home data;                     // ����������
    struct HomeNode *next;         // ����ָ����
} HomeNode, *HomeList;

int length = 0; // ������

// �������ܼҾ�ϵͳ����
void CreateHomeList(HomeList *L) {
    *L = (HomeNode *)malloc(sizeof(HomeNode));
    (*L)->next = NULL; // ����һ����ͷ���Ŀ�����
    length = 0;
}

// ��������
Status InsertHomeData(HomeList L, int i, Home e) {
    if (i < 1 || i > length + 1) return ERROR; // ���λ�úϷ���

    HomeNode *p = L;
    int j;
    for (j = 0; j < i - 1; j++) {
        p = p->next; // �ҵ���i-1�����
    }

    HomeNode *s = (HomeNode *)malloc(sizeof(HomeNode)); // �����½��
    s->data = e; // ��ֵ
    s->next = p->next; // ���½�����
    p->next = s;
    length++;
    return OK;
}

// ��ֵ����
HomeNode* LocateHome(HomeList L, char *date, char *time, char *addr) {
    HomeNode *p = L->next;
    while (p != NULL) {
        if (strcmp(p->data.date, date) == 0 && strcmp(p->data.time, time) == 0 && strcmp(p->data.addr, addr) == 0) {
            return p; // �ҵ����
        }
        p = p->next; // ָ����һ�����
    }
    return NULL; // δ�ҵ�
}

// ������ɾ��
Status DeleteByDate(HomeList L, char *date) {
    HomeNode *p = L;
    HomeNode *q;

    while (p->next != NULL && strcmp(p->next->data.date, date) != 0) {
        p = p->next; // �ҵ���ɾ������ǰ��
    }

    if (p->next == NULL) return ERROR; // δ�ҵ�

    q = p->next; // ���汻ɾ���ĵ�ַ
    p->next = q->next; // ɾ�����
    free(q); // �ͷ��ڴ�
    length--;
    return OK;
}

// ��ʾ����
void DisplayList(HomeList L) {
    HomeNode *p = L->next;
    printf("%-12s %-6s %-20s %-6s %-6s\n", "����", "ʱ��", "�ص�", "�¶�", "ʪ��");
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
    printf("���ܼҾ��������ɹ�\n");
	
	choosenum=-1;
    while (choosenum!=0) {
        printf("\n1. ����\n2. ��ʾ\n3. ����\n4. ����\n5. ɾ��\n0. �˳�\nѡ�����: ");
        scanf("%d", &choosenum);
        switch (choosenum) {
            case 1:
                printf("�����������:\n����(yyyy-mm-dd): ");
                scanf("%s", myhome.date);
                printf("ʱ�䣨hh:mm����");
                scanf("%s", myhome.time);
                printf("�ص㣺");
                scanf("%s", myhome.addr);
                printf("�¶ȣ�");
                scanf("%f", &myhome.temp);
                printf("ʪ�ȣ�");
                scanf("%f", &myhome.humi);
                InsertHomeData(hL, 1, myhome);
                printf("���ݲ���ɹ���\n");
                break;
            case 2:
                DisplayList(hL);
                break;
            case 3:
                printf("�������������:\n����(yyyy-mm-dd): ");
                scanf("%s", date);
                printf("ʱ�䣨hh:mm����");
                scanf("%s", time);
                printf("�ص㣺");
                scanf("%s", addr);
                HomeNode *found = LocateHome(hL, date, time, addr);
                if (found) {
                    printf("�ҵ���¼: %s %s %s %.2f %.2f\n", found->data.date, found->data.time, found->data.addr, found->data.temp, found->data.humi);
                } else {
                    printf("δ�ҵ���¼��\n");
                }
                break;
            case 4:
                printf("���������λ��: ");
                int pos;
                scanf("%d", &pos);
                InsertHomeData(hL, pos, myhome);
                break;
            case 5:
                printf("������Ҫɾ����������Ϣ: ");
                scanf("%s", delDate);
                if (DeleteByDate(hL, delDate) == OK) {
                    printf("ɾ���ɹ�!\n");
                } else {
                    printf("ɾ��ʧ��!\n");
                }
                break;
            case 0:
                free(hL); // �ͷ������ڴ�
                return 0;
            default:
                printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}


