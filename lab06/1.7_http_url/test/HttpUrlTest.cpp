#include "HttpUrl.hpp"
#include "UrlParsingError.hpp"
#include "catch.hpp"
#include <map>

using namespace std::string_literals;

using Protocol = CHttpUrl::Protocol;

const std::map<Protocol, int> PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
};

void CheckHttpUrl(const CHttpUrl& url,
							const std::string& expectedUrl,
							Protocol protocolExpected,
							int portExpected,
							const std::string& domainExpected,
							const std::string& documentExpected)
{
	CHECK(url.GetUrl() == expectedUrl);
	CHECK(url.GetProtocol() == protocolExpected);
	CHECK(url.GetDomain() == domainExpected);
	CHECK(url.GetPort() == portExpected);
	CHECK(url.GetDocument() == documentExpected);
}

void CheckHttpUrl(const CHttpUrl& url,
							const std::string& expectedUrl,
							Protocol protocolExpected,
							const std::string& domainExpected,
							const std::string& documentExpected)
{
	const int portExpected = PORT.at(protocolExpected);
	return CheckHttpUrl(url, expectedUrl, protocolExpected, portExpected, domainExpected, documentExpected);
}

void CheckHttpUrlFail(const std::string& url)
{
	CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);
}

void CheckHttpUrlFail(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP)
{
	CHECK_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);

}
void CheckHttpUrlFail(const std::string& domain, const std::string& document, Protocol protocol, uint16_t port)
{
	CHECK_THROWS_AS(CHttpUrl(domain, document, protocol, port), CUrlParsingError);

}

TEST_CASE("Parses sample URL")
{
	std::string url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	CheckHttpUrl(url, url, Protocol::HTTP, "www.mysite.com", "/docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("Parses URLs with all possible protocols")
{
	CheckHttpUrl("http://abc.com"s, "http://abc.com/", Protocol::HTTP, "abc.com", "/");
	CheckHttpUrl("https://abc.com"s, "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
}

TEST_CASE("Fails to parse URL with wrong protocol")
{
	CheckHttpUrlFail("ftp://example.com/index.html");
}

TEST_CASE("Parses protocols in any letter cases")
{
	CheckHttpUrl("hTTp://abc.com"s, "http://abc.com/", Protocol::HTTP, "abc.com", "/");
	CheckHttpUrl("httPS://abc.com"s, "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
}

TEST_CASE("Fails to parse url without required parts")
{
	CheckHttpUrlFail("abc.com");
	CheckHttpUrlFail("http://:8080/index.html");
	CheckHttpUrlFail("http:///index.html");
	CheckHttpUrlFail("http://");
}

TEST_CASE("Parses URL without port")
{
	CheckHttpUrl("https://abc.com"s, "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
	CheckHttpUrl("http://abc.com/about.htm"s, "http://abc.com/about.htm", Protocol::HTTP, "abc.com", "/about.htm");
}

TEST_CASE("Parses URL with wrong port")
{
	CheckHttpUrlFail("https://abc.com:kek");
	CheckHttpUrlFail("http://abc.com:");
	CheckHttpUrlFail("http://abc.com:42kek");
}

TEST_CASE("Fails to parse port out of bounds")
{
	CheckHttpUrlFail("https://abc.com:0");
	CheckHttpUrlFail("http://abc.com:65536");
	CheckHttpUrlFail("http://abc.com:99999999999999");
}

TEST_CASE("Parses URL with empty document or without document")
{
	CheckHttpUrl("https://abc.com"s, "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
	CheckHttpUrl("https://abc.com/"s, "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
}

TEST_CASE("Parses URL with default port and hides it")
{
	CheckHttpUrl("https://abc.com:443"s, "https://abc.com/", Protocol::HTTPS, "abc.com", "/");
	CheckHttpUrl("http://abc.com:80"s, "http://abc.com/", Protocol::HTTP, "abc.com", "/");
}

TEST_CASE("Parses URL with custom port and shows it")
{
	CheckHttpUrl("https://abc.com:42"s, "https://abc.com:42/", Protocol::HTTPS, 42, "abc.com", "/");
	CheckHttpUrl("http://abc.com:42"s, "http://abc.com:42/", Protocol::HTTP, 42, "abc.com", "/");
}



TEST_CASE("Other constructors")
{
	SECTION("Constructs properly with default protocol")
	{
		CheckHttpUrl(CHttpUrl("example.com", "doc"),
			"http://example.com/doc", Protocol::HTTP, "example.com", "/doc");
	}

	SECTION("Constructs properly with default port")
	{
		CheckHttpUrl(CHttpUrl("example.com", "doc", Protocol::HTTP, 80),
			"http://example.com/doc", Protocol::HTTP, "example.com", "/doc");
	}

	SECTION("Constructs properly with non-default port")
	{
		CheckHttpUrl(CHttpUrl("example.com", "doc", Protocol::HTTP, 42),
			"http://example.com:42/doc", Protocol::HTTP, 42, "example.com", "/doc");
		CheckHttpUrl(CHttpUrl("example.com", "doc", Protocol::HTTPS, 42),
			"https://example.com:42/doc", Protocol::HTTPS, 42, "example.com", "/doc");
	}

	SECTION("Constructs properly with HTTPS protocol")
	{
		CheckHttpUrl(CHttpUrl("example.com", "doc", Protocol::HTTPS),
			"https://example.com/doc", Protocol::HTTPS, "example.com", "/doc");
	}

	SECTION("Fails to construct with wrong domains")
	{
		CheckHttpUrlFail("example.com:", "doc");
		CheckHttpUrlFail("example:com", "doc");
		CheckHttpUrlFail("example.com/", "doc");
		CheckHttpUrlFail("example/com", "doc");
	}

	SECTION("Fails to construct with wrong ports")
	{
		CheckHttpUrlFail("example.com", "doc", Protocol::HTTP, 0);
	}
}