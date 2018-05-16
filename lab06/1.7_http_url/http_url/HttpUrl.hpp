#pragma once

#include <optional>
#include <string>

class CHttpUrl final
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS,
	};

	CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, uint16_t port);

	std::string GetUrl() const;
	Protocol GetProtocol() const;
	std::string GetDomain() const;
	uint16_t GetPort() const;
	std::string GetDocument() const;

private:
	Protocol m_protocol;
	std::string m_domain;
	std::optional<uint16_t> m_optPort;
	std::string m_document;
};

