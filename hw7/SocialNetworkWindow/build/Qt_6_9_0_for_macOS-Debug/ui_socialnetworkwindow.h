/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QPushButton *loginButton;
    QPushButton *backToProfileButton;
    QPushButton *addFriendButton;
    QPushButton *addPostButton;
    QTextEdit *nameInput;
    QLabel *loginPrompt;
    QLabel *postsHeader;
    QTableWidget *friendsTable;
    QLabel *profileHeader;
    QLabel *friendsHeader;
    QLabel *friendSuggestionsHeader;
    QLabel *postsDisplay;
    QLineEdit *postInput;
    QTableWidget *friendSuggestionsTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(942, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(390, 290, 91, 32));
        backToProfileButton = new QPushButton(centralwidget);
        backToProfileButton->setObjectName("backToProfileButton");
        backToProfileButton->setGeometry(QRect(30, 20, 111, 32));
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(160, 20, 101, 32));
        addPostButton = new QPushButton(centralwidget);
        addPostButton->setObjectName("addPostButton");
        addPostButton->setGeometry(QRect(760, 280, 101, 32));
        nameInput = new QTextEdit(centralwidget);
        nameInput->setObjectName("nameInput");
        nameInput->setGeometry(QRect(350, 260, 181, 31));
        loginPrompt = new QLabel(centralwidget);
        loginPrompt->setObjectName("loginPrompt");
        loginPrompt->setGeometry(QRect(380, 240, 151, 16));
        postsHeader = new QLabel(centralwidget);
        postsHeader->setObjectName("postsHeader");
        postsHeader->setGeometry(QRect(30, 290, 111, 16));
        friendsTable = new QTableWidget(centralwidget);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(20, 80, 256, 192));
        profileHeader = new QLabel(centralwidget);
        profileHeader->setObjectName("profileHeader");
        profileHeader->setGeometry(QRect(390, 50, 91, 16));
        friendsHeader = new QLabel(centralwidget);
        friendsHeader->setObjectName("friendsHeader");
        friendsHeader->setGeometry(QRect(30, 60, 111, 16));
        friendSuggestionsHeader = new QLabel(centralwidget);
        friendSuggestionsHeader->setObjectName("friendSuggestionsHeader");
        friendSuggestionsHeader->setGeometry(QRect(620, 40, 141, 16));
        postsDisplay = new QLabel(centralwidget);
        postsDisplay->setObjectName("postsDisplay");
        postsDisplay->setGeometry(QRect(30, 310, 641, 231));
        postInput = new QLineEdit(centralwidget);
        postInput->setObjectName("postInput");
        postInput->setGeometry(QRect(690, 310, 241, 231));
        friendSuggestionsTable = new QTableWidget(centralwidget);
        friendSuggestionsTable->setObjectName("friendSuggestionsTable");
        friendSuggestionsTable->setGeometry(QRect(620, 60, 256, 192));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 942, 24));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        backToProfileButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Back to profile", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Friend", nullptr));
        addPostButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add post", nullptr));
        nameInput->setHtml(QCoreApplication::translate("SocialNetworkWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        loginPrompt->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your name", nullptr));
        postsHeader->setText(QCoreApplication::translate("SocialNetworkWindow", "Recent Posts:", nullptr));
        profileHeader->setText(QCoreApplication::translate("SocialNetworkWindow", "Profile:", nullptr));
        friendsHeader->setText(QCoreApplication::translate("SocialNetworkWindow", "Friends list:", nullptr));
        friendSuggestionsHeader->setText(QCoreApplication::translate("SocialNetworkWindow", "Friend Suggestion:", nullptr));
        postsDisplay->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
