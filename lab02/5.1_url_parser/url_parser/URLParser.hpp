#pragma once

#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

struct URLInfo
{
	Protocol protocol;
	std::string host;
	int port;
	std::string document;
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);
bool ParseURL(const std::string& url, URLInfo& info);
