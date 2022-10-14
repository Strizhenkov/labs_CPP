#ifndef LAB2_REQUEST_H
#define LAB2_REQUEST_H

#include <curl/curl.h>

class Request {
public:
    static bool getUrl(const char *url, std::string &outData) {
        CURL *curl;

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outData);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        return (res == CURLE_OK);
    }

private:
    //  Function called when part of data received
    //  Args:
    //      pInputData - part of data (pointer to buffer)
    //      itemsCount * itemLength - length of data in bytes
    //      outData - where we will save this data (pointer to some user's data)
    static size_t write_data(char *pInputData, size_t itemsCount, size_t itemLength, std::string *outData) {
        if (outData) {
            outData->append(pInputData, itemsCount * itemLength);
            return itemsCount * itemLength;
        }
        return 0;
    }
};

#endif