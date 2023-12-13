#pragma once

#include "includes.h"

class request
{
private:
    int request_id;
    request_t req_type;
    string from;

public:
    static int counter;

    request();
    request(request_t req_type);

    int requestId() const { return request_id; }
    void setRequestId(int requestId) { request_id = requestId; }

    request_t reqType() const { return req_type; }
    void setReqType(const request_t &reqType) { req_type = reqType; }

    string getFrom() const { return from; }
    void setFrom(const string &from_) { from = from_; }
};

class request_connect : public request
{
};