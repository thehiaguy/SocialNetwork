#include "reactionsdialog.h"
#include "reactiontype.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

ReactionsDialog::ReactionsDialog(Post* post, Network* network, std::string reactionType, QWidget* parent)
    : QDialog(parent), post_(post), network_(network), reactionType_(reactionType) {

    setWindowTitle("Reactions");
    resize(300, 400);

    layout_ = new QVBoxLayout(this);

    ReactionType type = ReactionType::getById(reactionType_);
    titleLabel_ = new QLabel(QString::fromStdString("Users who reacted with " + type.getEmoji()));
    titleLabel_->setStyleSheet("font-weight: bold; font-size: 14px;");
    layout_->addWidget(titleLabel_);

    usersList_ = new QListWidget();
    layout_->addWidget(usersList_);

    QPushButton* closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    layout_->addWidget(closeButton);

    populateUsersList();
}


void ReactionsDialog::populateUsersList() {
    std::vector<User*> users = network_->getUsersByReaction(post_->getMessageId(), reactionType_);

    for (User* user : users) {
        usersList_->addItem(QString::fromStdString(user->getName()));
    }

    if (users.empty()) {
        usersList_->addItem("No users found");
    }
}
