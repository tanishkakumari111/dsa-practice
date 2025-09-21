struct Comp {
    // sort by price ascending, then shop ascending
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    }
};

class MovieRentingSystem {
    // cost[shop][movie] = price
    unordered_map<int, unordered_map<int,int>> cost;

    // for each movie → set of (shop, price) that currently have it unrented
    unordered_map<int, set<pair<int,int>, Comp>> unrented;

    // all rented movies: (shop, movie, price)
    set<tuple<int,int,int>> rented; 
    // tuple used because we want (price, shop, movie) ordering easily

public:
    MovieRentingSystem(int nShops, vector<vector<int>>& entries) {
        for (auto &e : entries) {
            int shop=e[0], movie=e[1], price=e[2];
            cost[shop][movie] = price;
            unrented[movie].insert({shop,price});
        }
    }

    vector<int> search(int movie) {
        vector<int> res;
        auto it = unrented.find(movie);
        if (it == unrented.end()) return res;

        int cnt=0;
        for (auto &p : it->second) {
            res.push_back(p.first); // shop
            if (++cnt==5) break;
        }
        return res;
    }

    void rent(int shop, int movie) {
        int price = cost[shop][movie];
        unrented[movie].erase({shop,price});
        rented.insert({price,shop,movie}); // note tuple (price,shop,movie)
    }

    void drop(int shop, int movie) {
        int price = cost[shop][movie];
        rented.erase({price,shop,movie});
        unrented[movie].insert({shop,price});
    }

    vector<vector<int>> report() {
        vector<vector<int>> ans;
        int cnt=0;
        for (auto &t : rented) {
            auto [price,shop,movie] = t;
            ans.push_back({shop,movie});
            if (++cnt==5) break;
        }
        return ans;
    }
};


/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
