//
//  Program:    main.cpp
//  Author:     Lily Naoudom
//  Date:       06/17/2015
//  Purpose:    This is a menu-driven program that is designed to implement different search and sort
//              techniques. Given a list of books, book IDs, and book prices stored in parallel arrays,
//              the user is prompted to search for a book by using either the linear search or binary
//              search option. After retrieving the book of user's choice as well as how many copies
//              the user would like to purchase, the program calculates the total cost of the book(s).
//              The user can also choose to do a bubble sort or selection sort of 1000 random generated
//              numbers. The program will display the array of random numbers before and after the
//              sorting is complete. The user can choose to quit the program any time the menu is displayed.

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

using namespace std;

// Prototypes
void showMenu(int, int[], string[], double[], int);
int linearSearch(int[], int, int);
int binarySearch(int[], int, int);
void bubbleSort(int[], int);
void selectionSort();
void display(int[], string[], double[]);
void calcCost(double[], int, int, int);
void sortBooks(int[], int);
void getNum(int[], int);
void showArray(int[], int);
void selectionSort(int[], int);

int main()
{
    // Declare array size and book title/ book ID/ book price arrays
    const int arrSize = 10;
    
    string bookTitle[] = { "Starting out with C++", "Java Programming",
                            "Software Structures", "Analysis of Algorithms",
                            "Computer Graphics", "Artificial Intelligence: A Modern Approach",
                            "Probability and Statistics", "Cognitive Science",
                            "Modern Information Retrieval", "Speech and Language Processing"};

    int bookID[] = {1101, 1211, 1333, 1456, 1567, 1642, 1699, 1755, 1800, 1999};
    double bookPrice[] = {112.32, 73.25, 54.00, 67.32, 135.00, 173.22, 120.00, 42.25, 32.11, 123.75};
    
    int userChoice;
    
    // Function call to generate random numbers for bubble/selection sort
    srand(time(NULL));
    
    // Function call to show menu
    showMenu(userChoice, bookID, bookTitle, bookPrice, arrSize);

    return 0;
}


// showMenu function
void showMenu(int userChoice, int bookID[], string bookTitle[], double bookPrice[], int arrSize)
{

    // Declare variables and arrays
    int copies;
    int position, target;
    const int numSize = 1000;
    int num[numSize] = {0};
    
    // Do-while loop to display menu as long as user does not choose to quit the program
    do {
        
        cout<<"\n*** SEARCHING & SORTING MENU ***"<<endl;
        cout<<"1.   Linear Search"<<endl;
        cout<<"2.   Binary Search"<<endl;
        cout<<"3.   Bubble Sort"<<endl;
        cout<<"4.   Selection Sort"<<endl;
        cout<<"5.   Quit"<<endl;
        cout<<"Please enter a menu choice. "<<endl;
        cin>>userChoice;
        
        // Switch function to execute user choice from menu
        switch (userChoice)
        {
            // LINEAR SEARCH
            case 1:
                cout<<"*** LINEAR SEARCH ***"<<endl;
                
                display(bookID, bookTitle, bookPrice);  // Function call to display array contents
                
                cout<<endl;
            
                cout<<"Enter the book ID you wish to purchase:";    // Prompt user choice of book
                cin>>target;
                cout<<"Enter the number of books you wish to purchase:";    // Prompt number of copies
                cin>>copies;
                
                position = linearSearch(bookID, arrSize, target);   // Function call to perform linear search
                
                if (position == -1)                                 // User input validation
                    cout<<"Book ID "<< target << " not found.";
                else
                {
                    cout<<"Book ID: "<< target << endl;
                    cout<<"Book Title: "<< bookTitle[position] <<endl;
                    cout<<"Number of books bought: " << copies << endl;
                    calcCost(bookPrice, arrSize, position, copies);     // Calculate total cost of books
                }
                
                cout<<endl;
                break;
                
            // BINARY SEARCH
            case 2:
                cout<<"*** BINARY SEARCH ***"<<endl;
                
                display(bookID, bookTitle, bookPrice);      // Function call to display array contents
                
                cout<<endl;
                
                cout<<"Enter the book ID you wish to purchase:";    // Prompt user choice of book
                cin>>target;
                cout<<"Enter the number of books you wish to purchase:";    // Prompt number of copies
                cin>>copies;
                
                sortBooks(bookID, arrSize);         // Function call to sort books before doing binary search
                
                position = binarySearch(bookID, arrSize, target);   // Function call to perform binary search
     
                if (position == -1)                 // User input validation
                    cout<<"Book ID "<< target << " not found.";
                else
                {
                    cout<<"Book ID: "<< target << endl;
                    cout<<"Book Title: "<< bookTitle[position] <<endl;
                    cout<<"Number of books bought: " << copies << endl;
                    calcCost(bookPrice, arrSize, position, copies); // Calculate total cost of books
                }
                cout<<endl;
                break;
                
            // BUBBLE SORT NUMBERS
            case 3:
                cout<<"*** BUBBLE SORT ***"<<endl;
                
                getNum(num, numSize);           // Function call to get numbers
                bubbleSort(num, numSize);       // Function call to bubble sort numbers
                break;
                
            // SELECTION SORT NUMBERS
            case 4:
                cout<<"*** SELECTION SORT ***"<<endl;
                
                getNum(num, numSize);           // Function call to get numbers
                selectionSort(num, numSize);    // Function call to selection sort numbers
                break;
                
            // QUIT PROGRAM
            case 5:
                cout<<"Goodbye!"<<endl;         // User decides to quit the program.
                break;
                
            // USER CHOICE VALIDATION
            default:
                cout<<"Invalid menu choice."<<endl;
   
        }
        
    } while(userChoice !=5);
    
}

// Function to display array contents
void display(int bookID[], string bookTitle[], double bookPrice[])
{
    cout<<"Book ID"<<"        "<<"Title"<<"                                        "<<fixed<<setprecision(2)<<"Cost"<<endl;
    for (int i = 0; i<10; i++)
    {   std::string str(bookTitle[i]);
        
        int titleSize = str.length();
        
        cout<<" "<<bookID[i]<<setw(5)<<" "<<bookTitle[i]<<" "<<setw(50-titleSize)<<"$"<<bookPrice[i]<<endl;
    }
}

// Function to calculate total cost of books
void calcCost(double bookPrice[], int arrSize, int position, int copies)
{
    double totalCost = 0;
    
    for (int i = 0; i < arrSize; i++)
        totalCost = bookPrice[position] * copies;

    cout<<"Total Cost: $ "<<fixed<<setprecision(2)<<totalCost;
         
}

// Function to perform linear search of books
int linearSearch(int bookID[], int arrSize, int target)
{
    int index = 0;
    int position = -1;
    bool found = false;

    while (index < arrSize && !found)
    {
        if (bookID[index] == target)
        {
            found = true;
            position = index;
        }
        index++;
    }
    
    return position;

}

// Function to bubble sort books before sending to binary search
void sortBooks(int bookID[], int arrSize)
{
    bool swap;
    int temp;
    
    do{
        swap = false;
        for (int i = 0; i < (arrSize-1); i++)
        {
            if (bookID[i] > bookID[i+1])
            {
                temp = bookID[i];
                bookID[i] = bookID[i+1];
                bookID[i+1] = temp;
                swap = true;
            }
        }
    } while (swap);
}

// Function to perform binary search of books
int binarySearch(int bookID[], int arrSize, int target)
{
    int first = 0;
    int last = arrSize - 1;
    int middle;
    int position = -1;
    bool found = false;
    
    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if (bookID[middle] == target)
        {
            found = true;
            position = middle;
        }
        else if (bookID[middle] > target)
            last = middle - 1;
        else
            first = middle + 1;
    }
    
    return position;

}

// Function to get random numbers
void getNum(int num[], int numSize)
{
    for (int i = 0; i < numSize; i++)
        num[i] = rand()%500+1;          // Set range of random numbers 1-500
}

// Function to show array contents
void showArray(int num[], int numSize)
{
    for (int i = 0; i < numSize; i++)
        cout<<" "<<num[i];
    
}

// Function to perform bubble sort of random numbers
void bubbleSort(int num[], int numSize)
{
    cout<<"Unsorted Array: "<<endl;
    showArray(num, numSize);        // Display unsorted array
    cout<<endl;
    cout<<endl;
    
    bool swap;
    int temp;
    
    do{
        swap = false;
        for (int i = 0; i < (numSize-1); i++)
        {
            if (num[i] > num[i+1])
            {
                temp = num[i];
                num[i] = num[i+1];
                num[i+1] = temp;
                swap = true;
            }
        }
    } while (swap);
    
    cout<<"Sorted Array: "<<endl;
    showArray(num, numSize);        // Display sorted array
    cout<<endl;
    
}

// Function to perform selection sort of random numbers
void selectionSort(int num[], int numSize)
{
    cout<<"Unsorted Array: "<<endl;
    showArray(num, numSize);        // Display unsorted array
    cout<<endl;
    cout<<endl;
    
    int startScan, minIndex, minValue;
    
    for (startScan = 0; startScan < (numSize-1); startScan++)
    {
        minIndex = startScan;
        minValue = num[startScan];
        for (int index = startScan + 1; index < numSize; index++)
        {
            if (num[index] < minValue)
            {
                minValue = num[index];
                minIndex = index;
            }
        }
        num[minIndex] = num[startScan];
        num[startScan] = minValue;
    }

    cout<<"Sorted Array: "<<endl;
    showArray(num, numSize);        // Display sorted array
    cout<<endl;
    
}