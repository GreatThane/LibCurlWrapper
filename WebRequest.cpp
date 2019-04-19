#include <utility>

//
// Created by ethan on 4/15/19.
//

#include "WebRequest.h"

WebRequest::~WebRequest() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

CURLcode WebRequest::perform() {
    return curl_easy_perform(curl);
}

WebRequest::operator bool() const {
    return curl;
}

void WebRequest::setURL(const char *url) {
    std::string sUrl{url};
    setURL(sUrl);
}

void WebRequest::setURL(std::string &url) {
    url.append("?");
    for (std::pair<std::string, std::string> pair : getMap) {
        url.append(pair.first).append("=").append(pair.second).append("&");
    }
    if (!getMap.empty()) url.pop_back();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
}

void *WebRequest::getCurl() const {
    return curl;
}

WebRequest::WebRequest() {
    curl = curl_easy_init();
}

void WebRequest::setWriteFunction(std::function<size_t(void *contents, size_t size, size_t nmemb, void *userp)> &func) {
    typedef void *function_t(void *contents, size_t size, size_t nmemb, void *userp);
    auto *funcPtr = func.target<function_t>();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, funcPtr);
}

void WebRequest::setReadData(const char *read) {
    curl_easy_setopt(curl, CURLOPT_READDATA, read);
}

void WebRequest::setReadData(std::string &read) {
    setReadData(read.c_str());
}

void WebRequest::addGetParameters(std::map<std::string, std::string> map) {
    WebRequest::getMap.insert(map.begin(), map.end());
}

void WebRequest::setGetParameters(std::map<std::string, std::string> map) {
    WebRequest::getMap = std::move(map);
}

void WebRequest::addGetParameters(std::pair<std::string, std::string> pair) {
    WebRequest::getMap.insert(pair);
}

const std::map<std::string, std::string> &WebRequest::getGetMap() const {
    return getMap;
}
