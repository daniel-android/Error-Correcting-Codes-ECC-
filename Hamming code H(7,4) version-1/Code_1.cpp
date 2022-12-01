
#include <typeinfo>//for checking the type of the variable
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib> //abs() function
#include <iostream>
#include <fstream>
#include <list>
#include <array>
#include <string>
#include <bitset>//for transforming the string into binary

#include "Normal_dist.h"//call the header with multiplying matrices function
#include "NNDecodingForH(7,4).h" //call the header with the decoder of the Hamming Code H(7,4)

using namespace std;



//This program simmulates the Hamming code of lenght n=7 bits and dimension k=4 bits (3 parity bits).
//The Hamming code H(7,4) is able of transmitte 16 messages, hamming minimum distance 2t+1=3, it corrects 
//t=1 error and detect 2t=2 or fewer errors. Recall that, because only code words are transmitted, an error
//will be detected when-ever a received word is not a code word.

int main()
{	
   //Defining the encoding matrix of the Hamming(7,4) code 
   int mat2[4][7] = { { 1, 0,0,0,1,1,0 }, { 0,1,0,0,1,0,1 }, {0,0,1,0,1,1,1},{0,0,0,1,0,1,1}};//If one changes the dimensions of the matrix mat1
   //one may change the dimension of the argument in the function Mult_Matrices.h
   //Defining the vector that will storage the noncodified message 
   int mat1[4];//Initiallizing with zero entrances
   //Dimensions
   int m2 = 4, n1 = 4, n2 = 7;
   //Defining the matrix that will receive the multiplication mat1*mat2
   int mat3[n2];
   //Defining a matrix that will receive the decoded message
   int DecMessage[m2];
   //creating pointer to mat3
   int* ptr = mat3;
   //creating a pointer to DecMessage
   int* ptrDecMessage=DecMessage;
   //initialize random seed:
   srand (time(NULL));

   /* Before a stream can be opened, a stream object has to be created.
   Opening a stream means establishing a channel between the C++ program and the file in disk.*/
	fstream newfile;//creating an object of type fstream
   fstream newfile2;

	std::ofstream { "NewFile.txt" };// NewFile.txt has been created here

	newfile.open("File_1.txt",ios::in); //open a file to perform read operation using file object
	
/////////////////////////////////////////////////////////////////////////////////////////////////////

   if (newfile.is_open()){ //checking whether the file is open
      string tp;//creates a string variable
      while(getline(newfile, tp)){ //read data from file object and put it into string tp.
      	//the funciton getline takes lines of the text file
      	
         //cout << tp.size() << endl;
      	//for (std::size_t i = 0; i < tp.size(); ++i){//transforming the string tp into binary
         //   cout << bitset<8>(tp[i]) << endl;//cout << bitset<4>(tp.c_str()[i]) << endl;
         //}
         
         //Checking the size of the messages in the file: File_1.txt
         int SIZE=0;
         SIZE=tp.size();//size of the string tp
         if (SIZE>4)
         {
            cout << "The file File_1.txt contains a message of bit lenght longer than 4."<<endl;
            exit(0);
         }
         //cout << tp <<endl;

         //writting the set message into the NewFile.txt file
         newfile2.open("NewFile.txt", ios::app);//reopening to writte into a text file
         //writting into a file
         if(newfile2.is_open()){
            newfile2 <<" Sent message: " << tp << " ";
            newfile2.close();
         }  

         //Passing the string tp to the vector mat1
         for (int i = 0; i < SIZE; ++i)
         {
            //cout << typeid(tp[i]).name() <<endl;
            int num=tp[i]-48;//converting the character tp[i] into an integer value (48 is the integer value equivalent to 0)
            mat1[i]= num;
         }

         //Encoding the message mat1--------------------------------------------
         
         int x, i;
         for (i = 0; i < 7; ++i){
            mat3[i]=0;
            for (x = 0; x < 4; ++x){
               mat3[i]=mat3[i]+(mat1[x])*(mat2[x][i]);
            }
         mat3[i]=mat3[i]%2;
         //cout << mat3[i] << "\n";
         }
         
         //Rewritting the encoded message into the NewFile.txt file
         newfile2.open("NewFile.txt", ios::app);//reopening to writte into a text file
         //writting into a file
         if(newfile2.is_open()){
            newfile2 << " --> Encoded message: ";
            for (int i = 0; i < n2; ++i)
            {
               newfile2 << mat3[i];  
            }
            newfile2.close();
         }
         
         //Simulation of a noisy communication channel--------------------------------
         double y;
         for (int i = 0; i < n2; ++i)
         {  
            y=Normal_variable();
            if (abs(y)>=0.35)
            {
               //sum mat3[i] to a random bit 
               mat3[i]=(mat3[i]+rand()%2)%2;
            }
         }

         //Rewritting the message after the channel into the NewFile.txt file
         newfile2.open("NewFile.txt", ios::app);//reopening to writte into a text file
         //writting into a file
         if(newfile2.is_open()){
            newfile2 << "--> Message after the channel: ";
            for (int i = 0; i < n2; ++i)
            {
               newfile2 << mat3[i];  
            }
            newfile2.close();
         }

         //Decoding: nearest-neighbor decoding method------------------------------------------------
         
         //Detection=NNDecoding(ptr,ptrDecMessage);
         NNDecoding(ptr,ptrDecMessage);
         
         //Rewritting the received message into the NewFile.txt file
         newfile2.open("NewFile.txt", ios::app);//reopening to writte into a text file
         //writting into a file
         if(newfile2.is_open()){
            //newfile2 << Detection << " --> The decoded message is: ";
            newfile2 <<" --> The decoded message is: ";
            for (int i = 0; i < m2; ++i)
            {
               newfile2 << DecMessage[i];  
            }
            newfile2 <<"\n\n";
            newfile2.close();
         }
         

      }
      //stop reading the file File_1.txt
      newfile.close(); //close the file object.
   }
////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}
