struct Task{
    int user;
    int id;
    int priority;
};

struct taskComp{
    bool operator()(Task const &a, Task const &b) const{
        if(a.priority != b.priority) return a.priority>b.priority;//first high priority
        return a.id > b.id;// tie: first larger taskId 
    } 
};

class TaskManager {
private:
    unordered_map<int, pair<int, int>> map;  //Map: {taskId -> userId, priority}
    set<Task, taskComp> st; //stores all the active tasks
public:
    TaskManager(vector<vector<int>>& tasks) {
        map.reserve(tasks.size()*2);
        for(auto& t : tasks){
            int u = t[0], id = t[1], p = t[2];
            map[id] = {u, p};
            st.insert(Task{u, id, p});
        }
    }
    
    void add(int userId, int taskId, int priority) {
        map[taskId] = {userId, priority};
        st.insert(Task{userId, taskId, priority});
    }
    
    void edit(int taskId, int newPriority) {
        auto editTask = map.find(taskId);
        if(editTask == map.end()) return;
        int u = editTask->second.first;
        int oldP = editTask->second.second;

        st.erase(Task{u, taskId, oldP});
        st.insert(Task{u, taskId, newPriority});

        editTask->second.second = newPriority;
    }
    
    void rmv(int taskId) {
        auto rmvTask = map.find(taskId);
        if(rmvTask == map.end()) return;

        int u = rmvTask->second.first;
        int p = rmvTask->second.second;

        st.erase(Task{u,taskId, p});
        map.erase(rmvTask);
    }
    
    int execTop() {
        if(st.empty()) return -1;
        auto exeTask = st.begin();
        Task t = *exeTask;
        st.erase(exeTask);
        map.erase(t.id);
        return t.user;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */
