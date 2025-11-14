#ifndef REACTIONSDIALOG_H
#define REACTIONSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "post.h"
#include "network.h"

class ReactionsDialog : public QDialog {
    Q_OBJECT

private:
    Post* post_;
    Network* network_;
    std::string reactionType_;
    QVBoxLayout* layout_;
    QLabel* titleLabel_;
    QListWidget* usersList_;

public:
    ReactionsDialog(Post* post, Network* network, std::string reactionType, QWidget* parent = nullptr);

private:
    void populateUsersList();
};

#endif // REACTIONSDIALOG_H
