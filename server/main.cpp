#include "httplib.h"
#include "json.hpp"
#include <format>
#include <iostream>
#include <iomanip>

// for convenience
using json = nlohmann::json;
using namespace httplib;

int main(void) {
    Server svr;

    svr.Options(R"(\*)", [&](const Request &req, Response &res) {
        res.set_header("Allow", "GET, POST, HEAD, OPTIONS"); 
    });

    svr.Options("/data", [&](const Request &req, Response &res) {
        res.set_header("Access-Control-Allow-Origin", req.get_header_value("Origin").c_str());
        res.set_header("Allow", "GET, POST, HEAD, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept, Origin, Authorization");
        res.set_header("Access-Control-Allow-Methods", "OPTIONS, GET, POST, HEAD");
    });

    svr.Get("/hi", [](const Request &req, Response &res) { 
        res.set_content("{\"hello\":\"world\"}", "application/json"); 
    });

    svr.Post("/data", [&](const Request &req, Response &res) {
        auto postBody = json::parse(req.body);

        time_t _tm =time(NULL );

        struct tm * curtime = localtime ( &_tm );

            json respBody;

            respBody["timestamp"] = asctime(curtime);

            respBody["postBody"] = postBody;

            res.set_header("Access-Control-Allow-Origin", req.get_header_value("Origin").c_str());

            res.set_content(respBody.dump(), "application/json");
            res.status = 200;
    });

    svr.listen("0.0.0.0", 8080);
}