/*
queues
*/

typedef struct node {
	int data;
	struct node* next;
}node;

typedef struct queue{
	node * front;
	node * back;
}queue;

// Initalizes the queue pointed to by myQ to be and empty queue
void initialize(queue * myQ);

void enqueue(queue * myQ, node* item);

node* dequeue(queue* myQ);

int size(queue* myQ);

queue* merge(queue* q1, queue* q2);

int main (void)
{
	return 0;
	
}

void initialize(queue * myQ)
{
	while()
}

void enqueue(queue * myQ, node* item);

node* dequeue(queue* myQ);

int size(queue* myQ);

queue* merge(queue* q1, queue* q2);


