#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include<stdio.h>
#include<string.h>
using namespace std;

bool ifpresent(string key, string values[]);
int ret_freq (string key, string map[300][300]);
bool maketable_ham (string values_ham[5000],string table[300][300]);
bool calculate_weights(double weights[2001], int matrix[2001]);
bool construct_matrix (string values_ham[5000],string ham_array[300][300],string spam_array[123][300],int matrix[463][2001]);
int checking_func(double weights[2001], int matrix[2001]);

int main()
{

// extract the name of the  files in a string array
//cout << "Hello" << endl;
string myArray[340];
int size = 340 ;
    ifstream file("name_file.csv");
    if(file.is_open())
    {

        for(int i = 0; i < size; ++i)
        {
            file >> myArray[i];
        }
    }

//////////////////////////////////////////////////

string myArray_spam[123];
int size_spam = 123 ;
    ifstream file2("name_file2.csv");
    if(file2.is_open())
    {

        for(int i = 0; i < size_spam; ++i)
        {
            file2 >> myArray_spam[i];
        }
    }
//////////////////////////////////////////////////
string myArray_test_ham[348];
int size_test_ham = 348 ;
    ifstream file_test_ham("test_ham.csv");
    if(file_test_ham.is_open())
    {

        for(int i = 0; i < size_test_ham; ++i)
        {
            file_test_ham >> myArray_test_ham[i];
        }
    }
//////////////////////////////////////////////////
string myArray_test_spam[130];
int size_test_spam = 130 ;
    ifstream file_test_spam("test_spam.csv");
    if(file_test_spam.is_open())
    {

        for(int i = 0; i < size_test_spam; ++i)
        {
            file >> myArray_test_spam[i];
        }
    }

/////////////////////////////////////////////////
string mysecond_Array[340][300];
int size2 = 300 ;

for (int j=0; j< 340; j++)
{
    ifstream file_two(myArray[j].c_str());
    if(file_two.is_open())
    {

        for(int i = 0; i < size2; ++i)
        {
            file_two >> mysecond_Array[j][i];
        }
    }
file_two.close();
}

///////////////////////////////////////////////

string mysecond_Array_spam[123][300];
int size2_spam = 123;
for (int j=0; j < 123; j++)
{
    ifstream file2_two(myArray_spam[j].c_str());
    if(file2_two.is_open())
    {

        for(int i = 0; i < 300; ++i)
        {
            file2_two >> mysecond_Array_spam[j][i];
        }
    }
file2_two.close();
}
///////////////////////////////////////////////
string mysecond_Array_test_spam[130][300];
//int size2_spam = 130;
for (int j=0; j < 130; j++)
{
    ifstream file2_two_test_spam(myArray_test_spam[j].c_str());
    if(file2_two_test_spam.is_open())
    {

        for(int i = 0; i < 300; ++i)
        {
            file2_two_test_spam >> mysecond_Array_test_spam[j][i];
        }
    }
file2_two_test_spam.close();
}
//////////////////////////////////////////////
string mysecond_Array_test_ham[348][300];
//int size2_spam = 130;
for (int j=0; j < 348; j++)
{
    ifstream file2_two_test_ham(myArray_test_ham[j].c_str());
    if(file2_two_test_ham.is_open())
    {

        for(int i = 0; i < 300; ++i)
        {
            file2_two_test_ham >> mysecond_Array_test_ham[j][i];
        }
    }
file2_two_test_ham.close();
}
///////////////////////////////////////////////

// mysecond_Array has every string in all the spam files
// now we will count the frequency of occurence of each word

///////////////////////////////////////////////
string values_ham[5000];
maketable_ham(values_ham,mysecond_Array);

// making the matrix

int matrix[463][2001];
construct_matrix(values_ham,mysecond_Array,mysecond_Array_spam,matrix);
//for (int i = 0 ; i < 2001 ; i++)
//cout << matrix[1][i] << " ";


double weights[2001] = {0};

for (int i = 0 ; i < 463 ; i++)
{
calculate_weights(weights,matrix[i]);
}

//for (int i = 0 ; i < 2001 ; i++)
//cout << weights[i] <<" " ;

// check now 
for (int i = 0 ; i < 460 ; i++ )
cout << checking_func(weights, matrix[i]) << " checking value " << endl;



}

int checking_func(double weights[2001], int matrix[2001])
{
double value = weights[0];
	for (int i = 0 ; i < 2000 ; i++)
	{
	value = weights[i+1]*matrix[i] + value;
	}
 return value;
}

bool construct_matrix (string values[5000],string ham_array[340][300],string spam_array[123][300],int matrix[463][2001])
{

//cout << "Hello"<< endl;
	for (int k = 0 ; k < 463 ; k++)
	{
		for (int i = 0 ; i < 2000 ; i++)
		{
			int counter = 0;
			for (int j = 0 ; j < 300 ; j++)
				{
				 if ((k < 340))
				 {
					if(values[i].compare(ham_array[k][j]) == 0)
					{
					counter ++ ;
					}
				 matrix[k][i] = counter;
				 matrix[k][2000] = 0;

				 }
				 if ((k >= 340))
				 {
				    if ((values[i].compare(spam_array[k-340][j]) == 0))
					{
					counter++ ;
					}
				 matrix[k][i] = counter;
				 matrix[k][2000] = 1;
				 }
				}
		}
	}

}

bool calculate_weights(double weights[2001], int matrix[2001])
{
double  alpha = 0.3;
double prediction = 0;
double new_weights[2001];
	for (int i = 1 ; i < 2001; i++)
	{
	prediction = (weights[i]*matrix[i]) + prediction;
	}

	prediction = 1/(1+exp((-1*weights[0]) + prediction));


	for (int i =0 ; i < 2001 ; i++)
	{
	new_weights[i]= weights[i] + (alpha * (matrix[2000] - prediction)) + ((1 - prediction) *matrix[i]);
	}

	for (int i =0 ; i < 2001 ; i++)
	{
	weights[i] = new_weights[i];
	}



}

bool maketable_ham (string values_ham[5000],string mysecond_Array[340][300])
{
int counter=0;
	for (int i = 0 ; i < 340 ; i++)
	{
		for (int j = 0 ; j < 300 ; j++)
		{
			if ( (ifpresent(mysecond_Array[i][j],values_ham) == 1) && ((mysecond_Array[i][j].length()) > 2) )
			{
			counter++;
			values_ham[counter] = mysecond_Array[i][j];
			}
		}
	}
}
int ret_freq (string key, string map[340][300])
{
int count=0;
	for (int i = 0; i < 300 ; i++)
	{
		for(int j = 0; j < 300 ; j++)
		{
			if (key.compare(map[i][j]) ==0)
			{
			count++;
			}
		}
	}
return count;
}
bool ifpresent(string key, string values[])
{
int count = 0;
	for (int i = 0 ; i < 5000 ; i++)
	{
                        if (key.compare(values[i]) == 0 )
                        {
                        count++;
                        }

	}

	if (count == 0)
	{
		return 1;
	}
}
