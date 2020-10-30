package com.example.nativelibrary

import android.util.Log

class NativeCallJava:NativeCallJavaParent() {

    var customName: String = "nativeCallJavaCustomProperty"
    var srcField: String ="我是原属性"
    var desField: String = "我是hook后的属性"

    fun sayHelloFromJava(nativeMsg: String): String {
        var str = nativeMsg + " But shown in java"
        return str;
    }

    fun srcMethod():String{
        return "我是原来要执行的方法"
    }

    fun desMethod():String{
        return "我是被hook后执行的方法"
    }

    companion object{
        var staticName = "nativeCallJavaStaticProperty"

        //kotlin的object类和compaion object中，属性声明都是静态的，方法并不是静态，必须通过@JvmStatic注解，方法才会声明为静态
        @JvmStatic
        fun sayHello(nativeMsg: String): String {
            var str = nativeMsg + " But shown in java"
            return str
        }

        @JvmStatic
        fun exceptionCallBack(){
            var a = 20 / 0
        }

        @JvmStatic
        fun normalCallBack(){
            var a = 20 / 4
            Log.i("bug","正常JNI调用, a=$a")
        }
    }

    override fun toString(): String {
        return "customName:$customName, staticName:$staticName"
    }

}