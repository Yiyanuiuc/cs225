#include <cmath>
using namespace std;
#include <vector>
using namespace std;

vector<int> buildMaxHeap(vector<int> partialMaxHeap)
{
    // Your code here
	vector<int> newHeap(partialMaxHeap.size());
	size_t h=1;
	while (pow(2,h)<partialMaxHeap.size()) h++;
	
	for (size_t i=pow(2,h-1); i<pow(2,h); i++){
		newHeap[i] = partialMaxHeap[i];
	}
	h--;
	while (h>=1) {
		for (size_t i=pow(2,h-1); i<pow(2,h); i++){
			newHeap[i] = max(newHeap[2*i],newHeap[2*i+1]) + 1;
		}
		h--;
	}
	newHeap[0] = partialMaxHeap[0];
	return newHeap;
}

//void changeKey(vector<int> & elem, vector<int> & source, int index) {
//	if (index<=0 || index>=elem.size()) return;
//	else if (index>=size/2) elem[index] = source[index];
//	else {
//changeKey(elem, source, 2*index);
//		changeKey(elem, source, 2*index+1);
//		elem[index] = elem[2*index]+elem[2*index+1];
//	}
//
