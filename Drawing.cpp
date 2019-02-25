#include <iostream>
#include "Section.h"
#include "Lane.h"

using namespace std;

int main(){

	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){

				if(j == 4 || j == 5 || i == 4 || i == 5){
					
					cout << " ";
				}
				else{
                    
                    cout << "." << " ";
				}

		}
		cout << endl;

	}

}