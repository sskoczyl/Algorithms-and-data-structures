#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
  
struct Node { 
    int data; 
    struct Node* next; 
}; 

void printList(struct Node* n) 
{ 
    while (n != NULL) { 
        printf(" %d \n", n->data); 
        n = n->next; 
    } 
} 

struct Node* newNode(){
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->next=NULL;
    return new;
}

void linkLists(struct Node* n1, struct Node* n2){
    n1->next=n2;
}
  
int main() 
{ 
    time_t t;
    srand((unsigned) time(&t));

    struct Node* head = (struct Node*)malloc(sizeof(struct Node)); 
    head->data=1111;
    struct Node* last = head; 

    for(int i=0; i<1000; i++){
        struct Node* new=newNode();;
        last->next=new;
        last=new;
        last->data=rand()%1000;
    }
  
    printList(head); 

    struct Node* head_other = (struct Node*)malloc(sizeof(struct Node)); 
    head_other->data=1111;
    struct Node* last_other = head_other; 

    for(int i=0; i<1000; i++){
        struct Node* new_other=newNode();;
        last_other->next=new_other;
        last_other=new_other;
        last_other->data=rand()%1000;
    }
  
    printList(head_other); 

    linkLists(last, head_other);

    printList(head);

    clock_t start = clock();

    for(int i=0; i<1000; i++){    //mesure time
        head=head->next;
    }
    clock_t end = clock();

    float seconds = (float)(end - start) ;
    printf("Czas dostepu: %f \n", seconds);

    return 0; 
}
