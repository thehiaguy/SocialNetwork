#ifndef REACTIONTYPE_H
#define REACTIONTYPE_H

#include <string>
#include <vector>

class ReactionType{
private:
    std::string id_;
    std::string emoji_;
    std::string label_;
public:
    ReactionType();
    ReactionType(std::string id, std::string emoji, std::string label);

    std::string getId() const;
    std::string getEmoji() const;
    std::string getLabel() const;

    static std::vector<ReactionType> getAllReactionTypes();
    static ReactionType getById(std::string id);

    static const ReactionType LIKE;
    static const ReactionType LOVE;
    static const ReactionType LAUGH;
    static const ReactionType WOW;
    static const ReactionType SAD;


};

#endif // REACTIONTYPE_H
