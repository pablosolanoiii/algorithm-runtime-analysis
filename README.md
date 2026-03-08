# Algorithm Runtime Analysis 

This project analyzes the runtime performance of several sorting algorithms across best-case, average-case, and worst-case inputs.  

## Overview 

The project benchmarks the following sorting algorithms:

- Bubble Sort 
- Insertion Sort 
- Selection Sort
- Quick Sort 

A C++ program generates input vectors, runs each sorting algorithm on multiple inp;ute sizes, measures execution time using high-resolution clocks, and records the results in CSV files.  Runtime data is then visualized using a Python plotting script.  

## My Contribution 

I implemented the C++ benchmarking system for this project, including: 

- Implementing Bubble Sort, Insertion Sort, Selection Sort, and Quicksort
- Generating best-case, average-case, and worst-case input vectors
- Measuring execution time using 'std::chrono'
- Writing runtime data to CSV files
- Verifying that sorting results are correct 
- Organizing experiments across multiple input sizes

## Attribution 

The Python plotting scripe used to visualized the runtime data was provided by Kun Tian and is included for visualization purposes.  The benchmarking sysytem and runtime generation were implemented by me.  

## Technologies Used 

- C++
- Python 
- Linux 
- Numpy 
- Matplotlib
- Excel

## Files 

- 'algorithmAnalysis.cpp'
    C++ benchmarking programs used to generate sorting runtime data 

- 'plotData.py'
    Python script used to visualize runtime results 

## Output Files

The benchmarking program generates CSV files containing runtime data and corresponding plots for each input case.

Directory contents:

- `best.csv`, `average.csv`, `worst.csv`  
  Runtime measurements for each sorting algorithm and input size.

- `*_fig.png`  
  Standard scale runtime comparison plots.

- `log_*_fig.png`  
  Log-scale runtime plots used to better visualize growth differences between algorithms.

## Method 

The program tests sorting performance across multiple input sizes:

- 10 
- 100 
- 1000
- 5000 
- 10000

For each size:

- Best-case input is generated as an already sorted vector 
- Worst-case input is generated as a reverse-sorted vector 
- Average-case input is generated as a reverse-sorted vector 

Execution time is measured using 'std::chrono::high_resolution_clock'

## Skills Demonstrated 

- Algorithm implementation in C++ 
- Runtime benchmarking 
- Experimental performance analysis 
- Data visualization 
- File-based data pipelines

## Limitations and Future Improvements

Several areas of the benchmarking system could be improved:

- Insufficient experimental data
  
  The current CSV files contain limited runtime measurements. Future experiments should run a larger number of trials for each input size to produce more statistically reliable results.

- Quicksort best-case testing

  The current implementation does not explicitly construct a reliable best-case input for quicksort. Future versions should generate inputs designed to produce balanced partitions in order to properly evaluate best-case performance.

- Improved validation of experimental output

  The generated CSV files should be compared against known sample outputs to verify correctness and ensure that runtime measurements are being recorded properly.

- Expanded statistical analysis

  While the current project computes mean runtime values, future work could include reporting additional statistics such as variance, standard deviation, and confidence intervals directly from the C++ benchmarking program.

- More detailed algorithm analysis

  Additional written analysis could explore why certain algorithms performed differently across input cases and compare the observed results with theoretical time complexity.

## Results

Benchmark results show expected performance trends:

- Bubble Sort and Selection Sort exhibit quadratic runtime growth.
- Insertion Sort performs well for small inputs but degrades as input size increases.
- Quicksort shows significantly better scalability compared to the other algorithms.

Log-scale plots highlight the differences in growth rates between algorithms as input size increases.

