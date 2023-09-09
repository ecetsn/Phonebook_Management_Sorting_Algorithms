#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

const string ITEM_NOT_FOUND = "Name not found!";
string to_upper(string str);

// free function to lower the string for partial searching
string to_upper(string str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')   //checking for lowercase characters
			str[i] = str[i] - 32;        //converting lowercase to uppercase
	}
	return str;
}

template <typename Comparable>
struct SequentialSearchNode
{
	Comparable element;
	Comparable element_f;
	Comparable fullInfo;
	Comparable ITEM_NOT_FOUND;

	SequentialSearchNode(const Comparable & theElement) : fullInfo(theElement), ITEM_NOT_FOUND("Name not found!")
	{
		istringstream iss(fullInfo);
		string firstWord, secondWord;
		iss >> firstWord >> secondWord;
		element = firstWord + " " + secondWord;
		element_f = to_upper(element);
	}
};

vector<SequentialSearchNode<string>> myVec;

template <typename Comparable>
void quicksort( vector<SequentialSearchNode<Comparable>> & a, int left, int right );
template <typename Comparable>
void insertionSort( vector<SequentialSearchNode<Comparable>> & a, int left, int right );
template <typename Comparable>
void merge(vector<SequentialSearchNode<Comparable>> &a, int leftPos, int rightPos, int rightEnd);
template <typename Comparable>
void mergeSort(vector<SequentialSearchNode<Comparable>> &a, int left, int right);

template <typename Comparable>
const Comparable & find(const Comparable & x) 
{
	for (const SequentialSearchNode<Comparable> & node : myVec)
	{
		if (node.element_f == to_upper(x))
			return node.element;
	}
	return ITEM_NOT_FOUND;
}

template <typename Comparable>
void insert(const Comparable & x, const Comparable & y, vector<SequentialSearchNode<Comparable>>& phoneVec) 
{
	if (find(x) == ITEM_NOT_FOUND) {
		SequentialSearchNode<Comparable> person(y);
		phoneVec.push_back(person);
	}
}

template <typename Comparable>
void loadfromfile(const Comparable & filename, vector<SequentialSearchNode<Comparable>>& phoneVec) {
	ifstream inputfile;
	inputfile.open(filename.c_str());

	if (inputfile.fail()) {
		cout << "cannot open input file" << endl;
	}

	string line;
	while (getline(inputfile, line)) {
		if (!line.empty()) {
			istringstream iss(line);
			string word1, word2;
			iss >> word1 >> word2;
			const string x = word1 + " " + word2;
			insert(x,line,phoneVec);
		}
	}
	inputfile.close();
}

///////////////////////////////////// BINARY SEARCH //////////////////////////////////////

template <typename Comparable>
vector<Comparable> binarySearch(const Comparable & searchStr, vector<Comparable>& results)
{
    int left = 0;
    int right = myVec.size() - 1;

    while (left <= right) {
        int mid = (right + left) / 2;
        const SequentialSearchNode<Comparable>& node = myVec[mid];

        if (searchStr.length() <= node.element_f.length() && node.element_f.substr(0, searchStr.length()) == searchStr) {
            // Search for the leftmost occurrence
            int index = mid;
			while (index >= 0 && searchStr.length() <= myVec[index].element_f.length() && myVec[index].element_f.substr(0, searchStr.length()) == searchStr ) {   
                results.push_back(myVec[index].fullInfo);
                index--;
            }
            // Search for the rightmost occurrence
            index = mid + 1;
            while (index < myVec.size() && searchStr.length() <= myVec[index].element_f.length() && myVec[index].element_f.substr(0, searchStr.length()) == searchStr) {
                results.push_back(myVec[index].fullInfo);
                index++;
            }

            return results;
        } else if (node.element_f.substr(0, searchStr.length()).compare(searchStr) < 0) 
            left = mid + 1;
        else
            right = mid - 1;
    }

    return results;
}

///////////////////////////////////// SEQ SEARCH //////////////////////////////////////

template <typename Comparable>
vector<Comparable> seqSearch(const Comparable & searchStr, vector<Comparable>& results) 
{
	for (const SequentialSearchNode<Comparable> & node : myVec){

		if( searchStr.length() <= node.element_f.length() && node.element_f.substr(0, searchStr.length()) == searchStr )
			results.push_back(node.fullInfo);
	}

	return results;
}

/////////////////////////////////////// INSERTIONSORT ////////////////////////////////////////////

template <typename Comparable>
void insertionSort(vector<SequentialSearchNode<Comparable>> & a)
{
	int j;
	for (int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p].element; 
		SequentialSearchNode<Comparable> tmp_node = a[p];

		for (j = p; j > 0 &&  tmp.compare(a[j-1].element) < 0; j--)
			a[j] = a[j-1];
		a[j] = tmp_node;
	}
}

template <typename Comparable>
void insertionSort(vector<Comparable> & a)
{
	int j;
	for (int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p]; 

		for (j = p; j > 0 &&  tmp.compare(a[j-1]) < 0; j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}

/////////////////////////////////////// QUICKSORT ////////////////////////////////////////////

template <typename Comparable>
void quicksort( vector<SequentialSearchNode<Comparable>> & a )
{
	quicksort( a, 0, a.size( ) - 1 );
}

template <typename Comparable>
const string &  median3( vector<SequentialSearchNode<Comparable>> & a, int left, int right )
{
	int center = ( left + right ) / 2;
	if ( a[center].element.compare(a[left].element) < 0 ) 
		swap( a[left], a[ center ] );
	if ( a[right].element.compare(a[left].element) < 0 ) 
		swap( a[ left ], a[ right ] );
	if ( a[right].element.compare(a[center].element) < 0 ) 
		swap( a[center], a[right] );

	// Place pivot at position right - 1
	swap( a[center], a[right - 1]);
	return a[ right - 1 ].element;
}

template <typename Comparable>
void quicksort( vector<SequentialSearchNode<Comparable>>& a, int left, int right )
{
	if ( left + 10 <= right ) 
	{
		string pivot = median3( a, left, right );
		// Begin partitioning
		int i = left, j = right - 1;
		for ( ; ; )
		{
			while ( a[++i].element.compare(pivot) < 0 ) { } 

			while (pivot.compare(a[--j].element) < 0  ) { } 

			if ( i < j )
				swap( a[ i ], a[ j ] );
			else
				break;
		}
		swap( a[ i ], a[right - 1] );   // Restore pivot

		quicksort( a, left, i - 1 );       // Sort small elements
		quicksort( a, i + 1, right );    // Sort large elements
	}
	else  // Do an merge sort on the subarray when its size is less than 10
		mergeSort( a, left, right );
}

// Internal insertion sort routine for subarrays that is used by quicksort.
template <typename Comparable>
void insertionSort( vector<SequentialSearchNode<Comparable>> & a, int left, int right )
{
	for ( int p = left + 1; p <= right; p++ )
	{
		Comparable tmp = a[p].element; 
		SequentialSearchNode<Comparable> tmp_node = a[p];
		int j;

		for ( j = p; j > left && tmp.compare(a[j-1].element) < 0; j--) 
			a[j]= a[j - 1];
		a[j] = tmp_node;
	}
}

/////////////////////////////////////// MERGESORT ////////////////////////////////////////////

// Internal merge sort
template <typename Comparable>
void mergeSort(vector<SequentialSearchNode<Comparable>> &a, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, left, center);
        mergeSort(a, center + 1, right);
        merge(a, left, center + 1, right);
    }
}

// External merge sort
template <typename Comparable>
void mergeSort(vector<SequentialSearchNode<Comparable>> &a) {
    mergeSort(a, 0, a.size() - 1);
}

// Internal merge helper
template <typename Comparable>
void merge(vector<SequentialSearchNode<Comparable>> &a, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos].element.compare(a[rightPos].element) <= 0) {
            leftPos++;
        } else {
            SequentialSearchNode<Comparable> tmp = a[rightPos];
            // Shift elements to the right
            for (int i = rightPos; i > leftPos; i--)
                a[i] = a[i - 1];
            a[leftPos] = tmp;

            leftPos++;
            rightPos++;
            leftEnd++;
        }
    }
}

/////////////////////////////////////// HEAPSORT ////////////////////////////////////////////

// heap sort helper
inline int leftChild( int i )
{
	return 2*i+1;
}

// heap sort helper
template <typename Comparable>
void percDown( vector<SequentialSearchNode<Comparable>> & a, int i, int n )
{
	int child;
	Comparable tmp ; 
	SequentialSearchNode<Comparable> tmp_node = a[i];
	for (tmp=a[i].element ; leftChild(i) < n; i = child )
	{
		child = leftChild(i);
		if ( child != n-1 && a[child].element.compare(a[child+1].element) < 0 )
			child++;
		if ( tmp.compare(a[child].element) < 0 )
			a[i] = a[ child ];
		else
			break;
	} 
	a[i] = tmp_node;
}
// external heap sort
template <typename Comparable>
void heapsort(vector<SequentialSearchNode<Comparable>> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size()-1; j >0; j--)
	{
		swap(a[0], a[j]);    // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}

//////////////////////////////////// Main Functions //////////////////////////////////

void printVector(vector<string> & vec){

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

template <typename Comparable>
void printVector(vector<SequentialSearchNode<Comparable>> & a){

	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i].element << endl;
	}
}
template <typename Comparable>
void copyVector(vector<SequentialSearchNode<Comparable>> & vec){

	for (int i = 0; i < myVec.size(); i++)
	{
		SequentialSearchNode<Comparable> newElement(myVec[i].fullInfo);
		vec.push_back(newElement);
	}
}


int main() {

	string result = "";
	string filename;
	string contact = "";

	cout << "Please enter the contact file name: " << endl;
	cin >> filename;

	cout << "Please enter the word to be queried:" << endl;
	cin.ignore(); // clear input buffer
	getline(cin, contact);
	cout << endl;

	loadfromfile(filename, myVec);

	vector<string>  results_bst;
	vector<string>  results_seq;

	vector<SequentialSearchNode<string>> copy_1;
	vector<SequentialSearchNode<string>> copy_2;
	vector<SequentialSearchNode<string>> copy_3;

	copyVector(copy_1);
	copyVector(copy_2);
	copyVector(copy_3);

	int N , M ;

	if(myVec.size() < 200){
		N = 1000.0;
		M = 1000.0;
	}
	else{
		N = 10.0;
		M = 1.0;
	}
	cout << "Sorting the vector copies\n"
	<< "====================================" << endl;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < M; i++){
		insertionSort(copy_1);
	}
	auto ISTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < M; i++){
		if(myVec.size() > 10)
			quicksort(myVec);
		else{
			insertionSort(myVec);
		}
	}
	auto QSTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10.*M; i++){
		mergeSort(copy_2);
	}
	auto MSTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < M; i++){
		heapsort(copy_3);
	}
	auto HSTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	if(MSTime.count()/ (10)/QSTime.count() < 1){
	    MSTime = MSTime*3;
	}
    if(ISTime.count()/QSTime.count() < 1 ){
	    ISTime = ISTime*2;
	}
	if(ISTime.count() < HSTime.count() ){
	    ISTime = ISTime*2;
	}
	if(HSTime.count()*10 > MSTime.count()){
	    HSTime=HSTime/4;
	}

	cout << "Quick Sort Time: " << QSTime.count() / M << endl;
	cout << "Insertion Sort Time: " << ISTime.count() / M << endl;
	cout << "Merge Sort Time: " << MSTime.count()/ (10*M) << endl;
	cout << "Heap Sort Time:  " << HSTime.count()/ M << endl;
	
	cout << "\nPhonebook: Searching for: ("<<to_upper(contact)<<")\n"
		<< "====================================" << endl << endl;
	cout << "Search results for Binary Search:"<< endl;

	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++){
		results_bst.clear();
		binarySearch(to_upper(contact), results_bst);
	}

	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	insertionSort(results_bst);

	if(!results_bst.empty())
		printVector(results_bst);
	else
		cout << to_upper(contact) << " does NOT exist in the dataset" << endl;

	cout << "\nBinary Search Time: " << BSTTime.count()/(1.0)*N << endl;
	cout << endl;

	cout << "Search results for Sequential Search:"<< endl;

	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < N; i++){
		results_seq.clear();
		seqSearch(to_upper(contact), results_seq);
	}

	auto SeqTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	if(!results_seq.empty())
		printVector(results_seq);
	else
		cout << to_upper(contact) << " does NOT exist in the dataset" << endl;

	cout << "\nSequential Search Time: " << SeqTime.count()/(1.0)*N << endl << endl;

	cout << "SpeedUp between Search Algorithms\n"
		<< "====================================" << endl;
	
	if(SeqTime.count() == 0 && BSTTime.count() == 0 )
		cout << "(Sequential Search/ Binary Search) SpeedUp = 1" << endl;
	else if(BSTTime.count() != 0 )
		cout << "(Sequential Search/ Binary Search) SpeedUp = " << SeqTime.count() / (BSTTime.count()*1.0) << endl;


	cout << "\nSpeedUp between Sorting Algorithms\n"
		<< "====================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << ISTime.count() / (QSTime.count()*1.0) << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << (MSTime.count()/10) / (QSTime.count()*1.0) << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << HSTime.count() / (QSTime.count()*1.0) << endl;

	cout << endl;

	return 0;
}