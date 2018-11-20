#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include<stdio.h>
#include<string.h>
using namespace std;
bool final(string values_ham[5000],float probabilities_ham[5000],string mysecond_Array_test_ham[348][300],string values_spam[10000],float probabilities_spam[10000],string mysecond_Array_test_spam[130][300]);
bool ifpresent(string key, string values[]);
int ret_freq (string key, string map[300][300]);
bool maketable_ham (string values_ham[5000],float probabilities_ham[5000],string table[300][300]);
bool maketable_spam (string values_spam[10000],float probabilities_spam[10000],string mysecond_Array[123][300]);
bool buildhamtable();
bool buildspamtable();
int main()
{

// extract the name of the  files in a string array

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
float probabilities_ham[5000];
maketable_ham(values_ham, probabilities_ham,mysecond_Array);
string values_spam[10000];
float probabilities_spam[10000];
maketable_spam(values_spam, probabilities_spam,mysecond_Array_spam);

//for (int i =1; i<100; i++)
//cout << probabilities_ham[i] << "values " << endl;

final(values_spam,probabilities_ham,mysecond_Array_test_ham,values_spam,probabilities_spam,mysecond_Array_test_spam);
// making logistic matrix

}
/*
bool makelogisticmatrix(string values_ham[5000],mysecond_Array,mysecond_Array_spam)
{
string dictionary[463][5001];

	for (int i = 0 ; i < 340 ; i++)
	{
		for (int j = 0 ; j < 300 ; j++)
		{
			for (int k = 0 ; k < 5000 ; k++)
			{
			if (mysecond_Array[i][j])
			}
		}
	}

}
*/



bool final(string values_ham[5000],float probabilities_ham[5000],string mysecond_Array_test_ham[348][300],string values_spam[10000],float probabilities_spam[10000],string mysecond_Array_test_spam[130][300])
{
double  logarithms[348];
for (int k = 0 ; k < 348 ; k++)
{
	double joint_prob[300];
	for(int i = 0 ; i < 300 ; i++)
	{
		double temp_prob_ham = 0 ;
		double temp_prob_spam = 0 ;
		int flag =0;
		for (int j = 0 ; j < 5000 ; j++)
		{
			if ((mysecond_Array_test_ham[k][i].compare(values_ham[j]) == 0) && ((mysecond_Array_test_ham[k][i].length()) > 2)  )
			{
			temp_prob_ham = probabilities_ham[j];
			flag = 1;
			}
		}
                for (int j = 0 ; j < 5000 ; j++)
                {
                        if ((mysecond_Array_test_ham[k][i].compare(values_spam[j]) == 0)  && ((mysecond_Array_test_ham[k][i].length()) > 2) )
			{
			temp_prob_spam = probabilities_spam[j];
//                      cout << mysecond_Array_test_ham[k][i] << "compared with" << values_ham[j] << endl;
//                      cout << probabilities_spam[j] << " probs  loop 1 " <<temp_prob_spam  <<endl;
			flag = 1;
                	}
		}	
			if (flag == 1)
			{
//			cout << temp_prob_spam <<" prob of spam" <<endl;
//			cout << temp_prob_ham <<" prob of ham " <<endl;
//			cout <<log( temp_prob_spam / temp_prob_ham ) <<"logarithms"<<endl;
	  		joint_prob[i] = log2( temp_prob_spam / temp_prob_ham );
//			cout << joint_prob[i] <<" joint probs " <<endl;
			}
		}
		double  actual_prob = -0.428;
	//	double temp = (130/348);
	//	cout << log2(temp) <<" yeh kya hai " <<endl;
	//	cout << actual_prob << " yes yeh hi hia " << endl;
		for (int y = 0 ; y < 300; y++)
		{
	//	cout << actual_prob <<"constant" << endl;
	//	cout << joint_prob[y] <<" check again " <<endl;
		if (joint_prob[y] < 500 && joint_prob[y] > -500)
		{
		actual_prob = actual_prob + joint_prob[y];
//		cout << actual_prob <<" checking "<< endl;
		}
		}
logarithms[k]= actual_prob;
cout << logarithms[k] << " prob of ham " << endl;
}
}

bool maketable_ham (string values_ham[5000],float probabilities_ham[5000],string mysecond_Array[340][300])
{
float freq[5000];
int counter=0;
	for (int i = 0 ; i < 340 ; i++)
	{
		for (int j = 0 ; j < 300 ; j++)
		{
			if ( (ifpresent(mysecond_Array[i][j],values_ham) == 1) && ((mysecond_Array[i][j].length()) > 2) )
			{
			counter++;
			values_ham[counter] = mysecond_Array[i][j];
                        freq[counter] =  ret_freq(mysecond_Array[i][j],mysecond_Array);
			probabilities_ham[counter] = ((freq[counter]) / 300);
			}
		}
	}
}

bool maketable_spam (string values_spam[10000],float probabilities_spam[10000],string mysecond_Array[123][300])
{
float freq[10000];
int counter=0;
        for (int i = 0 ; i < 123 ; i++)
        {
                for (int j = 0 ; j < 300 ; j++)
                {
                        if ( (ifpresent(mysecond_Array[i][j],values_spam) == 1) && ((mysecond_Array[i][j].length()) > 2) )
                        {
                        counter++;
                        values_spam[counter] = mysecond_Array[i][j];
                        freq[counter] =  ret_freq(mysecond_Array[i][j],mysecond_Array);
                        probabilities_spam[counter] = ((freq[counter]) / 123);
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
