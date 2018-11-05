/*
Student name   : Mihai Lapuste
Student number : 301 282 531
Student email  : mlapuste@sfu.ca
*/


#include "Deque.h"
#include <iostream>
#include <iomanip>

using namespace std;

Deque::Deque(){ // constructor
  left_p = NULL; // Points to left end node, or NULL if Deque is empty.
  rear_p = NULL; // Points to right end node, or NULL if Deque is empty.
  current_size = 0;// current number of elements in the queue.
  cursor = NULL; // pointer to "current" node (or NULL if deque is empty).
}

Deque::Deque(const Deque& dq){//segmentation fault

    if(dq.left_p != NULL){//deque not empty
        node * temp = dq.left_p;
        current_size = dq.current_size;
        node * newNode = new node(temp -> data, NULL, NULL);
        left_p = newNode;
        if(current_size==1){//deque has 1 element
            rear_p = newNode;
            cursor = newNode;
        }
        else{//deque has more than 1 element
          temp = temp -> next;//now have 2 node ptrs to original deque.
          while(temp != NULL){
              node * newNode2 = new node(temp -> data, newNode, NULL);
              if(temp == dq.cursor){//cursor check
                cursor = newNode2;
              }
              newNode -> next = newNode2;
              temp = temp -> next;  //move along original deque
              newNode = newNode2;
            }
          rear_p = newNode;
      }
      delete temp;
    }

  }


Deque::~Deque(){ // Destructor, destroys all nodes from left to right
  while (!empty()) pop_left(); // calls pop_left until empty
}


void Deque::push_left(int item){
  node * newNode = new node(item, NULL, left_p);
  if(left_p == NULL){ // queue is empty
    rear_p = newNode;
    cursor = newNode;
  }else{
    left_p -> prev = newNode;
  }
  left_p = newNode;
  current_size++;
}


void Deque::push_right(int item){
  node * newNode = new node(item, rear_p, NULL);
  if(rear_p == NULL){
    left_p = newNode;
    cursor = newNode;
  }else{
    rear_p -> next = newNode;
  }
  rear_p = newNode;
  current_size++;
}


int Deque::pop_left(){
  if(!empty()){
    node * temp = left_p;
    left_p = left_p -> next;


    if(left_p != NULL){ //if queue is not empty
      left_p -> prev = NULL;
    }else{ //if queue is empty
      rear_p = NULL;
      left_p = NULL;
      cursor = NULL;
    }

    if(cursor == temp){
      cursor = temp -> next;
    }


    int return_val = temp -> data;
    delete temp;
    current_size--;
    return return_val;
  }
}


int Deque::pop_right(){
  if(!empty()){
    node * temp = rear_p;
    rear_p = rear_p -> prev;


    if(rear_p != NULL){
      rear_p -> next = NULL;
    }else{
      rear_p = NULL;
      left_p = NULL;
      cursor = NULL;
    }

    if(cursor == temp){
      cursor = temp-> prev;
    }

    int return_val = temp -> data;
    delete temp;
    current_size--;
    return return_val;
  }
}


bool Deque::empty(){
  if(left_p == NULL && rear_p == NULL){
    return true;
  }
  else{
    return false;
  }
}


int Deque::size(){
  return current_size;
}


bool Deque::cursor_left(){
  if(cursor == NULL && rear_p != NULL){
    cursor = rear_p;
    return true;
  }
  else if(cursor -> prev != NULL){
    cursor = cursor -> prev;
    return true;
  }
  else{
    return false;
  }
}


bool Deque::cursor_right(){
  if(cursor == NULL && left_p != NULL){
    cursor = left_p;
    return true;
  }
  else if(cursor -> next != NULL){
    cursor = cursor -> next;
    return true;
  }
  else{
    return false;
  }
}


int Deque::peek_left(){
    if(!empty()){
      return left_p -> data;
    }
  }


int Deque::peek_right(){
    if(!empty()){
      return rear_p -> data;
    }
  }


int Deque::get_cursor(){
    if(!empty()){
      return cursor -> data;
    }
  }


void Deque::set_cursor(int item){
    if(!empty()){
       cursor -> data = item;
    }
  }


void Deque::display(){
    if(!empty()){
      node * temp = left_p;
      cout << "[";
      while(temp != NULL){
        cout << temp -> data << ";";
        temp = temp -> next;
      }
      cout << "]";
      delete temp;
    }
    else{
      cout << "[]";
    }
    cout << " size=" << size()<< ", cursor=";
    if(cursor == NULL)
       cout << "NULL.\n";
    else
       cout << get_cursor() << ".\n";
}


void Deque::verbose_display(){ // like display, but includes node addresses and pointer values.
    if(!empty()){
      node * temp = left_p;
      const char separator = ' ';
      int i = 0;
      cout << left << setw(10) << setfill(separator) << "node"
           << left << setw(16) << setfill(separator) << "prev"
           << left << setw(16) << setfill(separator) << "address"
           << left << setw(10) << setfill(separator) << "key"
           << left << setw(16) << setfill(separator) << "next"
           << left << setw(16) << setfill(separator) << "cursor"
           << left << setw(16) << setfill(separator) << "cursor value" << endl << endl;

      while(temp != NULL){
        if(temp -> prev == NULL) cout << left << setw(10) << setfill(separator) << "left_p";
        else if(temp -> next == NULL) cout << left << setw(10) << setfill(separator) << "rear_p";
        else cout << left << setw(10) << setfill(separator) << i;
        cout << left << setw(16) << setfill(separator) << temp -> prev
             << left << setw(16) << setfill(separator) << temp
             << left << setw(10) << setfill(separator) << temp -> data
             << left << setw(16) << setfill(separator) << temp -> next
             << left << setw(16) << setfill(separator) << cursor
             << left << setw(16) << setfill(separator) << cursor->data  << endl;
        temp = temp -> next;
        i++;
      }
      delete temp;
    }
    else{
      cout << "Empty." << endl;
    }
  }
