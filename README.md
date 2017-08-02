# UninstallDemo:这个demo可在app被卸载时执行一次网络请求（发送一些必要信息给后台），注：只在5.0以下有作用


主要需要修改的位置：
native-lib.cpp文件中的方法名

MainActivity中定义的方法名，以及其中的/data/data/包名


build.gradle中:(其中的CMakeLists.txt直接copy过去，放到app文件夹中，与build.gradle同级)
android{
defaultConfig{
externalNativeBuild {
            cmake {
                cppFlags "-frtti -fexceptions"
            }
        }

}
...

externalNativeBuild {
        cmake {
            path "CMakeLists.txt"
        }
    }
}
