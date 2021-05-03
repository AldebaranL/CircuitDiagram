#ifndef MYLIST_H
#define MYLIST_H

template<class T>
class MyList
{
    int eleoreder;
public:
    int size;
    T*begin,*end;
    MyList(void){
          size=0;
          begin=end=0;
          eleoreder=0;
    }
  //  ~MyList();
    T* find(int);
    void push_back(T*);
    void erase(int);
};

#endif // MYLIST_H
