package com.example.nativeapplication;

import android.util.Log;
import de.robv.android.xposed.XC_MethodHook;

class ThreadMethodHook extends XC_MethodHook {

    @Override
    protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
        super.beforeHookedMethod(param);
        Thread t = (Thread) param.thisObject;
        Log.i("test", "beforeHookedMethod thread:" + t.getName() + ", started");
    }

    @Override
    protected void afterHookedMethod(MethodHookParam param) throws Throwable {
        super.afterHookedMethod(param);
        Thread t = (Thread) param.thisObject;
        Log.i("test", "afterHookedMethod thread:" + t.getName() + ", exit");
    }
}
