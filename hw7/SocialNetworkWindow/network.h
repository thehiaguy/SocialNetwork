#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "user.h"
#include "reactiontype.h"


class Network{
private:
    std::vector<User*> users_;
    std::vector<Post*> posts_;
public:
    
    //pre: none
    //post: empty netowrk object created
    Network();
    
    //pre:none 
    //post:Adds user to the network if not in network already
    void addUser(User* user);
    
    //pre: two users
    //post: Connection is created if it has not already been created and
    //returns 0 if successful and -1 if one or both users do not exist
    int addConnection(std::string s1, std::string s2);
    
    //pre: two users
    //post: Terminate the connection if they ar\e connected and
    //returns 0 if successful and -1 if one or both users do not exist 
    int deleteConnection(std::string s1, std::string s2);
    
    //pre: none 
    //post: returns the User's Id if it is found, if not return -1  
    int getId(std::string name);

    //pre: two valid Post pointers
    //post: returns true if the first post's messageId is less than the second post's messageId
    static bool comparePostsByMessageId(Post* a, Post* b);
    
    //pre: filename
    //post: users read are added to the network and returns 0 if successful else -1
    int readUsers(char* fname);
    
    //pre: filename
    //post: users are written into the file and returns 0 if successful else -1
    int writeUsers(char* fname);
    
    //pre: none 
    //post: returns the number of users
    int numUsers();
    
    //pre: id 
    //post: returns a pointer to the user if found, else nullptr
    User* getUser(int id);

    //pre: from is a valid id and to is also valid
    //post: returns the shortest path between two given valid ids
    std::vector<int>shortestPath(int from, int to);

    //pre: from is a valid friend id, distance is always positive
    //post: if a user exist at the distance given from from and it will
    //set to to the user's id and return the path from from to to
    //if not returns -1 and also an empty vector   
    std::vector<int> distanceUser(int from, int& to, int distance);

    //pre: who is a valid friend id
    //post: it returns a vector of ids for users with the highest number of common 
    //friends with users who and sets score to the number 
    //if no suggestions that exists it will return an empty vector and the set score as 0
    std::vector<int> suggestFriends(int who, int& score);
   
    //pre: none 
    //post: returns a vector of vectors where the inner vecotr has the IDs of users 
    //in the entire network 
    std::vector<std::vector<int>>groups();

    //pre: node is the user's id and visited tracks the visted nodes and component 
    // stores the current component
    //post: turns all the reachable nodes into visited and adds them into component
    void dfsHelper(int node, std::vector<bool>& visited, std::vector<int>&component);

    //pre:valid ownerId, message content, likes count , isIncoming flag, authoerName, and isPublic flag
    //post:creates and adds the appropriate type of post to the specified user
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool ispublic);

    //pre: valid ownerId, howMnay value, and showOnlyPublic flag
    //post: returns a formatted string containing the user's posts according to the parameters
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    //pre: valid filename as a character array 
    //post: reads posts from the file and ads them to the appropriate useres reutrns 0 if successful 
    //and -1 if file could not be opened
    int readPosts(char* fname);

    //pre: Valid filename as a character array
    //post: writes all posts from all users to the file in a specific format returns 0 if succesfful,
    //returns -1 iff file could not be opened
    int writePosts(char* fname);

    std::vector<Post*> getAllPosts();

    std::vector<Post*> getVisiblePosts(int userId);

    std::vector<User*> getUsersByReaction(int postId, std::string reactionType);

};

#endif //NETWORK_H
