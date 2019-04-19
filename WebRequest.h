#ifndef LIBCURLWRAPPER_WEBREQUEST_H
#define LIBCURLWRAPPER_WEBREQUEST_H


#include <curl/curl.h>
#include <string>
#include <functional>
#include <map>

class WebRequest {
    CURL *curl;
    std::map<std::string, std::string> getMap{};

public:
    static std::function<size_t (void *contents, size_t size, size_t nmemb, void *userp)>& cloneResponsePageWriteFunction() {
        static std::function<size_t (void *contents, size_t size, size_t nmemb, void *userp)> writeFunc = [](void *contents, size_t size, size_t nmemb, void *userp) {
            ((std::string *) userp)->append((char *) contents, size * nmemb);
            return size * nmemb;
        };
        return writeFunc;
    }

    WebRequest();

    virtual ~WebRequest();

    template <typename T>
    void setOpt(CURLoption option, T param)  {
        curl_easy_setopt(curl, option, param);
    }

    CURLcode perform();

    explicit operator bool() const;

    void setURL(std::string& url);

    void setURL(const char* url);

    void setGetParameters(std::map<std::string, std::string> map);

    void addGetParameters(std::map<std::string, std::string> map);

    void addGetParameters(std::pair<std::string, std::string> pair);

    template <typename T>
    void addGetParameters(const std::string& key, T value) {
        getMap.insert(std::pair<std::string, std::string>{key, std::to_string(value)});
    }

    const std::map<std::string, std::string> &getGetMap() const;

    void *getCurl() const;

    void setWriteFunction(std::function<size_t (void *contents, size_t size, size_t nmemb, void *userp)>& func);

    void setReadData(std::string& read);

    void setReadData(const char* read);
};


#endif //LIBCURLWRAPPER_WEBREQUEST_H
