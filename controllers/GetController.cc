#include "GetController.h"
#include <fstream>
#include <sstream>

GetController::GetController() {
    loadFromCsv("../ttd_domain_yesterday.csv"); 
}

void GetController::loadFromCsv(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header line
    if (std::getline(file, line)) {
        // Header line is read and discarded
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, ',') && std::getline(ss, value)) {
            std::unique_lock lock(mutex);
            map[key] = value;
        }
    }
}

void GetController::get(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {
    auto key = req->getParameter("key");
    if (!key.empty()) {
        std::shared_lock lock(mutex);
        auto it = map.find(key);
        if (it != map.end()) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody(it->second);
            callback(resp);
        } else {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("not_existing");
            callback(resp);
        }
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Missing 'key' parameter");
        callback(resp);
    }
}
