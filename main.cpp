#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

/* range of random integer values */
const int MAX_RANGE = 10000;

/* number of tries to make an experiment */
const int NUMBER_OF_TRIES = 100;

/* output file stream */
ofstream outf;


/**
 * this method works in O(n)
*/
void time_n(int n){
	int arr[n];
	for (int i=0; i<n; ++i){
		arr[i] = arr[i] + arr[i + 1];
	}
}

/**
 * this method works in O(n^2)
*/
void time_n_square(int n){
	int arr[n];
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			arr[i] = arr[i] * arr[j];
			arr[j] = arr[j] * arr[j];
		}
	}
}

/**
 * This method ensures that user gets in positive integer 
 * values for N and X
 * @param ch - character for which value to be get in
*/
int get_positive_integer(char ch){
	int ans = -1;
	while (ans <= 0){
		cout <<"Get positive integer value of " <<ch <<": ";
		cin >>ans;
	}
	return ans;
}


/**
 * partition array for quick sort
 * @params vector <int> &arr - array to partition
*/
int partition(vector <int> &arr, int l, int r, bool is_rand){
	int pivot;
	if (is_rand) 
		pivot = arr[l + rand() % (r - l + 1)];
	else pivot = arr[r];
	l--;
	for (int i=l + 1; i<=r; ++i){
		if (arr[i] <= pivot){
			swap(arr[++l], arr[i]);
		}
	}
	return l;
}


/**
 * this method check if subarray is array of equal elements
 * @params vector <int> &arr, int l, int r
*/
bool is_equal(vector <int> &arr, int l, int r){
	bool ind = 1;
	for (int i=l + 1; i<=r; ++i){
		if (arr[i - 1] != arr[i]){
			ind = 0;
		}
	}
	return ind;
}


/**
 * quick sort of array
*/
void quick_sort(vector <int> &arr, int l, int r){
	if (is_equal(arr, l, r)){
		return;
	}
	if (l < r){
		/* create apartition */
		int pi = partition(arr, l, r, false);

		quick_sort(arr, l, pi - 1);
		quick_sort(arr, pi + 1, r);
	}
}

/**
 * randomized quick sort of array
*/
void random_quick_sort(vector <int> &arr, int l, int r){
	if (is_equal(arr, l, r)){
		return;
	}
	if (l < r){
		/* create apartition */
		int pi = partition(arr, l, r, true);

		random_quick_sort(arr, l, pi);
		random_quick_sort(arr, pi + 1, r);
	}
}

/**
 * sort sorted and not sorted array
 * @param bool ind - indicates if it should be sorted with randomized quick sort
*/
void sort_array(vector <int> &sorted, vector <int> &random_array, string str, bool ind){
	int N = sorted.size();

	/* this is for measuring time */
	double start_time, end_time;
	
	outf <<"------" <<str <<"-------\n";
	outf <<"Sorted Case\n";
	outf <<"\tOriginal array:\t";
	for (int i=0; i<N; ++i){
		outf <<sorted[i] <<' ';
	}
	outf <<'\n';
	start_time = clock();
	if (ind)
		quick_sort(sorted, 0, N - 1);
	else random_quick_sort(sorted, 0, N - 1);
	end_time = clock();

	outf <<"\tSorted array:\t";
	for (int i=0; i<N; ++i){
		outf <<sorted[i] <<' ';
	}
	outf <<'\n';
	outf <<"\tTime required:\t" <<(end_time - start_time) / CLOCKS_PER_SEC <<" seconds\n";

	outf <<"Random Case\n";
	outf <<"\tOriginal array:\t";
	for (int i=0; i<N; ++i){
		outf <<random_array[i] <<' ';
	}
	outf <<'\n';

	start_time = clock();
	if (ind)
		quick_sort(random_array, 0, N - 1);
	else random_quick_sort(random_array, 0, N - 1);
	end_time = clock();

	outf <<"\tSorted array:\t";
	for (int i=0; i<N; ++i){
		outf <<random_array[i] <<' ';
	}
	outf <<'\n';
	outf <<"\tTime required:\t" <<(end_time - start_time) / CLOCKS_PER_SEC <<" seconds" <<'\n';
}

/**
 * this is a fundtion which makes experiments
 * NUMBER_OF_TRIES times
*/
void make_experiment(){
	int N = get_positive_integer('N');
	int X = get_positive_integer('X');
	for (int i=0; i<NUMBER_OF_TRIES; ++i){
		/* arrays */
		vector <int> sorted_array_qsort(N), random_array_qsort(N);
		vector <int> sorted_array_rand_qsort(N), random_array_rand_qsort(N);

		/* fill in sorted array */
		sorted_array_qsort[0] = sorted_array_rand_qsort[0] = N;
		for (int i=1; i<N; ++i){
			sorted_array_rand_qsort[i] = sorted_array_qsort[i] = sorted_array_qsort[i - 1] + X;
		}

		/* fill in random array */
		for (int i=0; i<N; ++i){
			random_array_rand_qsort[i] = random_array_qsort[i] = rand() % (MAX_RANGE + 1);
		}
		
		sort_array(sorted_array_qsort, random_array_qsort, "Quick Sort", true);
		sort_array(sorted_array_rand_qsort, random_array_rand_qsort, "Randomised Quick Sort", false);
	}
}

int main(){
	srand(time(0));
	outf.open("output.txt");
	make_experiment();
	return 0;
}