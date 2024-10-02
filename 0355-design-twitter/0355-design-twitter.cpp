class Twitter {
public:
    vector<unordered_set<int>> followersList;
    unordered_map<int,vector<pair<int,int>>> tweet;
    int time;
    Twitter() {
        time = 0;
        followersList.resize(501);
    }
    
    void postTweet(int userId, int tweetId) {
        time++;
        tweet[userId].push_back({time , tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(auto i : tweet[userId]){
            pq.push({i.first,i.second});
            if(pq.size() > 10) pq.pop();
        }
        for(int follower : followersList[userId]){
            for(auto i : tweet[follower]){
                pq.push({i.first,i.second});
                if(pq.size() > 10) pq.pop();
            }
        }
        while(!pq.empty()){
            res.push_back(pq.top().second);
            pq.pop();
        }
        reverse(res.begin(),res.end());
        return res;

    }
    
    void follow(int followerId, int followeeId) {
        followersList[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if(followersList[followerId].find(followeeId) != followersList[followerId].end()){
            followersList[followerId].erase(followeeId);
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */