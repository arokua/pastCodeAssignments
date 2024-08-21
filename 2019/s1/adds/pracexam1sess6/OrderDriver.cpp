#include "Order.h"
#include "RealOrder.h"

#include<iostream>

int main(){
  // driver program...
  
  // set up entities 
    Order o = Order("Jennifer",52,27);
    Order *p = new RealOrder("Billy",0,83);
    RealOrder q = RealOrder("John",10,109);
  
  // print out starting values
  std::cout << o.get_name() << " " << o.get_price() << " " << o.get_date() << std::endl;
  std::cout << q.get_name() << " " << q.get_price() << " " << q.get_date() << std::endl;
  std::cout << p->get_name() << " " << p->get_price() << " " << p->get_date() << std::endl;
  std::cout << "--------" << std::endl;

  // set the current date
  ((RealOrder*)p)->set_current_date(32);
  q.set_current_date(32);

  // now print out - prices should change
  std::cout << o.get_name() << " " << o.get_price() << " " << o.get_date() << std::endl;
  std::cout << q.get_name() << " " << q.get_price() << " " << q.get_date() << std::endl;
  std::cout << p->get_name() << " " << p->get_price() << " " << p->get_date() << std::endl;
  std::cout << "--------" << std::endl;
  // try out copy constructors
  o=*p;
  *p=q;

  // now look at how aliasing looks
  // now print out - prices should change
  std::cout << o.get_name() << " " << o.get_price() << " " << o.get_date() << std::endl;
  std::cout << q.get_name() << " " << q.get_price() << " " << q.get_date() << std::endl;
  std::cout << p->get_name() << " " << p->get_price() << " " << p->get_date() << std::endl;
  std::cout << "--------" << std::endl;
  // delete... just to clean up
  delete(p);
}
  
