package com.example.nativelibrary

import android.util.Pair
import java.lang.reflect.Field
import java.lang.reflect.Method
import java.util.concurrent.ConcurrentHashMap

object HookManager {

    private val HOOK_MAP: MutableMap<Pair<String, String>, FieldMethodHook?> = ConcurrentHashMap()

    fun hookMethod(originMethod: Method?, hookMethod: Method?): Boolean {
        originMethod?.let {
            hookMethod?.let {
                val key: Pair<String, String> = Pair.create(hookMethod.declaringClass.name, hookMethod.name)
                if (HOOK_MAP.containsKey(key)) {
                    val methodHook: FieldMethodHook? = HOOK_MAP[key]
                    methodHook?.restoreMethod()
                }
                val methodHook = FieldMethodHook(originMethod, hookMethod)
                HOOK_MAP[key] = methodHook
                methodHook.hookMethod()
                return true
            }
        }
        return false
    }

    fun restoreMethod(hookMethod: Method?):Boolean{
        hookMethod?.let {
            val key: Pair<String, String> = Pair.create(hookMethod.declaringClass.name, hookMethod.name)
            if (HOOK_MAP.containsKey(key)) {
                val methodHook: FieldMethodHook? = HOOK_MAP[key]
                methodHook?.restoreMethod()
                HOOK_MAP.remove(key)
                return true
            }
        }
        return false
    }


    fun restoreField(hookField: Field?):Boolean{
        hookField?.let {
            val key: Pair<String, String> = Pair.create(hookField.declaringClass.name, hookField.name)
            if (HOOK_MAP.containsKey(key)) {
                val methodHook: FieldMethodHook? = HOOK_MAP[key]
                methodHook?.restoreField()
                HOOK_MAP.remove(key)
                return true
            }
        }
        return false
    }

    fun hookField(originField: Field?, hookField: Field?): Boolean {
        originField?.let {
            hookField?.let {
                val key: Pair<String, String> = Pair.create(hookField.declaringClass.name, hookField.name)
                if (HOOK_MAP.containsKey(key)) {
                    val methodHook: FieldMethodHook? = HOOK_MAP[key]
                    methodHook?.restoreField()
                }
                val methodHook = FieldMethodHook(originField, hookField)
                HOOK_MAP[key] = methodHook
                methodHook.hookField()
                return true
            }
        }
        return false
    }

}