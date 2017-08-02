#include "UninstallApp.h"
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/inotify.h>
#include <stdlib.h>
#include <android/log.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <fcntl.h>

UninstallApp::~UninstallApp() { }
UninstallApp::UninstallApp() {}
UninstallApp::UninstallApp(string url,string parameters ,string filePath,int pid ) {
    this->url=url;
    this->parameters=parameters;
    this->pid=pid;
    this->filepath=filePath;
}

void UninstallApp::createFileobserver() {
    LOGD("开始创建文件监听\r\n");
    int fileDescriptor = inotify_init();
    if (fileDescriptor < 0)
    {
        LOGD("系统调用失败\r\n");
        exit(1);

    }

    int watchDescriptor;
    LOGD("filePath %s",filepath.c_str());
    watchDescriptor = inotify_add_watch(fileDescriptor, filepath.c_str(), IN_DELETE);
    if (watchDescriptor < 0)
    {
        LOGD("文件监听失败\r\n");
        exit(1);
    }
    LOGD("监听文件改变\r\n");
    //分配缓存，以便读取event，缓存大小=一个struct inotify_event的大小，这样一次处理一个event
    void *p_buf = malloc(sizeof(struct inotify_event));
    if (p_buf == NULL)
    {
        LOGD("内存申请失败");
        exit(1);
    }
    //开始监听
    LOGI("开始监听\r\n");
    size_t readBytes = read(fileDescriptor, p_buf, sizeof(struct inotify_event));
    free(p_buf);
    inotify_rm_watch(fileDescriptor, IN_DELETE);
    LOGD("文件删除删除！\r\n");
    char* response = (char*)malloc(BUFSIZE);
    memset(response, 0, BUFSIZE);
    LOGD("提交数据");
    httpRequest->HttpPost(url.c_str(),parameters.c_str(),response);
    LOGD(" reponse is %s",response);
    free(response);

}
void UninstallApp::setHttpRequest(HttpRequest *httpRequest) {

    this->httpRequest=httpRequest;
}

void UninstallApp::setPid(int pid) {

    this->pid=pid;
}
string UninstallApp::getFilepath() {
    return this->filepath;
}

