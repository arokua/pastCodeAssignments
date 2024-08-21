#include <iostream>
#include <string>
using namespace std;

void print_class(string courses[4], string students[], int report_card[][4], int nstudents){
	cout<< "Report Card ";
	for (int c = 0; c < 4; c++){
		cout<< courses[c];
		if (c < 3){
			cout<< " ";
		}

	}
	cout << "\n";
	for (int s = 0; s < nstudents; s++ ){
		cout<< students[s]<< " ";
		for (int j = 0; j < 4; j++){
			cout<< report_card[s][j];
			if (j < 3){
				cout<< " ";
			}
		}
		
		cout<< endl;
 	
	}

 	
}