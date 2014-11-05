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

struct Loc {
	int r;
	int c;
};

Loc operator+(Loc const& l1, Loc const& l2) {
	return Loc{l1.r+l2.r,l1.c+l2.c};
}

bool operator!=(Loc const& l1, Loc const& l2) {
	return tie(l1.r,l1.c)!=tie(l2.r,l2.c);
}

Loc reflect(Loc l, char c) {
	switch (c) {
		case '\\': {
			swap(l.r,l.c);
		} break;
		case '/': {
			swap(l.r,l.c);
			l.r *= -1;
			l.c *= -1;
		} break;
		case '.': {
		} break;
		case 'x': {
			l.r = 0;
			l.c = 0;
		} break;
	}
	return l;
}

int main() {
	int W;
	int L;
	
	ifstream in ("fun.in");
	
	vector<string> strs;
	
	int counter = 0;
	
	while ((in >> W >> L) && W>0) {
		++counter;
	
		strs.resize(L);
		for (int i=0; i<L; ++i) {
			in >> strs[i];
		}
		
		Loc pos;
		
		for (int i=0; i<strs.size(); ++i) {
			auto& s = strs[i];
			auto iter = find(begin(s),end(s),'*');
			if (iter != end(s)) {
				pos.r = i;
				pos.c = iter-begin(s);
			}
		}
		
		Loc dir;
		
		if (pos.r == 0) {
			dir = Loc{1,0};
		} else if (pos.c == 0) {
			dir = Loc{0,1};
		} else if (pos.r == strs.size()-1) {
			dir = Loc{-1,0};
		} else {
			dir = Loc{0,-1};
		}
		
		while ((pos = pos+dir), (dir = reflect(dir,strs[pos.r][pos.c])), (dir != Loc{0,0})) {
			// NOTHING!
		}
		
		strs[pos.r][pos.c] = '&';
		
		cout << "HOUSE " << counter << endl;
		for (auto& s : strs) {
			cout << s << endl;
		}
	}
}
