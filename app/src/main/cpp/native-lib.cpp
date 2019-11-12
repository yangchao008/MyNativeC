#include <jni.h>
#include <string>
#include <cstdio>
#include <list>

using namespace std;

string hello(){
    string hello = "Hello from C++";
    return hello;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_chao_mynativec_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    return env -> NewStringUTF("Hello from C++");
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

jintArray selection_sort3(JNIEnv* env,jintArray arr);
jintArray selection_sort2(JNIEnv* env,jintArray arr);
jintArray selection_sort(JNIEnv* env,jintArray arr);

list<int> real_sort(list<int> list);

extern "C" JNIEXPORT jintArray JNICALL
Java_com_chao_mynativec_MainActivity_sort(JNIEnv* env,jobject,jintArray arr) {
    return selection_sort3(env,arr);
}

jintArray selection_sort(JNIEnv* env,jintArray a){
    jint* arr = env->GetIntArrayElements(a, NULL);
    jsize size = env->GetArrayLength(a);

    list<int> b;
    for (int i = 0; i < size; ++i) {
        int value = arr[i];
        b.push_front(value);
    }
    list<int> e = real_sort(b);

    list<int>::iterator i_;
    int d_index = 0;
    for(i_ = e.begin();i_ != e.end();++i_){
        arr[d_index] = int(*i_);
        d_index++;
    }
    env->ReleaseIntArrayElements(a, arr, JNI_COMMIT);
    return a;
//    if(size < 2){
//        env->ReleaseIntArrayElements(a, arr, JNI_COMMIT);
//        return a;
//    } else {
//        int l = arr[0];
//
//        list<int> b,c;
//        list<int>::iterator i_;
//        for (int i = 1; i < size; ++i) {
//            int value = arr[i];
//            if (value > l){
//                c.push_front(value);
//            } else{
//                b.push_front(value);
//            }
//        }
//        env->ReleaseIntArrayElements(a, arr, JNI_COMMIT);
//        int new_size = sizeof(b) + sizeof(c) + 1;
//        jintArray d = env->NewIntArray(new_size);
//        int* d_arr = env->GetIntArrayElements(d, NULL);
//        int d_index = 0;
//        for(i_ = b.begin();i_ != b.end();++i_){
//            d_arr[d_index] = int(*i_);
//            d_index++;
//        }
//        d_arr[d_index] = l;
//        d_index++;
//        for(i_ = c.begin();i_ != c.end();i_++){
//            d_arr[d_index] = int(*i_);
//            d_index++;
//        }
//        env->ReleaseIntArrayElements(d, d_arr, JNI_COMMIT);
//        return d;
//    }
}

list<int> real_sort(list<int> a) {
    int size = sizeof(a);
    if (size < 2){
        return a;
    } else{
        list<int> b,c;
        list<int>::iterator i_;

        int stand = int(*a.begin());
        for(i_ = ++a.begin();i_ != a.end();i_++){
            int value = int(*i_);
            if (value > stand){
                b.push_front(value);
            } else {
                c.push_front(value);
            }
        }
        list<int> e = real_sort(b);
        list<int> f = real_sort(c);

        list<int> d;
        for(i_ = e.begin();i_ != e.end();++i_){
            int value = int(*i_);
            d.push_front(value);
        }
        d.push_front(stand);
        for(i_ = f.begin();i_ != f.end();i_++){
            int value = int(*i_);
            d.push_front(value);
        }
        return d;
    }
}

jintArray selection_sort3(JNIEnv* env,jintArray a){
    jint* arr = env->GetIntArrayElements(a, NULL);
    jsize size = env->GetArrayLength(a);

    list<int> b;
    for (int i = 0; i < size; ++i) {
        int value = arr[i];
        b.push_front(value);
    }
    b.sort();
    b.reverse();
    list<int>::iterator i_;
    int d_index = 0;
    for(i_ = b.begin();i_ != b.end();++i_){
        arr[d_index] = int(*i_);
        d_index++;
    }
    env->ReleaseIntArrayElements(a, arr, JNI_COMMIT);
    return a;
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
