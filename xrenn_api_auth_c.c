#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define TOKEN_URL "https://xrenn.ai/api/v1/auth_xrenn_token/obtain/"
#define REFRESH_URL "https://xrenn.ai/api/v1/auth_xrenn_token/refresh/"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void obtain_token(const char *username, const char *password) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        char data[256];
        snprintf(data, sizeof(data), "username=%s&password=%s", username, password);

        curl_easy_setopt(curl, CURLOPT_URL, TOKEN_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
            printf("%s\n", chunk.memory);
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    }
    curl_global_cleanup();
}

void refresh_token(const char *refresh) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        char data[256];
        snprintf(data, sizeof(data), "refresh=%s", refresh);

        curl_easy_setopt(curl, CURLOPT_URL, REFRESH_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
            printf("%s\n", chunk.memory);
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    }
    curl_global_cleanup();
}

int main(void) {
    obtain_token("your_username", "your_password");
    refresh_token("your_refresh_token");
    return 0;
}