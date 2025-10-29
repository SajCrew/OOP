#include "CHttpUrl.h"
#include <iostream>
#include <string>

int main()
{
    std::string urlStr;
    while (std::getline(std::cin, urlStr))
    {
        try
        {
            CHttpUrl url(urlStr);
            std::cout << "URL: " << url.GetURL() << std::endl;
            std::cout << "Domain: " << url.GetDomain() << std::endl;
            std::cout << "Document: " << url.GetDocument() << std::endl;
            std::cout << "Protocol: " << (url.GetProtocol() == Protocol::HTTP ? "HTTP" : "HTTPS") << std::endl;
            std::cout << "Port: " << url.GetPort() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}