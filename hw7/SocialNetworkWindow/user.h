#ifndef USER_H
#define USER_H

#include<string>
#include<set>
#include<vector>
#include "post.h"

class User{
private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
    std::vector<Post*> messages_;

public:
    
    //pre: none
    //post: creates an empty User
    User();

    User(int id, std::string name, int year, int zip);
    
    //pre: id , name, zip, year and friend set 
    //post: A User object is created with the parameters 
    User(int id_, std::string name_, int year_, int zip_, std::set<int> friends_);
    
    //pre: id to add as friend
    //post: Friend is added to the User's friends list 
    void addFriend(int id);
    
    //pre: need an existing id to remove friend
    //post: friend gets removed from the user's friends list
    void deleteFriend(int id);
    
    //pre: none 
    //post: returns the user's id
    int getId();
    
    //pre: none 
    //post: return's the user's name 
    std::string getName();
    
    //pre: none 
    //post: return's the user's year 
    int getYear();
    
    //pre: none 
    //post: return's the user's zipcode
    int getZip();
    
    //pre: none 
    //post: return's reference to the user's friends set
    const std::set<int>& getFriends() const;

    //pre: none 
    //post: return's reference to the user's friends set
    std::set<int>& getFriends();

    //pre: Valid Post pointer that is not null
    //post: Adds the post to the user's messages vector
    void addPost(Post* post);

    //pre: none 
    //post: Returns a vector containing pointer to all posts owned by this user
    std::vector<Post*> getPosts();

    //pre: Valid howMany value
    //post:Returns a formatted string containing the most recent posts If showOnlyPublic is true, only public posts will be included
    std::string getPostsString(int howMany, bool showOnlyPublic);
};

#endif //USER_H