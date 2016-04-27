//tego pliku nie wolno modyfikować
//napisać zadanie które stworzy liste.

#include "LAB_2014_03_27.h"

int main(int argc, char** argv)
{
  list<int> l;
  
  for(int i=0;i<10;++i)
    l.push_back(i);

  for(int i=0;i<10;++i)
    l.push_front(i);
  
  std::cout << "Standard out:" << l << std::endl;

  std::cout << "Extended: ";

  for(list<int>::iterator i = l.begin(); i != l.end(); ++i) 
      std::cout << *i << ", ";
}
