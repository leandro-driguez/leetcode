class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<double, int>> _kClosest;
        for (int i=0, x, y; i<points.size();i++){
            x = points[i][0];
            y = points[i][1];
            double dist = sqrt(pow(x, 2) + pow(y, 2));
            if (_kClosest.size() < k) {
                _kClosest.push({dist, i});
            }
            else if (_kClosest.top().first > dist) {
                _kClosest.pop();
                _kClosest.push({dist, i});
            }
        }

        vector<vector<int>> ans;
        while(_kClosest.size() > 0) {
            ans.push_back(points[_kClosest.top().second]);
            _kClosest.pop();
        }
        return ans;
    }
};