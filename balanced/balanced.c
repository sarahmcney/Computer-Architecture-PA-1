#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Struct to hold the expected close brace character and a pointer to the next element.
//its just a stack

typedef struct node node;
struct node {
    char data;
    node* next;
};
void push(node** head_ptr, char data);
char pop(node** head_ptr);
void clear(node** head_ptr);
bool is_empty(node* head);

int main(int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");

    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    node* head = NULL;
    char buff;


    while ( fscanf(fp, "%c", &buff)==1 ) {
        if(buff == '{' || buff == '<' || buff == '[' || buff == '(') {
            push(&head, buff);
        }
        else if(buff == '}' || buff == '>' || buff == ']' || buff == ')') {
            if(is_empty(head)) { 
                printf("no");
                clear(&head);
                return 0; 
            }
            else {
                char c = pop(&head);
                if(buff == '}' && c != '{') {
                    printf("no");
                    clear(&head);
                    return 0;
                }
                else if(buff == ')' && c != '(') {
                    printf("no");
                    clear(&head);
                    return 0;
                }
                else if(buff == '>' && c != '<') {
                    printf("no");
                    clear(&head);
                    return 0;
                }
                else if(buff == ']' && c != '[') {
                    printf("no");
                    clear(&head);
                    return 0;
                }
            }
        }
    }
    if(is_empty(head)) {
        printf("yes");
    } else {
        printf("no");
    }
    //printf ( balanced ? "yes" : "no" );
    fclose(fp);
    clear(&head);
    return 0;
}

void push(node** head_ptr, char data) {
    node* temp = malloc(sizeof(node));
    temp->data = data;
    temp->next = *head_ptr;
    *head_ptr = temp;
    return;
}

char pop(node** head_ptr) {
    node* temp = *head_ptr;
    char popped = temp->data;
    *head_ptr = temp->next;
    free(temp);
    return popped;
}

bool is_empty(node* head) {
    if(head == NULL) {
        return true;
    }
    return false;
}

void clear(node** head_ptr) {
    while(!is_empty(*head_ptr)) {
        pop(head_ptr);
    }
}
