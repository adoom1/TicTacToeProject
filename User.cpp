// User.cpp
#include "User.h"
#include <iostream>
#include <openssl/evp.h> // Use EVP instead of SHA
#include <sstream>
#include <iomanip>

User::User() : isLoggedIn(false) {
}

User::~User() {
    // Cleanup code if needed
}

// SHA-256 hashing function using EVP API
std::string hashPassword(const std::string& password) {
    unsigned char hash[EVP_MAX_MD_SIZE]; // Buffer for hash (SHA-256 produces 32 bytes)
    unsigned int hashLen = 0; // Length of hash

    // Initialize EVP context
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        std::cerr << "Failed to create EVP context" << std::endl;
        return "";
    }

    // Initialize digest with SHA-256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) {
        std::cerr << "Failed to initialize digest" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Update with password data
    if (EVP_DigestUpdate(mdctx, password.c_str(), password.size()) != 1) {
        std::cerr << "Failed to update digest" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Finalize hash
    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
        std::cerr << "Failed to finalize digest" << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Clean up
    EVP_MD_CTX_free(mdctx);

    // Convert hash to hex string
    std::stringstream ss;
    for (unsigned int i = 0; i < hashLen; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

bool User::login(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) {
        return false;
    }

    std::string hashedPassword = hashPassword(password);

    // Check if credentials are valid
    if (DBManager::getInstance().checkUserCredentials(username, hashedPassword)) {
        currentUsername = username;
        isLoggedIn = true;
        return true;
    }

    return false;
}

bool User::signup(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) {
        return false;
    }

    // Check if username already exists
    if (DBManager::getInstance().usernameExists(username)) {
        std::cerr << "Username already exists!" << std::endl;
        return false;
    }

    std::string hashedPassword = hashPassword(password);

    // Add user to database
    if (DBManager::getInstance().addUser(username, hashedPassword)) {
        std::cout << "User registered successfully!" << std::endl;
        return true;
    }

    return false;
}

bool User::logout() {
    currentUsername = "";
    isLoggedIn = false;
    return true;
}

bool User::isUserLoggedIn() const {
    return isLoggedIn;
}

std::string User::getUsername() const {
    return currentUsername;
}
