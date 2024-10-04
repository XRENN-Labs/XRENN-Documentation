#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

const utility::string_t tokenUrl = U("https://xrenn.ai/api/v1/auth_xrenn_token/obtain/");
const utility::string_t refreshUrl = U("https://xrenn.ai/api/v1/auth_xrenn_token/refresh/");

json::value obtainToken(const utility::string_t& username, const utility::string_t& password) {
    http_client client(tokenUrl);
    json::value json_data;
    json_data[U("username")] = json::value::string(username);
    json_data[U("password")] = json::value::string(password);

    http_response response = client.request(methods::POST, U(""), json_data).get();
    if (response.status_code() == status_codes::OK) {
        return response.extract_json().get();
    } else {
        std::wcout << L"Error: " << response.status_code() << L", " << response.extract_utf8string().get() << std::endl;
        return json::value();
    }
}

json::value refreshToken(const utility::string_t& refresh) {
    http_client client(refreshUrl);
    json::value json_data;
    json_data[U("refresh")] = json::value::string(refresh);

    http_response response = client.request(methods::POST, U(""), json_data).get();
    if (response.status_code() == status_codes::OK) {
        return response.extract_json().get();
    } else {
        std::wcout << L"Error: " << response.status_code() << L", " << response.extract_utf8string().get() << std::endl;
        return json::value();
    }
}