struct Comp {
    // Sort by rating desc, then name asc
    bool operator()(const pair<int,string>& a, const pair<int,string>& b) const {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    }
};

class FoodRatings {
private:
    unordered_map<string, pair<string,int>> food_info; // food -> (cuisine, rating)
    unordered_map<string, set<pair<int,string>, Comp>> cuisine_set; // cuisine -> set of (rating, food)

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; ++i) {
            food_info[foods[i]] = {cuisines[i], ratings[i]};
            cuisine_set[cuisines[i]].insert({ratings[i], foods[i]});
        }
    }

    void changeRating(string food, int newRating) {
        auto &info = food_info[food];
        string cuisine = info.first;
        int oldRating = info.second;
        // Erase old entry and insert new one
        cuisine_set[cuisine].erase({oldRating, food});
        cuisine_set[cuisine].insert({newRating, food});
        // Update stored rating
        info.second = newRating;
    }

    string highestRated(string cuisine) {
        // set is sorted by rating desc then name asc; begin() is highest
        auto &s = cuisine_set[cuisine];
        return s.begin()->second;
    }
};
