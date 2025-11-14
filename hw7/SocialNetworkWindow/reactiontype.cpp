#include "reactiontype.h"


const ReactionType ReactionType::LIKE("like","👍","Like");
const ReactionType ReactionType::LOVE("love","❤️","Love");
const ReactionType ReactionType::LAUGH("laugh","😂","Laugh");
const ReactionType ReactionType::WOW("wow","😱","Wow");
const ReactionType ReactionType::SAD("sad","😢","Sad");

ReactionType::ReactionType() : id_(""), emoji_(""), label_("") {}

ReactionType::ReactionType(std::string id, std::string emoji, std::string label): id_(id), emoji_(emoji), label_(label) {}

std::string ReactionType::getId() const {
    return id_;
}

std::string ReactionType::getEmoji() const{
    return emoji_;
}

std::string ReactionType::getLabel() const{
    return label_;
}

std::vector<ReactionType> ReactionType::getAllReactionTypes() {
    return {LIKE, LOVE, LAUGH, WOW, SAD};
}


ReactionType ReactionType::getById(std::string id){
    std::vector<ReactionType> types = getAllReactionTypes();
    for ( const ReactionType& type : types){
        if (type.getId()==id){
            return type;
        }
    }
    return ReactionType();
}
