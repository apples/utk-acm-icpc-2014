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

struct Tile {
	int upper = 0;
	int lower = 0;
};

int main() {
	
	ifstream in ("multiply.in");
	
	string A;
	string B;
	
	vector<Tile> tiles;
	vector<int> left;
	vector<int> bottom;
	
	auto tileat = [&](int r, int c) -> Tile& {
		return tiles[r*A.size()+c];
	};
	
	while ((in >> A >> B) && A!="0") {
		tiles.clear();
		tiles.resize(A.size()*B.size());
		
		left.clear();
		left.resize(B.size(), 0);
		
		bottom.clear();
		bottom.resize(A.size(), 0);
		
		for (int r=0; r<B.size(); ++r) {
			for (int c=0; c<A.size(); ++c) {
				int prod = (A[c]-'0')*(B[r]-'0');
				auto& t = tileat(r,c);
				t.upper = prod/10;
				t.lower = prod%10;
			}
		}
		
		for (int i=A.size()-1; i>=0; --i) {
			int cc = 1;
			int rr = 0;
			for (int c=i, r=B.size()-1; c<A.size() && r>=0; c+=cc, r-=rr, swap(cc,rr)) {
				if (cc == 0) {
					bottom[i] += tileat(r,c).upper;
				} else {
					bottom[i] += tileat(r,c).lower;
				}
			}
			if (bottom[i]>=10) {
				if (i==0) {
					left[left.size()-1] += bottom[i]/10;
				} else {
					bottom[i-1] += bottom[i]/10;
				}
				bottom[i] %= 10;
			}
		}
		
		for (int i=B.size()-1; i>=0; --i) {
			int cc = 0;
			int rr = 1;
			for (int c=0, r=i; c<A.size() && r>=0; c+=cc, r-=rr, swap(cc,rr)) {
				if (cc == 0) {
					left[i] += tileat(r,c).upper;
				} else {
					left[i] += tileat(r,c).lower;
				}
			}
			if (left[i]>=10) {
				if (i!=0) {
					left[i-1] += left[i]/10;
				}
				left[i] %= 10;
			}
		}
		
		for (int& x : left) {
			if (x != 0) {
				break;
			}
			x = -1;
		}
		
		if (left.back() == -1) {
			for (int& x : bottom) {
				if (x != 0) {
					break;
				}
				x = -1;
			}
		}
		
		cout << "+" << string(3*(A.size()+1)+A.size(),'-') << "+" << endl;
		
		cout << "|";
		for (char c : A) {
			cout << string(3,' ') << c;
		}
		cout << "   |" << endl;
		
		bool slash = false;
		
		for (int i=0; i<B.size(); ++i) {
			cout << "| ";
			for (int j=0; j<A.size(); ++j) {
				cout << "+---";
			}
			cout << "+ |" << endl;
			if (slash) {
				cout << "|/";
			} else {
				cout << "| ";
			}
			for (int j=0; j<A.size(); ++j) {
				cout << "|" << tileat(i,j).upper << " /";
			}
			cout << "| |" << endl;
			cout << "| ";
			for (int j=0; j<A.size(); ++j) {
				cout << "| / ";
			}
			cout << "|" << B[i] << "|" << endl;
			if (left[i] == -1) {
				cout << "| ";
			} else {
				cout << "|" << left[i];
				slash = true;
			}
			for (int j=0; j<A.size(); ++j) {
				cout << "|/ " << tileat(i,j).lower;
			}
			cout << "| |" << endl;
		}
		
		cout << "| ";
		for (int j=0; j<A.size(); ++j) {
			cout << "+---";
		}
		cout << "+ |" << endl;
		
		cout << "|";
		for (int i=0; i<bottom.size(); ++i) {
			if (slash) {
				cout << "/ ";
			} else {
				cout << "  ";
			}
			if (bottom[i] != -1) {
				cout << bottom[i] << " ";
				slash = true;
			} else {
				cout << "  ";
			}
		}
		cout << "   |" << endl;
		
		cout << "+" << string(3*(A.size()+1)+A.size(),'-') << "+" << endl;
		
		
	}

}
