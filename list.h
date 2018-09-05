#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"
#include "iterator.h"

using namespace std;

template <typename T>
class List {
    private:
        Node<T>* start;
        int nodes;
    public:
        List(){
          start=nullptr;
          nodes=0;
        };

        T front(){
          if(!start){
              throw "Lista Vacia";
          } else{
              return start->data;
          }
        };
        T back(){
          if(!start){
              throw "Lista Vacia";
          } else{
              return start->prev->data;
          }
        };
        void push_front(T value){
          this->push_back(value);
          start=start->prev;
        };
        void push_back(T value){
          auto* temp= new Node<T>{value, nullptr, nullptr};
          if (start==nullptr) {
              start=temp;
              start->next=start;
              start->prev=start;
          }else{
            start->prev->next=temp;
            temp->prev=start->prev;
            temp->next=start;
            start->prev=temp;
          }
          nodes++;
        };
        void pop_front(){
          auto* temp=start;
          if(!start)
              throw "Lista vacia";
          if(nodes==1)
              start=nullptr;
          else{
              start->prev->next=start->next;
              start->next->prev=start->prev;
              start=start->next;
          }
          delete temp;
          nodes--;
        };
        void pop_back(){
          start=start->prev;
          this->pop_front();
        };
        T get(int position){
          if(!start){
              throw "Vacio";
          }
          auto* temp=start;
          for (int i = 0; i < position; ++i) {
              temp=temp->next;
          }
          return temp->data;
        };
        void concat(List<T> &other){
          if (!start) {
            start=other.start;
          }else if(other.start){
            auto* temp=other.start->prev;
            this->start->prev->next=other.start;
            other.start->prev->next=this->start;
            other.start->prev=this->start->prev;
            this->start->prev=temp;
          }
        };
        bool empty(){
          return start==nullptr;
        };
        int size(){
          return nodes;
        };
        void clear(){
          auto* temp=start;
          if (nodes>1) {
            start->prev->next=nullptr;
            while(start->next!=nullptr){
              start=start->next;
              delete start->prev;
              if(start->next==nullptr)
                temp=start;
            }
          }
          start=start->prev=start->next=nullptr;
          delete temp;
          nodes=0;
        };
        Iterator<T> begin(){
          return Iterator<T>(start);
        };
        Iterator<T> end(){
          return Iterator<T>(start->prev);
        };
        ~List(){
          auto* temp=start;
          if (nodes>1) {
            start->prev->next=nullptr;
            while(start->next!=nullptr){
              start=start->next;
              delete start->prev;
              if(start->next==nullptr)
                temp=start;
            }
          }
          delete temp;
        };
};

#endif
