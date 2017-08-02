//
// Created by cp on 2016/11/9.
//卸载app观察class
//
#include <string>
#include "HttpRequest.h"

using namespace std;


#ifndef TESTC_UNINSTALLOBERSER_H
#define TESTC_UNINSTALLOBERSER_H


class UninstallApp {
public:
    UninstallApp();
    UninstallApp(string url,string parameters,string filePath,int pid=-1);
    ~UninstallApp();
    /**
     * 创建文件观察监听
     */
    void createFileobserver();
    void setHttpRequest(HttpRequest* httpRequest);
    void setPid(int pid);
    string getFilepath();

private:
    string url;
    string parameters;
    int pid;
    HttpRequest* httpRequest;
    string filepath;

};


#endif //TESTC_UNINSTALLOBERSER_H
