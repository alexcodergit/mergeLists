#include<vector>
#include<limits>
#include<queue>
#include<assert.h>
#include<algorithm>
#include<iostream>

using namespace std;

/*
  holds the element vaue, the index of th list (in the list of lists)
  and the index of the element in the list, for example:
  1 2 3
  4 5 6
  7 8 9
  Triplet(4,1,0) holds the first eleemnt of the second row
*/
template<typename T>
struct Triplet
{
	T elm;
	size_t listIdx;
	size_t elmIdx;

	Triplet(T e, size_t ldx, size_t eIdx) : elm(e), listIdx(ldx), elmIdx(eIdx) {}

	bool operator<(const Triplet &trp) const {
		return elm < trp.elm;
	}
	bool operator>(const Triplet &trp) const {
		return elm > trp.elm;
	}

};

template<typename T>
vector<T> mergeSortedLists(const vector<vector<T>> &vec)
{
	vector<T> ret;
	priority_queue<Triplet<T>, vector<Triplet<T>>, std::greater<Triplet<T>>> pq;
	// fill the queue with first elements of the lists
	// because the lists are presorted every inserted eleemnt is the smallest
	// in its list
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i].size() > 0) {
			pq.push({ vec[i][0], i, 0 });
		}
	}
	/*
	 select the smallest element of the queue
	 insert the element in the final result vector
	 update  the element index
	*/
	while (!pq.empty()) {
		Triplet<T> trp = pq.top();
		pq.pop();
		ret.push_back(trp.elm);
		while ((trp.elmIdx < vec[trp.listIdx].size() - 1) && (vec[trp.listIdx][trp.elmIdx + 1] == ret.back())) {
			ret.push_back(vec[trp.listIdx][trp.elmIdx + 1]);
			trp.elmIdx++;
		}
		if (trp.elmIdx < vec[trp.listIdx].size() - 1) {
			pq.push({ vec[trp.listIdx][trp.elmIdx + 1], trp.listIdx, trp.elmIdx + 1 });
		}
	}
	return ret;
}

int main()
{
	vector<vector<int>> v = { {1,3,5}, {2,4,6}, {3,5,7} };
	vector<int> res = mergeSortedLists(v);
	vector<int> combined = { 1,3,5,2,4,6,3,5,7 };
	std::sort(combined.begin(), combined.end());
	assert(res == combined);


	v = { {1,3,5,6}, {2,4,6,7}, {3,5,6,7} };
	res = mergeSortedLists(v);
	combined = { 1,3,5,6,2,4,6,7,3,5,6,7 };
	std::sort(combined.begin(), combined.end());
	assert(res == combined);

	v = { {10, 15, 30}, {12, 15, 20}, {17, 20, 32} };
	res = mergeSortedLists(v);
	combined = { 10, 12, 15, 15, 17, 20, 20, 30, 32 };
	std::sort(combined.begin(), combined.end());
	assert(res == combined);

	v = { {10, 15, 30}, {12, 15, 20, 21}, {17, 20, 32} };
	res = mergeSortedLists(v);
	combined = { 10, 12, 15, 15, 17, 20, 20, 21, 30, 32 };
	std::sort(combined.begin(), combined.end());
	assert(res == combined);

	v = { {10, 12}, {13, 15, 20, 21}, {17, 18, 19, 20, 32} };
	res = mergeSortedLists(v);
	combined = { 10,12,13,15,20,21,17,18,19,20,32 };
	std::sort(combined.begin(), combined.end());
	assert(res == combined);

	v = {  };
	res = mergeSortedLists(v);
	combined = {  };
	assert(res == combined);

	vector<vector<string>> vstr = { {"abc"}, {"adef"}, {"ccfgt"}, {"aaabb"} };
	vector<string> rstr = mergeSortedLists(vstr);
	vector<string> sexp = { "aaabb" , "abc", "adef", "ccfgt" };
	assert(rstr == sexp);

	vector<vector<char>> vcstr = { {'a', 'b', 'c'}, {'d', 'e' }, {'b', 'd', 'f'}, {'e','f','g','h'} };
	vector<char> cstr = mergeSortedLists(vcstr);
	vector<char> cexp = { 'a', 'b', 'c', 'd', 'e' , 'b', 'd', 'f','e','f','g','h' };
	std::sort(cexp.begin(), cexp.end());
	assert(cstr == cexp);

	cout << __FUNCTION__ << " ok\n";
	return 0;
}