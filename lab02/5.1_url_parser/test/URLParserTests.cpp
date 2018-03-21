#include "../url_parser/URLParser.hpp"
#include "catch.hpp"
#include <map>

bool CheckParseURL(const std::string url, Protocol protocolExpected,
	int portExpected, const std::string& hostExpected, const std::string& documentExpected)
{
	URLInfo info;
	if (!ParseURL(url, info))
	{
		return false;
	}

	return (info.protocol == protocolExpected && info.port == portExpected
		&& info.host == hostExpected && info.document == documentExpected);
}

const std::map<Protocol, int> PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 },
};

bool CheckParseURL(const std::string url, Protocol protocolExpected,
	const std::string& hostExpected, const std::string& documentExpected)
{
	const int portExpected = PORT.at(protocolExpected);
	return CheckParseURL(url, protocolExpected, portExpected, hostExpected, documentExpected);
}

TEST_CASE("Parses sample URL", "[parseURL]")
{
	std::string url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	CHECK(CheckParseURL(url, Protocol::HTTP, "www.mysite.com", "docs/document1.html?page=30&lang=en#title"));
}

TEST_CASE("Parses URLs with all possible protocols", "[parseURL]")
{
	CHECK(CheckParseURL("http://abc.com", Protocol::HTTP, "abc.com", ""));
	CHECK(CheckParseURL("https://abc.com", Protocol::HTTPS, "abc.com", ""));
	CHECK(CheckParseURL("ftp://abc.com", Protocol::FTP, "abc.com", ""));
}

TEST_CASE("Parses protocols in any letter cases", "[parseURL]")
{
	URLInfo info;
	CHECK(CheckParseURL("hTTp://abc.com", Protocol::HTTP, "abc.com", ""));
	CHECK(CheckParseURL("httPS://abc.com", Protocol::HTTPS, "abc.com", ""));
	CHECK(CheckParseURL("FTp://abc.com", Protocol::FTP, "abc.com", ""));
}

TEST_CASE("Fails to parse url without required parts", "[parseURL]")
{
	URLInfo info;
	CHECK_FALSE(ParseURL("abc.com", info));
	CHECK_FALSE(ParseURL("http://:8080/index.html", info));
	CHECK_FALSE(ParseURL("http:///index.html", info));
	CHECK_FALSE(ParseURL("http://", info));
}

TEST_CASE("Parses URL without port", "[parseURL]")
{
	CHECK(CheckParseURL("https://abc.com", Protocol::HTTPS, "abc.com", ""));
	CHECK(CheckParseURL("http://abc.com/about.htm", Protocol::HTTP, "abc.com", "about.htm"));
}

TEST_CASE("Fails to parse port out of bounds", "[parseURL]")
{
	URLInfo info;
	CHECK_FALSE(ParseURL("https://abc.com:0", info));
	CHECK_FALSE(ParseURL("http://abc.com:65536", info));
	CHECK_FALSE(ParseURL("http://abc.com:99999999999999", info));
}

TEST_CASE("Parses URL with empty document ot without document", "[parseURL]")
{
	CHECK(CheckParseURL("https://abc.com", Protocol::HTTPS, "abc.com", ""));
	CHECK(CheckParseURL("https://abc.com/", Protocol::HTTPS, "abc.com", ""));
}
