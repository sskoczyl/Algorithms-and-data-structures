#include <random>
#include <algorithm> 
#include <iostream>

void swap(int* a, int* b){  
    std::cerr<<"Swap: "<< *a<<" and "<<*b<<std::endl;
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

namespace randomSelect{

    int partition(int arr[], int left, int right) { 
        int x = arr[right], i = left; 
        for (int j = left; j <= right - 1; j++) { 
            std::cerr<<"Comparison: "<< arr[j]<<" and "<<x<<std::endl;
            if (arr[j] <= x) { 
                swap(&arr[i], &arr[j]); 
                i++; 
            } 
        } 
        swap(&arr[i], &arr[right]); 
        return i; 
    } 
  
    int randomPivot(int arr[], int left, int right) { 
        srand(time(NULL)); 
        int pivot = rand() % (right-left+1); 
        std::cerr<<"Pivot: "<<pivot<<std::endl;
        swap(&arr[left + pivot], &arr[right]); 
        return partition(arr, left, right); 
    } 

    int select(int arr[], int left, int right, int element) { 
        if (element > 0 && element <= right - left + 1) { 
            int idx = randomPivot(arr, left, right); 

            
            if (idx-left == element-1) 
                return arr[idx]; 

            std::cerr<<"Comparison: "<< idx-left<<" and "<<element-1<<std::endl;
            if (idx-left > element-1) 
                return select(arr, left, idx-1, element); 

            return select(arr, idx+1, right, element-idx+left-1); 
        }   
    
        return -1; 
    } 
}

namespace normalSelect{

    int Median(int arr[], int n) {

        std::sort(arr, arr+n);

        return arr[n/2];
    } 

    int partition(int arr[], int l, int r, int x) { 
        int i; 
        for (i=l; i<r; i++) 
            if (arr[i] == x){
                std::cerr<<"Comparison: "<< arr[i]<<" and "<<x<<std::endl;
                break; 
            }
        swap(&arr[i], &arr[r]); 
    
        i = l; 
        for (int j = l; j <= r - 1; j++) { 
            if (arr[j] <= x) { 
                std::cerr<<"Comparison: "<< arr[j]<<" and "<<x<<std::endl;
                swap(&arr[i], &arr[j]); 
                i++; 
            } 
        } 
        swap(&arr[i], &arr[r]); 
        return i; 
    } 

    int select(int arr[], int left, int right, int element) { 
        if (element > 0 && element <= right - left + 1) { 
            int n = right-left+1; 
            int i, median[(n+4)/5];
            for (i=0; i<n/5; i++) 
                median[i] = Median(arr+left+i*5, 5); 

            if (i*5 < n){ 
                median[i] = Median(arr+left+i*5, n%5);  
                i++; 
            }     

            int medianOfMedians;
            if(i==1)
                medianOfMedians = median[i-1];
            else
                medianOfMedians = select(median, 0, i-1, i/2); 


            std::cerr<<"Pivot: "<<medianOfMedians<<std::endl;
            int pos = partition(arr, left, right, medianOfMedians); 

            if (pos-left == element-1) 
                return arr[pos]; 

            std::cerr<<"Comparison: "<< pos-left<<" and "<<element-1<<std::endl;
            if (pos-left > element-1)
                return select(arr, left, pos-1, element); 
     
            return select(arr, pos+1, right, element-pos+left-1); 
        } 
    
        return -1; 
    } 

}
