package com.example.nativelibrary

class JniPerson {
    //保存c++类的地址
    var nativePerson: Long = 0

    //构造函数
    constructor () {
        nativePerson = createNativeObject()
    }

    fun setAge(age: Int) {
        setAge(nativePerson, age)
    }

    fun getAge(): Int {
        return getAge(nativePerson)
    }

    fun setName(name:String){
        setName(nativePerson,name)
    }

    fun getName():String{
        return getName(nativePerson)
    }

    /**本地方法：创建c++对象并返回地址 */
    private external fun createNativeObject(): Long
    private external fun setAge(addr: Long, age: Int)
    private external fun getAge(addr: Long): Int
    private external fun setName(addr: Long,name:String)
    private external fun getName(addr: Long):String
}