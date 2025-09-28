class DetectSquares {
private: 
    unordered_map<int, unordered_map<int, int>> countMap; //(x, y): x -> (y -> cnt)
public:
    DetectSquares() {}
    
    void add(vector<int> point) {
        int x = point[0];
        int y = point[1];
        countMap[x][y] += 1;
    }
    
    int count(vector<int> point) {
        int x1 = point[0];
        int y1 = point[1];
        if(countMap.find(x1) == countMap.end()) return 0;

        int total = 0;

        for(auto &p : countMap[x1]){
            int y2 = p.first;
            int c1 = p.second;

            if(y1 == y2) continue; //skip as same point

            //square side length
            int side = y2 - y1;

            int xA = x1 + side;
            int xB = x1-side;

            //for xA
            if(countMap.find(xA) != countMap.end()){
                int c2 = countMap[xA].count(y1) ? countMap[xA][y1]: 0;
                int c3 = countMap[xA].count(y2) ? countMap[xA][y2] : 0;
                total += c1*c2*c3;
            }
            //for xA
            if(countMap.find(xB) != countMap.end()){
                int c2 = countMap[xB].count(y1) ? countMap[xB][y1] : 0;
                int c3 = countMap[xB].count(y2) ? countMap[xB][y2] : 0;
                total += c1*c2*c3;
            }
        }
        return total;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
