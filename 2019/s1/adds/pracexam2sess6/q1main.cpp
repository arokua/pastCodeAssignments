#include "Node.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

int main() {
    int arr1[3]={5, -1, -3};
    LinkedList *list = new LinkedList(arr1, 3);
    list->duplicateElements();
    list->printItems();
    
    int arr2[2]= {1, 6};
    list = new LinkedList(arr2, 2);
    list->duplicateElements();
    list->printItems();

    int arr3[2]= {5, 2};
    list = new LinkedList(arr3, 2);
    list->duplicateElements();
    list->printItems();

    int arr4[1]= {4};
    list = new LinkedList(arr4, 1);
    list->duplicateElements();
    list->printItems();

}
