#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
    , network(new Network())
    , loggedInUser(nullptr)
    , displayedUser(nullptr)
    , usersFile(nullptr)
    , postsFile(nullptr)
    , globalFeedView(nullptr)
    , globalFeedButton(nullptr)
    , showingGlobalFeed(false)
{
    ui->setupUi(this);


    loadFiles("users.txt", "posts.txt");
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::onLoginButtonClicked);
    connect(ui->backToProfileButton, &QPushButton::clicked, this, &SocialNetworkWindow::onBackToProfileButtonClicked);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddFriendButtonClicked);
    connect(ui->addPostButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddPostButtonClicked);
    connect(ui->friendsTable, &QTableWidget::cellClicked, this, &SocialNetworkWindow::onFriendClicked);

    globalFeedButton = new QPushButton("Global Feed", this);
    globalFeedButton->setVisible(false);
    connect(globalFeedButton, &QPushButton::clicked, this, &SocialNetworkWindow::onGlobalFeedButtonClicked);

    globalFeedButton->setGeometry(10,10,100,30);

    display();
}



SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
    delete network;

    if (globalFeedView) delete globalFeedView;
    if (globalFeedButton) delete globalFeedButton;

    if (usersFile) delete[] usersFile;
    if (postsFile) delete[] postsFile;
}



bool SocialNetworkWindow::loadFiles(const char* usersFilePath, const char* postsFilePath)
{
    // Free any existing filenames
    if (usersFile) {
        delete[] usersFile;
        usersFile = nullptr;
    }

    if (postsFile) {
        delete[] postsFile;
        postsFile = nullptr;
    }

    // Copy the new filenames character by character
    size_t usersLen = strlen(usersFilePath);
    usersFile = new char[usersLen + 1];
    for (size_t i = 0; i < usersLen; i++) {
        usersFile[i] = usersFilePath[i];
    }
    usersFile[usersLen] = '\0';

    size_t postsLen = strlen(postsFilePath);
    postsFile = new char[postsLen + 1];
    for (size_t i = 0; i < postsLen; i++) {
        postsFile[i] = postsFilePath[i];
    }
    postsFile[postsLen] = '\0';

    // Read the files
    int result = network->readUsers(usersFile);
    if (result == -1) {
        QMessageBox::critical(this, "Error", "Failed to read users file: " + QString(usersFile));
        return false;
    }

    result = network->readPosts(postsFile);
    if (result == -1) {
        QMessageBox::warning(this, "Warning", "Failed to read posts file: " + QString(postsFile));

    }

    // Reset user state when loading new files
    loggedInUser = nullptr;
    displayedUser = nullptr;

    // Clear suggested friends
    for (char* name : suggestedFriends) {
        delete[] name;
    }
    suggestedFriends.clear();

    display(); // Update UI
    return true;
}
bool SocialNetworkWindow::initializeNetwork(const char* usersFile, const char* postsFile){

    this->usersFile = new char[strlen(usersFile)+1];
    strcpy(this->usersFile, usersFile);

    this->postsFile = new char[strlen(postsFile)+1];
    strcpy(this->postsFile, postsFile);


    int result = network->readUsers(this->usersFile);
    if (result == -1){
        return false;
    }

    result = network->readPosts(this->postsFile);
    return true;

}

void SocialNetworkWindow::display(){
    if(!loggedInUser){
        displayLoginPage();
        return;
    }
    if (showingGlobalFeed){
        displayGlobalFeedPage();
    }else {
        displayProfilePage();
    }

}

void SocialNetworkWindow::displayLoginPage(){
    // Show login elements
    ui->loginPrompt->setVisible(true);
    ui->nameInput->setVisible(true);
    ui->loginButton->setVisible(true);


    // Hide profile elements
    ui->profileHeader->setVisible(false);
    ui->friendsHeader->setVisible(false);
    ui->friendsTable->setVisible(false);
    ui->backToProfileButton->setVisible(false);
    ui->friendSuggestionsHeader->setVisible(false);
    ui->friendSuggestionsTable->setVisible(false);
    ui->postInput->setVisible(false);
    ui->addPostButton->setVisible(false);
    ui->addFriendButton->setVisible(false);

    if (globalFeedButton) {
        globalFeedButton->setVisible(false);
    }
    if (globalFeedView) {
        globalFeedView->setVisible(false);
    }
}

void SocialNetworkWindow::displayProfilePage(){
    // Hide login elements
    ui->loginPrompt->setVisible(false);
    ui->nameInput->setVisible(false);
    ui->loginButton->setVisible(false);


    // Show profile elements
    ui->profileHeader->setVisible(true);
    ui->friendsHeader->setVisible(true);
    ui->friendsTable->setVisible(true);
    ui->postInput->setVisible(true);
    ui->addPostButton->setVisible(true);

    if (globalFeedButton) {
        globalFeedButton->setVisible(true);
        globalFeedButton->setText("Global Feed");
    }

    if (globalFeedView) {
        globalFeedView->setVisible(false);
    }


    if (displayedUser->getId() == loggedInUser->getId()){
        ui->profileHeader->setText("My Profile");
        ui->backToProfileButton->setVisible(false);
        ui->friendSuggestionsHeader->setVisible(true);
        ui->friendSuggestionsTable->setVisible(true);
        ui->addFriendButton->setVisible(false);

        updateFriendSuggestions();
    }
    else{
        ui->profileHeader->setText(QString::fromStdString(displayedUser->getName()) + "'s Profile");
        ui->backToProfileButton->setVisible(true);
        ui->friendSuggestionsHeader->setVisible(false);
        ui->friendSuggestionsTable->setVisible(false);
        ui->addFriendButton->setVisible(true);

    }

    updateFriendList();
    updatePosts();

}

void SocialNetworkWindow::displayGlobalFeedPage(){
    ui->profileHeader->setVisible(false);
    ui->friendsHeader->setVisible(false);
    ui->friendsTable->setVisible(false);
    ui->backToProfileButton->setVisible(false);
    ui->friendSuggestionsHeader->setVisible(false);
    ui->friendSuggestionsTable->setVisible(false);
    ui->postInput->setVisible(false);
    ui->addPostButton->setVisible(false);
    ui->addFriendButton->setVisible(false);

    if (globalFeedButton) {
        globalFeedButton->setVisible(true);
        globalFeedButton->setText("Back to Profile");
    }


    if (!globalFeedView) {
        globalFeedView = new GlobalFeedView(network, loggedInUser->getId(), this);
        globalFeedView->setGeometry(50, 50, width() - 100, height() - 100);
        globalFeedView->setPostsFile(postsFile);
    }

    globalFeedView->setVisible(true);
    globalFeedView->refresh();

}

void SocialNetworkWindow::onGlobalFeedButtonClicked(){
    showingGlobalFeed = !showingGlobalFeed;
    display();
}

void SocialNetworkWindow::onLoginButtonClicked(){
    QString name = ui->nameInput->toPlainText().trimmed();
    if(name.isEmpty()){
        QMessageBox::warning(this, "Login Error", "Please enter a name.");
        return;
    }

    int userId = network->getId(name.toStdString());

    if(userId == -1){
        QMessageBox::warning(this, "Login Error", "User not found. Please enter a valid name.");
        return;
    }

    loggedInUser = network->getUser(userId);
    displayedUser= loggedInUser;

    display();
}

void SocialNetworkWindow::onBackToProfileButtonClicked(){
    displayedUser = loggedInUser;

    display();
}

void SocialNetworkWindow::onSuggestion0Clicked() {
    if (suggestedFriends.size() > 0) {
        addFriendByName(suggestedFriends[0]);
    }
}

void SocialNetworkWindow::onSuggestion1Clicked() {
    if (suggestedFriends.size() > 1) {
        addFriendByName(suggestedFriends[1]);
    }
}

void SocialNetworkWindow::onSuggestion2Clicked() {
    if (suggestedFriends.size() > 2) {
        addFriendByName(suggestedFriends[2]);
    }
}

void SocialNetworkWindow::onSuggestion3Clicked() {
    if (suggestedFriends.size() > 3) {
        addFriendByName(suggestedFriends[3]);
    }
}

void SocialNetworkWindow::onSuggestion4Clicked() {
    if (suggestedFriends.size() > 4) {
        addFriendByName(suggestedFriends[4]);
    }
}

void SocialNetworkWindow::addFriendByName(const char* friendName)
{
    // Check if they are already friends
    int friendId = network->getId(friendName);
    if (friendId == -1) {
        return; // Invalid friend name
    }

    const std::set<int>& friends = loggedInUser->getFriends();
    if (friends.find(friendId) != friends.end()) {
        QMessageBox::information(this, "Add Friend", "You are already friends with " + QString(friendName));
        return;
    }

    // Add friend connection
    network->addConnection(loggedInUser->getName(), friendName);

    // Update the files
    network->writeUsers(usersFile);

    QMessageBox::information(this, "Add Friend", "You are now friends with " + QString(friendName));

    // Update the UI
    display();
}

void SocialNetworkWindow::onAddFriendButtonClicked(){
    const std::set<int>& friends = loggedInUser->getFriends();
    if(friends.find(displayedUser->getId()) != friends.end()){
        QMessageBox::information(this, "Add Friend", "You are already friends with " + QString::fromStdString(displayedUser->getName()));
        return;
    }

    network->addConnection(loggedInUser->getName(), displayedUser->getName());

    network->writeUsers(usersFile);

    QMessageBox::information(this, "Add Friend" , "You are now friends with " + QString::fromStdString(displayedUser->getName()));

    display();
}

void SocialNetworkWindow::onAddPostButtonClicked(){
    QString postContent = ui->postInput->text();

    if(postContent.isEmpty()){
        QMessageBox::warning (this,"Add post", "Post content cannot be empty.");
        return;
    }

    if(displayedUser->getId() == loggedInUser->getId()){
        network->addPost(loggedInUser->getId(), postContent.toStdString(),0,false, "", true);
    }
    else{
        network->addPost(displayedUser->getId(), postContent.toStdString(), 0,true, loggedInUser->getName(), true);

    }

    ui->postInput->clear();

    network->writePosts(postsFile);

    updatePosts();
}

void SocialNetworkWindow::onFriendClicked(int row, int column){

    Q_UNUSED(column);
    QTableWidgetItem* item =ui->friendsTable->item(row,0);
    QString friendName = item->text();

    int friendId = network->getId(friendName.toStdString());
    if (friendId != -1){
        displayedUser = network->getUser(friendId);
        display();
    }
}


void SocialNetworkWindow::updateFriendList(){
    ui->friendsTable->clearContents();
    ui->friendsTable->setRowCount(0);
    ui->friendsTable->setColumnCount(1);
    ui->friendsTable->setHorizontalHeaderLabels(QStringList() << "Friends");

    const std::set<int>& friends = displayedUser->getFriends();
    int row = 0;

    for (int friendId: friends){
        User* friend_user = network->getUser(friendId);
        if(friend_user){
            ui->friendsTable->insertRow(row);
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(friend_user->getName()));
            ui->friendsTable->setItem(row, 0 ,nameItem);
            row++;
        }
    }

}

void SocialNetworkWindow::updatePosts(){
    bool showOnlyPublic = (displayedUser->getId() != loggedInUser->getId());
    std::string postsStr = network->getPostsString(displayedUser->getId(), 5 ,showOnlyPublic);
}


void SocialNetworkWindow::updateFriendSuggestions(){
    ui->friendSuggestionsTable->clearContents();
    ui->friendSuggestionsTable->setRowCount(0);
    ui->friendSuggestionsTable->setColumnCount(2);
    ui->friendSuggestionsTable->setHorizontalHeaderLabels(QStringList() << "Suggested Friends" << "Action");


    for(char* name : suggestedFriends){
        delete[] name;
    }
    suggestedFriends.clear();

    int score;
    std::vector<int> suggestions = network->suggestFriends(loggedInUser->getId(), score);

    int row = 0;

    for (int suggestedId : suggestions){
        User* suggested = network->getUser(suggestedId);
        if (suggested){
            std::string stdName = suggested->getName();

            char* nameCopy = new char[stdName.length() + 1];
            strcpy(nameCopy, stdName.c_str());

            suggestedFriends.push_back(nameCopy);

            ui->friendSuggestionsTable->insertRow(row);
            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(stdName));
            ui->friendSuggestionsTable->setItem(row,0,nameItem);

            QPushButton* addButton = new QPushButton("Add Friend", this);

            if (row == 0) {
                connect(addButton, &QPushButton::clicked, this, &SocialNetworkWindow::onSuggestion0Clicked);
            } else if (row == 1) {
                connect(addButton, &QPushButton::clicked, this, &SocialNetworkWindow::onSuggestion1Clicked);
            } else if (row == 2) {
                connect(addButton, &QPushButton::clicked, this, &SocialNetworkWindow::onSuggestion2Clicked);
            } else if (row == 3) {
                connect(addButton, &QPushButton::clicked, this, &SocialNetworkWindow::onSuggestion3Clicked);
            } else if (row == 4) {
                connect(addButton, &QPushButton::clicked, this, &SocialNetworkWindow::onSuggestion4Clicked);
            }

            ui->friendSuggestionsTable->setCellWidget(row, 1, addButton);
            row++;


            if (row >= 5) {
                break;
            }
        }
    }
}
