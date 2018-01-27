# ParallelSortingTeam
## Problem Description
Sorting algorithms are essential for managing data. Most sorting algorithms work by comparing the data being sorted. Usually these are judged by their efficiency as the size of the input grows large and is generally based on the number of elements to sort. Many algorithms that have the same efficiency vary their speed depending on the input. Some algorithms, perform exceptionally well for some inputs, but badly for others. On the other hand, some are unaffected by the order of input data. Another factor that may affect greatly the performance of an algorithms is the hardware on which the algorithms is running. The plan is to identify efficient parallel implementations for the Quicksort, MergeSort and CountSort algorithms.
## Objectives
Compare parallel sorting algorithms, in this case: quicksort, counting sort, merge sort, based on execution time and speedup (Amdahl’s Law)
Compare between CPU (OpenMP) and GPU (CUDA) execution time.
Compare our results with the results in the paper "Performance Analysis of Parallel Sorting Algorithms using GPU Computing" by Neetu Faujdar and SP Ghrera found below:
Demonstrate which sorting algorithm is more efficient in terms of resources.
## Scope 
Since there are numerous algorithms we have to narrow down the scope of algorithms that we are going to test. The scope of this project will span 3 sorting algorithms for which each has different time complexity. In this project, parallel Quicksort, parallel Merge sort and parallel Count Sort will be evaluated using specific metrics. For example we will take into account the size of the input data to determine which algorithm is more efficient with different sizes of data. Also, the type of this data may affect in the performance of the algorithm since not all data types takes same amount of space in memory. Measurements will take a Run-Time analysis and complexity for comparison between each algorithm. All tests will be performed using the resources provided by Chameleon Cloud. Specifics of the environment to be used will be provided as the experiments start to be developed. For this project, we will use
## References
Faujdar, Neetu, and SP SP Ghrera. “Performance Analysis of Parallel Sorting Algorithms Using GPU Computing.” International Journal of Computer Applications , doi:http://research.ijcaonline.org/ricsit2016/number2/ricsit2024.pdf.

Saadeh, Maha, et al. “Performance Evaluation of Parallel Sorting Algorithms on IMAN1 Supercomputer.” International Journal of Advanced Science and Technology, vol. 95, 2016, pp. 57–72., doi:10.14257/ijast.2016.95.06. 
