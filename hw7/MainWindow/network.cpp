#include "network.h"

Network::Network(){}

void Network::addUser(User* user){
    //if user doesn't exist add to vector
    if (user){
        users_.push_back(user);
    }
}   

int Network::getId(std::string name){
    //loops through the users vector if current iterator value is name return ID
    for (int i = 0; i < users_.size(); i++){
        if(users_[i]->getName() == name){
            return users_[i]->getId();
        }
    }
    return -1;
}

bool Network::comparePostsByMessageId(Post* a, Post* b){
    return a->getMessageId() < b->getMessageId();
}

int Network::addConnection(std::string s1, std::string s2){
    //gets the id of the two users
    int user1 = getId(s1);
    int user2 = getId(s2);

    //checks if either or both users exists
    if (user1 == -1 || user2 == -1){
        return -1;
    }
    
    //add the users into each other's friends list
    users_[user1]->addFriend(user2);
    users_[user2]->addFriend(user1);

    return 0;
}

int Network::deleteConnection(std::string s1, std::string s2){
    //gets the id of the two users
    int user1 = getId(s1);
    int user2 = getId(s2);

    //checks if either or both users exists
    if (user1 == -1|| user2 == -1){
        return -1;
    }

    //removes the users from each other's friends lists
    users_[user1]->deleteFriend(user2);
    users_[user2]->deleteFriend(user1);

    return 0;
}

int Network::readUsers(char* fname){
    //opens file
    std::ifstream infile(fname);

    //if file fales to open 
    if(!infile.is_open()){
        return -1;
    }

    for (User* user : users_){
        delete user;
    }
    users_.clear();

    int num_users;
    infile >> num_users;
    infile.ignore();

    for (int i = 0; i < num_users; i++){
        int id;
        std::string name;
        int year, zip;
        std::set<int> friends;

        infile >> id;
        infile.ignore();

        std::string line;
        std::getline(infile, line);
        std::string tab = line;
        name = tab.substr(1);

        std::getline(infile, line);
        std::istringstream years1(line.substr(1));
        years1 >> year;
        
        std::getline(infile, line);
        std::istringstream zips1(line.substr(1));
        zips1 >> zip;

        std::getline(infile, line);
        std::istringstream friends1(line.substr(1));

        int friend_id;
        while (friends1 >> friend_id){
            friends.insert(friend_id);
        }

        User* user = new User(id, name, year, zip, friends);
        addUser(user);
    }
    
    infile.close();
    return 0;
}

int Network::writeUsers(char* fname){
    //opens file
    std::ofstream outfile(fname);
    if(!outfile.is_open()){
        return -1;
    }
    outfile << users_.size() << std::endl;
    for(User* user : users_){
        outfile << user->getId() << std::endl;
        outfile << "\t" << user->getName() << std::endl;
        outfile << "\t" << user->getYear() << std::endl;
        outfile << "\t" << user->getZip() << std::endl;

        outfile << "\t";
        const std::set<int>& friends = user->getFriends();
        for (int friend_id : friends){
            outfile << friend_id << " ";
        }
        outfile << std::endl;
    }
    
    outfile.close();
    return 0;
}

int Network::numUsers(){
    //returns the size of the vector
    return users_.size();
}

User* Network::getUser(int id){
    //returns the user
    if (id >= 0 && id < users_.size()) {
        return users_[id];
    }
    return nullptr;
}

std::vector<int>Network::shortestPath(int from, int to){
    //Checking if the origin and the desintiation ids are valid
    if (from <0 || from >=users_.size()||to <0 ||to>=users_.size()){
        return std::vector<int>();
    }

    //If the origin and the destination are the same return a path with just the node
    if (from==to){
        return std::vector<int>{from};
    }

    //queue for bfs 
    std::queue<int> q;
    //Create vector to track which nodes have been visited initialize to all false
    std::vector<int> visited(users_.size(), false);
    //ne vector to track the preivous node in the path, intialized to all -1
    std::vector<int> previous(users_.size(), -1);

    //makes the curr node visited
    visited[from] = true;
    //pops from the queue
    q.push(from);

    //when the q is empty
    while(!q.empty()){
        int current = q.front();
        q.pop();

        //Check all friends of the curr
        for (int neighbor: users_[current]->getFriends()){
            if(!visited[neighbor]){
                visited[neighbor]= true;
                previous[neighbor] = current;
                q.push(neighbor);

                //When the destination is found
                if (neighbor == to){
                    std::vector<int>path;
                    //start from the destination
                    int curr = to;
                    //go backwards through the previous nodes until we reach the origin 
                    while(curr != -1){
                        //add current node to path
                        path.push_back(curr);
                        //move to previous node in path
                        curr = previous[curr];
                    }
                    //reverse to get path of from origin to destination
                    std::reverse(path.begin(),path.end());
                    return path;
                }
            }
        }
    }
    //If goes through everything without finding a path
    return std::vector<int>();
}


std::vector<int> Network::distanceUser(int from, int& to, int distance){
    //initialize the parameter to -1
    to = -1;

    //Check if the form id is valid and distance is positive
    if (from <0 || from >=users_.size()|| distance<0){
        return std::vector<int>();
    }
    
    std::queue<int> q;
    std::vector<bool> visited(users_.size(),false);
    std::vector<int> previous(users_.size(),-1);
    std::vector<int>dist(users_.size(),-1);

    visited[from] = true;
    dist[from] = 0;
    q.push(from);

    while(!q.empty()){
        int current = q.front();
        q.pop();

        //checks all friends of curr
        for (int friend_id : users_[current]->getFriends()){
            if(!visited[friend_id]){
                visited[friend_id] = true;
                //set dist to 1 more than dist to curr
                dist[friend_id]= dist[current]+1;
                //to make sure taht we record that we got to this node from curr
                previous[friend_id] = current;
                q.push(friend_id);

                if (dist[friend_id]== distance){
                    to = friend_id;


                    std::vector<int> path;
                    int path_current = to;
                    while (path_current != -1){
                        path.push_back(path_current);
                        path_current = previous[path_current];
                    }

                    std::reverse(path.begin(),path.end());
                    return path;
                }
            }
        }
        

    }
    return std::vector<int>();
}

std::vector<int> Network::suggestFriends(int who, int& score){
    //initilize the score to 0
    score = 0;

    //Checks if the user Id is valid and if not returns empty vector
    if(who < 0|| who >=users_.size()){
        return std::vector<int>();
    }

    //Get the set of friends for the user we are finding suggestions for 
    const std::set<int>& friends = users_[who]->getFriends();

    //Create a map to count how many friends the suggestions have in common
    std::map<int,int>friend_incommon;

    //each friend of user
    for (int friend_id : friends){
        //friends of friends
        for (int potential : users_[friend_id]->getFriends()){
            //SKip if the suggestion is the user themselves or already a friend
            if (potential == who || friends.count(potential)>0){
                continue;
            }
            //Increment the count of common friends for the specific potential suggestion
            friend_incommon[potential]++;
        }
    }

    //Find the highest score/max mumber of common friends
    for (const auto& pair: friend_incommon){
        if (pair.second> score){
            score = pair.second;
        }
    }

    //If there are no suggestions found return an empty vector
    if (score == 0){
        return std::vector<int>();
    }

    // Create a vector to hold all the suggestions
    std::vector<int>suggestions;
    //Adding all the users who have the max score to the suggestion list
    for (const auto& pair: friend_incommon){
        if(pair.second == score){
            suggestions.push_back(pair.first);
        }
    }
    //Then return the list of suggested friends
    return suggestions;

}


void Network::dfsHelper(int node, std::vector<bool>& visited, std::vector<int>&component){
    //make the current node as visited
    visited[node] = true;
    //add current to component vector
    component.push_back(node);

    //For each friend of curr
    for (int neighbor : users_[node]->getFriends()){
        //IF the neighbor has not been visited yet
        if (!visited[neighbor]){
            //recursively call the neighbor
            dfsHelper(neighbor, visited, component);
        }
    }
}

std::vector<std::vector<int>>Network::groups(){
    //Create new vecotr to store every connected component
    std::vector<std::vector<int>> result;
    //Create new vecotr to track which nodes have been visited and initilize it as all false
    std::vector<bool> visited(users_.size(),false);

    //looping through every user in the network
    for (int i = 0; i<users_.size(); i++){
        //if curr is not visited
        if(!visited[i]){
            //Create a new component vetoir to store this connected component
            std::vector<int>component;
            //using dfs to find all the user in the specific component
            dfsHelper(i, visited, component);
            //add the completed componnent to result
            result.push_back(component);
        }
    }
    return result;
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){
    if (ownerId<0||ownerId>= users_.size()){
        return;
    }

    int messageId=0;
    for (User* user : users_){
        messageId+= user->getPosts().size();
    }

    Post* post = nullptr;

    if (isIncoming){
        post = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
    }
    else{
        post = new Post(messageId, ownerId, message, likes);
    }

    users_[ownerId]->addPost(post);
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic){
    if (ownerId<0 || ownerId >= users_.size()){
        return "";
    }
    return users_[ownerId]->getPostsString(howMany, showOnlyPublic);
}

int Network::readPosts(char* fname){
    std::ifstream infile(fname);

    if (!infile.is_open()) {
        return -1;
    }

    int num_posts;
    infile >> num_posts;
    infile.ignore();

    for (int i = 0; i < num_posts; i++) {
        int messageId;
        std::string message;
        int ownerId, likes;
        std::string line;
        bool isIncoming = false;
        bool isPublic = true;
        std::string author = "";

        infile >> messageId;
        infile.ignore();

        // Read message
        std::getline(infile, line);
        if (!line.empty() && line[0] == '\t') {
            message = line.substr(1);
        }
        
        // Read ownerId
        std::getline(infile, line);
        if (!line.empty() && line[0] == '\t') {
            std::istringstream ownerStream(line.substr(1));
            ownerStream >> ownerId;
        } else {
            ownerId = 0;
        }
        
        // Read likes
        std::getline(infile, line);
        if (!line.empty() && line[0] == '\t') {
            std::istringstream likesStream(line.substr(1));
            likesStream >> likes;
        } else {
            likes = 0;
        }
        
        // Read privacy status
        std::getline(infile, line);
        std::string privacyStr;
        if (!line.empty() && line[0] == '\t') {
            privacyStr = line.substr(1);
        }
        
        if (privacyStr == "public" || privacyStr == "private") {
            isIncoming = true;
            isPublic = (privacyStr == "public");
            
            // Read author
            std::getline(infile, line);
            if (!line.empty() && line[0] == '\t') {
                author = line.substr(1);
            }
        } else {
            // Skip the author line for owner posts
            std::getline(infile, line);
        }
        
        // Create and add the post
        if (ownerId >= 0 && ownerId < users_.size()) {
            Post* post = nullptr;
            if (isIncoming) {
                post = new IncomingPost(messageId, ownerId, message, likes, isPublic, author);
            } else {
                post = new Post(messageId, ownerId, message, likes);
            }
            users_[ownerId]->addPost(post);
        }
    }
    
    infile.close();
    return 0;

}

int Network::writePosts(char* fname){
    std::ofstream outfile(fname);

    if(!outfile.is_open()){
        return -1;
    }

    std::vector<Post*>allPosts;
    for(User* user : users_){
        std::vector<Post*> userPosts= user->getPosts();
        allPosts.insert(allPosts.end(), userPosts.begin(), userPosts.end());
    }

    std::sort(allPosts.begin(), allPosts.end(), comparePostsByMessageId);

    outfile << allPosts.size() << std::endl;

    for (Post* post : allPosts){
        outfile << post->getMessageId() <<std::endl;
        outfile << "\t" << post->getMessage() << std::endl;
        outfile << "\t" << post->getOwnerId() << std::endl;
        outfile << "\t" << post->getLikes() << std::endl;

        if(post->getAuthor() != ""){
            outfile << "\t" << (post->getIsPublic() ? "public" : "private") << std::endl;
            outfile << "\t" << post->getAuthor() << std::endl;
        }
        else{
            outfile <<"\t" << std::endl;
            outfile <<"\t" << std::endl;
        }
    }

    outfile.close();
    return 0;
}
