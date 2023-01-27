#include <iostream>
#include <string>
#include <curl/curl.h>

std::string get_website_html(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string html;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* data, size_t size, size_t nmemb, std::string* buffer) {
            buffer->append(data, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return html;
}

void check_for_bug(const std::string& html) {
    if (html.find("BUG") != std::string::npos) {
        std::cout << "BUG FOUND!" << std::endl;
    } else {
        std::cout << "No bug found." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <URL>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    std::string html = get_website_html(url);
    check_for_bug(html);

    return 0;
}
