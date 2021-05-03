#ifndef MYLIST_H
#define MYLIST_H

template<class T>
class MyList
{
    T*head,*tail;
    int size;
    int eleoreder=0;
public:
    MyList(void){
          size=0;
          head=tail=0;
    }
    void display();
    void add(int);
};

#endif // MYLIST_H
