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
	
	int N;
	string str;
	
	ifstream in ("rot.in");
	
	while ((in >> N >> str) && N!=0) {
		reverse(begin(str),end(str));
		for (char& c : str) {
			if (c == '.') {
				c = '\\';
			} else if (c == '_') {
				c = '[';
			}
			c = (((c-'A')+N)%(28))+'A';
			if (c == '\\') {
				c = '.';
			} else if (c == '[') {
				c = '_';
			}
		}
		cout << str << endl;
	}

}
