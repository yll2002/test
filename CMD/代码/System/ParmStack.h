#  ifndef  ParmStack_h
#  define  ParmStack_h
#  include <assert.h>
#  include <iostream>
#  include <string>

   using namespace std;
///////////////////////////////////////////////////////
template <class type>
class abstack
{
	public:
		bool IsEmpty()
		{return (height == 0)? true:false;}
		virtual void Push(type&) = 0;
		virtual bool Pop(type&) = 0;
		virtual void Clear() = 0;
	protected:
		unsigned height;
};
///////////////////////////////////////////////////////
template <class type>
struct StackNode
{
	type data;
	StackNode *next;
};
///////////////////////////////////////////////////////
template <class type>
class LinkStack:public abstack<type>
{
	public:
		LinkStack();
		LinkStack(LinkStack &g)
		{
			top = NULL;
			Copy(g);
		}
		~LinkStack()
		{Clear();}
		void Clear();
		void Push(type &x);
		bool Pop(type &x);
		LinkStack & operator = (LinkStack &g)
		{
			Copy(g);
			return *this;
		}
	protected:
		StackNode<type> *top;
		LinkStack &Copy(LinkStack &s);
};
///////////////////////////////////////////////////////
//-----------------------------------------------------
template <class type>
LinkStack<type>::LinkStack()
{
	height = 0;
	top = NULL;
}
//-----------------------------------------------------
template <class type>
LinkStack<type> &LinkStack<type>::Copy(LinkStack<type> &g)
{
	StackNode<type>*p,*q,*r;
	if(top) Clear();
	height = g.height;
	top = NULL;
	if(!g.top)
		return *this;
	top = new StackNode<type>;
	assert(top);
	top->next=NULL;
	top->data = g.top->data;
	q = q.top->next;
	p = top;
	while(q)
	{
		r = new StackNode<type>;
		assert(r);
		r->data = q->data;
		r->next NULL;
		p->next = r;
		p = p->next;
		q = q->next;
	}
	return *this;
}
//-----------------------------------------------------
template <class type>
void LinkStack<type>::Clear()
{
	type x;
	while(Pop(x));
}
//-----------------------------------------------------
template <class type>
void LinkStack<type>::Push(type &x)
{
	StackNode<type> *p;
	if(top)
	{
		p = new StackNode<type>;
		assert(p);
		p->data = x;
		p->next = top;
		top = p;
	}
	else
	{
		top = new StackNode<type>;
		assert(top);
		top->data = x;
		top->next = NULL;
	}
	height++;
}
//-----------------------------------------------------
template <class type>
bool LinkStack<type>::Pop(type &x)
{
	StackNode<type> *p;
	if(height)
	{
		x = top->data;
		p = top;
		top = top->next;
		delete p;
		height--;
		return true;
	}
	return false;
}
//-----------------------------------------------------
#endif