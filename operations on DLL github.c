#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node *head = NULL;

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void insertBeginning(int data) {
    struct Node *newNode = createNode(data);

    if (head == NULL) {
        head = newNode;
        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertEnd(int data) {
    struct Node *newNode = createNode(data);

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPos(int data, int pos) {
    if (pos == 1) {
        insertBeginning(data);
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp; i++)
        temp = temp->next;

    if (!temp) {
        printf("Position out of range\n");
        return;
    }

    struct Node *newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next)
        temp->next->prev = newNode;

    temp->next = newNode;
}

void deleteBeginning() {
    if (!head) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    if (head)
        head->prev = NULL;

    free(temp);
}

void deleteEnd() {
    if (!head) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    if (!temp->next) {
        head = NULL;
        free(temp);
        return;
    }

    while (temp->next)
        temp = temp->next;

    temp->prev->next = NULL;
    free(temp);
}

void deleteAtPos(int pos) {
    if (pos == 1) {
        deleteBeginning();
        return;
    }

    struct Node *temp = head;
    for (int i = 1; temp && i < pos; i++)
        temp = temp->next;

    if (!temp) {
        printf("Position out of range\n");
        return;
    }

    if (temp->prev)
        temp->prev->next = temp->next;

    if (temp->next)
        temp->next->prev = temp->prev;

    free(temp);
}

void display() {
    struct Node *temp = head;
    printf("DLL: ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void reverseDLL() {
    struct Node *curr = head, *temp = NULL;

    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp)
        head = temp->prev;
}

void findMiddle() {
    if (!head) {
        printf("List is empty\n");
        return;
    }

    struct Node *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    printf("Middle Element: %d\n", slow->data);
}

void sortDLL() {
    if (!head) return;

    struct Node *i, *j;
    for (i = head; i->next; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (i->data > j->data) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void detectLoop() {
    struct Node *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            printf("Loop detected!\n");
            return;
        }
    }
    printf("No loop found\n");
}

void sumOfData() {
    struct Node *temp = head;
    int sum = 0;

    while (temp) {
        sum += temp->data;
        temp = temp->next;
    }

    printf("Sum of data = %d\n", sum);
}

void printOddEven() {
    struct Node *temp = head;

    printf("Even Data: ");
    while (temp) {
        if (temp->data % 2 == 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }

    temp = head;
    printf("\nOdd Data:  ");
    while (temp) {
        if (temp->data % 2 != 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Node* mergeDLL(struct Node *h1, struct Node *h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct Node *temp = h1;
    while (temp->next)
        temp = temp->next;

    temp->next = h2;
    h2->prev = temp;

    return h1;
}

int main() {
    int choice, data, pos;
    struct Node *head2 = NULL;

    while (1) {
        printf("\n---- DOUBLY LINKED LIST MENU ----\n");
        printf("1. Insert at Beginning\n2. Insert at End\n3. Insert at Position\n");
        printf("4. Delete at Beginning\n5. Delete at End\n6. Delete at Position\n");
        printf("7. Display\n8. Reverse\n9. Find Middle\n10. Sort\n");
        printf("11. Detect Loop\n12. Sum of Data\n13. Print Odd/Even\n14. Merge Another DLL\n15. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertBeginning(data);
                break;

            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(data);
                break;

            case 3:
                printf("Enter data & position: ");
                scanf("%d %d", &data, &pos);
                insertAtPos(data, pos);
                break;

            case 4: deleteBeginning(); break;
            case 5: deleteEnd(); break;
            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deleteAtPos(pos);
                break;

            case 7: display(); break;
            case 8: reverseDLL(); break;
            case 9: findMiddle(); break;
            case 10: sortDLL(); break;
            case 11: detectLoop(); break;
            case 12: sumOfData(); break;
            case 13: printOddEven(); break;

            case 14:
                printf("Creating 2nd DLL (enter -1 to stop):\n");
                int val;
                while (1) {
                    printf("Enter data: ");
                    scanf("%d", &val);
                    if (val == -1) break;

                    struct Node *newNode = createNode(val);
                    if (!head2) head2 = newNode;
                    else {
                        struct Node *tmp = head2;
                        while (tmp->next)
                            tmp = tmp->next;
                        tmp->next = newNode;
                        newNode->prev = tmp;
                    }
                }
                head = mergeDLL(head, head2);
                printf("DLLs merged successfully!\n");
                break;

            case 15:
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }
}
