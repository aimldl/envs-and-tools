// template_simple.cc

// This is a simple example to use template class TemplateSimple.
// Basically, there are two ways to use it.
// (1) Same file
//     The simplest way is to declare and define template class in a single file.
//     For example, main.cpp declares, implements, and instantiates a template class TemplateSimple within the same file.
// (2) Separate files
//     The second and practical way is to use separate files to declare, define, and instantiate the template class.
//     This may be trickier than (1) because of link error.

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>

template <typename E>
class TemplateSimple {
 public:
  TemplateSimple();
  ~TemplateSimple();
 
  void MemberFunction();

 private:
  int member_var_;  // member variable
};

template <typename E>
TemplateSimple<E>::TemplateSimple() {
  std::cout << "Constructor is called." << std::endl;
}

template <typename E>
TemplateSimple<E>::~TemplateSimple() {
  std::cout << "Destructor is called." << std::endl;
}

template <typename E>
void TemplateSimple<E>::MemberFunction() {
  std::cout << "MemberFunction is called." << std::endl;
}

int main() {
  std::cout << "Hello, world!" << std::endl;

  TemplateSimple<int> template_simple_obj;
  template_simple_obj.MemberFunction();

  return 0;
}
