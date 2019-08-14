#include <jni.h>
#include <string>
#include <cstdio>
#include <list>

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_chao_mynativec_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_chao_mynativec_MainActivity_getLowest(
        JNIEnv* env,
        jobject,jintArray arr) {

    jint* a = env->GetIntArrayElements(arr, JNI_FALSE);
    jsize size = env->GetArrayLength(arr);
    jint lowest = a[0];
    for (int i = 1; i < size; ++i) {
        if (lowest > a[i]){
            lowest = a[i];
        }
    }
    env->ReleaseIntArrayElements(arr, a, 0);
    return lowest;
}

jintArray selection_sort2(JNIEnv* env,jintArray arr);
jintArray selection_sort(JNIEnv* env,jintArray arr);

extern "C" JNIEXPORT jintArray JNICALL
Java_com_chao_mynativec_MainActivity_sort(JNIEnv* env,jobject,jintArray arr) {
    list<int> lt;
    lt.push_back(2);
    lt.push_front(1);
    return selection_sort2(env,arr);
}

jintArray selection_sort(JNIEnv* env,jintArray a){
    jint* arr = env->GetIntArrayElements(a, NULL);
    jsize size2 = env->GetArrayLength(a);
    jsize size = size2;

    for (int i = 1; i < size2; ++i) {
        if (arr[i] == NULL){
            size = i + 1;
            break;
        }
    }

    if(size < 2){
        env->ReleaseIntArrayElements(a, arr, JNI_COMMIT);
        return a;
    } else {
        jint l = arr[0];

        jintArray b = env->NewIntArray(size);
        jintArray c = env->NewIntArray(size);

        jint* pb = env->GetIntArrayElements(b, NULL);
        jint* pc = env->GetIntArrayElements(c, NULL);
        for (int i = 1; i < size; ++i) {
            pb[i] = NULL;
            pc[i] = NULL;
        }

        int bIndex = 0,cIndex = 0,dIndex = 0;
        for (int i = 1; i < size; ++i) {
            if (arr[i] == NULL){
                continue;
            }
            if (arr[i] >= l){
                pb[bIndex] = arr[i];
                bIndex++;
            } else {
                pc[cIndex] = arr[i];
                cIndex++;
            }
        }

        env->ReleaseIntArrayElements(a, arr, JNI_COMMIT);
        env->ReleaseIntArrayElements(b, pb, JNI_COMMIT);
        env->ReleaseIntArrayElements(c, pc, JNI_COMMIT);

        jintArray e = selection_sort(env,b);
        jintArray f = selection_sort(env,c);


        jint* pe = env->GetIntArrayElements(e, NULL);
        jint* pf = env->GetIntArrayElements(f, NULL);

        jintArray d = env->NewIntArray(size);
        jint* pd = env->GetIntArrayElements(d, NULL);

        for (int i = 1; i < size; ++i) {
            if (pe[i] == NULL){
                continue;
            }
            pd[dIndex] = pe[i];
            dIndex++;
        }
        pd[dIndex] = l;
        dIndex++;
        for (int i = 1; i < size; ++i) {
            if (pf[i] == NULL){
                continue;
            }
            pd[dIndex] = pf[i];
            dIndex++;
        }

        env->ReleaseIntArrayElements(d, pd, JNI_COMMIT);
        env->ReleaseIntArrayElements(e, pe, JNI_COMMIT);
        env->ReleaseIntArrayElements(f, pf, JNI_COMMIT);
        return d;
    }
}

jintArray selection_sort2(JNIEnv* env,jintArray arr) {
    jint* a = env->GetIntArrayElements(arr, NULL);
//    *a = 100;
    jsize size = env->GetArrayLength(arr);
    //使用两层循环
    int t = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - (i + 1); j++)
            if (a[j] < a[j + 1])//比较大小
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
    }
    //4.释放资源
    env->ReleaseIntArrayElements(arr, a, JNI_COMMIT);
    return arr;
}
