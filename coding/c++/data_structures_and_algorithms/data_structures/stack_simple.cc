// stack_simple.cc

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>

class StackSimple {
 public:
  StackSimple(int stack_size) { init(stack_size); }
  ~StackSimple() { delete[] array_; }
  
  void push(int num);
  int  pop();

 private:
  void init(int stack_size);
  
  int  stack_size_;
  int* array_;
  int  l;   // locator index
};

void StackSimple::init(int stack_size)
{
  stack_size_ = stack_size;
  array_      = new int[stack_size];
  l = 0;
}

void StackSimple::push(int num)
{
  if (l >= stack_size_) {
    std::cout << "Stack Overflow: " << num << std::endl;
    return;
  }
  array_[l] = num;
  l++;
}

int StackSimple::pop()
{
  // I'm not sure if returning 0 is accurate, but...
  if (l == 0)
  {
    std::cout << "Stack Underflow" << std::endl;
    return 0;
  }
  l--;
  return array_[l];
}

int main()
{
  StackSimple stack(3);

  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << "-------" << std::endl;

  return 0;
}
