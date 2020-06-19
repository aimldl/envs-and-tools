// queue_simple-using_stl_vector.cpp

#include <iostream>
#include <vector>
#include "pch.h"

// I have a doubt about this implementation with vector.
// If a STL vector is used, the size of queue can increase.
// The queue size is fixed for linear queue, isn't it?

class MyQueue {
 public:
  MyQueue(int size);
  ~MyQueue();

  bool enqueue(int value);  // Insert a value to the tail of queue_
  bool dequeue();           // Delete a value at the head of queue_
  int front();              // Get the value in the head
  int back();
  bool is_full();
  bool is_empty();

 private:
  void init(int size);

  std::vector<int> queue_;
  int size_;
  int index_front_;
  int index_back_;
};

MyQueue::MyQueue() {}

MyQueue::~MyQueue() {}

bool MyQueue::enqueue(int value) {
  if (is_full()) {
    std::cout << "Error: Queue overflow" << std::endl;
    return false;
  }
  queue_.push_back(value);

  return true;
}

bool MyQueue::dequeue() {
  if (is_empty()) {
    std::cout << "Error: queue underflow!" << std::endl;
    return false;
  }
  // TODO: delete queue_[index_front_]
  return true;
}

int MyQueue::front() {
  if (is_empty()) {
    std::cout << "Warning: queue is empty" << std::endl;
  }
  int value = queue_[index_front_];
  return value;
}

int MyQueue::back() {
  if (is_empty()) {
    std::cout << "Warning: queue is empty" << std::endl;
  }
  int value = queue_[index_back_];
  return value;
}

bool MyQueue::is_full() {
  if (size_ == queue_.size()) return true;
  return false;  // else
}

bool MyQueue::is_empty() {
  if (queue_.size() == 0) return true;
  return false;  // else
}

void MyQueue::init(int size) { size_ = size;
  queue_.

}

int main() {
  MyQueue linear_queue_with_vector;

  std::cout << "Hello World!\n";
}