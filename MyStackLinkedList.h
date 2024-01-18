#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <memory>
#include <condition_variable>

template<typename T>
class Node
{
    public:
    T data;
    Node* next;
};

template<typename T>
class MyStackLinkedList
{
    private:
    Node<T>* head;
    std::atomic<int> count;
    std::mutex m_mutex;
    std::condition_variable cv;
    void pop();
    T& peek();
    public:
    MyStackLinkedList():
    head{nullptr},
    count{0}
    {}
    void push(T&& new_data);
    bool empty() const
    {
        return count <= 0;
    }
    bool pop_and_get(T& get_value);
    void pop_and_get_consumer(T& get_value);
};

template<typename T>
void MyStackLinkedList<T>::push(T&& new_data)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    Node<T>* new_node = new Node<T>();
    new_node->data = new_data;
    new_node->next = head;
    head = new_node;
    ++count;
    lock.unlock();
    cv.notify_one();
}

template<typename T>
void MyStackLinkedList<T>::pop()
{
    if (head == nullptr)
    {
        return;
    }
    Node<T>* delete_this = head;
    head = head->next;
    delete delete_this;
    --count;
}

template<typename T>
T& MyStackLinkedList<T>::peek() 
{
    return head->data;
}

template<typename T>
bool MyStackLinkedList<T>::pop_and_get(T& get_value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (empty())
    {
        return false;
    }
    get_value = peek();
    pop();
    return true;
}

template<typename T>
void MyStackLinkedList<T>::pop_and_get_consumer(T& get_value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(empty())
    {
        cv.wait(lock);
    }
    get_value = peek();
    pop();
}
