//Description:
//Reading tweets line by line and updating the median of number of unique words per tweet
//For each line, we first sort the words (using merge sort) in alphabetical order. This helps similar words to be placed next to each other. then going
//through the sorted array of words in the line, we can find the number of unique words in that line. To keep track of the median of thses numbers at all
//times we define a linked list class, in which its elemensta are sorted from small to large and each element reflects the number of unique words in
//one line. Starting from an empty list, at each time we place the new element at its correct location and update the median and write it in the output file.

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

//Definition of classes
class unique_index
{
	//Description:
	//This class reflects the number of unique words in a line

public:
	//Features:
	unique_index *next;
	unique_index *previous;
	int index;

	//Functions:
	unique_index();//Constructor
};
class unique_indices_linked_list
{
	//Description:
	//Linked list of unique_index's

public:
	//Features:
	unique_index *first;
	unique_index *last;
	int number_of_indices;

	//Functions:
	unique_indices_linked_list();//Constructor
	~unique_indices_linked_list();//Dstructor
};

//Definition of functions of classes
unique_index::unique_index()
{
	//Description:
	//Constructor function of unique_index class
	
	next=NULL;
	previous=NULL;
}
unique_indices_linked_list::unique_indices_linked_list()
{
	//Description:
	//Constructor function of class_indices_linked_list class

	first=NULL;
	last=NULL;
	number_of_indices=0;
}
unique_indices_linked_list::~unique_indices_linked_list()
{
	//Description:
	//Destructor function of class_indices_linked_list class

	//Variables:
	unique_index *ptr_to_current_unique_index;
	unique_index *ptr_to_next_unique_index;
	
	//Memory deallocation

	//First we set the current to the first element of the linked list
	ptr_to_current_unique_index=this->first;

	while(ptr_to_current_unique_index!=NULL) 
	{
		ptr_to_next_unique_index=ptr_to_current_unique_index->next;
		delete ptr_to_current_unique_index;
		ptr_to_current_unique_index=ptr_to_next_unique_index;
	} 
}

int main()
{
	//Description:
	//The main function that is called by the machine

	//Median is indicated by an element in the linked list. If the number of elements are odd, that one element is the median. Otherwise that element and its next
	//one together reflect the median

	//Parameters
	const int maximum_number_of_elements_in_line=200;

	//Vaiables:
	int i;//Counter
	ifstream input_tweets_stream;//Stream to read the tweets from the input file
	ofstream output_tweets_stream;//Stream to read the tweets from the input file
	string line_string;
	int fragment_counter;//To count the words in each line
	string array_of_fragment_strings_in_line[maximum_number_of_elements_in_line];
	istringstream line_string_stream;
	int line_counter;
	string *sorted_fragments;
	int number_of_unique_words_in_tweet;
	unique_index *ptr_to_unique_index;
	unique_indices_linked_list *ptr_to_indices_linked_list;
	unique_index *ptr_to_median_index;
	unique_index *ptr_to_temp_index;
	int number_of_moves;
	
	//Opening the file that contains the tweets
	input_tweets_stream.open("..\\tweet_input\\tweets.txt");

	//Opening the output file
	output_tweets_stream.open("..\\tweet_output\\ft2.txt");

	//Initiating a class_indices_linked_list
	ptr_to_indices_linked_list=new unique_indices_linked_list;

	//Setting line_counter=0 initially
	line_counter=0;
	
	
	//Reading lines one by one
	while(getline(input_tweets_stream,line_string))//We keep reading line as long as there are some to read and we put them in line_string each time
	{
		
		//We need to extract words from each tweet

		//Updating line_counter
		line_counter++;
		
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

		//sorting the elements of a line
		merge_sort_words(array_of_fragment_strings_in_line,fragment_counter,sorted_fragments);

		//Setting number_of_unique_words_in_tweet to 1 initially
		number_of_unique_words_in_tweet=1;		
		//Going through the sorted words of a line
		for(i=1;i<fragment_counter;i++)
		{
			if(strcmp(sorted_fragments[i].c_str(),sorted_fragments[i-1].c_str())!=0)
			{
				number_of_unique_words_in_tweet++;
			}
		}

		//Deleting output_tweets_stream
		delete [] sorted_fragments;

		//Initiating a unique_index
		ptr_to_unique_index=new unique_index;
		ptr_to_unique_index->index=number_of_unique_words_in_tweet;

		//If this is the first line, it is the median
		if(line_counter==1)
		{
			//Setting the median
			ptr_to_median_index=ptr_to_unique_index;
			//Adding the unique_index to the linked list
			ptr_to_indices_linked_list->first=ptr_to_indices_linked_list->last=ptr_to_unique_index;
			//Updating the number of elements in the linked list
			ptr_to_indices_linked_list->number_of_indices++;
		}
		else
		{
			//Finding the location of the new unique_index object in the linked list
			if(ptr_to_unique_index->index<=ptr_to_median_index->index)//Left half
			{
				//Starting from the left end of the list and moving to the right until we find the location of the new index
				ptr_to_temp_index=ptr_to_indices_linked_list->first;
				//Setting number_of_moves to zero initially
				number_of_moves=0;
				while(ptr_to_unique_index->index>ptr_to_temp_index->index)
				{
					//We move forward in the list one by one
					ptr_to_temp_index=ptr_to_temp_index->next;
					//Updating number_of_moves
					number_of_moves++;
				}
				//Now that we have found the location of the new unique_index, we update the list and the median
				//Adding the unique_index to the linked list
				if(number_of_moves==0)//This means that we need to put the new unique_index at the begining of the list
				{
					ptr_to_unique_index->next=ptr_to_indices_linked_list->first;
					ptr_to_indices_linked_list->first->previous=ptr_to_unique_index;
					ptr_to_indices_linked_list->first=ptr_to_unique_index;
					//Updating the number of elements in the linked list
					ptr_to_indices_linked_list->number_of_indices++;
				}
				else
				{
					ptr_to_temp_index->previous->next=ptr_to_unique_index;
					ptr_to_unique_index->previous=ptr_to_temp_index->previous;
					ptr_to_unique_index->next=ptr_to_temp_index;
					ptr_to_temp_index->previous=ptr_to_unique_index;
					//Updating the number of elements in the linked list
					ptr_to_indices_linked_list->number_of_indices++;
				}
				//Updating median
				//Only if we have even number of elements the element indicating median is going to change
				if(line_counter%2==0)
				{
					ptr_to_median_index=ptr_to_median_index->previous;				
				}
			}
			else//Right half
			{
				//Starting from the right end of the list and moving to the left until we find the location of the new index
				ptr_to_temp_index=ptr_to_indices_linked_list->last;
				//Setting number_of_moves to zero initially
				number_of_moves=0;
				while(ptr_to_unique_index->index<=ptr_to_temp_index->index)
				{
					//We move forward in the list one by one
					ptr_to_temp_index=ptr_to_temp_index->previous;
					//Updating number_of_moves
					number_of_moves++;
				}
				//Now that we have found the location of the new unique_index, we update the list and the median
				//Adding the unique_index to the linked list
				if(number_of_moves==0)//This means that we need to put the new unique_index at the begining of the list
				{
					ptr_to_unique_index->previous=ptr_to_indices_linked_list->last;
					ptr_to_indices_linked_list->last->next=ptr_to_unique_index;
					ptr_to_indices_linked_list->last=ptr_to_unique_index;
					//Updating the number of elements in the linked list
					ptr_to_indices_linked_list->number_of_indices++;
				}
				else
				{
					ptr_to_temp_index->next->previous=ptr_to_unique_index;
					ptr_to_unique_index->next=ptr_to_temp_index->next;
					ptr_to_unique_index->previous=ptr_to_temp_index;
					ptr_to_temp_index->next=ptr_to_unique_index;
					//Updating the number of elements in the linked list
					ptr_to_indices_linked_list->number_of_indices++;
				}
				//Updating median
				//Only if we have odd number of elements the element indicating median is going to change
				if(line_counter%2==1)
				{
					ptr_to_median_index=ptr_to_median_index->next;				
				}
			}
		}

		//Printing the median
		if(line_counter%2==0)
		{
			output_tweets_stream<<(double)(ptr_to_median_index->index+ptr_to_median_index->next->index)/2<<endl;
		}
		else
		{
			output_tweets_stream<<ptr_to_median_index->index<<endl;
		}
	}

	//Deleting ptr_to_indices_linked_list
	delete ptr_to_indices_linked_list;

	return 0;
}
