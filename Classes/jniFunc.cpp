#include "jniFunc.h"
//#include "cocos-ext.h"
#include "../cocos2d/extensions/cocos-ext.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos2d.h"
USING_NS_CC;
#include "platform/android/jni/JniHelper.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

	void jni_vibrate()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "vibrator", "()V"))
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
#endif
	}

#ifdef __cplusplus
}
#endif
