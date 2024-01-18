#include <iostream>
#include "MyStackLinkedList.h"

class A
{
    int val;
    public:
    A(int x):
    val{x}
    {
        std::cout << "Cons" << std::endl;
    }
    ~A()
    {
        std::cout << "Dest" << std::endl;
    }
    int getVal() const
    {
        return val;
    }
};

int main()
{
    MyStackLinkedList<A*> st;
    A a1(1);
    st.push(std::move(&a1));
    A a2(2);
    st.push(std::move(&a2));
    A a3(3);
    st.push(std::move(&a3));
    A* v = &a3;
    st.pop_and_get(v);
    A a4(4);
    st.push(std::move(&a4));
    A a5(5);
    st.push(std::move(&a5));


    while(!st.empty())
    {
        st.pop_and_get(v);
        std::cout << v->getVal() << std::endl;
    }
    
}
