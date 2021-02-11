#include <iostream>
#include <ctime>  
#include <string.h>
#include <bits/stdc++.h> 
#include <fstream>
#include "sorting.hpp"

template <class T>
void printArray(std::vector<T> arr, int n){  
    int i;  
    for (i = 0; i < n; i++)  
        std::cout << arr[i] << " ";  
    std::cout << std::endl; 
}  

template <class T>
bool checkIfSorted(std::vector<T> arr, int n, bool order){  

    for (int i = 0; i < n-1; i++)  
        if(order){
            if(!(arr[i]<=arr[i+1]))
                return false;
        }else{
            if(!(arr[i]>=arr[i+1]))
                return false;
        }

    return true;        
}  

template <class T>
void randomArray(std::vector<T> &arr, int n){
    srand(time(0));
    for(int i=0; i<n; i++)
        arr.push_back(rand()%100000-16383);
}


int main(int argc, char** argv){                        //driver function

    if(argc>6 && strcmp(argv[5], "--stat")==0){
        int k=std::stoi(argv[7]);
        std::fstream file (argv[6], std::ios::out);
        bool order=true;          // Sorting in order '<=' if order==true, else '>='

        if (strcmp(argv[3], "--comp")==0)
                    if(strcmp(argv[4], ">=")==0)
                        order=false;

        for(int n=100; n<=10000; n+=100){
            std::vector<int> arr;

            for(int i=0; i<k; i++){
                randomArray(arr, n);
                int swaps=0, comparisons=0;
                float clk;
                long long int mem=0;

                if(strcmp(argv[2], "insertion")==0){
                    clock_t start = clock();
                    insertionSort::sort(arr, n, order); 
                    clock_t end = clock();
                    clk= (float)(end - start);
                }else if (strcmp(argv[2], "merge")==0){
                    clock_t start = clock();
                    mergeSort::sort(arr, 0, n - 1, order); 
                    clock_t end = clock();
                    clk= (float)(end - start);
                }else if (strcmp(argv[2], "quick")==0){
                    clock_t start = clock();
                    quickSort::sort(arr, 0, n - 1, order);
                    clock_t end = clock();
                    clk= (float)(end - start);
                }else if (strcmp(argv[2], "dualpivot")==0){
                    clock_t start = clock();
                    dualPivot::sort(arr, 0, n - 1, order);
                    clock_t end = clock();
                    clk= (float)(end - start);
                }else if (strcmp(argv[2], "hybrid")==0){
                    clock_t start = clock();
                    hybridSort::sort(arr, n, order);
                    clock_t end = clock();
                    clk= (float)(end - start);
                }else if (strcmp(argv[2], "radix")==0){
                    clock_t start = clock();
                    radixSort::sort(arr, n);
                    clock_t end = clock();
                    clk= (float)(end - start);
                }else{
                    std::cout<<"Wrong parameters!"<<std::endl;
                    return -1;
                }

                struct sysinfo memInfo;
                sysinfo (&memInfo);
                long long int physMemUsed = memInfo.totalram - memInfo.freeram;
                mem=physMemUsed*memInfo.mem_unit/1024/1024;

                getStats(&swaps, &comparisons);
                file<<"N: "<<n<<" swp: "<<swaps<<" comp: "<<comparisons<<" t: "<<clk/CLOCKS_PER_SEC<<" mem:"<<mem<<std::endl;
            }
        }

        file.close();
    }else{
        long long int mem=0;
        int n;
        int swaps=0, comparisons=0;
        std::vector<int> arr;    // To define type of array, change "int" to your choosen type (ex. std::string)
        bool order=true;          // Sorting in order '<=' if order==true, else '>='
        std::cout<<"Number of elements: ";
        std::cin>>n;
        std::cout<<"Array: ";

        if (strcmp(argv[3], "--comp")==0)
            if(strcmp(argv[4], ">=")==0)
                order=false;
        
        for(int i=0; i<n; i++){
            int temp;             // To define type of auxiliary variable "temp" , change "int" to your choosen type (ex. std::string)
            std::cin>>temp;
            arr.push_back(temp);
        }

        if(strcmp(argv[1], "--type")==0){

            if(strcmp(argv[2], "insertion")==0)
                insertionSort::sort(arr, n, order); 
            else if (strcmp(argv[2], "merge")==0)
                mergeSort::sort(arr, 0, n - 1, order); 
            else if (strcmp(argv[2], "quick")==0)
                quickSort::sort(arr, 0, n - 1,order);
            else if (strcmp(argv[2], "dualpivot")==0)
                dualPivot::sort(arr, 0, n - 1, order);
            else if (strcmp(argv[2], "hybrid")==0)
                hybridSort::sort(arr, n, order);
            else if (strcmp(argv[2], "radix")==0)
                radixSort::sort(arr, n);
            else{
                std::cout<<"Wrong parameters!"<<std::endl;
                return -1;
            }
        }
        
        struct sysinfo memInfo;
        sysinfo (&memInfo);
        long long int physMemUsed = memInfo.totalram - memInfo.freeram;
        mem=physMemUsed*memInfo.mem_unit/1024/1024;

        getStats(&swaps, &comparisons);
        std::cerr<<"Swaps: "<<swaps<<" Comparisons: "<<comparisons<<" Mem:"<<mem<<std::endl;
        
        if(checkIfSorted(arr, n ,order))
            std::cout<<"Checking sorting order... "<<"OK"<<std::endl;
        else
            std::cout<<"Checking sorting order... "<<"WRONG !!"<<std::endl;

        std::cout <<"Sorted elements:"<<n<<"\nSorted array: \n";  
        printArray(arr, n);  
    }

    return 0;
}
 
