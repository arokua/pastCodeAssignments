#include "RealOrder.h"
#include "Order.h"
#include <string>

using namespace std;

RealOrder::RealOrder(string nawa, int dat, int val) :Order(nawa, dat, val){}


int RealOrder::get_price(){
	int defau_lt = Order::get_price();
	if (current_date - Order::get_date() < 21){
		return defau_lt;
	}return defau_lt * 0.95;
}

void RealOrder::set_current_date(int date)  {
	current_date = date;
}
