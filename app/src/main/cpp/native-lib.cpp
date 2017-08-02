#include <jni.h>
#include <string>
#include "UninstallApp.h"


extern "C"
jint
Java_lins_uninstalldemo_MainActivity_progressPid(
        JNIEnv *env,
        jobject thisz,jstring url,jstring data,jstring filePat,jint jpid) {
    LOGD("原始进程pid is %d",jpid);
    std::string hello = "Hello from C++";
    pid_t pid = fork();
    if(pid<0){
        LOGD("进程创建失败");
    }else if(pid==0){
//        LOGD("子进程开始运行:pid is %d,",getpid());
        const char* uurl=env->GetStringUTFChars(url,0);
        const char* cdata=env->GetStringUTFChars(data,0);
        const char* cfilePath=env->GetStringUTFChars(filePat,0);
        LOGD("url is %s, data is %s,cfilepath is %s",uurl,cdata,cfilePath);
        UninstallApp* uninstallApp=new UninstallApp(uurl,cdata,cfilePath,jpid);
        uninstallApp->createFileobserver();
    }else
    {
        //父进程直接退出，使子进程被init进程领养，以避免子进程僵死
    }
    return pid;
}
