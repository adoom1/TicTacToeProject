#ifndef TEST_USER_H
#define TEST_USER_H

#include <QtTest>
#include <QObject>
#include "../User.h"

class TestUser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testInitialState();
    void testSignup();
    void testLogin();
    void testLoginFailure();
    void testLogout();
    void testDuplicateSignup();

private:
    User* user;
};

#endif // TEST_USER_H
