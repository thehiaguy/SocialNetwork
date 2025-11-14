#ifndef POST_H
#define POST_H

#include <string>
#include<set>
#include<map>

class Post{
private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;
    std::map<std::string ,std::set<int>> reactions_;
public:
    //pre: none 
    //post: Creates an empty Post with defaul values 
    Post();

    //pre: Valid messageId, ownerId, message content, and number of lieks 
    //post: Creates a Post with the specified parameters
    Post(int messageId, int ownerId,std::string message , int likes);

    //pre: none 
    //post: Returns a string representation of the post in the format "message + Liked by X people"
    virtual std::string toString();

    //pre: none 
    //post: returns the unieque message ID of the post
    int getMessageId();

    //pre: none 
    //post: Returns the owner ID of the post 
    int getOwnerId();

    //pre: none 
    //post: Returns the mesage content of the post 
    std::string getMessage();

    //pre: none 
    //post: Returns the number of likes the post has recieved
    int getLikes();

    //pre: none 
    //post: Returns the author of the post 
    virtual std::string getAuthor();

    //pre: none 
    //post: Returns whether the post is public 
    virtual bool getIsPublic();

    void addReaction(int userId, std::string reactionType);

    void removeReaction(int userId, std::string reactionType);

    int getReactionCount(std::string reactionType);

    std::string getUserReaction(int userId);

    const std::set<int> & getUsersWithReaction(std::string reactionType) const;

};

class IncomingPost : public Post{
private: 
    std::string author_;
    bool isPublic_;

public:
    
    //pre: none 
    //post: Creates an empty IncomingPost with default values and empty author, set as public
    IncomingPost();

    //pre: Valid messageId, ownerId, mesage content, likes count, visibility status, and authoer name
    //post: Creates an IncomingPost with the specified parameters
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    //pre: none 
    //post: Returns a string representation of the post including aitho name and privacy status
    std::string toString() override;

    //pre: none 
    //post: Returns the name of the author of the post
    std::string getAuthor() override;

    //pre: none 
    //post: returns whether the post is public or private
    bool getIsPublic() override;


};


#endif//POST_H
