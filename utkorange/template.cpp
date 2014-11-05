#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
	int W;
	int L;
	
	vector<string> strs;
	
	while ((cin >> W >> L) && W>0) {
		strs.resize(L);
		for (int i=0; i<L; ++i) {
			cin >> strs[i];
			cout << strs[i];
		}
	}
}
