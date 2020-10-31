package com.example.nativeapplication

import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.nativelibrary.HookManager
import com.example.nativelibrary.Native
import com.example.nativelibrary.NativeCallJava
import com.example.nativelibrary.NativeCallJavaParent

class MainActivity : AppCompatActivity() ,View.OnClickListener{
    private lateinit var nativeCallJava:NativeCallJava

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        nativeCallJava = NativeCallJava()
    }

    override fun onClick(v: View?) {
        try {
            v?.let {
                when (it.id) {
                    R.id.jni_version -> {
                        var jniVerison = Native.getJNIVersion().toString()
                        Toast.makeText(this, jniVerison, Toast.LENGTH_SHORT).show()
                    }

                    R.id.new_string -> {
                        var newString = Native.createString()
                        Toast.makeText(this, newString, Toast.LENGTH_SHORT).show()
                    }
                    R.id.string_length -> {
                        var length = Native.getStringLength("hello zhangshidong").toString()
                        Toast.makeText(
                            this,
                            "字符串\"hello zhangshidong\"的length：$length",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.sub_string -> {
                        var subString = Native.subString("I am zhangshidong", 3)
                        Toast.makeText(
                            this,
                            "字符串I am zhangshidong截取后为：$subString",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.char_index -> {
                        var char = Native.getCharWithIndex("hello zhangshidong", 6).toString()
                        Toast.makeText(
                            this,
                            "字符串hello zhangshidong中下标为6的字符为：$char",
                            Toast.LENGTH_SHORT
                        ).show()
                    }

                    R.id.new_array -> {
                        var newArray = Native.createArray().toList().toString()
                        Toast.makeText(this, newArray, Toast.LENGTH_SHORT).show()
                    }
                    R.id.array_length -> {
                        var array = intArrayOf(1, 2, 3, 4, 5, 6)
                        var length = Native.getArrayLenght(array).toString()
                        Toast.makeText(this, "数组(1,2,3,4,5,6)的length：$length", Toast.LENGTH_SHORT)
                            .show()
                    }
                    R.id.element_index -> {
                        var array = arrayOf("1", "2", "3", "4", "5")
                        var str = Native.getElementFromArray(3, array)
                        Toast.makeText(
                            this,
                            "数组(\"1\",\"2\",\"3\",\"4\",\"5\")中下标为3的元素为$str",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.set_element_index -> {
                        var array = arrayOf("1", "2", "3", "4", "5")
                        Native.setObjectArrayElement(array, 2, "10")
                        Toast.makeText(
                            this,
                            "(\"1\",\"2\",\"3\",\"4\",\"5\") => ${array.toList()}",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.sub_array -> {
                        var array = intArrayOf(1, 2, 3, 4, 5, 6)
                        var newArray = Native.subArray(array, 2, 4)
                        Toast.makeText(
                            this,
                            "截取前array:${array.toList()}, 截取后newArray:${newArray.toList()}",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.sort_array -> {
                        var array = intArrayOf(10, 2, 3, 140, 51, 6, 0, 11)
                        var newArray = Native.sortArray(array)
                        Toast.makeText(
                            this,
                            "array排序前${array.toList()}, array排序后${newArray.toList()}",
                            Toast.LENGTH_SHORT
                        ).show()
                    }

                    R.id.native_call_java_custom_property -> {
                        var str = Native.nativeCallJavaCustomProperty()
                        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
                    }
                    R.id.native_call_java_static_property -> {
                        var str = Native.nativeCallJavaStaticProperty()
                        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
                    }
                    R.id.native_set_java_custom_property -> {
                        var nativeCallJava = NativeCallJava()
                        var customName = nativeCallJava.customName
                        Native.nativeSetJavaCustomProperty(nativeCallJava)
                        Toast.makeText(
                            this,
                            "customName初始值：$customName, 改变后的值：${nativeCallJava.customName}",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.native_set_java_static_property -> {
                        var staticName = NativeCallJava.staticName
                        Native.nativeSetJavaStaticProperty(NativeCallJava::class.java)
                        Toast.makeText(
                            this,
                            "staticName初始值：$staticName, 改变后的值：${NativeCallJava.staticName}",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                    R.id.native_call_java_custom_method -> {
                        var str = Native.nativeCallJavaCustomMethod()
                        Toast.makeText(this, "NativeCallJavaCustomMethod: $str", Toast.LENGTH_SHORT)
                            .show()
                    }
                    R.id.native_call_java_static_method -> {
                        var str = Native.nativeCallJavaStaticMethod()
                        Toast.makeText(this, "NativeCallJavaStaticMethod: $str", Toast.LENGTH_SHORT)
                            .show()
                    }
                    R.id.native_call_parent_java_method -> {
                        var objects = NativeCallJava() as NativeCallJavaParent
                        var str = Native.nativeCallJavaParentMethod(objects)
                        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
                    }
                    R.id.native_create_java_object -> {
                        var objects =
                            Native.nativeCreateJavaObject(NativeCallJava::class.java) as NativeCallJava
                        var result: String =
                            if (objects != null) "对象创建成功${objects.toString()}" else "对象创建失败null"
                        Toast.makeText(this, result, Toast.LENGTH_SHORT).show()
                    }
                    R.id.check_exception -> {
                        try {
                            Native.nativeCheckException()
                        } catch (th: Throwable) {//捕捉从c++层抛出来的自定义异常信息
                            th.printStackTrace()
                            Toast.makeText(this, th.message, Toast.LENGTH_SHORT).show()
                        }

                    }
                    R.id.catch_exception -> {
                        try {
                            Native.catchNativeException()
                        } catch (th: Throwable) {//捕捉从c++层抛出来的异常信息
                            th.printStackTrace()
                            Toast.makeText(this, th.message, Toast.LENGTH_SHORT).show()
                        }
                    }
                    R.id.reference_operation -> {
                        Native.nativeReferenceOperation()
                        Toast.makeText(this, "操作成功，详见日志和代码内部逻辑", Toast.LENGTH_SHORT).show()
                    }
                    R.id.native_synchronized -> {
                        Native.nativeSynchronized(this)
                        Toast.makeText(this, "操作成功，详见日志和代码内部逻辑", Toast.LENGTH_SHORT).show()
                    }
                    R.id.java_reference_native_object -> {

                    }
                    R.id.native_reference_java_object -> {

                    }
                    R.id.dynamic_register_natives -> {
                        var result = Native.dynamicRegisterNative()
                        Toast.makeText(this, result, Toast.LENGTH_SHORT).show()
                    }
                    R.id.dynamic_unRegister_natives -> {
                        var result = Native.dynamicUnregisterNative()
                        Toast.makeText(this, result, Toast.LENGTH_SHORT).show()
                    }

                    R.id.reflectedField -> {
                        var srcField = NativeCallJava::class.java.getDeclaredField("srcField")
                        var desField = NativeCallJava::class.java.getDeclaredField("desField")
                        HookManager.hookField(srcField, desField)
                        Toast.makeText(this, nativeCallJava.srcField, Toast.LENGTH_SHORT).show()
                    }
                    R.id.restoreField -> {
                        var desField = NativeCallJava::class.java.getDeclaredField("desField")
                        HookManager.restoreField(desField)
                        Toast.makeText(this, nativeCallJava.srcField, Toast.LENGTH_SHORT).show()
                    }
                    R.id.reflectedMethod -> {
                        var srcMethod = NativeCallJava::class.java.getDeclaredMethod("srcMethod")
                        var desMethod = NativeCallJava::class.java.getDeclaredMethod("desMethod")
                        var str = nativeCallJava.srcMethod() //先调用，否则hook完，没有该方法
                        HookManager.hookMethod(srcMethod, desMethod)
                        Toast.makeText(this, nativeCallJava.srcMethod(), Toast.LENGTH_SHORT).show()
                    }
                    R.id.restoreMethod -> {
                        var desMethod = NativeCallJava::class.java.getDeclaredMethod("desMethod")
                        HookManager.restoreMethod(desMethod)
                        Toast.makeText(this, nativeCallJava.srcMethod(), Toast.LENGTH_SHORT).show()
                    }
                }
            }
        }catch (th: Throwable){
            th.printStackTrace()
            Toast.makeText(this, th.message, Toast.LENGTH_SHORT).show()
        }
    }

}
