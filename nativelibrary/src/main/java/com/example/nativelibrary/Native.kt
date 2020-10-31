package com.example.nativelibrary

import java.lang.reflect.Field
import java.lang.reflect.Method

object Native {

    //字符串相关操作
    external fun createString():String
    external fun getStringLength(str:String): Int
    external fun getCharWithIndex(str:String,index:Int):Char
    external fun subString(str: String,startIndex:Int):String

    //数组操作
    external fun getArrayLenght(array:IntArray):Int
    external fun createArray():IntArray
    external fun getElementFromArray(index:Int,array:Array<String>):String
    external fun setObjectArrayElement(array:Array<String>,index: Int,value:String)
    external fun subArray(array: IntArray,startIndex: Int,endIndex:Int):IntArray
    external fun sortArray(array: IntArray)

    //反射支持
    external fun nativeCallJavaStaticMethod():String
    external fun nativeCallJavaCustomMethod():String
    external fun nativeCallJavaParentMethod(obj:NativeCallJavaParent):String
    external fun nativeCallJavaCustomProperty():String
    external fun nativeCallJavaStaticProperty():String
    external fun nativeSetJavaStaticProperty(cls: Class<*>?)
    external fun nativeSetJavaCustomProperty(obj:NativeCallJava)
    external fun nativeCreateJavaObject(cls: Class<*>?):Any

    external fun hookMethod(srcMethod:Method, desMethod:Method):Long
    external fun restoreMethod(srcMethod:Method, srcMethodPtr:Long)
    external fun hookField(srcField: Field, desField:Field):Long
    external fun restoreField(srcField:Field,srcFieldPtr:Long)

    //异常操作
    external fun nativeCheckException()
    external fun catchNativeException()

    //全局引用和局部引用
    external fun nativeReferenceOperation()

    //本地同步
    external fun nativeSynchronized(obj:Any)

    //获取 JNI 版本信息
    external fun getJNIVersion():Int

    external fun dynamicRegisterNative():String
    external fun dynamicUnregisterNative():String

}