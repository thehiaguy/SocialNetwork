#ifndef GLOBALFEEDVIEW_H
#define GLOBALFEEDVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include "network.h"
#include "postwidget.h"

class GlobalFeedView : public QWidget {
    Q_OBJECT
private:
    Network* network_;
    int currentUserId_;
    QScrollArea* scrollArea_;
    QWidget* scrollContent_;
    QVBoxLayout* postsLayout_;
    std::vector<PostWidget*> postWidgets_;
    QPushButton* refreshButton_;
    char* postsFile_;
public:
    GlobalFeedView(Network* network, int currentUserId, QWidget* parent = nullptr);
    void loadPosts();
    void refresh();
    void setPostsFile(char* filename) { postsFile_ = filename; }

private slots:
    void onPostChanged();



};

#endif // GLOBALFEEDVIEW_H
