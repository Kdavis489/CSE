#pragma once

#include <string>

class Account
{
public:
	bool AddAccount(const std::string& username, const std::string& password);
	bool DelAccount(const std::string& username);
	bool Login(const std::string& username, const std::string& password);

};