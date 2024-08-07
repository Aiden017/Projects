#include <iostream>
using namespace std;
class Array1D
{
private:
int capacity;
int size;
int *array;
public:
Array1D(int Arraycap=10): capacity(Arraycap), size(0) 
{array = new int[capacity];} 
~Array1D()
{ delete [] array;} /*don't touch*/
int GetSize() const
{return size;}
bool isEmpty()const
{return size==0;}
bool isFull() const
{return size==capacity;}
void InsertItem (int pos,int val){
{if (pos < 0 || pos > size || isFull())
cout<<"Array is FULL! CANNOT ADD ANYMORE!";}
for (int i = size - 1; i >= pos; --i)
 {
 array[i + 1] = array[i];
 }
 array[pos] = val;
 size++;
}
void RemoveItem(int pos)
{if (pos < 0 || pos >= size || isEmpty())
 {
 cout << "Invalid position or array is empty." << endl;
 return;
 }
 for (int i = pos; i < size - 1; ++i)
 {
 array[i] = array[i + 1];
 }
 size--;
}
void AddItem(int val)
{
 if (isFull())
 {
 cout << "Array is Full. Cannot add anymore Elements!" << endl;
 return;
 }
 array[size] = val;
 size++;
 }
void DisplayElements() 
{if (isEmpty())
 {
 cout << "Array is empty." << endl;
 return;
 }
 for (int i = 0; i < size; ++i)
 {
 cout << array[i] << " ";
 }
 cout << endl;
 }
};
int main(){ /*DON'T TOUCH AS WELL*/
Array1D arr(5);
 arr.AddItem(10);
 arr.AddItem(20);
 arr.AddItem(30);
 arr.DisplayElements();
 arr.InsertItem(1, 15);
 arr.DisplayElements();
 arr.AddItem(40);
 arr.DisplayElements();
 arr.AddItem(50);
 arr.RemoveItem(0);
 arr.DisplayElements();
 cout << "Array size: " << arr.GetSize() << endl;
 if (arr.isEmpty())
 {
 cout << "Array is empty!" << endl;
 }
 else
 {
 cout << "Array is not empty!" << endl;
 }
 return 0;
}
