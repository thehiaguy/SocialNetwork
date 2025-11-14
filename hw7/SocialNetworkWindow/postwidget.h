#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "post.h"
#include "network.h"
#include "reactionbar.h"

class PostWidget : public QWidget{
    Q_OBJECT
private:
    Post* post_;
    Network* network_;
    int currentUserId_;
    QLabel* authorLabel_;
    QLabel* contentLabel_;
    ReactionBar* reactionBar_;


public:
    PostWidget(Post* post, Network* network, int currentUserId, QWidget* parent = nullptr);
    void updateDisplay();

signals:
    void postChanged();

private slots:
    void showReactionsDialog(std::string reactionType);
    void onReactionChanged();
};

#endif // POSTWIDGET_H
