class Solution {
private:
    bool aux(vector<vector<int>>& matrix, int target, int startR, int endR, int startC, int endC) {
        if (startR > endR || startC > endC)
            return false;
        if (!(matrix[startR][startC] <= target && target <= matrix[endR][endC]))
            return false;
        if (startR == endR && startC == endC)
            return matrix[startR][startC] == target;
        
        int midR = startR + (endR-startR)/2;
        int midC = startC + (endC-startC)/2;

        if (matrix[midR][midC] == target)
            return true;
        
        if (matrix[midR][midC] < target) {
            // startR - midR, midC+1 endC
            if (aux(matrix, target, startR, midR, midC+1, endC))
                return true;
            // midR+1 - endR, midC+1 endC
            if (aux(matrix, target, midR+1, endR, midC+1, endC))
                return true;
            // midR+1 - endR, startC - midC
            if (aux(matrix, target, midR+1, endR, startC, midC))
                return true;
        }
        else {
            // midR - endR, startC - midC-1
            if (aux(matrix, target, midR, endR, startC, midC-1))
                return true;
            // startR - midR-1, startC - midC-1
            if (aux(matrix, target, startR, midR-1, startC, midC-1))
                return true;
            // startR - midR-1, midC - endC
            if (aux(matrix, target, startR, midR-1, midC, endC))
                return true;
        }
        return false;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        return aux(matrix, target, 0, matrix.size()-1, 0, matrix[0].size()-1);
    }
};