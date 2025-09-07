#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T data_){
        data = data_;
    }
};

template<typename T>
class List {
private:
    Node* head;
    Node* tail;
public:

    List() : head(nullptr), tail(nullptr) {}

    T front(){
        return head->data;
    }
    T back(){
        return tail->data;
    }
    void push_front(T dat){
        Node<T>* nuevo = new Node<T>(dat);
        nuevo->next = head;
        nuevo->prev = nullptr;
        if (head) {
            head->prev = nuevo;
        }
        head = nuevo;
        if (!tail){
            tail = nuevo;
        }

    }

    void push_back(T dat){
        Node<T>* nuevo = new Node(dat);
        nuevo->next = nullptr;
        nuevo->prev = tail;
        if (tail){
            tail->next = nuevo;
        }

        tail = nuevo;

        if (!head){
            head = nuevo; 
        }
    }

    T pop_front(){
        if (!head)
        {
            throw std::out_of_range("Lista vacía");
        }
        
        Node<T>* temp = head;
        head = temp->next;
        if (head)
        {
            head->prev = nullptr;
        }
        else{
            tail = nullptr;
        }
        T valor = temp->data;
        delete temp;
        return valor;
    }

    T pop_back(){
        if (!head)
        {
            throw std::out_of_range("Lista vacía");
        }
        Node<T>* temp = tail;
        tail = temp->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else{
            head = nullptr; 
        } 
        T valor = temp->data;
        delete temp;
        return valor;
    }

    T operator[](int i){
        Node<T>* temp = head;
        while (i-- && temp)
        {
            temp = temp->next;
        }
        if (!temp)
        {
            throw out_of_range("Índice inválido")
        }
        return temp->data;
    }

    bool empty(){
        if (!head)
        {
            return true;
        }
        return false;
    }

    int size(){
        int i = 0;
        Node<T>* temp = head;
        while (temp)
        {
            i++;
            temp = temp->next;
        }
        return i;
    }
    void clear(){
        Node<T>* temp = head;
        while (temp) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = nullptr;
    }
    Node<T>* split(Node<T>* head) {
        Node<T>* slow = head;
        Node<T>* fast = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node<T>* second = slow->next;
        slow->next = nullptr;
        if (second){
            second->prev = nullptr;
        }
        return second;
    }

    Node<T>* merge(Node<T>* first, Node<T>* second) {
        if (!first) {
            return second;
        }
        if (!second) {
            return first;
        }

        if (first->data <= second->data) {
            first->next = merge(first->next, second);
            if (first->next){
                first->next->prev = first;
            } 
            first->prev = nullptr;
            return first;
        } else {
            second->next = merge(first, second->next);
            if (second->next) {
                second->next->prev = second;
            }
            second->prev = nullptr;
            return second;
        }
    }
    Node<T>* mergeSort(Node<T>* head) {
        if (!head || !head->next) {
            return head;
        }

        Node<T>* second = split(head);

        head = mergeSort(head);
        second = mergeSort(second);

        return merge(head, second);
    }

    void sort() {
        head = mergeSort(head);

        tail = head;
        if (tail) {
            while (tail->next) {
                tail = tail->next;
            }
        }
    }

    void reverse(){
        Node<T>* act = head;
        Node<T>* ant = nullptr;
        while (act)
        {
            ant = act->prev;
            act->prev = act->next;
            act->next = ant;

            act = act->prev;
        }

        if (ant) {
            ant = head;
            head = tail;
            tail = ant;
        }
    }

};

