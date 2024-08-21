#include "Order.h"
#include <string>

using namespace std;

Order::Order(string nawa, int dat, int val){
	name = nawa;
	date = dat;
	price = val;
}

string Order::get_name(){ return name;}

int Order::get_date(){return date;}

int Order::get_price(){return price;}