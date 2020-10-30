#include <jni.h>
#include <string.h>
#include <android/log.h>
#include <assert.h>

#define TAG "test" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

//注意：如果不知道方法签名，在Terminal中执行以下命令即可获得：javap -s  /Users/zhangshidong/Documents/NativeApplication/nativelibrary/build/tmp/kotlin-classes/debug/com/example/nativelibrary/NativeCallJava.class

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativelibrary_Native_getStringLength(JNIEnv *env, jobject thiz, jstring str) {
    return env->GetStringLength(str);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_createString(JNIEnv *env, jobject thiz) {
    return (*env).NewStringUTF("Hello world JNI");
}

extern "C"
JNIEXPORT jchar JNICALL
Java_com_example_nativelibrary_Native_getCharWithIndex(JNIEnv *env, jobject thiz, jstring str,jint index) {
    const jchar* jchar1 = env->GetStringChars(str,NULL);
    env->ReleaseStringChars(str,jchar1);
    return *(jchar1 + index);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_subString(JNIEnv *env, jobject thiz,jstring str, jint start_index) {
   char *subStr = new char;
   env ->GetStringUTFRegion(str,start_index,env ->GetStringLength(str) - start_index,subStr);
   return env->NewStringUTF(subStr);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativelibrary_Native_getJNIVersion(JNIEnv *env, jobject thiz) {
   return (*env).GetVersion();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativelibrary_Native_getArrayLenght(JNIEnv *env, jobject thiz, jintArray array) {
    return env ->GetArrayLength(array);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_getElementFromArray(JNIEnv *env, jobject thiz, jint index,jobjectArray array) {
    return static_cast<jstring>(env->GetObjectArrayElement(array, index));
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_nativelibrary_Native_createArray(JNIEnv *env, jobject thiz) {
    int length = 5;
    jintArray array = env->NewIntArray(length);
    jint *jint1 = env->GetIntArrayElements(array,NULL);
    for(int i=0;i<length;i++){
        jint1[i] = i * 10;
    }
    env->ReleaseIntArrayElements(array,jint1,0);
    return array;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_setObjectArrayElement(JNIEnv *env, jobject thiz,jobjectArray array, jint index,jstring value) {
    env->SetObjectArrayElement(array,index,value);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_nativelibrary_Native_subArray(JNIEnv *env, jobject thiz, jintArray array,jint startIndex,jint endIndex) {
    int length = endIndex - startIndex + 1;
    jintArray newArray = env->NewIntArray(length);
    jint *jint1 = env->GetIntArrayElements(newArray, NULL);
    env->GetIntArrayRegion(array, startIndex, length , jint1);

    //0:表示会把缓冲区（即在GetArrayElements方法中返回的）的内容拷贝回原始Java数组中，然后释放缓冲区
    //JNI_COMMIT：表示也会把缓冲区的内容拷贝回原始Java数组中，但是不会释放缓冲区
    //JNI_ABORT：表示不会把缓冲区的内容拷贝回原始Java数组中，直接释放缓冲区。
    env->ReleaseIntArrayElements(newArray, jint1, 0);
    return newArray;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_nativelibrary_Native_sortArray(JNIEnv *env, jobject thiz, jintArray array) {
//    jint *intArray = env->GetIntArrayElements(array,NULL);
//    int length = env->GetArrayLength(array);

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_nativeCallJavaCustomMethod(JNIEnv *env, jobject thiz) {
    jstring str = NULL;
    jclass clz = (*env).FindClass("com/example/nativelibrary/NativeCallJava");
    jmethodID ctor = (*env).GetMethodID(clz,"<init>","()V");
    jobject obj = env->NewObject(clz,ctor);
    jmethodID mid = (*env).GetMethodID(clz, "sayHelloFromJava","(Ljava/lang/String;)Ljava/lang/String;");
    if (mid) {
        jstring jmsg = (*env).NewStringUTF("I'm born in native.");
        str = static_cast<jstring>((*env).CallObjectMethod(obj, mid, jmsg));
    }
    return str;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_nativeCallJavaStaticMethod(JNIEnv *env, jobject thiz) {
    jstring str = NULL;
    jclass clz = (*env).FindClass("com/example/nativelibrary/NativeCallJava");
    jmethodID mid = (*env).GetStaticMethodID(clz, "sayHello","(Ljava/lang/String;)Ljava/lang/String;");
    if (mid) {
        jstring jmsg = (*env).NewStringUTF("I'm born in native.");
        str = static_cast<jstring>((*env).CallStaticObjectMethod(clz, mid, jmsg));
    }
    return str;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_nativeCallJavaParentMethod(JNIEnv *env, jobject thiz,jobject obj) {
    jclass fclass=env->FindClass("com/example/nativelibrary/NativeCallJavaParent");
    jmethodID fm= env->GetMethodID(fclass,"toString","()Ljava/lang/String;");
    return (jstring)env->CallNonvirtualObjectMethod(obj,fclass,fm);//第二个参数决定调用哪个类的方法
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_nativeCallJavaCustomProperty(JNIEnv *env, jobject thiz) {
    jclass clz = (*env).FindClass("com/example/nativelibrary/NativeCallJava");
    jmethodID ctor = (*env).GetMethodID(clz,"<init>","()V");
    jobject obj = env->NewObject(clz,ctor);
    jfieldID  _jfieldID = env->GetFieldID(clz,"customName", "Ljava/lang/String;");
    jstring _jstring = (jstring)env->GetObjectField(obj,_jfieldID);
    return _jstring;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativelibrary_Native_nativeCallJavaStaticProperty(JNIEnv *env, jobject thiz) {
    jclass clz = (*env).FindClass("com/example/nativelibrary/NativeCallJava");
    jfieldID  _jfieldID = env->GetStaticFieldID(clz,"staticName", "Ljava/lang/String;");
    jstring _jstring = (jstring)env->GetStaticObjectField(clz,_jfieldID);
    return _jstring;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_nativeSetJavaCustomProperty(JNIEnv *env, jobject thiz,jobject obj) {
    jclass clz = (*env).GetObjectClass(obj);
    jfieldID  _jfieldID = env->GetFieldID(clz,"customName", "Ljava/lang/String;");
    env->SetObjectField(obj,_jfieldID,env->NewStringUTF("JniCustomName"));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_nativeSetJavaStaticProperty(JNIEnv *env, jobject thiz,jclass cls) {
    jfieldID  _jfieldID = env->GetStaticFieldID(cls,"staticName", "Ljava/lang/String;");
    env->SetStaticObjectField(cls,_jfieldID,env->NewStringUTF("JniStaticName"));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_nativelibrary_Native_nativeCreateJavaObject(JNIEnv *env, jobject thiz,jclass cls) {
    jmethodID ctor = (*env).GetMethodID(cls,"<init>","()V");
    jobject obj = env->NewObject(cls,ctor);
    return obj;
   // return env->AllocObject(cls);//该种创建方式，创建的对象除了静态属性，所以实例属性为空
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_nativeCheckException(JNIEnv *env, jobject thiz) {
    jthrowable exc = NULL;
    jclass clz = (*env).FindClass("com/example/nativelibrary/NativeCallJava");
    jmethodID mid = (*env).GetStaticMethodID(clz, "exceptionCallBack","()V");
    if (mid) {
        env->CallStaticVoidMethodA(clz,mid,NULL);
    }
    if(env -> ExceptionCheck()){// 检查JNI调用是否有引发异常也可以用 if(env->ExceptionOccurred() != NULL)替换
        env ->ExceptionDescribe();//调用ExceptionDescribe函数打印这个异常的堆栈信息
        env ->ExceptionClear(); // 清除异常堆栈信息(如果不清除，后面调用ThrowNew抛出的异常堆栈信息会覆盖前面的异常信息)，且在Java层不会打印异常的堆栈信息
    }

    //调用ExceptionClear()后，后续代码才能使用env
    //发生异常后，本地接口并不会马上退出，而是会继续执行后面的代码，所以我们在调用完一个任何一个JNI接口之后，必须要做的一件事情就是检查这次JNI调用是否发生了异常，如果发生了异常不处理，而继续让程序执行后面的逻辑，将会产生不可预知的后果。
    jmethodID midNormal = (*env).GetStaticMethodID(clz, "normalCallBack","()V");
    if (midNormal) {
        env->CallStaticVoidMethodA(clz,midNormal,NULL);
    }

    jclass  expetionClazz = env->FindClass("java/lang/Exception");//也可以加载自定义的Java异常类
    if(expetionClazz == NULL) return;
    env->ThrowNew(expetionClazz,"this is a exception");//自定义异常信息
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_catchNativeException(JNIEnv *env, jobject thiz) {
    jthrowable exc = NULL;
    jclass clz = (*env).FindClass("com/example/nativelibrary/NativeCallJava");
    jmethodID mid = (*env).GetStaticMethodID(clz, "exceptionCallBack","()V");
    if (mid) {
        env->CallStaticVoidMethodA(clz,mid,NULL);
    }
    jthrowable th = env->ExceptionOccurred();
    if(th != NULL){// 检查JNI调用是否有引发异常也可以用 if(env->ExceptionOccurred() != NULL)替换
        env ->ExceptionDescribe();//调用ExceptionDescribe函数打印这个异常的堆栈信息
        env ->ExceptionClear(); // 清除异常堆栈信息(如果不清除，后面调用ThrowNew抛出的异常堆栈信息会覆盖前面的异常信息)，且在Java层不会打印异常的堆栈信息
        env ->Throw(th);
    }
}

/**
 * Java代码的内存是由垃圾回收器来管理，而JNI代码则不受Java的垃圾回收器来管理。所以JNI代码提供了一组函数，来管理通过JNI代码生成的JNI对象，比如jobject，jclass，jstring，jarray等。
 * (1)在JNI接口函数中引用JNI对象的局部变量，都是对JNI对象的局部引用，一旦JNI接口函数返回，所有这些JNI对象都会被自动释放。不过我们也可以采用JNI代码提供的DeleteLocalRef函数来删除一个局部JNI对象引用
 * (2)对于JNI对象，绝对不能简单的声明一个全局变量，在JNI接口函数里面给这个全局变量赋值这么简单，一定要使用JNI代码提供的管理JNI对象的函数.
 *  JNI 全局引用分为两种: 一种全局引用,这种引用会阻止Java垃圾回收器回收JNI代码引用的对象；
 *  另一种是弱全局引用，这种全局引用不会阻止垃圾回收器回收JNI 代码引用的Java对象
 *  - NewGlobalRef用来创建强全局引用的JNI对象
 *  - DeleteGlobalRef用来删除强全局引用的JNI对象
 *  - NewWeakGlobalRef用来创建弱全局引用的JNI对象
 *  - DeleteWeakGlobalRef用来删除弱全局引用的JNI对象
 *  - IsSameObject用来判断两个JNI对象是否相同
 */
jobject  gThiz; //全局JNI对象引用
jobject  gWeakThiz;//全局JNI对象弱应用
extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_nativeReferenceOperation(JNIEnv *env, jobject thiz) {
   //声明局部变量clazz
    jclass clazz = env->GetObjectClass(thiz);
    //手动释放 局部变量 clazz ;DeleteLocalRef 也可不用手动调用，JNI方法返回之后，会自动释放局部JNI变量
    env->DeleteLocalRef(clazz);
    LOGD("局部引用 已经被释放了");

    //---- 强全局变量
    gThiz = env->NewGlobalRef(thiz);//生成全局的JNI 对象引用,这样生成的全局的JNI对象 才可以在其他函数中使用
    env->DeleteGlobalRef(gThiz);//在我们不需要gThis这个全局JNI对象应用时，可以将其删除。
    LOGD("全局强引用 已经被释放了");

    //---- 全局弱引用
    gWeakThiz = env->NewWeakGlobalRef(thiz);//生成全局的JNI对象引用，这样生成的全局的JNI对象才可以在其它函数中使用
    if(env->IsSameObject(gWeakThiz,NULL)){
        LOGD("全局弱引用 已经被释放了");
    }
    //释放 全局弱应用对象
    env->DeleteWeakGlobalRef(gWeakThiz);
    LOGD("全局弱引用 已经被释放了");
}

/**
* 由于从Java中访问native方法并没有线程限制，所以我们的本地代码并不一定只会运行在main线程中，一旦本地方法被多个线程调用，那么我们就不得不考虑如何保证数据的安全访问问题了。
* 为了解决这个问题，JNI提供了监视器机制，与Java中的synchronize相同，用来对临界区进行保护性访问。
* JNI 利用 java 对象进行线程同步
* MonitorEnter函数用来锁定Java对象
* MonitorExit函数用来释放Java对象锁
* @param lock
*/
extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativelibrary_Native_nativeSynchronized(JNIEnv *env, jobject thiz, jobject obj) {
    //加锁
    env->MonitorEnter(obj);

    //doSomething
    LOGD("enter lock success, do something now");

    //释放锁
    env->MonitorExit(obj);

    LOGD("exit lock success");

}




//****************************动态注册****************************


// 指定要注册的类
#define JNIREG_CLASS "com/example/nativelibrary/Native"
#define JNIHOOK_CLASS "com/example/nativelibrary/NativeMethod"
static struct {
    jfieldID f1;
    jfieldID f2;
    jmethodID m1;
    jmethodID m2;
    size_t methodSize;
    size_t fieldSize;
} hookClassInfo;

static void initMethodHookClassInfo(JNIEnv *env){
    hookClassInfo.f1 = env -> GetStaticFieldID(env->FindClass(JNIHOOK_CLASS), "f1", "Ljava/lang/Object;");
    hookClassInfo.f2 = env -> GetStaticFieldID(env->FindClass(JNIHOOK_CLASS), "f2","Ljava/lang/Object;");
    hookClassInfo.m1 = env -> GetStaticMethodID(env->FindClass(JNIHOOK_CLASS), "m1", "()V");
    hookClassInfo.m2 = env -> GetStaticMethodID(env->FindClass(JNIHOOK_CLASS), "m2", "()V");
    hookClassInfo.methodSize = reinterpret_cast<size_t>(hookClassInfo.m2) - reinterpret_cast<size_t>(hookClassInfo.m1);
    hookClassInfo.fieldSize = reinterpret_cast<size_t>(hookClassInfo.f2) - reinterpret_cast<size_t>(hookClassInfo.f1);
}

static long hookMethod(JNIEnv *env, jobject thiz, jobject src_method,jobject des_method) {
    void* srcMethod = reinterpret_cast<void*>(env -> FromReflectedMethod(src_method));
    void* destMethod = reinterpret_cast<void*>(env -> FromReflectedMethod(des_method));
    int* backupMethod = new int[hookClassInfo.methodSize];
    memcpy(backupMethod, srcMethod, hookClassInfo.methodSize);
    memcpy(srcMethod, destMethod, hookClassInfo.methodSize);
    return reinterpret_cast<long>(backupMethod);
}

static void restoreMethod(JNIEnv *env, jobject thiz, jobject src_method,jlong src_method_ptr) {
    int* backupMethod = reinterpret_cast<int*>(src_method_ptr);
    void* artMethodSrc = reinterpret_cast<void*>(env -> FromReflectedMethod(src_method));
    memcpy(artMethodSrc, backupMethod, hookClassInfo.methodSize);
    delete []backupMethod;
}

static long hookField(JNIEnv *env, jobject thiz, jobject src_field,jobject des_field) {
    void* srcField = reinterpret_cast<void*>(env -> FromReflectedField(src_field));
    void* destField = reinterpret_cast<void*>(env -> FromReflectedField(des_field));
    int* backupField = new int[hookClassInfo.fieldSize];
    memcpy(backupField, srcField, hookClassInfo.fieldSize);
    memcpy(srcField, destField, hookClassInfo.fieldSize);
    return reinterpret_cast<long>(backupField);
}

static void restoreField(JNIEnv *env, jobject thiz, jobject src_field,jlong src_field_ptr) {
    int* backupField = reinterpret_cast<int*>(src_field_ptr);
    void* artFieldSrc = reinterpret_cast<void*>(env -> FromReflectedField(src_field));
    memcpy(artFieldSrc, backupField, hookClassInfo.fieldSize);
    delete []backupField;
}

jstring dynamicRegisterNative(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("动态注册成功，我被调用了");
}

/** 取消注册类的本地方法。类将返回到链接或注册了本地方法函数前的状态。
 * 该函数不应在常规平台相关代码中使用。相反，它可以为某些程序提供一种重新加载和重新链接本地库的途径。
 */
jstring dynamicUnregisterNative(JNIEnv *env, jobject thiz) {
    jclass jcl = env->FindClass(JNIREG_CLASS);
    env->UnregisterNatives(jcl);
    return env->NewStringUTF("动态注销成功，依赖动态注册的native方法均不可调用");
}
/*需要注册的函数列表，放在JNINativeMethod 类型的数组中，
以后如果需要增加函数，只需在这里添加就行了
参数：
1.java中用native关键字声明的函数名
2.签名（传进来参数类型和返回值类型的说明）
3.C/C++中对应函数的函数名（地址）
*/
static JNINativeMethod gMethods[] = {
        { "dynamicRegisterNative", "()Ljava/lang/String;", (void*)dynamicRegisterNative},
        { "dynamicUnregisterNative", "()Ljava/lang/String;", (void*)dynamicUnregisterNative},
        { "hookMethod", "(Ljava/lang/reflect/Method;Ljava/lang/reflect/Method;)J", (void*)hookMethod},
        { "restoreMethod", "(Ljava/lang/reflect/Method;J)V", (void*)restoreMethod},
        { "hookField", "(Ljava/lang/reflect/Field;Ljava/lang/reflect/Field;)J", (void*)hookField},
        { "restoreField", "(Ljava/lang/reflect/Field;J)V", (void*)restoreField},
};

/***
 * 注册native方法,此函数通过调用RegisterNatives方法来注册我们的函数
 */
static int registerNativeMethods(JNIEnv* env){
    int methodsNum = sizeof(gMethods) / sizeof(gMethods[0]);
    jclass clazz;
    //找到声明native方法的类
    clazz = env->FindClass(JNIREG_CLASS);
    if(clazz == NULL){
        return JNI_FALSE;
    }
    //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
    if(env->RegisterNatives(clazz,gMethods,methodsNum) < 0){
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/**
 *动态注册基本思想是在JNI_Onload()函数中通过JNI中提供的RegisterNatives()方法来将C/C++方法和java方法对应起来(注册)
 * 调用System.loadLibrary的时候,调用JNI_OnLoad该方法,在这个函数中一般是做一些初始化相关操作, 我们可以在这个方法里面注册函数, 注册整体流程如下:
 * 1.编写Java端的相关native方法
 * 2.编写C/C++代码, 实现JNI_Onload()方法
 * 3.将Java 方法和 C/C++方法通过签名信息一一对应起来
 * 4.通过JavaVM获取JNIEnv, JNIEnv主要用于获取Java类和调用一些JNI提供的方法
 * 5.使用类名和对应起来的方法作为参数, 调用JNI提供的函数RegisterNatives()注册方法
 * @return
 */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env = NULL;
    jint result = -1;

    // 获取JNI env变量
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        // 失败返回-1
        return result;
    }

    assert(env != NULL);

    // 动态注册native方法
    if(!registerNativeMethods(env)){
        return result;
    }
    initMethodHookClassInfo(env);
    // 返回成功
    result = JNI_VERSION_1_4;
    return result;
}







