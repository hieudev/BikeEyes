#include <jni.h>
#include <string>
#include <android/log.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define TAG "NativeLib"

using namespace std;
using namespace cv;

extern "C" JNIEXPORT jstring JNICALL
Java_com_hieudev_bikevision_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C" {
void JNICALL
Java_com_hieudev_bikevision_MainActivity_adaptiveThresholdFromJNI(JNIEnv *env,
                                                                  jobject instance,
                                                                  jlong matAddr) {

    // get Mat from raw address
    Mat &mat = *(Mat *) matAddr;

    clock_t begin = clock();

    cv::adaptiveThreshold(mat, mat, 255,
                          ADAPTIVE_THRESH_MEAN_C,
                          THRESH_BINARY_INV, 21, 5);

    // log computation time to Android Logcat
    double totalTime = double(clock() - begin) / CLOCKS_PER_SEC;
    __android_log_print(ANDROID_LOG_INFO, TAG,
                        "adaptiveThreshold computation time = %f seconds\n",
                        totalTime);
}
}
