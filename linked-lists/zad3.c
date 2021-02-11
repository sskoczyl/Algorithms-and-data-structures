#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
  
struct Node { 
    int data; 
    struct Node* next;
    struct Node* previous; 
}; 


struct Node* newNode(){
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->previous=NULL;
    new->next=NULL;
    return new;
}

void linkLists(struct Node* n1, struct Node* n2, struct Node* n3, struct Node* n4){
    n1->next=n2;
    n2->previous=n2;
    n3->next=n4;
    n3->previous=n4;
}
  
int main() 
{ 
    time_t t;
    srand((unsigned) time(&t));

    struct Node* head = (struct Node*)malloc(sizeof(struct Node)); 
    head->data=1111;
    struct Node* last = head; 

    for(int i=0; i<5; i++){
        struct Node* new=newNode();;
        last->next=new;
        last->previous=new;
        last=new;
        last->data=rand()%1000;
        head->previous=new;
        last->next=head;
    }


    struct Node* head_other = (struct Node*)malloc(sizeof(struct Node)); 
    head_other->data=1111;
    struct Node* last_other = head_other;

     for(int i=0; i<5; i++){
        struct Node* new_other=newNode();;
        last_other->next=new_other;
        last_other->previous=new_other;
        last_other=new_other;
        last_other->data=rand()%1000;
        head_other->previous=new_other;
        last_other->next=head;
    }
   
    linkLists(last, head_other, last_other, head);

    return 0; 
}
