struct LazySegmentTree {
    int n;
    vector<long long> tree, lazy;
    
    // Constructor: builds the segment tree from the initial array.
    LazySegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }
    
    // Build the segment tree.
    void build(const vector<long long>& arr, int node, int start, int end) {
        if(start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, node * 2, start, mid);
            build(arr, node * 2 + 1, mid + 1, end);
            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        }
    }
    
    // Update the range [l, r] by adding 'val' to each element.
    // (To subtract a value, call updateRange(l, r, -value).)
    void updateRange(int l, int r, long long val) {
        updateRangeUtil(1, 0, n - 1, l, r, val);
    }
    
    // Utility function to update range using lazy propagation.
    void updateRangeUtil(int node, int start, int end, int l, int r, long long val) {
        // If there's a pending update, apply it first.
        if(lazy[node] != 0) {
            tree[node] += lazy[node];
            if(start != end) { // not a leaf node
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        
        // No overlap.
        if(start > r || end < l)
            return;
        
        // Total overlap.
        if(start >= l && end <= r) {
            tree[node] += val;
            if(start != end) {
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }
        
        // Partial overlap.
        int mid = (start + end) / 2;
        updateRangeUtil(node * 2, start, mid, l, r, val);
        updateRangeUtil(node * 2 + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }
    
    // Query the minimum value in the range [l, r].
    long long queryRange(int l, int r) {
        return queryRangeUtil(1, 0, n - 1, l, r);
    }
    
    // Utility function for range query with lazy propagation.
    long long queryRangeUtil(int node, int start, int end, int l, int r) {
        if(start > r || end < l)
            return LLONG_MAX; // No overlap: return a value that will not affect the minimum.
        
        // If there's a pending update, apply it.
        if(lazy[node] != 0) {
            tree[node] += lazy[node];
            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        
        // Total overlap.
        if(start >= l && end <= r)
            return tree[node];
        
        // Partial overlap.
        int mid = (start + end) / 2;
        long long leftMin = queryRangeUtil(node * 2, start, mid, l, r);
        long long rightMin = queryRangeUtil(node * 2 + 1, mid + 1, end, l, r);
        return min(leftMin, rightMin);
    }
};

class Solution {
public:
    int minIncrements(int n, vector<int>& cost) {
        int maxHeigth = (int)log2(n+1);

        auto accumSumLeaves = new vector<long long>({cost[0]});
        auto nextLevel = new vector<long long>();

        int i = 1;
        for (int h = 1; h < maxHeigth; h++) {
            // int amountNodes = pow(2, h-1);
            nextLevel->clear();

            for (int j = 0; j < accumSumLeaves->size(); j++) {
                // left child
                nextLevel->push_back((*accumSumLeaves)[j] + cost[i++]);
                // right child
                nextLevel->push_back((*accumSumLeaves)[j] + cost[i++]);
            }

            auto tmp = accumSumLeaves;
            accumSumLeaves = nextLevel;
            nextLevel = tmp;
        }

        // get the maximum value
        auto it = max_element(accumSumLeaves->begin(), accumSumLeaves->end());

        // substract this value to each item of the vector
        int sub_val = *it;
        transform(accumSumLeaves->begin(), accumSumLeaves->end(), accumSumLeaves->begin(), [sub_val](int x) {
            return sub_val - x;
        });

        // build segment tree
        LazySegmentTree segTree(*accumSumLeaves);
        
        int increments = 0;

        int rangeSize = accumSumLeaves->size()/2;
        while (rangeSize > 0) {
            for (int j = 0, minIncrement; j < accumSumLeaves->size(); j += rangeSize) {
                minIncrement = segTree.queryRange(j, j + rangeSize-1);
                segTree.updateRange(j, j+rangeSize-1, -minIncrement);
                increments += minIncrement;
            }
            rangeSize /= 2;
        }

        return increments;
    }
};
