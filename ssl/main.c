#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        while(1) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://official-joke-api.appspot.com/random_joke");

            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }

            sleep(3);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
