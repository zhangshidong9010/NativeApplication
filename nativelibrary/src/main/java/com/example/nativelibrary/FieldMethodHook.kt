package com.example.nativelibrary

import java.lang.reflect.Field
import java.lang.reflect.Method

class FieldMethodHook {

    private lateinit var srcMethod: Method
    private lateinit var destMethod: Method
    private lateinit var srcField: Field
    private lateinit var destField: Field

    private var backupMethodPtr: Long = 0L
    private var backupFieldPtr: Long = 0L

    constructor(src: Method, dest: Method) {
        srcMethod = src
        destMethod = dest
        srcMethod!!.isAccessible = true
        destMethod!!.isAccessible = true
    }

    constructor(src: Field, dest: Field) {
        srcField = src
        destField = dest
        srcField!!.isAccessible = true
        destField!!.isAccessible = true
    }

    fun hookMethod() {
        if (backupMethodPtr == 0L) {
            backupMethodPtr = Native.hookMethod(srcMethod, destMethod)
        }
    }

    fun restoreMethod() {
        if (backupMethodPtr != 0L) {
            Native.restoreMethod(srcMethod, backupMethodPtr)
            backupMethodPtr = 0L
        }
    }

    fun hookField() {
        if (backupFieldPtr == 0L) {
            backupFieldPtr = Native.hookField(srcField, destField)
        }
    }

    fun restoreField() {
        if (backupFieldPtr != 0L) {
            Native.restoreField(srcField, backupFieldPtr)
            backupFieldPtr = 0L
        }
    }


}