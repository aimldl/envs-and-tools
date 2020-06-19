// queue_linear-using_dynamic_array.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>

class MyQueue {
 public:
  MyQueue(int size);
  ~MyQueue();

  bool enqueue(int value);  // return false if something goes wrong
  bool dequeue();
  int  front();

 private:
  void init(int size);
  bool is_empty();

  int size_;
  int* front_;
  int* back_;
  int* queue_;  // dynamic array is used to store the data
};

MyQueue::MyQueue(int size) { init(size); }

MyQueue::~MyQueue() {}

bool MyQueue::enqueue(int value) {
  *back_ = value;
  back_++;
  return true;
}

bool MyQueue::dequeue() {
  if (is_empty()) {
    std::cout << "Error: dequeue failed." << std::endl;
    return false;
  }
  front_++;
  return true;
}

int MyQueue::front() {
  int value = *front_;
  return value;
}

void MyQueue::init(int size) {
  size_ = size;
  queue_ = new int[size];
  front_ = queue_;
  back_ = queue_;
}

bool MyQueue::is_empty() { 
  if (back_ <= front_) {
    std::cout << "Error: no space left in the queue" << std::endl;
    return true;
  } else {
    return false;
  }
}

int main() {
  MyQueue q(5);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  std::cout << q.front() << std::endl;
  q.dequeue();
  std::cout << q.front() << std::endl;
  q.dequeue();

  q.enqueue(4);
  q.enqueue(5);
  q.enqueue(6);

  std::cout << q.front() << std::endl;
  q.dequeue();
  std::cout << q.front() << std::endl;
  q.dequeue();
  std::cout << q.front() << std::endl;
  q.dequeue();
  std::cout << q.front() << std::endl;
  q.dequeue();
  std::cout << q.front() << std::endl;
  q.dequeue();

  return 0;
}

// Expected Output
// 1
// 2
// 3
// 4
// 5
// 6
// 556319166
// Error: no space left in the queue
// Error: dequeue failed.
