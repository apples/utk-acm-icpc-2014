#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

int main() {
	ifstream in ("lex.in");
	
	string str;
	int N;
	while ((in >> str >> N) && str != "#") {
		sort(begin(str),end(str));
		for (int i=0; i<str.size(); ++i) {
			swap(str[N/(str.size()-1 + i)], str[i]);
			sort(begin(str)+i, end(str));
		}
		cout << str << endl;
	}
}
