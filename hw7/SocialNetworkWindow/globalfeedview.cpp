#include "globalfeedview.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>

GlobalFeedView::GlobalFeedView(Network* network, int currentUserId, QWidget* parent)
    : QWidget(parent), network_(network), currentUserId_(currentUserId) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    refreshButton_ = new QPushButton("Refresh Feed");
    connect(refreshButton_, &QPushButton::clicked, this, &GlobalFeedView::refresh);
    mainLayout->addWidget(refreshButton_);

    scrollArea_ = new QScrollArea();
    scrollContent_ = new QWidget();
    postsLayout_ = new QVBoxLayout(scrollContent_);

    scrollArea_->setWidget(scrollContent_);
    scrollArea_->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea_);

    loadPosts();
}


void GlobalFeedView::loadPosts() {
    for (PostWidget* widget : postWidgets_) {
        delete widget;
    }
    postWidgets_.clear();

    std::vector<Post*> posts = network_->getVisiblePosts(currentUserId_);

    for (Post* post : posts) {
        PostWidget* postWidget = new PostWidget(post, network_, currentUserId_);
        connect(postWidget, &PostWidget::postChanged, this, &GlobalFeedView::onPostChanged);
        postWidgets_.push_back(postWidget);
        postsLayout_->addWidget(postWidget);
    }

    postsLayout_->addStretch();
}

void GlobalFeedView::refresh() {
    loadPosts();
}

void GlobalFeedView::onPostChanged(){
    if(postsFile_){
        network_->writePosts(postsFile_);
    }
}



