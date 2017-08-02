//
// Created by cp on 2016/11/9.
//

#ifndef TESTC_HTTPREQUEST_H
#define TESTC_HTTPREQUEST_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 41000
#define URLSIZE 1024
#define INVALID_SOCKET -1
#define __DEBUG__
#define  TAG    "unistalled"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
class HttpRequest {
public:
    HttpRequest();
    ~HttpRequest();
    void DebugOut(const char *fmt, ...);

    int HttpGet(const char* strUrl, char* strResponse);
    int HttpPost(const char* strUrl, const char* strData, char* strResponse);

private:
    int   HttpRequestExec(const char* strMethod, const char* strUrl, const char* strData, char* strResponse);
    char* HttpHeadCreate(const char* strMethod, const char* strUrl, const char* strData);
    char* HttpDataTransmit(char *strHttpHead, const int iSockFd);

    int   GetPortFromUrl(const char* strUrl);
    char* GetIPFromUrl(const char* strUrl);
    char* GetParamFromUrl(const char* strUrl);
    char* GetHostAddrFromUrl(const char* strUrl);

    int   SocketFdCheck(const int iSockFd);

    static int m_iSocketFd;
};

#endif //TESTC_HTTPREQUEST_H
