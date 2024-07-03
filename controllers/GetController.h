#pragma once

#include <drogon/HttpController.h>
#include <unordered_map>
#include <shared_mutex>
#include <string>

using namespace drogon;

class GetController : public drogon::HttpController<GetController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(GetController::get, "/get", Get);
    METHOD_LIST_END

    GetController();

    void get(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

private:
    std::unordered_map<std::string, std::string> map;
    mutable std::shared_mutex mutex;

    void loadFromCsv(const std::string &filename);
};
