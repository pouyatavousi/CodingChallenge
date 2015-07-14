Description of meadin_unique.cpp:
Reading tweets line by line and updating the median of number of unique words per tweet
For each line, we first sort the words (using merge sort) in alphabetical order. This helps similar words to be placed next to each other. then going
through the sorted array of words in the line, we can find the number of unique words in that line. To keep track of the median of thses numbers at all
times we define a linked list class, in which its elemensta are sorted from small to large and each element reflects the number of unique words in
one line. Starting from an empty list, at each time we place the new element at its correct location and update the median and write it in the output file.

Description of words_tweeted.cpp:
Listing the words tweeted as well as the number of times each one has appeared. The words are read line by line and put into an array. Then the array is sorted
using merge sort, where for sorting an array it is recursively divided into two halves, each half gets sorted and then the two halves get merged. The recursion
continues until we reach the base cases in which we have only one or two elements in the array to sort, solving of which is trivial. NOTE THAT THE USER MUST
INDICATE THE MAXIMUM NUMBER OF WORDS AS A PARAMETER.

Use gcc COMPILER
