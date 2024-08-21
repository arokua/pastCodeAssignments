/*  Order class... 
    Base class for a order for an online company
*/

#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order{
  public:
     // Constructor - takes name, date, and price - string and integers
     Order(std::string, int, int);
   
     // getter methods
   
     virtual std::string get_name();
     virtual int get_date();
     virtual int get_price();
  protected:
     // field variables
     std::string name;
     int date;
     int price;
};
  
  
#endif // ORDER_H
