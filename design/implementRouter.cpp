class Router {
private: 
    int MaxSize;
    unordered_map<string, vector<int>> pktStore; // [key] -> (S, D, T)
    unordered_map<int, vector<int>> destTimeMap; // [dest] -> T1, T2, T3...
    queue<string> q;
public:
    Router(int memoryLimit) {
        MaxSize = memoryLimit;
    }
    
    string makeKey(int source, int destination, int timestamp){
        return to_string(source) + '_' + to_string(destination) + '_' + to_string(timestamp);
    }

    bool addPacket(int source, int destination, int timestamp) {
        string key = makeKey(source, destination, timestamp);
        
        if(pktStore.find(key) != pktStore.end()) return false;
        if(q.size()==MaxSize) forwardPacket();

        pktStore[key] = {source, destination, timestamp};
        q.push(key);
        destTimeMap[destination].push_back(timestamp);

        return true; 
    }
    
    vector<int> forwardPacket() {
        if(pktStore.empty()) return {};
        string key = q.front();
        q.pop();

        vector<int> pktInfo = pktStore[key];
        pktStore.erase(key);

        int dest = pktInfo[1];
        destTimeMap[dest].erase(destTimeMap[dest].begin());

        return pktInfo;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        auto it = destTimeMap.find(destination);

        if(it==destTimeMap.end() || it->second.empty()) return 0;

        vector<int> &timeStamps = it->second;
        int i = lower_bound(begin(timeStamps), end(timeStamps), startTime) - begin(timeStamps);
        int j = upper_bound(begin(timeStamps), end(timeStamps), endTime) - begin(timeStamps);

        return j-i;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */
