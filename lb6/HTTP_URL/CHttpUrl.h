#include <stdexcept>

enum class Protocol
{
    HTTP,
    HTTPS
};

class CUrlParsingError : public std::invalid_argument
{
public:
    explicit CUrlParsingError(const std::string& message)
        : std::invalid_argument(message)
    {}
};

class CHttpUrl
{
public:
    // ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
    // ����������� ���������� CUrlParsingError, ���������� ��������� �������� ������
    CHttpUrl(std::string const& url);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
    // ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
    // �� ������ ����������
    std::string GetURL()const;

    std::string GetDomain()const;

    /*
        ���������� ��� ���������. �������:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    Protocol GetProtocol()const;

    unsigned short GetPort()const;

private:
    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned short m_port;

    void ParseURL(const std::string& url);

    static Protocol ParseProtocol(const std::string& protocolStr);

    static unsigned short ParsePort(const std::string& portStr, Protocol protocol);

    static std::string ParseDomain(const std::string& domainStr);

    static std::string ParseDocument(const std::string& documentStr);

    static unsigned short GetDefaultPort(Protocol protocol);

    static bool IsDefaultPort(unsigned short port, Protocol protocol);

    static std::string ProtocolToString(Protocol protocol);

    static std::string ToLower(const std::string& str);
};