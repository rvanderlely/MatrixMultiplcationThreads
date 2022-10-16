/*****************************************************************************************
 * Name: Rachel Vanderlely
 * Date: October 16 2022
 * Project: Matrix Multiplcation
 * Class: Operating Systems
 * Professor: Dr. Zhao
 ****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using std::cin;             
using std::cout;
using std::setw;



/*****************************************************************************************
 *  							Global Variables 
 ****************************************************************************************/
int** Dynamic_MatrixA;	//make a 2d array matrixA dynamcailly 	
int** Dynamic_MatrixB;	//make a 2d array matrixA dynamcailly 
int** Dynamic_MatrixC; //make a 2d array matrixA dynamcailly 
//Matrix Dimensions
int matrix_A_rows;
int matrix_A_cols;
int matrix_B_rows;
int matrix_B_cols;



/*****************************************************************************************
 * 							Matrix Index Structure
 * Holds two integers to be passed into the matrix_thread function which is called by the 
 * create_thread function. The create_thread function only allows one parameter to be passed 
 * into it and used as the parameters for the function the thread will call. Therefore, all 
 * parameters needed by the matrix_thread must be stored in this struct in order to be passed in.  
 ****************************************************************************************/
struct matrix_index
{
	int i, j;
};


/***************************************************************************************************
 * 										Matrix_thread
 * This function is called by my create_thread function.Function takes in a void pointer, 
 * called param. Function casts the  pointer to a struct matrix_index pointer. It then extracts the 
 * information from the structure to use as parameters within the matrix_thread function. This function 
 * then calculates the matrix multiplication for a single element and stores it in element C[i][j]. 
 * Where i and j were the two numbers passed in by the structure. 
 *****************************************************************************************************/
void* matrix_thread(void* param)
{
	struct matrix_index values = *(struct matrix_index *) param;

	//i and j are attributes of the param called values that was passed in by pointer.
	int c_rows = values.i; //i
	int c_cols = values.j; //j
	int sum = 0;

	//Calculate the number to be saved in Matrix C
			for (int k= 0;k<matrix_A_cols;k++)
			{
				Dynamic_MatrixC[c_rows][c_cols]+= Dynamic_MatrixA[c_rows][k] * Dynamic_MatrixB[k][c_cols];
				
			}
	//WHAT SHOULD I BE RETURNING????????????????
}

/************************************************************************************************************
 *  											Make2DArray 
 * This function takes in two integer parameters which will server  as the numbers of rows and then colounms
 * respectively. This function  then creates a 2D array, also called a matrix of size i*j and then  returns 
 * a pointer to the matrix, wherever the function was called. 
 ***********************************************************************************************************/
int** make2DArray(int rows, int cols)
{
 int** dp;							//Make double pointer, dp that points to pointers that point to integers
 dp = new int*[rows];				//Dynamically make array of size "rows" that holds int pointers, pointed to by dp
	for(int i =0; i < rows; i++ )	//Fill the rows array with integer pointers (integer arrays) 
	{
		dp[i] = new int[cols];
	}   
	return dp;						//Return dp
}


/************************************************************************************************************
 *  						print_matrix 
 * This function prints a matrix. It requires three parameters. First, a double pointer to the matrix that
 * needs to be printed. Then it takes in two integers which hold the number of rows and colounms.
 ***********************************************************************************************************/
void print_matrix(int** printme, int matrixRows, int matrixCols)
{
for(int r = 0;r<matrixRows;r++){
		for(int c = 0;c<matrixCols;c++){
			cout<<setw(7)<<printme[r][c];
		}
		cout<<"\n";
	}
}


/******************************************************************************************
 *  						Main Function
 *****************************************************************************************/
int main()
{
//Try to place all global variables back into main

//Get user input
//get_cols_rows(&matrix_A_rows,&matrix_A_cols,&matrix_B_rows,&matrix_B_cols);
//TRY TO MAKE THIS A FUNCTOIN LATER :,(
cout<<(" \nWARNING: Matrix B Cols will automatically match Matrix A Rows!\n");
cout<<("Enter # of Row for Matrix A:");
cin>>matrix_A_rows;
cout<<("Enter # of Cols for Matrix A:");
cin>>matrix_A_cols;
cout<<("Number of Rows for Matrix B:");
matrix_B_rows=matrix_A_cols;
cout<<matrix_B_rows;
cout<<("\nEnter # of Cols for Matrix B:");  
cin>>matrix_B_cols;
cout<<"\n";


//Create Matrix A,B,C dynamically based on user input 
Dynamic_MatrixA = make2DArray(matrix_A_rows,matrix_A_cols);
Dynamic_MatrixB = make2DArray(matrix_B_rows,matrix_B_cols);
Dynamic_MatrixC = make2DArray(matrix_A_rows,matrix_B_cols);

//Fill Matrix A with numbers 
for(int r = 0;r<matrix_A_rows;r++)
{		
	cout<<"Enter "<< matrix_A_cols<<" numbers for row "<< r+1<<" of MatrixA (seperated by a space):";
	for(int c = 0;c<matrix_A_cols;c++)
	{
		cin>>Dynamic_MatrixA[r][c];
	}
}
//Print Matrix A
cout<<"Matrix A is:\n";
print_matrix(Dynamic_MatrixA,matrix_A_rows,matrix_A_cols);
cout<<"\n";


//Fill matrix B with numbers
for(int r = 0;r<matrix_B_rows;r++)
{
	cout<<"Enter "<< matrix_B_cols<<" numbers for row "<< r+1<<" of MatrixB (seperated by a space):";
	for(int c = 0;c<matrix_B_cols;c++)
	{
		cin>>Dynamic_MatrixB[r][c];
	}
}
//Print Matrix A
cout<<"Matrix B is:\n";
print_matrix(Dynamic_MatrixB,matrix_B_rows,matrix_B_cols);
cout<<"\n";



//Do all work here for making matrix C
	//Make two integers for your for loops 
	int i, j;

	for(i = 0; i < matrix_A_rows; i++)
	{
	 for(j = 0; j <matrix_B_cols; j++)
	 {	

		//Make a pointer that points to matrix indexes and call it two_integers
		struct matrix_index* two_integers;   
	
		//Dynamically create a matrix index structure anf cast it to a struct matrix_index pointer (I THINK???)
		//two_integers = (struct matrix_index* ) malloc(sizeof(struct matrix_index));
		two_integers = (struct matrix_index* ) new struct matrix_index;

		//Save i and j from the for loops into the structure called two pointers
		//you will use these are the parameters when you call matrix_thread in the prthread create functin.
		two_integers->i = i;
		two_integers->j = j;


		//Why do i even need these three things? Arent the impicitly created? 
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr); 

		//Here is where you call the matrix_thread function and pass the two integers in as params
		pthread_create(&tid, &attr, matrix_thread, two_integers);

		//WHY IS THIS THE SAME THREAD??
		//cout<<"MY THREAD ID IS"<<pthread_self()<<" ";

		//Make the process wait for the threads to finish and join them
		//LOOK THIS UP. This will need to be in a for loop I think. ?? to bring all the 9 threads together or whatvere 
		pthread_join(tid, NULL);
		}
	}

	//Print Completed Matrix C
	cout<<"Matrix C is:\n";
	print_matrix(Dynamic_MatrixC,matrix_A_rows,matrix_B_cols);
	cout<<("\n");

	return 0;
}
			













//This function takes in 4 integers that represent the dimenstions of the 2D array
// void get_cols_rows(int* matrix_A_rows,int* matrix_A_cols,int* matrix_B_rows,int* matrix_B_cols)
// {
// cout<<(" \nWARNING: Matrix B Cols will automatically match Matrix A Rows!\n");
// cout<<("Enter # of Row for Matrix A:");
// cin>>*matrix_A_rows;
// cout<<("Enter # of Cols for Matrix A:");
// cin>>*matrix_A_cols;
// cout<<("\nEnter # of Rows for Matrix B:");
// cin>>*matrix_B_rows;
// //B cols will be fiiled in automatically 
// int copy = *matrix_A_rows;
// *matrix_B_cols = copy;
// cout<<("Matrix B Cols is :");
// cout<<matrix_A_rows<<"\n";
// }