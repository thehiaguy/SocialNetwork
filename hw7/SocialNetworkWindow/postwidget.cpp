#include "postwidget.h"
#include "reactionsdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

PostWidget::PostWidget(Post* post, Network* network, int currentUserId, QWidget* parent)
    : QWidget(parent), post_(post), network_(network), currentUserId_(currentUserId) {

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Author label
    User* owner = network_->getUser(post_->getOwnerId());
    authorLabel_ = new QLabel();
    if (owner) {
        authorLabel_->setText(QString::fromStdString(owner->getName() + " wrote:"));
    }
    authorLabel_->setStyleSheet("font-weight: bold;");
    layout->addWidget(authorLabel_);

    // Content label
    contentLabel_ = new QLabel(QString::fromStdString(post_->getMessage()));
    contentLabel_->setWordWrap(true);
    layout->addWidget(contentLabel_);

    // Reaction bar
    reactionBar_ = new ReactionBar(post_, currentUserId_, this,network_);


    connect(reactionBar_, &ReactionBar::reactionCountClicked,
            this, &PostWidget::showReactionsDialog);

    connect(reactionBar_, &ReactionBar::reactionChanged, this, &PostWidget::onReactionChanged);

    layout->addWidget(reactionBar_);

    // Add border using CSS only
    setStyleSheet(
        "PostWidget {"
        "   border: 1px solid gray;"
        "   margin: 5px;"
        "   padding: 10px;"
        "   background-color: white;"
        "   border-radius: 5px;"
        "}"
        );

    updateDisplay();
}

void PostWidget::updateDisplay() {
    reactionBar_->updateDisplay();
}

void PostWidget::showReactionsDialog(std::string reactionType) {
    ReactionsDialog* dialog = new ReactionsDialog(post_, network_, reactionType, this);
    dialog->exec();
    delete dialog;
}


void PostWidget::onReactionChanged(){
    emit postChanged();
}
