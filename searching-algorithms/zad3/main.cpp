#include <iostream>
#include <ctime>  
#include <string.h>
#include <random>
#include <fstream>

int comparisons=0;

int binarySearch(int arr[], int low, int high, int element){
	if (low > high)
		return -1;

	int middle = (low + high)/2;

	comparisons++;
	if (element == arr[middle])
		return middle;
	else if (element < arr[middle]){
		comparisons++;
		return binarySearch(arr, low,  middle - 1, element);
	}else
		return binarySearch(arr, middle + 1,  high, element);
}

void sortedDistinctArray(int arr[], int n){
	for(int i=0; i<n; i++ )
		arr[i]=i-n/2;
}

int main(int argc, char** argv){

	int n;
	float clk=0;

	if(argc>1){

		if (strcmp(argv[1], "--stat")==0){
			srand(time(NULL));
			std::fstream file ("binary_stats.txt", std::ios::out);


			for(int n=1000; n<=100000; n+=1000){

				int arr[n];
				sortedDistinctArray(arr, n);
				int target= (-n/2) + ( std::rand() % ( (n-(n/2)) - (-n/2)  + 1 ) );

				int low = 0, high = n - 1;
				clock_t start = clock();
				int index = binarySearch(arr, low, high, target);
				clock_t end = clock();
				clk= (float)(end - start);

				file<<"n: "<<n<<" k: "<<target<<" comp: "<<comparisons<<" time: "<<clk/CLOCKS_PER_SEC<<std::endl;

				int arr2[n/2];
				sortedDistinctArray(arr2, n/2);
				int target2= (-n/4) + ( std::rand() % ( (n-(n/4)) - (-n/4)  + 1 ) );

				low = 0, high = n - 1;
				start = clock();
				index = binarySearch(arr2, low, high, target2);
				end = clock();
				clk= (float)(end - start);

				file<<"n/2: "<<n/2<<" k: "<<target2<<" comp: "<<comparisons<<" time: "<<clk/CLOCKS_PER_SEC<<std::endl;

				
			}
			file.close();

		}else if(strcmp(argv[1], "--manual")==0){

			std::cout<<"Podaj ilosc elementow w tablicy: \n";
			std::cin>>n;
			std::cout<<"Podaj POSORTOWANA tablice: \n";

			int arr[n];

			for(int i=0; i<n; i++)       
					std::cin>>arr[i];
		
			std::cout<<"Podaj szukana wartosc: \n";
			int target;
			std::cin>>target;

			int low = 0, high = n - 1;
			clock_t start = clock();
			int index = binarySearch(arr, low, high, target);
			clock_t end = clock();
			clk= (float)(end - start);

			std::cout<<"Elementy: "<<n<<" Szukana wartosc: "<<target<<" Porownania: "<<comparisons<<" Czas: "<<clk/CLOCKS_PER_SEC<<std::endl;
			if (index != -1){
				std::cout<<"Element w indeksie: "<<index<<std::endl;
				return 1;
			}else{
				std::cout<<"Element nie jest w tablicy! \n";
				return 0;
			}
		}else
		std::cout<<"Bledny parametr wywolania! \nWprowadz '--stat' dla trybu statystycznego, lub '--manual' dla manualnego \n";

	}else
		std::cout<<"Bledny parametr wywolania! \nWprowadz '--stat' dla trybu statystycznego, lub '--manual' dla manualnego \n";
	
}