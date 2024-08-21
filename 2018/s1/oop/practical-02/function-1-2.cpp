#include <iostream>

using namespace std;

int identity(int array[10][10]){
	int no1 = 0;
	int not1or0 = 0;
	for (int r = 0; r < 10; r++){
		for (int c = 0; c < 10; c++){
			if (r == c){
				if (array[r][c] == 1)  {
					no1 += 1;
				}
			}else {
				if (array[r][c] != 0)  {
					not1or0 += 1;
					break;
				}
			}
		}
	}

	if (no1 == 10 && not1or0 == 0) {
		return 1;
	}

	else {
		return 0;
	}
}