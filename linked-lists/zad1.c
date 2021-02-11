#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
  
struct Queue{ 
    int front, last, size; 
    unsigned capacity; 
    int* array; 
}; 
  
struct Queue* createQueue(unsigned int capacity){ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front =0;
    queue->size = 0;  
    queue->last = capacity - 1;  // This is important, see the enqueue 
    queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
    
    return queue; 
}

int isFull(struct Queue* queue) {  
    return (queue->size == queue->capacity);  
} 

int isEmpty(struct Queue* queue) {
     return (queue->size == 0); 
} 

int front(struct Queue* queue) { 
    if (isEmpty(queue)) {
        printf("Error, empty");
        return INT_MIN; 
    }  
    return queue->array[queue->front]; 
} 


int last(struct Queue* queue) { 
    if (isEmpty(queue)) {
        printf("Error, empty");
        return INT_MIN; 
    } 
        
    return queue->array[queue->last]; 
} 

void enqueue(struct Queue* queue, int item) { 
    if (isFull(queue)) 
        return; 

    queue->last = (queue->last + 1)%queue->capacity; 
    queue->array[queue->last] = item; 
    queue->size++; 
    printf("%d Dodano do kolejki\n", item); 
} 
  
int dequeue(struct Queue* queue) { 
    if (isEmpty(queue)) {
        printf("Error, empty");
        return INT_MIN; 
    }  
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 

//Testowanie
int main() { 
    struct Queue* queue = createQueue(1000); 
  
    enqueue(queue, 101); 
    enqueue(queue, 203); 
    enqueue(queue, 304); 
    enqueue(queue, 450); 
    enqueue(queue, 666); 
    enqueue(queue, 222); 
  
    printf("Pierwszy %d\n", front(queue)); 
    printf("Ostatni %d\n", last(queue)); 

    printf("%d Usunieto z kolejki\n", dequeue(queue)); 
    printf("%d Usunieto z kolejki\n", dequeue(queue)); 
    printf("%d Usunieto z kolejki\n", dequeue(queue)); 
    printf("%d Usunieto z kolejki\n\n", dequeue(queue)); 
  
    printf("Pierwszy %d\n", front(queue)); 
    printf("Ostatni %d\n", last(queue)); 
  
    return 0; 
} 
