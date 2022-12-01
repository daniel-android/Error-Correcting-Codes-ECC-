//Nearest-neighbor decoding method for the Hamming Code H(7,4)

#include <iostream>
#include <array>

using namespace std;

string NNDecoding(int a[], int b[]){//a[] receives the message after the noisy channel
	//b[] receives the vector that will return the decoded message
	//Defining a matrix with all the possibles codewords
	//each line of the matrix MatMessages defines a possible codeword
	int MatMessages[16][7]={{0,0,0,0,0,0,0},
							{0,0,0,1,0,1,1},
						    {0,0,1,0,1,1,1},
							{0,1,0,0,1,0,1},
							{1,0,0,0,1,1,0},
							{1,1,0,0,0,1,1},
							{1,0,1,0,0,0,1},
							{1,0,0,1,1,0,1},
							{0,1,1,0,0,1,0},
							{0,1,0,1,1,1,0},
							{0,0,1,1,1,0,0},
							{1,1,1,0,1,0,0},
							{1,1,0,1,0,0,0},
							{1,0,1,1,0,1,0},
							{0,1,1,1,0,0,1},
							{1,1,1,1,1,1,1}};

	int LineIndex;//line of the matrix MatMessages that will be sent by the decoder
	int Errors{7};//number of errors
	int Errors1{0};

	//Comparing ech line of the matrid MatMessages with the vector a[]
	for (int i = 0; i < 16; ++i){
		Errors1=0;
		for (int j = 0; j < 7; ++j){
			if(*(a+j)!=*(*(MatMessages+i)+j)){//Compare each entrance of the vector a[] 
				//with the entrances of the vector MatMessages[i][j]
				Errors1=Errors1+1;
			}
		}
		if (Errors1<Errors){
			Errors=Errors1;
			LineIndex=i;
		}
	}
	//Detecting the errors (the H(7,4) code detect 2 or fewer errrors).
	//An error will be detected when-ever a received word is not a code word.
	string Detection;
	if (Errors==0){
		Detection="(0 errors)";
	}
	if(Errors==1){
		Detection="(1 error)";
	}
	if(Errors==2){
		Detection="(2 errors)";
	}
	if(Errors>2){
		Detection="(3 or more errors)";
	}


	//Passing the decoded message to the vector b[]
	for (int i = 0; i < 4; ++i){
		*(b+i)=*(*(MatMessages+LineIndex)+i);
	}
	return Detection;
}