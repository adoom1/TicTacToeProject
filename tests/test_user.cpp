#include "test_user.h"
#include <QDir>
#include <QFile>

void TestUser::initTestCase()
{
    // Remove test database if it exists
    QFile::remove("test_tictactoe.db");
}

void TestUser::cleanupTestCase()
{
    // Clean up test database
    QFile::remove("test_tictactoe.db");
}

void TestUser::init()
{
    user = new User();
}

void TestUser::cleanup()
{
    delete user;
    user = nullptr;
}

void TestUser::testInitialState()
{
    QVERIFY(!user->isUserLoggedIn());
    QCOMPARE(user->getUsername(), std::string(""));
}

void TestUser::testSignup()
{
    QVERIFY(user->signup("user", "testpass123"));
    QVERIFY(!user->isUserLoggedIn()); // Signup doesn't auto-login
}

void TestUser::testLogin()
{
    // First signup
    user->signup("logintest", "password123");

    // Then login
    QVERIFY(user->login("logintest", "password123"));
    QVERIFY(user->isUserLoggedIn());
    QCOMPARE(user->getUsername(), std::string("logintest"));
}

void TestUser::testLoginFailure()
{
    // Try to login with non-existent user
    QVERIFY(!user->login("nonexistent", "wrongpass"));
    QVERIFY(!user->isUserLoggedIn());

    // Signup then try wrong password
    user->signup("wrongpasstest", "correctpass");
    QVERIFY(!user->login("wrongpasstest", "wrongpass"));
    QVERIFY(!user->isUserLoggedIn());
}

void TestUser::testLogout()
{
    user->signup("logouttest", "password");
    user->login("logouttest", "password");

    QVERIFY(user->isUserLoggedIn());
    QVERIFY(user->logout());
    QVERIFY(!user->isUserLoggedIn());
    QCOMPARE(user->getUsername(), std::string(""));
}

void TestUser::testDuplicateSignup()
{
    QVERIFY(user->signup("duplicate_user", "pass1"));
    QVERIFY(!user->signup("duplicate_user", "pass2")); // Should fail
}
