class Solution {
 public:
  bool pyramidTransition(string bottom, vector<string>& allowed) {
    for (const string& a : allowed)
      mp[a.substr(0, 2)].push_back(a[2]);

    return dfs(bottom);
  }

 private:
  unordered_map<string, vector<char>> mp;
  unordered_set<string> bad; // memo for impossible rows

  bool dfs(const string& row) {
    if (row.length() == 1)
      return true;

    if (bad.count(row))
      return false;

    vector<string> nextRows;
    buildNextRows(row, 0, "", nextRows);

    for (const string& next : nextRows)
      if (dfs(next))
        return true;

    bad.insert(row);
    return false;
  }

  void buildNextRows(const string& row, int i, string cur,
                     vector<string>& res) {
    if (i + 1 == row.length()) {
      res.push_back(cur);
      return;
    }

    string key = row.substr(i, 2);
    if (!mp.count(key))
      return;

    for (char c : mp[key])
      buildNextRows(row, i + 1, cur + c, res);
  }
};
