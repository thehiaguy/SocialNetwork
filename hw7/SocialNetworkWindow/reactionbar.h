#ifndef REACTIONBAR_H
#define REACTIONBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <map>
#include <string>
#include "post.h"
#include "network.h"

class Network;

class ReactionBar : public QWidget {
    Q_OBJECT

private:
    Post* post_;
    int currentUserId_;
    QHBoxLayout* layout_;
    std::map<std::string, QPushButton*> reactionButtons_;
    std::map<std::string, QPushButton*> reactionCountButtons_;
    Network* network_;

    void handleReaction(const std::string& reactionType);


public:
    ReactionBar(Post* post, int currentUserId, QWidget* parent = nullptr, Network* network = nullptr);
    void updateDisplay();

signals:
    void reactionCountClicked(std::string reactionType);
    void reactionChanged();

private slots:
    void onLikeClicked();
    void onLoveClicked();
    void onLaughClicked();
    void onWowClicked();
    void onSadClicked();
    void onReactionCountButtonClicked();

};

#endif // REACTIONBAR_H
