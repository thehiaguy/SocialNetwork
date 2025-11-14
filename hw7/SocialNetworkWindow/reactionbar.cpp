#include "reactionbar.h"
#include "reactiontype.h"
#include "network.h"
#include <QHBoxLayout>
#include <QPushButton>

ReactionBar::ReactionBar(Post* post, int currentUserId, QWidget* parent, Network* network)
    : QWidget(parent), post_(post), currentUserId_(currentUserId), network_(network) {

    layout_ = new QHBoxLayout(this);

    std::vector<ReactionType> types = ReactionType::getAllReactionTypes();


    for (const ReactionType& type : types) {

        // Create reaction button
        QPushButton* button = new QPushButton(QString::fromStdString(type.getEmoji()));
        button->setObjectName(QString::fromStdString(type.getId()));
        button->setFixedSize(40, 30);
        button->setToolTip(QString::fromStdString("React with " + type.getLabel()));

        // FIXED: Connect each button individually to the correct slot
        std::string typeId = type.getId();
        if (typeId == "like") {
            connect(button, &QPushButton::clicked, this, &ReactionBar::onLikeClicked);
        } else if (typeId == "love") {
            connect(button, &QPushButton::clicked, this, &ReactionBar::onLoveClicked);
        } else if (typeId == "laugh") {
            connect(button, &QPushButton::clicked, this, &ReactionBar::onLaughClicked);
        } else if (typeId == "wow") {
            connect(button, &QPushButton::clicked, this, &ReactionBar::onWowClicked);
        } else if (typeId == "sad") {
            connect(button, &QPushButton::clicked, this, &ReactionBar::onSadClicked);
        }

        reactionButtons_[type.getId()] = button;
        layout_->addWidget(button);

        // Create count button
        QPushButton* countButton = new QPushButton("0");
        countButton->setObjectName(QString::fromStdString(type.getId()));
        countButton->setFlat(true);
        countButton->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background: transparent;"
            "   color: gray;"
            "   font-size: 12px;"
            "   min-width: 20px;"
            "   padding: 2px;"
            "}"
            "QPushButton:hover {"
            "   background-color: lightgray;"
            "   border-radius: 3px;"
            "}"
            );
        countButton->setToolTip("Click to see who reacted");
        connect(countButton, &QPushButton::clicked, this, &ReactionBar::onReactionCountButtonClicked);
        reactionCountButtons_[type.getId()] = countButton;
        layout_->addWidget(countButton);
    }

    updateDisplay();
}

void ReactionBar::updateDisplay() {
    std::vector<ReactionType> types = ReactionType::getAllReactionTypes();
    for (const ReactionType& type : types) {
        int count = post_->getReactionCount(type.getId());
        reactionCountButtons_[type.getId()]->setText(QString::number(count));

        std::string userReaction = post_->getUserReaction(currentUserId_);
        if (userReaction == type.getId()) {
            reactionButtons_[type.getId()]->setStyleSheet(
                "QPushButton {"
                "   background-color: lightblue;"
                "   border: 2px solid blue;"
                "   border-radius: 5px;"
                "}"
                );
        } else {
            reactionButtons_[type.getId()]->setStyleSheet(
                "QPushButton {"
                "   border: 1px solid #ccc;"
                "   border-radius: 5px;"
                "   background-color: #f9f9f9;"
                "}"
                "QPushButton:hover {"
                "   background-color: #e9e9e9;"
                "}"
                );
        }

        if (count > 0) {
            reactionCountButtons_[type.getId()]->show();
            reactionCountButtons_[type.getId()]->setEnabled(true);
        } else {
            reactionCountButtons_[type.getId()]->hide();
        }
    }
}


void ReactionBar::onLikeClicked() { handleReaction("like"); }
void ReactionBar::onLoveClicked() { handleReaction("love"); }
void ReactionBar::onLaughClicked() { handleReaction("laugh"); }
void ReactionBar::onWowClicked() { handleReaction("wow"); }
void ReactionBar::onSadClicked() { handleReaction("sad"); }


void ReactionBar::handleReaction(const std::string& reactionType) {
    qDebug() << "Handling reaction:" << QString::fromStdString(reactionType);


    std::string currentUserReaction = post_->getUserReaction(currentUserId_);

    if (currentUserReaction == reactionType) {
        post_->removeReaction(currentUserId_, reactionType);
    } else {
        if (!currentUserReaction.empty()) {
            post_->removeReaction(currentUserId_, currentUserReaction);
        }
        post_->addReaction(currentUserId_, reactionType);
    }


    emit reactionChanged();

    updateDisplay();
}

void ReactionBar::onReactionCountButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        std::string reactionType = button->objectName().toStdString();
        if (post_->getReactionCount(reactionType) > 0) {
            emit reactionCountClicked(reactionType);
        }
    }
}


