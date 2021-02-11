#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <algorithm> 
#include <sys/sysinfo.h>


#ifndef SORTING_HPP_
#define SORTING_HPP_

int swaps=0;
int comparisons=0;

template <class T>
void swap(T* a, T* b){  
        T t = *a;  
        *a = *b;  
        *b = t;  
}  

void getStats(int* a, int* b){
    *a=swaps;
    *b=comparisons;
    swaps=0;
    comparisons=0;
}

namespace insertionSort{

    template <class T>
    void sort(std::vector<T> &arr, int arr_size, bool order){  
        T key;
        int prev_i;  
        
        for (int i = 1; i < arr_size; i++){  
            bool use=false;
            key = arr[i];  
            prev_i = i - 1;  

            std::cerr<<"Comparison: "<<arr[prev_i]<<" and "<<"key: "<<key<<std::endl;
            comparisons++;

            if(order)
                while (prev_i >= 0 && arr[prev_i] > key){  
                    std::cerr<<"Swap: "<<arr[prev_i+1]<<" and "<<arr[prev_i]<<std::endl;
                    swaps++;
                    arr[prev_i+1] = arr[prev_i];  
                    prev_i=prev_i-1;  
                    use=true;
                }
            else
                while (prev_i >= 0 && arr[prev_i] < key){  
                    std::cerr<<"Swap: "<<arr[prev_i+1]<<" and "<<arr[prev_i]<<std::endl;
                    swaps++;
                    arr[prev_i+1] = arr[prev_i];  
                    prev_i=prev_i-1;  
                    use=true;
                } 

            arr[prev_i+1] = key; 
            
            if(use){
                std::cerr<<"Swap: "<<arr[prev_i+1]<<" and "<<key<<std::endl;
                swaps++;
            }
        } 
    }  
    
}

namespace quickSort{

    template <class T>
    int partition(std::vector<T> &arr, int low, int high, bool order){  
        T pivot = arr[high];  
        int i = (low - 1); 
  
        for (int j = low; j <= high - 1; j++){
            std::cerr<<"Comparison: "<<arr[j]<<" and "<<"pivot: "<<pivot<<std::endl;  
            comparisons++;

            if(order){
                if (arr[j] < pivot){  
                    i++;
                    std::cerr<<"Swap: "<<arr[i]<<" and "<<arr[j]<<std::endl;
                    swaps++;
                    swap(&arr[i], &arr[j]);  
                }
            }else { 
                if (arr[j] > pivot){  
                    i++;
                    std::cerr<<"Swap: "<<arr[i]<<" and "<<arr[j]<<std::endl;
                    swaps++;
                    swap(&arr[i], &arr[j]);  
                }
            }
        }  
        std::cerr<<"Swap: "<<arr[i+1]<<" and "<<arr[high]<<std::endl;
        swaps++;
        swap(&arr[i + 1], &arr[high]);  
        return (i + 1);  
    }  
  
    template <class T>
    void sort(std::vector<T> &arr, int low, int high, bool order)  {  

        if (low < high){  
            int pi = partition(arr, low, high, order);  
 
            sort(arr, low, pi - 1, order);  
            sort(arr, pi + 1, high, order);  
        }  

    }  
}

namespace mergeSort{ 
    
    template <class T>
    void merge(std::vector<T> &arr, int l, int m, int r, bool order) { 
        int i, j, k; 
        int n1 = m - l + 1; 
        int n2 =  r - m; 

        std::vector<T> L, R; 
  
        for (i = 0; i < n1; i++)
            L.push_back(arr[l + i]);
        for (j = 0; j < n2; j++)
            R.push_back(arr[m + 1+ j]); 
  
 
        i = 0; 
        j = 0;
        k = l; 
        while (i < n1 && j < n2) { 
            comparisons++;
            std::cerr<<"Comparison: "<<L[i]<<" and "<<R[j]<<std::endl;

            if(order)
                if (L[i] <= R[j]) { 
                    swaps++;
                    std::cerr<<"Swap: "<<arr[k]<<" and "<<L[i]<<std::endl;
                    arr[k] = L[i]; 
                    i++; 
                }else{ 
                    swaps++;
                    std::cerr<<"Swap: "<<arr[k]<<" and "<<R[j]<<std::endl;
                    arr[k] = R[j]; 
                    j++; 
                } 
            else
                if (L[i] > R[j]) { 
                    swaps++;
                    std::cerr<<"Swap: "<<arr[k]<<" and "<<L[i]<<std::endl;
                    arr[k] = L[i]; 
                    i++; 
                }else{ 
                    swaps++;
                    std::cerr<<"Swap: "<<arr[k]<<" and "<<R[j]<<std::endl;
                    arr[k] = R[j]; 
                    j++; 
                } 

            k++; 
        } 

        while (i < n1){ 
            swaps++;
            std::cerr<<"Swap: "<<arr[k]<<" and "<<L[i]<<std::endl;
            arr[k] = L[i]; 
            i++; 
            k++; 
        } 

        while (j < n2) { 
            swaps++;
            std::cerr<<"Swap: "<<arr[k]<<" and "<<R[i]<<std::endl;
            arr[k] = R[j]; 
            j++; 
            k++; 
        } 
    } 

    template <class T>
    void sort(std::vector<T> &arr, int l, int r, bool order) { 
        if (l < r){ 
            int m = l+(r-l)/2; 

            sort(arr, l, m, order); 
            sort(arr, m+1, r, order); 
  
            merge(arr, l, m, r, order); 
        } 

    }

}

namespace dualPivot{
  
    template <class T>
    int partition(std::vector<T> &arr, int low, int high, int* lp, bool order){  

            std::cerr<<"Comparison: "<<arr[low]<<" and "<<arr[high]<<std::endl;  
            comparisons++;
            if (arr[low] > arr[high])  {
                std::cerr<<"Swap: "<<arr[low]<<" and "<<arr[high]<<std::endl;
                swaps++;
                swap(&arr[low], &arr[high]); 
            } 

        int j = low + 1;  
        int g = high - 1, k = low + 1;
        T p = arr[low], q = arr[high];  


            while (k <= g)  {  
                comparisons+=2;
                std::cerr<<"Comparison: "<<k<<" and "<<g<<std::endl;  
                if (arr[k] < p){  
                   std::cerr<<"Comparison: "<<arr[k]<<" and "<<p<<std::endl;
                    std::cerr<<"Swap: "<<arr[k]<<" and "<<arr[j]<<std::endl;
                    swap(&arr[k], &arr[j]); 
                    swaps++;
                    j++;  
                }else if (arr[k] >= q){  
                    std::cerr<<"Comparison: "<<arr[k]<<" and "<<q<<std::endl;
                    while (arr[g] > q && k < g) {
                       std::cerr<<"Comparison: "<<arr[g]<<" and "<<q<<std::endl;
                        std::cerr<<"Comparison: "<<k<<" and "<<q<<std::endl;
                        g--;  
                        comparisons++;
                    }

                    std::cerr<<"Swap: "<<arr[k]<<" and "<<arr[g]<<std::endl;
                    swap(&arr[k], &arr[g]);  
                    swaps++;
                    g--;  

                    comparisons++;
                    std::cerr<<"Comparison: "<<arr[k]<<" and "<<p<<std::endl;
                    if (arr[k] < p){  
                        std::cerr<<"Swap: "<<arr[k]<<" and "<<arr[j]<<std::endl;
                        swap(&arr[k], &arr[j]);
                        swaps++;  
                        j++;  
                    }  
                }  
                k++;  
            }
        j--;  
        g++; 

      //  std::cerr<<"Swap: "<<arr[low]<<" and "<<arr[j]<<std::endl;
     //   std::cerr<<"Swap: "<<arr[high]<<" and "<<arr[g]<<std::endl;
        swap(&arr[low], &arr[j]);  
        swap(&arr[high], &arr[g]);  
        swaps+=2; 
    
        *lp = j; 
  
        return g;  
    }  

    template <class T>
    void sort(std::vector<T> &arr, int low, int high, bool order){  
        if (low < high) {  
            int lp, rp;  
            rp = partition(arr, low, high, &lp, order);  
            sort(arr, low, lp - 1, order);  
            sort(arr, lp + 1, rp - 1, order);  
            sort(arr, rp + 1, high, order);  
        }  
    }  

}


namespace hybridSort{

    template <class T>
    void insertionSort(std::vector<T> &arr, int left, int right, bool order) { 
        for (int i = left + 1; i <= right; i++) { 
            bool use=false;
            T temp = arr[i]; 
            int j = i - 1; 

            std::cerr<<"Comparison: "<<arr[j]<<" and "<<"key: "<<temp<<std::endl;
            comparisons++;

            if(order)
                while (arr[j] > temp && j >= left) { 
                   std::cerr<<"Swap: "<<arr[j+1]<<" and "<<arr[j]<<std::endl;
                    swaps++;
                    arr[j+1] = arr[j]; 
                    j--; 
                    use=true;
                }
            else
                while (arr[j] < temp && j >= left) { 
                    std::cerr<<"Swap: "<<arr[j+1]<<" and "<<arr[j]<<std::endl;
                    swaps++;
                    arr[j+1] = arr[j]; 
                    j--; 
                    use=true;
                }

            arr[j+1] = temp; 

            if(use){
                std::cerr<<"Swap: "<<arr[j+1]<<" and "<<temp<<std::endl;
                swaps++;
            }
        } 
    } 

    template <class T>
    void sort(std::vector<T> &arr, int n, bool order){
        const int SIZE=5;                              // To define a moment when array is divided into smaller ones, change the SIZE constant
        for (int i = 0; i < n; i+=SIZE) 
            insertionSort(arr, i, std::min(i+SIZE-1, n-1), order); 

        for (int size = SIZE; size < n; size = 2*size){ 
            for (int left = 0; left < n; left += 2*size){ 
        
                int mid = left + size - 1; 
                int right = std::min((left + 2*size - 1), (n-1)); 
                mergeSort::merge(arr, left, mid, right, order); 
            } 
        } 

    } 


}

namespace  countSort{
    
    template <class T>
    void sort(std::vector<T> &arr, int n, int power) { 
        T temp[n];
        int quantity[20] = {0}; 
    
        for (int i = 0; i < n; i++) 
            quantity[ (arr[i]/power)%10 +9 ]++; 
    
        for (int i = 1; i < 20; i++) 
            quantity[i] += quantity[i - 1]; 
    
        for (int i = n - 1; i >= 0; i--) { 
            std::cerr<<"Swap: "<<arr[i]<<" and "<<temp[i]<<std::endl;
            swaps++;
            temp[quantity[ (arr[i]/power)%10 + 9] - 1] = arr[i]; 
            quantity[ (arr[i]/power)%10 +9 ]--; 
        } 
    
        for (int i = 0; i < n; i++){
            arr[i] = temp[i];  
        }
    } 
}

namespace  radixSort{
    
    template <class T>
    void sort(std::vector<T> &arr, int n){
        int max=*max_element(arr.begin(), arr.end()); 
        int min=*min_element(arr.begin(), arr.end());
        
        if(abs(max)>abs(min))
            max=max;
        else if(max==0 && min==0)
            max=1;
        else
            max=abs(min);
  
        for(int power=1; max/power>0; power*=10)
            countSort::sort(arr, n, power);
    }

}


#endif  // SORTING_HPP_