//Pablo Solano III
//project_1.cpp

//necessary libraries
#include <iostream>         //for Input / Output operations 
#include <vector>           //to handle vectors 
#include <ctime>            //to seed the random number generator  
#include <cmath>            //for math functions  
#include <cstdlib>          //for rand() functions 
#include <algorithm>        //for algorithms likes swap, reverse 
#include <numeric>          //for calculating accumulations 
#include <fstream>          //for file reading and writing 
#include <chrono>           //for timing utilities

//generates random vectors of the size passed through in between the lowest and highest values
std::vector<int> randomVector(int size, int low, int high)
{
    std::vector<int> v(size, 0);

    for(int i = 0; i < size; i++)
    {
        v[i] = rand() % (high - low + 1) + low;
    }

    return v;
}

//if revers is true, vector is sorted in descending and then the converse
std::vector<int> sortedVector(int size, bool reverse)
{
    std::vector<int> v(size);

    for(int i = 0; i < size; i++)
    {
        v[i] = i;
    }
    if(reverse)
    {
        std::reverse(v.begin(), v.end());
    }

    return v;
}

//bubble sort sorting algorithm
void bubbleSort(std::vector<int>& v)
{
    bool sorted = false;

    while(!sorted)
    {
        sorted = true;
        for(int i = 1; i < v.size(); i++) 
        {
            if(v[i - 1] > v[i])
            {
                std::swap(v[i -1], v[i]);
                sorted = false;
            }
        }
    }
}
//works by sending largest vals to the top 

//insertion sorting algorithm
void insertionSort(std::vector<int>& v)
{
    int i = 1;
    
    while(i < v.size())
    {
        int j = i;

        while(j > 0 && v[j] < v[j - 1])
        {
            std::swap(v[j - 1], v[j]);
            j--;
        }

        i++;
    }
}
//works by placing the correct position by shifting larger vals to the right  

//seltion sorting algorithm 
void selectionSort(std::vector<int>& v)
{
    for(int i = 0; i < v.size() - 1; i++)
    {
        int small = i;
        
        for(int j = i + 1; j < v.size(); j++)
        {
            if(v[j] < v[small])
            {
                small = j;
            }
        }

        std::swap(v[i], v[small]);
    }
}
//works by selecting the smallest and swaps it with the current position 

//Quick Sort helper function for the paritions 
int splitVector(std::vector<int>& v, int left, int right)
{
    int pivot = v[right];
    int i = left - 1;

    for(int j = left; j < right; j++)
    {
        if(v[j] <= pivot)
        {
            i++;
            std::swap(v[i], v[j]);
        }
    }

    std::swap(v[i + 1], v[right]);

    return i + 1;
}
//works by partitioning the array around the pivot point

void quickSort(std::vector<int>& v, int left, int right)
{
    if(left < right)
    {
        int pivotIndex = splitVector(v, left, right);

        quickSort(v, left, pivotIndex - 1);
        quickSort(v, pivotIndex + 1, right);
    }
}

//third party function to ensure vector is sorted 
bool isSorted(std::vector<int>& v)
{
    for(size_t i = 1; i < v.size(); i++)
    {
        if(v[i] < v[i - 1])
            return false;
    }

    return true;
}

//function that calculates the standard deviation of a vector of doubles
double sampleSD(const std::vector<double>& v)
{
    double mean = 0;

    for(size_t i = 0; i < v.size(); i++)
    {
        mean += v[i];
    }

    mean = mean / v.size();

    double sd = 0;

    for(size_t i = 0; i < v.size(); i++)
    {
        sd += (v[i] - mean) * (v[i] - mean);
    }

    sd = sd / (v.size() - 1);

    return std::sqrt(sd);
}

//Function to test the sorting algorithms get the times and out put an error sign if need be 
void testFunction(int algorithm, const std::vector<std::vector<int>>& vectors, const std::string& caseType, std::ofstream& file)
{
    std::vector<double> timings;

    for(const auto& v : vectors)
    {
        std::vector<int> copy = v;
        auto start = std::chrono::high_resolution_clock::now();

        switch(algorithm)
        {
            case 1: bubbleSort(copy); break;
            case 2: insertionSort(copy); break;
            case 3: selectionSort(copy); break;
            case 4: quickSort(copy, 0, copy.size() - 1); break;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        timings.push_back(elapsed.count());

        if(!isSorted(copy))
        {
            std::cerr << "Sort failed for algorithm" << algorithm << " on case " << caseType << std::endl;
        }
    }

    double meanTime = std::accumulate(timings.begin(), timings.end(), 0.0) / timings.size();
    file << algorithm << "," << caseType << "," << meanTime << "\n";
}

//main function runs through all sizes, with all caseTypes
int main()
{
    srand(time(NULL));

    std::vector<int> sizes = {10, 100, 1000, 5000, 10000};
    std::ofstream bestCaseFile("best_case_times.csv");
    std::ofstream averageCaseFile("average_case_times.csv");
    std::ofstream worstCaseFile("worst_case_times.csv");

    for (const auto& size : sizes)
    {
        std::vector<std::vector<int>> bestVectors, averageVectors, worstVectors;

        //Generate best, average, and worst-case vectors
        bestVectors.push_back(sortedVector(size, false));
        worstVectors.push_back(sortedVector(size, true));

        for (int i = 0; i < 50; ++i) //Generate 50 random average-case vectors
        {
            averageVectors.push_back(randomVector(size, 0, size));
        }

        for (int algo = 1; algo <= 4; algo++)
        {
            //Collect timings for each case type
            std::vector<double> timingsBest, timingsAverage, timingsWorst;

            //Test best case
            for (const auto& v : bestVectors)
            {
                std::vector<int> copy = v;
                auto start = std::chrono::high_resolution_clock::now();

                switch (algo)
                {
                    case 1: bubbleSort(copy); break;
                    case 2: insertionSort(copy); break;
                    case 3: selectionSort(copy); break;
                    case 4: quickSort(copy, 0, copy.size() - 1); break;
                }

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                timingsBest.push_back(elapsed.count());
            }

            //Test average case
            for (const auto& v : averageVectors)
            {
                std::vector<int> copy = v;
                auto start = std::chrono::high_resolution_clock::now();

                switch (algo)
                {
                    case 1: bubbleSort(copy); break;
                    case 2: insertionSort(copy); break;
                    case 3: selectionSort(copy); break;
                    case 4: quickSort(copy, 0, copy.size() - 1); break;
                }

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                timingsAverage.push_back(elapsed.count());
            }

            //Test worst case
            for (const auto& v : worstVectors)
            {
                std::vector<int> copy = v;
                auto start = std::chrono::high_resolution_clock::now();

                switch (algo)
                {
                    case 1: bubbleSort(copy); break;
                    case 2: insertionSort(copy); break;
                    case 3: selectionSort(copy); break;
                    case 4: quickSort(copy, 0, copy.size() - 1); break;
                }

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                timingsWorst.push_back(elapsed.count());
            }

            //Calculate mean times
            double meanBest = std::accumulate(timingsBest.begin(), timingsBest.end(), 0.0) / timingsBest.size();
            double meanAverage = std::accumulate(timingsAverage.begin(), timingsAverage.end(), 0.0) / timingsAverage.size();
            double meanWorst = std::accumulate(timingsWorst.begin(), timingsWorst.end(), 0.0) / timingsWorst.size();

            //Print results
            std::cout << "************************\n";
            std::cout << "Algorithm: " << (algo == 1 ? "Bubble sort" : algo == 2 ? "Insertion sort" : algo == 3 ? "Selection sort" : "Quicksort") << "\n";
            std::cout << "Size: " << size << "\n";
            std::cout << "Best case time: " << meanBest << " sec\n";
            std::cout << "Average case time: " << meanAverage << " sec\n";
            std::cout << "Worst case time: " << meanWorst << " sec\n";
            std::cout << "************************\n";

            //Write to CSV files
            bestCaseFile << algo << "," << size << "," << meanBest << "\n";
            averageCaseFile << algo << "," << size << "," << meanAverage << "\n";
            worstCaseFile << algo << "," << size << "," << meanWorst << "\n";
        }
    }

    bestCaseFile.close();
    averageCaseFile.close();
    worstCaseFile.close();

    return 0;
}
