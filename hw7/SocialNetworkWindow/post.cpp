#include "post.h"

//Default constructor for Post class
Post::Post(): messageId_(0), ownerId_(0), message_(""), likes_(0){}

//Parameterized constructor for Post class
Post::Post(int messageId, int ownerId, std::string message, int likes)
    : messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes) {}

//Converst the post to a readable string format
//Returns the post message followed by tyhe number of likes
std::string Post::toString(){
    return message_ + " Liked by " + std::to_string(likes_) + " people.";
}

int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}

std::string Post::getMessage(){
    return message_;
}

int Post::getLikes(){
    return getReactionCount("Like");
}

std::string Post:: getAuthor(){
    return "";
}

bool Post::getIsPublic(){
    return true;
}

//Default constructor for IncomingPost class
IncomingPost::IncomingPost() : Post(), author_(""), isPublic_(true){}

//Parameterized constrtuctor for IncomingPost class

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author)
    : Post(messageId, ownerId, message, likes), author_(author), isPublic_(isPublic) {}

//Overrides the toString method to include author information
//FOrmats the post to show who wrote it and see if it is private
std::string IncomingPost::toString(){
    std::string ayo = isPublic_ ? "" : " (private)";
    return author_ +   " wrote" + ayo + ": " + Post::toString();
}

//Overrides the getAuthor method to reutnr the actual author name
std::string IncomingPost::getAuthor(){
    return author_;
}

//Overrides the getisPublic method to reutnr the post's privacy setting
bool IncomingPost::getIsPublic() {
    return isPublic_;
}

void Post::addReaction (int userId, std::string reactionType){
    for (auto& pair: reactions_){
        pair.second.erase(userId);
    }
    reactions_[reactionType].insert(userId);
}

void Post::removeReaction(int userId, std::string reactionType){
    reactions_[reactionType].erase (userId);
}

std::string Post::getUserReaction(int userId){
    for (const auto& pair: reactions_){
        if(pair.second.count(userId)>0){
            return pair.first;
        }
    }
    return "";
}

const std::set<int>& Post::getUsersWithReaction(std::string reactionType) const{
    static std::set<int> empty;
    auto it = reactions_.find(reactionType);
    return (it != reactions_.end()) ? it->second : empty;
}

int Post::getReactionCount(std::string reactionType) {
    auto it = reactions_.find(reactionType);
    if (it != reactions_.end()) {
        return it->second.size();
    }
    return 0;
}
