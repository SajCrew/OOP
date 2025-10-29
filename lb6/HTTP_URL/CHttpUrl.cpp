#include "CHttpUrl.h"
#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>

namespace
{
    const unsigned short MIN_PORT = 1;
    const unsigned short MAX_PORT = 65535;
    const unsigned short HTTP_DEFAULT_PORT = 80;
    const unsigned short HTTPS_DEFAULT_PORT = 443;
    const std::string HTTP_PREFIX = "http://";
    const std::string HTTPS_PREFIX = "https://";
    const std::regex URL_REGEX(R"(^([a-zA-Z]+)://([^/:]*)(?::([a-zA-Z0-9]+))?(/?.*)?$)");
    //добавить проверку на спец символ в домене
}

CHttpUrl::CHttpUrl(const std::string& url)
{
    ParseURL(url);
}

CHttpUrl::CHttpUrl(
    const std::string& domain,
    const std::string& document,
    Protocol protocol)
    : CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{}

CHttpUrl::CHttpUrl(
    const std::string& domain,
    const std::string& document,
    Protocol protocol,
    unsigned short port)
    : m_protocol(protocol)
{
    try 
    {
        m_domain = ParseDomain(domain);
        m_document = ParseDocument(document);
        if (port < MIN_PORT || port > MAX_PORT)
        {
            throw std::invalid_argument("Port is out of range");
        }
        m_port = port;
    }
    catch (const std::invalid_argument&)
    {
        throw;
    }
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

void CHttpUrl::ParseURL(const std::string& url)
{
    std::smatch match;
    
    if (url.empty())
        throw CUrlParsingError("Empty input");

    std::regex_match(url, match, URL_REGEX);

    try 
    {
        m_protocol = ParseProtocol(match[1].str()); 
        m_domain = ParseDomain(match[2].str());
        m_port = match[3].matched ? ParsePort(match[3].str(), m_protocol) : GetDefaultPort(m_protocol);
        m_document = ParseDocument(match[4].matched ? match[4].str() : "/");
    }

    catch (const CUrlParsingError&)
    {
        throw; 
    }
}

std::string CHttpUrl::GetURL() const
{
    std::stringstream url;
    url << ProtocolToString(m_protocol) << "://" << m_domain;
    if (!IsDefaultPort(m_port, m_protocol))
    {
        url << ":" << m_port;
    }
    url << m_document;
    return url.str();
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocolStr)
{
    if (protocolStr.empty())
    {
        throw CUrlParsingError("Missing protocol");
    }
    std::string lowerProtocol = ToLower(protocolStr);
    if (lowerProtocol == "http")
    {
        return Protocol::HTTP;
    }
    else if (lowerProtocol == "https")
    {
        return Protocol::HTTPS;
    }
    throw CUrlParsingError("Unknown protocol");
}

unsigned short CHttpUrl::ParsePort(const std::string& portStr, Protocol protocol)
{
    try 
    {
        if (!std::all_of(portStr.begin(), portStr.end(), ::isdigit))
        {
            throw CUrlParsingError("Invalid port: contains non-digit characters");
        }

        size_t pos;
        int port = std::stoi(portStr, &pos);

        if (port < MIN_PORT || port > MAX_PORT)
        {
            throw CUrlParsingError("Port is out of range!!!");
        }
        return static_cast<unsigned short>(port);
    }

    catch (const std::out_of_range&)
    {
        throw CUrlParsingError("Port is out of range!!!");;
    }
}

std::string CHttpUrl::ParseDomain(const std::string& domainStr)
{
    if (domainStr.empty())
    {
        throw CUrlParsingError("Empty domain");
    }

    const std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-";
    if (domainStr.find_first_not_of(allowedChars) != std::string::npos)
    {
        throw CUrlParsingError("Invalid domain");
    }

    if (domainStr.find("..") != std::string::npos)
    {
        throw CUrlParsingError("Invalid domain");
    }

    if (domainStr.front() == '.' || domainStr.back() == '.')
    {
        throw CUrlParsingError("Invalid domain");
    }
    return domainStr;
}

std::string CHttpUrl::ParseDocument(const std::string& documentStr)
{
    if (documentStr.empty() || documentStr[0] != '/')
    {
        return "/" + documentStr;
    }
    return documentStr;
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol)
{
    switch (protocol)
    {
    case Protocol::HTTP:
        return HTTP_DEFAULT_PORT;
    case Protocol::HTTPS:
        return HTTPS_DEFAULT_PORT;
    default:
        throw std::invalid_argument("Unknown protocol");
    }
}

bool CHttpUrl::IsDefaultPort(unsigned short port, Protocol protocol)
{
    return port == GetDefaultPort(protocol);
}

std::string CHttpUrl::ProtocolToString(Protocol protocol)
{
    switch (protocol)
    {
    case Protocol::HTTP:
        return "http";
    case Protocol::HTTPS:
        return "https";
    default:
        throw std::invalid_argument("Unknown protocol");
    }
}

std::string CHttpUrl::ToLower(const std::string& str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}
