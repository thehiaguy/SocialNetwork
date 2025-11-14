#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QPushButton>
#include <vector>
#include "network.h"
#include "user.h"
#include "globalfeedview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    bool initializeNetwork(const char* usersFile, const char* postsFile);

private slots:
    void onLoginButtonClicked();
    void onBackToProfileButtonClicked();
    void onAddFriendButtonClicked();
    void onAddPostButtonClicked();
    void onFriendClicked(int row, int column);

    void onSuggestion0Clicked();
    void onSuggestion1Clicked();
    void onSuggestion2Clicked();
    void onSuggestion3Clicked();
    void onSuggestion4Clicked();

    void onGlobalFeedButtonClicked();

private:

    Ui::SocialNetworkWindow *ui;
    Network* network;
    User* loggedInUser;
    User* displayedUser;

    std::vector<char*> suggestedFriends;

    char* usersFile;
    char* postsFile;

    GlobalFeedView* globalFeedView;
    QPushButton* globalFeedButton;
    bool showingGlobalFeed;

    bool loadFiles(const char* usersFilePath, const char* postsFilePath);
    void display();
    void displayLoginPage();
    void displayProfilePage();
    void displayGlobalFeedPage();
    void updateFriendList();
    void updatePosts();
    void updateFriendSuggestions();
    void addFriendByName(const char* friendName);
};
#endif // SOCIALNETWORKWINDOW_H
