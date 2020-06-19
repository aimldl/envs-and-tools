// tree-combination of numbers.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
using namespace std;

class node
{
public:
	 node() {}
	 node(int num) { set_val(num); }
	~node() {}

	void  set_val(int num)  { val = num; }
	void  set_prev(node* p) { prev = p;  }
	void  set_next(node* n) { next = n;  }

	int   get_val()  { return val;  }
	node* get_prev() { return prev; }
	node* get_next() { return next; }
private:
	int   val;  // value
	node* prev;
	node* next;
};

// Singly linked list
class linked_list
{
public:
	 linked_list() {}
	~linked_list() {}

	void  set_head(node* h) { head = h; }
	void  set_tail(node* t) { tail = t; }
	node* get_head() { return head; }
	node* get_tail() { return tail; }

	void  insert(node* n);
	void  remove(node* n);
private:
	node* head;
	node* tail;
};

void
linked_list::insert(node* n)
{

}

void
linked_list::remove(node* n)
{

}

int main()
{
	int  N        = 4;
	int  nums[4]  = { 1,2,3,4 };
	bool check[4] = { false, false, false, false };
	node* nd      = new node[N];

	for (int i = 0; i < N; i++)
		nd[i].set_val(nums[i]);

	for (int i = 0; i < N; i++)
		cout << nd[i].get_val() << " ";
	cout << endl;
	
	for (int i = 0; i < N; i++)
	{
		if ( i < N-1 )
		  nd[i].set_next(&nd[i + 1]);
		else
		  nd[i].set_next( NULL );
	}

	cout << "Use the nodes" << endl;
	node* curr = &nd[0];
	for (int i = 0; i < N; i++)
	{
		cout << curr->get_val() << " ";
		curr = curr->get_next();
	}
	cout << endl;

	return 0;
}