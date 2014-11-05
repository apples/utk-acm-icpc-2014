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
	int wetness = 0;
};

struct Loc {
	int r;
	int c;
};

int main() {
	
	int X;
	int Y;
	int T;
	int L;
	int W;
	
	ifstream in ("wet.in");
	
	vector<Tile> tiles;
	
	auto tileat = [&](int r, int c) -> Tile& {
		return tiles[r*X+c];
	};
	
	function<void(Loc,int)> go = [&](Loc loc, int depth){
		if (loc.r<0 || loc.r>=Y || loc.c<0 || loc.c>=X) {
			return;
		}
	
		auto& tile = tileat(loc.r,loc.c);
		if (tile.wetness < 0) {
			return;
		}
		
		if (tile.wetness >= depth) {
			return;
		}
		
		tile.wetness = depth;
		
		go(Loc{loc.r-1,loc.c}, depth-1);
		go(Loc{loc.r+1,loc.c}, depth-1);
		go(Loc{loc.r,loc.c-1}, depth-1);
		go(Loc{loc.r,loc.c+1}, depth-1);
	};
	
	while ((in >> X >> Y >> T >> L >> W) && X!=-1) {
		tiles.clear();
		tiles.resize(X*Y);
		
		int r;
		int c;
		
		vector<Loc> locs;
		
		for (int i=0; i<L; ++i) {
			in >> c >> r;
			--r;
			--c;
			locs.push_back(Loc{r,c});
		}
		
		int rr;
		int cc;
		
		for (int i=0; i<W; ++i) {
			in >> c >> r >> cc >> rr;
			--c;
			--r;
			--cc;
			--rr;
			int ci = 0;
			int ri = 0;
			
			if (c<cc) {
				ci = 1;
			} else if (cc<c) {
				ci = -1;
			}
			
			if (r<rr) {
				ri = 1;
			} else if (rr<r) {
				ri = -1;
			}
			
			for (; c!=cc && r!=rr; c+=ci, r+=ri) {
				tileat(r,c).wetness = -7777;
			}
			tileat(rr,cc).wetness = -7777;
		}
		
		for (auto loc : locs) {
			go(loc,T);
		}
		
		auto is_wet = [](Tile const& tile){
			return tile.wetness > 0;
		};
		
		auto result = count_if(begin(tiles),end(tiles),is_wet);
		
		cout << result << endl;
		
		for (int r=0; r<Y; ++r) {
			for (int c=0; c<X; ++c) {
				cout << tileat(r,c).wetness << ",";
			}
			cout << endl;
		}
	}

}
