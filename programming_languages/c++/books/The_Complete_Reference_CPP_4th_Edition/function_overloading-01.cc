// Function Overloading, pp.275~276

//#include "pch.h"  // Uncomment this in Visual Studio
#include <iostream>

using namespace std;

// MyAbs is overloaded three ways
int MyAbs(int i);
double MyAbs(double d);
long MyAbs(long l);

// Expected standard output
//Using int MyAbs()
//MyAbs(-10) = 10
//Using double MyAbs()
//MyAbs(-11.0) = 11
//Using long MyAbs()
//MyAbs(-9L) = 9

int main() {
	cout << "MyAbs(-10) = " << MyAbs(-10) << endl;
	cout << "MyAbs(-11.0) = " << MyAbs(-11.0) << endl;
	cout << "MyAbs(-9L) = " << MyAbs(-9L) << endl;

	return 0;
}

int MyAbs(int i) {
	cout << "Using int MyAbs()" << endl;
	return i < 0 ? -i : i;
}

double MyAbs(double d) {
	cout << "Using double MyAbs()" << endl;
	return d < 0.0 ? -d : d;
}

long MyAbs(long l) {
	cout << "Using long MyAbs()" << endl;
	return l < 0 ? -l : l;
}

// Discussion about the errors for this function overloading problem, https://stackoverflow.com/questions/17720978/function-overloading-in-visual-c
// When I run
// C2084 'long abs(const long) throw()' 함수에 이미 본문이 있습니다.
// C2264 'abs': 함수 정의 또는 선언에 오류가 있습니다.함수가 호출되지 않습니다.
// C2382 'abs' : 재정의.예외 사양이 다릅니다.
//
// None of the answers was satisfactory to me.
// The following code compiles well on Linux, but not on Visual Studio (Windows).
// My solution is to change the function name abs to something else, e.g. MyAbs.
// My guess is there's an issue with the namespace in "pch.h".
// (In the discussion, other includes for Visual Studio were used.)

// Function Overloading, pp.275~276

//#include "pch.h"  // Uncomment this in Visual Studio
//#include <iostream>
//
//using namespace std;
//
//// abs is overloaded three ways
//int abs(int i);
//double abs(double d);
//long abs(long l);
//
//int main() {
//	cout << "abs(-10) = " << abs(-10) << endl;
//	cout << "abs(-11.0) = " << abs(-11.0) << endl;
//	cout << "abs(-9L) = " << abs(-9L) << endl;
//
//	return 0;
//}
//
//int abs(int i) {
//	cout << "Using int abs()" << endl;
//	return i < 0 ? -i : i;
//}
//
//double abs(double d) {
//	cout << "Using double abs()" << endl;
//	return d < 0.0 ? -d : d;
//}
//
//long abs(long l) {
//	cout << "Using long abs()" << endl;
//	return l < 0 ? -l : l;
//}
