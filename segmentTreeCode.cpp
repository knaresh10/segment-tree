#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
	vector<int> seq;

public:
	SegmentTree(int n) {
		seq.resize(4 * n, INT_MAX);
	}

	void build(int ind, int low, int high, vector<int> &arr) {

		// base case
		if (low == high) {
			seq[ind] = arr[low];
			return ;
		}

		int mid = low + (high - low) / 2;

		// build the leftSubTree
		build(2 * ind + 1, low , mid, arr);
		// build the rightSubTree
		build(2 * ind + 2, mid + 1, high, arr);

		seq[ind] = min(seq[2 * ind + 1], seq[2 * ind + 2]);
		return ;
	}

	int query(int ind, int low, int high, int l, int r) {

		// complete overlap case
		if (l <= low  && high <= r) return seq[ind];

		// no overlap case
		if (r < low or high < l) return INT_MAX;

		// partial overlap case
		int mid = low + (high - low) / 2;

		int leftValue = query(2 * ind + 1, low, mid, l, r);
		int rightValue = query(2 * ind + 2, mid + 1, high, l, r);

		return min(leftValue, rightValue);
	}

	void update(int ind, int low, int high, int reqInd, int val) {
		// base case
		if (low == high) {
			seq[ind] = val;
			return ;
		}

		int mid = low + (high - low) / 2;

		// if reqInd is leftSubTree else rightSubTree
		if (reqInd <= mid) {
			update(2 * ind + 1, low, mid, reqInd, val);
		} else {
			update(2 * ind + 2, mid + 1, high, reqInd, val);
		}

		// update the index
		seq[ind] = min(seq[2 * ind + 1], seq[2 * ind + 2]);
		return ;
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];
	SegmentTree obj = SegmentTree(n);
	obj.build(0, 0, n - 1, arr);

	int queryLen;
	cin >> queryLen;
	for (int i = 0; i < queryLen; i++) {
		int type;
		cin >> type;
		if (type == 0) {
			int l, r;
			cin >> l >> r;
			cout << obj.query(0, 0, n - 1, l, r) << "\n";
		}
		else {
			int ind, val;
			cin >> ind >> val;
			obj.update(0, 0, n - 1, ind, val);
		}
	}
}

