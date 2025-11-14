#include "user.h"

//Default constructor for User class
User::User():id_(-1), name_(""), year_(0),zip_(0)  {}

//Constructor with basic user information with empty friends list
User::User(int id, std::string name, int year, int zip)
:id_(id), name_(name), year_(year), zip_(zip) {}

//Constructor with all user  information including friends list
User::User(int id, std::string name, int year, int zip, std::set<int>friends)
:id_(id), name_(name), year_(year), zip_(zip), friends_(friends) {}

//Adds a friend to this user's friends list 
//puts the given ID into the friends list
void User::addFriend(int id){
    friends_.insert(id);        
}

//Removes a friend from this user's friends list
//removes the give ID from the friends list 
void User::deleteFriend(int id){
    friends_.erase(id);
}


int User::getId(){
    return id_;
}

std::string User::getName(){
    return name_;
}

int User::getYear(){
    return year_;
}

int User::getZip(){
    return zip_;
}

const std::set<int>& User::getFriends() const{
    return friends_;
}

std::set<int>& User::getFriends(){
    return friends_;
}

//Adds a post to this user's messages 
// stores the post pointer in the user's mesages vector
void User::addPost(Post* post){
    messages_.push_back(post);
}

//Returns all posts by this user
// returns the vecotr with all the post pointers
std::vector<Post*> User::getPosts(){
    return messages_;
}

//Gets a formatted string ocntainng recent posts
//
std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string result = "";
    int count = 0;

    //Loop through posts from the newest post first
    for (int i = messages_.size() -1; i>=0 && count < howMany; i--){
        //check if should include this post according to the privacy setting
        if (!showOnlyPublic|| messages_[i]->getIsPublic()){
            //Add spaces between posts
            if (count > 0 ){
                result += "\n\n";
            }
            //ADD THE FORMATTED POST STRING
            result += messages_[i]->toString();
            count++;
        }
    }

    return result;
}

