//Description:
//Listing the words tweeted as well as the number of times each one has appeared. The words are read line by line and put into an array. Then the array is sorted
//using merge sort, where for sorting an array it is recursively divided into two halves, each half gets sorted and then the two halves get merged. The recursion
//continues until we reach the base cases in which we have only one or two elements in the array to sort, solving of which is trivial. NOTE THAT THE USER MUST
//INDICATE THE MAXIMUM NUMBER OF WORDS AS A PARAMETER.

//Including header files from C++ standard library
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Declaration of functions
void merge_sort_words(string *unsorted_array_of_words,int number_of_words,string *&sorted_array_of_words);

//Definition of functions
void merge_sort_words(string *unsorted_array_of_words,int number_of_words,string *&sorted_array_of_words)
{
	//Description:
	//This function sorts an array of words using dynamic programming. The problem of sorting an array is solved by dividing the array into two arrays, sorting
	//each one of them and them combining them together in a specific way. The base case happens when the length of the array is either 1 or 2, solving of which
	//is trivial.

	//Variables:
	string temp_word;//Used for swapping
	int i;//Counter
	int first_array_count;
	int second_array_count;
	string *begining_of_first_half;
	string *begining_of_second_half;
	string *sorted_first_half;
	string *sorted_second_half;
	int condition;

	//Memory allocation to sorted_array_of_words
	sorted_array_of_words=new string[number_of_words];

	if(number_of_words==1)//If we have one word in the array, the array is already sorted
	{
		//The array is sorted
		sorted_array_of_words[0]=unsorted_array_of_words[0];
	}
	else if(number_of_words==2)//If we had two words in the array
	{
		if(strcmp(unsorted_array_of_words[0].c_str(),unsorted_array_of_words[1].c_str())>0)//If not sorted
		{
			//Swapping the two words
			sorted_array_of_words[0]=unsorted_array_of_words[1];
			sorted_array_of_words[1]=unsorted_array_of_words[0];
		}
		else
		{
			//Same order
			sorted_array_of_words[0]=unsorted_array_of_words[0];
			sorted_array_of_words[1]=unsorted_array_of_words[1];
		}
	}
	else//Otherwise, we need to divide the array into two arrays and recursively call the function again
	{
		//Sorting the first half
		begining_of_first_half=unsorted_array_of_words;
		begining_of_second_half=&(unsorted_array_of_words[number_of_words/2]);
		
		
		//Initializing sorted_first_half and sorted_second_half
		//sorted_first_half=NULL;
		//sorted_second_half=NULL;
		
		//Sorting the first half		
		merge_sort_words(begining_of_first_half,number_of_words/2,sorted_first_half);
		//Sorting the second half
		merge_sort_words(begining_of_second_half,number_of_words-number_of_words/2,sorted_second_half);

		
		//Setting first_array_count and second_array_count to zero initially
		first_array_count=0;
		second_array_count=0;		
		
		//Merging the two arrays
		for(i=0;i<number_of_words;i++)
		{
			//Comparing elements from the two arrays
			if(first_array_count==number_of_words/2)
			{
				condition=2;
			}
			else if(second_array_count==number_of_words-number_of_words/2)
			{
				condition=1;
			}
			else if(strcmp(sorted_first_half[first_array_count].c_str(),sorted_second_half[second_array_count].c_str())<0)
			{
				condition=1;
			}
			else
			{
				condition=2;
			}
			if(condition==1)
			{
				sorted_array_of_words[i]=sorted_first_half[first_array_count];
				first_array_count++;				
			}
			else
			{
				sorted_array_of_words[i]=sorted_second_half[second_array_count];
				second_array_count++;				
			}
		}

		//Deleting sorted_first_half and sorted_second_half
		delete [] sorted_first_half;
		delete [] sorted_second_half;		
		
	}

}

int main()
{
	//Description:
	//The main function that is called by the machine

	//Parameters
	const int maximum_number_of_words=50000;//Indicate here, the maximum number of words
	const int maximum_number_of_elements_in_line=200;

	//Vaiables:
	int i;//Counter
	ifstream input_tweets_stream;//Stream to read the tweets from the input file
	ofstream output_tweets_stream;//Stream to read the tweets from the input file
	string line_string;
	int fragment_counter;//To count the words in each line
	string *unsoretd_array_of_words;
	string *soretd_array_of_words;
	string array_of_fragment_strings_in_line[maximum_number_of_elements_in_line];
	istringstream line_string_stream;
	int word_counter;
	int number_of_times_appeared;

	//Initiating unsoretd_array_of_words
	unsoretd_array_of_words=new string[maximum_number_of_words];
	
	//Opening the file that contains the tweets
	input_tweets_stream.open("..\\tweet_input\\tweets.txt");

	//Opening the output file
	output_tweets_stream.open("..\\tweet_output\\ft1.txt");

	//Initial setting of wordcounter
	word_counter=0;

	//Reading lines one by one
	while(getline(input_tweets_stream,line_string))//We keep reading line as long as there are some to read and we put them in line_string each time
	{
		//We need to extract words from each tweet
		
		//For each line, fragment_counter is initially set to zero
		fragment_counter=0;
		
		//Clearing line_string_stream
		line_string_stream.clear();

		//Linking line_string_stream to the line that is read from the file
		line_string_stream.str(line_string);
				
		//Extracting words from the line
		while(line_string_stream)
		{
			string fragment_string;
			if (!getline(line_string_stream,array_of_fragment_strings_in_line[fragment_counter],' ')) break;//The words are separated by white space
			//Updating fragment_counter
			fragment_counter++;
		}

		//Copying words to the array that contains all the words
		for(i=0;i<fragment_counter;i++)
		{			
			unsoretd_array_of_words[word_counter]=array_of_fragment_strings_in_line[i];
			word_counter++;
		}
	}

	//Sorting words
	merge_sort_words(unsoretd_array_of_words,word_counter,soretd_array_of_words);

	//Setting number_of_times_appeared initially to zero
	number_of_times_appeared=1;
	for(i=1;i<word_counter;i++)
	{
		if(strcmp(soretd_array_of_words[i-1].c_str(),soretd_array_of_words[i].c_str())!=0)
		{
			//Showing the word and the number of times it appeared
			output_tweets_stream<<soretd_array_of_words[i-1]<<"\t"<<number_of_times_appeared<<endl;
			//Setting number_of_times_appeared to 1 again
			number_of_times_appeared=1;
		}
		else
		{
			//Updating number_of_times_appeared
			number_of_times_appeared++;
		}
	}
	//For the last one
	output_tweets_stream<<soretd_array_of_words[word_counter-1]<<"\t"<<number_of_times_appeared<<endl;

	//Deleting unsoretd_array_of_words
	delete [] unsoretd_array_of_words;
	//Deleting soretd_array_of_words
	delete [] soretd_array_of_words;

	return 0;
}
