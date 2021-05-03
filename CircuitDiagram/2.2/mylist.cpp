#include "mylist.h"
#include<QDebug>
template<class T>
void MyList<T>::push_back(T* n1){
 n1->order=++eleoreder;
 if(size==0){
  begin=end=n1;
  size++;
  return;
 }
  end->next=n1;
  end=n1;
  size++;
}
template<class T>
T* MyList<T>::find(int torder){
 T *tem=begin;
  while(tem!=end){
      if(tem->order==torder){
          return tem;
      }
      tem=tem->next;
  }
  if(end->order==torder){
      return tem;
  }
  qDebug()<<"cannot find!";
  return nullptr;
}
template<class T>
void MyList<T>::erase(int torder){
    size--;
    if(size==0){
        delete begin;
        begin=end=nullptr;
        return;
     }
    T *tem=begin;
    if(tem->order==torder){
        begin=begin->next;
        delete tem;
        return;
    }
    while(tem->next!=end){
        if(tem->next->order==torder){
            T* t1=tem->next->next;
            delete tem->next;
            tem->next=t1;
            return;
        }
    tem=tem->next;
    }
    if(end->order==torder){
        delete end;
        end=tem;
        end->next=nullptr;
        return ;
    }
}

