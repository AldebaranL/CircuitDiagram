/*#include "mylist.h"

template<class T>
void MyList::display(){
 T * tmp=head;
 if(tmp){
  cout<<tmp->x;
  tmp=tmp->next;
 }
 while(tmp){
  cout<<' '<<tmp->x;
  tmp=tmp->next;
 }
}

template<class T>
void MyList::add(T n1){
 //T * n1=new T(x);
 n1.order=++eleoreder;
 if(nodenum==0){
  head=tail=n1;
  size++;
  return;
 }
 if(n1->x<head->x){
  n1->next=head;
  head=n1;
  size++;
  return;
 }
 if(n1->x>tail->x){
  tail->next=n1;
  tail=n1;
  size++;
  return;
 }
 T * tmp=head;
 while(tmp->next){
  if(tmp->x==n1->x)return;
  if(tmp->x<n1->x&&tmp->next->x>n1->x){
   n1->next=tmp->next;
   tmp->next=n1;
   size++;
   return;
  }
  tmp=tmp->next;
 }
}

template<class T>
void MyList::erase(T n1){
 //T * n1=new T(x);
 if(nodenum==0){
  head=tail=0;
  size--;
  return;
 }
 if(n1->x<head->x){
  n1->next=head;
  head=n1;
  size++;
  return;
 }
 if(n1->x>tail->x){
  tail->next=n1;
  tail=n1;
  size++;
  return;
 }
 T * tmp=head;
 while(tmp->next){
  if(tmp->x==n1->x)return;
  if(tmp->x<n1->x&&tmp->next->x>n1->x){
   n1->next=tmp->next;
   tmp->next=n1;
   size++;
   return;
  }
  tmp=tmp->next;
 }
}
*/
