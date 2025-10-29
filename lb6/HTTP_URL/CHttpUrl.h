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
    // выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
    // выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
    // не должен включатьс€
    std::string GetURL()const;

    std::string GetDomain()const;

    /*
        ¬озвращает им€ документа. ѕримеры:
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