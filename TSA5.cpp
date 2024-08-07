#include <iostream>
#define MAX_SIZE 100
using namespace std;
class Queue {
private:
 int front, rear, size;
 int arr[MAX_SIZE];
public:
 Queue() {
 front = rear = 
-1;
 size = 0;
 
}
 bool queueIsEmpty() {
 return (front == 
-1 && rear == 
-1);
 
}
 bool queueIsFull() {
 return (rear == MAX_SIZE 
- 1);
 
}
 void enqueueElement(int x) {
 if (queueIsFull()) {
 cout << "Error: Queue is full!" << endl;
 return;
 
}
 if (queueIsEmpty()) {
 front = rear = 0;
 } else {
 rear++;
 
}
 arr[rear] = x;
 size++;
 
}
 int dequeueElement() {
 if (queueIsEmpty()) {
 cout << "Error: Queue is empty!" << endl;
 return 
-1;
 
}
 int x = arr[front];
 if (front == rear) {
 front = rear = 
-1;
 } else {
 front++;
 
}
 size--;
 return x;
 
}
 int queueSize() {
 return size;
 
}
 void displayQueueElements() {
 if (queueIsEmpty()) {
 cout << "Queue is empty!" << endl;
 return;
 
}
 for (int i = front; i <= rear; i++) {
 cout << arr[i] << " ";
 
}
 cout << endl;
 
}
 int getFrontElement() {
 if (queueIsEmpty()) {
 cout << "Error: Queue is empty!" << endl;
 return 
-1;
 
}
 return arr[front];
 
}
};
int main() {
 Queue q;
 q.enqueueElement(5);
 q.enqueueElement(10);
 q.enqueueElement(15);
 q.enqueueElement(20);
 q.displayQueueElements();
 cout << "Front element: " << q.getFrontElement() << endl;
 q.dequeueElement();
 q.dequeueElement();
 q.displayQueueElements();
 cout << "Front element: " << q.getFrontElement() << endl;
 return 0;
}
