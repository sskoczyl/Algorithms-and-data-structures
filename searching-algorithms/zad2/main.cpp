#include <iostream> 
#include "selects.hpp"
#include <algorithm>
#include <random>
#include <string.h>

void permutation(int arr[], int n){    // random permutation of n-elem set
	for(int i=0; i<n; i++)
		arr[i]=i+1;

	std::random_shuffle(arr, arr+n);
}

void random(int arr[], int n){    //random distinct values in -((n+1000)/2) to (n+1000)/2 range
	srand(time(NULL));

	for(int i=0; i<n; i++){
		arr[i]=(-(n+1000)/2) + ( std::rand() % ( ((n+1000)-((n+1000)/2)) - (-(n+1000)/2)  + 1 ) );

		for(int j=0; j<i; j++)	
			if(arr[j]==arr[i]){
				i--;
				break;
			}	
	}
	
}

void printArray(int arr[], int n, int k){  
    int i;  
    for (i = 0; i < n; i++)
		if(arr[i]==k)
        	std::cout <<"["<< arr[i]<<"]"<< " ";  
		else
			std::cout << arr[i] << " ";  
			
    std::cout << std::endl; 
} 


int main(int argc, char** argv) {
	
	int n;
	int k;

	std::cout<<"Podaj ilosc elementow w tablicy: \n";
	std::cin>>n;
	std::cout<<"Podaj szukany k-ty najmniejszy element: \n";
	std::cin>>k;
	int arr[n], temp[n]; 

	if (strcmp(argv[1], "-r")==0){
		random(arr, n);
	}else if(strcmp(argv[1], "-p")==0){
		permutation(arr, n);
		srand(time(NULL));
		std::random_shuffle(arr, arr+n);
	}else{
		std::cout<<"Bledny parametr \n";
	}
	std::copy(arr,arr + n, temp);

	if(k<=n || k<=0){
		int idx;

		std::cerr<<"RANDOM SELECT: \n";	
		idx=randomSelect::select(arr, 0, n - 1, k);
		
		std::cerr<<"SELECT: \n";	
		idx=normalSelect::select(arr, 0, n - 1, k);

		std::cout<<"Wynik: \n";	
		printArray(temp, n, idx);
	}else
		std::cout <<"K musi byc w zakresie 1<=k<=n"<< std::endl; 

	return 0; 
} 
