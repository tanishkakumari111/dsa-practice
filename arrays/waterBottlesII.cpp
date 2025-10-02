class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int drunk = numBottles;
        int empty = numBottles;
        while(empty >= numExchange){
            empty++;
            drunk++;
            empty = empty - numExchange;
            numExchange++;
        }
        return drunk;
    }
};
