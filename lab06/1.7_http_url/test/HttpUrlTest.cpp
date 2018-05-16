#include "HttpUrl.hpp"
#include "UrlParsingError.hpp"
#include "catch.hpp"
#include <map>

using Protocol = CHttpUrl::Protocol;

const std::map<Protocol, int> PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
};

void CheckHttpUrlParsing(const std::string& url, const std::string& expectedUrl,
	Protocol protocolExpected, int portExpected, const std::string& domainExpected, const std::string& documentExpected)
{
	CHttpUrl httpUrl(url);
	
	CHECK(httpUrl.GetUrl() == expectedUrl);
	CHECK(httpUrl.GetProtocol() == protocolExpected);
	CHECK(httpUrl.GetDomain() == domainExpected);
	CHECK(httpUrl.GetPort() == portExpected);
	CHECK(httpUrl.GetDocument() == documentExpected);
}

void CheckHttpUrlParsing(const std::string& url, const std::string& expectedUrl,
	Protocol protocolExpected, const std::string& domainExpected, const std::string& documentExpected)
{
	const int portExpected = PORT.at(protocolExpected);
	return CheckHttpUrlParsing(url, expectedUrl, protocolExpected, portExpected, domainExpected, documentExpected);
}

void CheckHttpUrlParsingFail(const std::string& url)
{
	CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);
}

TEST_CASE("Parses sample URL")
{
	std::string url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	CheckHttpUrlParsing(url, url, Protocol::HTTP, "www.mysite.com", "/docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("Parses URLs with all possible protocols")
{
	CheckHttpUrlParsing("http://abc.com", "http://abc.com/", Protocol::HTTP, "abc.com", "/");
	CheckHttpUrlParsing("https://abc.com", "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
}

TEST_CASE("Parses protocols in any letter cases")
{
	CheckHttpUrlParsing("hTTp://abc.com", "http://abc.com/", Protocol::HTTP, "abc.com", "/");
	CheckHttpUrlParsing("httPS://abc.com", "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
}

TEST_CASE("Fails to parse url without required parts")
{
	CheckHttpUrlParsingFail("abc.com");
	CheckHttpUrlParsingFail("http://:8080/index.html");
	CheckHttpUrlParsingFail("http:///index.html");
	CheckHttpUrlParsingFail("http://");
}

TEST_CASE("Parses URL without port")
{
	CheckHttpUrlParsing("https://abc.com", "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
	CheckHttpUrlParsing("http://abc.com/about.htm", "http://abc.com/about.htm", Protocol::HTTP, "abc.com", "/about.htm");
}

TEST_CASE("Fails to parse port out of bounds")
{
	CheckHttpUrlParsingFail("https://abc.com:0");
	CheckHttpUrlParsingFail("http://abc.com:65536");
	CheckHttpUrlParsingFail("http://abc.com:99999999999999");
}

TEST_CASE("Parses URL with empty document or without document")
{
	CheckHttpUrlParsing("https://abc.com", "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
	CheckHttpUrlParsing("https://abc.com/", "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
}

TEST_CASE("Parses URL with default port and hides it")
{
	CheckHttpUrlParsing("https://abc.com:443", "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
	CheckHttpUrlParsing("http://abc.com:80", "http://abc.com/", Protocol::HTTP, "abc.com", "/");
}

TEST_CASE("Parses URL with custom port and shows it")
{
	CheckHttpUrlParsing("https://abc.com:42", "https://abc.com:42/", Protocol::HTTPS, 42, "abc.com", "/");
	CheckHttpUrlParsing("http://abc.com:42", "http://abc.com:42/", Protocol::HTTP, 42, "abc.com", "/");
}
