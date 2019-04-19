#include <iostream>
#include "WebRequest.h"

int main() {
    std::string readBuffer;

    WebRequest request;
    if (request) {
        request.addGetParameters(std::map<std::string, std::string>{{"lat", "35"}, {"lon", "139"}});
        request.setURL("api.openweathermap.org/data/2.5/weather");
        request.setWriteFunction(WebRequest::cloneResponsePageWriteFunction());
        request.setReadData(readBuffer);

        request.perform();

    }
    std::cout << readBuffer << std::endl;
}