//Parity-check matrix decoding method for the Hamming Code H(7,4)

#include <iostream>
#include <array>
#include <vector> 
#include<valarray> // for valarray functions

using namespace std;

void PCMDecoding(int a[], int b[]){//a[] receives the message after the noisy channel
	//b[] receives the vector that will return the decoded message
	
	//Defining the transpose of the parity-check matrix of the Hamming code H(7,4)(the matrix of the dual code)
	int ParityCheckMat[7][3]={{1,1,0},{1,0,1},{1,1,1},{0,1,1},{1,0,0},{0,1,0},{0,0,1}};
	int ParityVector[3]={0,0,0};
	
	
	//multiplying the vector a[] by ParityCheckMat. The resulte is storaged in ParityVector[]
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 7; ++j){
			ParityVector[i]=ParityVector[i] + *(a+j) * *(*(ParityCheckMat+j)+i);
		}
		ParityVector[i]=ParityVector[i]%2;//redusing mod 2
	}



	//Checking if ParityVector is a null vector (if ParityVector is null, then, no correction is necessary)
	int checker{1};//auxiliar variable
	for (int i = 0; i < 3; ++i){
		if (ParityVector[i]==checker){
			checker=0;//if ParityVector is not null, the variable checker changes its value
			break; //get out a the for loop
		}
	}

	/*
	for (int i = 0; i < 3; ++i)
	{
		cout << ParityVector[i];
	}
	cout << "\n\n";
	cout << "Checker: "<< checker;
	cout << "\n\n";
	*/

	//if the variable checker=1, then no error was made along the channel (ParityVector is null)
	if (checker==1){
		//Passing the decoded message to the vector b[]
		for (int i = 0; i < 4; ++i){
			*(b+i)=*(a+i);//the message consists of the four first bits of the vector a[]
		}
		return;
	}


	//if the variable checker!=1, some error occurs.
	int count=0;
	//Lets check if the vector ParityVector eqauls some line of the matrix ParityCheckMat
	for (int i = 0; i < 7; ++i){
		count=0;
		for (int j = 0; j < 3; ++j){
			if(*(ParityVector+j)==*(*(ParityCheckMat+i)+j)){//comparing the vector ParityVector with
				//the lines of the matrix ParityCheckMat
				count=count+1;
			}
			if(count==3){//if count=3 then ParityVector=ParityCheckMat[i][]
				//creating a null vector
				int nullVector[7]={0,0,0,0,0,0,0};
				nullVector[i]=1;// set the entrance i of nullVector equal to 1
				for (int l = 0; l < 7; ++l){//summing (a[] + nullVector[]) mod2
					*(a+l)=(*(a+l) + *(nullVector+l))%2;
				}
				//Passing the received message a[] to the vector b[]
				for (int l = 0; l < 4; ++l){
					*(b+l)=*(a+l);	
				} 
				return;
			}
		}
		
	}
	

	//If two or more erros occurs:
	//The alternative is to not decode the received codeword
		//Passing the received message a[] to the vector b[]
		for (int i = 0; i < 4; ++i){
			*(b+i)=*(a+i);	
		} 
}
