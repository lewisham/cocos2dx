LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := \
../../Classes/AppDelegate.cpp \
../../Classes/dragonbones/animation/Animation.cpp \
../../Classes/dragonbones/animation/AnimationState.cpp \
../../Classes/dragonbones/animation/TimelineState.cpp \
../../Classes/dragonbones/animation/WorldClock.cpp \
../../Classes/dragonbones/core/Armature.cpp \
../../Classes/dragonbones/core/Bone.cpp \
../../Classes/dragonbones/core/Object.cpp \
../../Classes/dragonbones/core/Slot.cpp \
../../Classes/dragonbones/events/EventData.cpp \
../../Classes/dragonbones/factories/BaseFactory.cpp \
../../Classes/dragonbones/parsers/BaseDataParser.cpp \
../../Classes/dragonbones/parsers/ConstValues.cpp \
../../Classes/dragonbones/parsers/dbtinyxml2.cpp \
../../Classes/dragonbones/parsers/XMLDataParser.cpp \
../../Classes/dragonbones/renderer/DBCCArmature.cpp \
../../Classes/dragonbones/renderer/DBCCArmatureNode.cpp \
../../Classes/dragonbones/renderer/DBCCFactory.cpp \
../../Classes/dragonbones/renderer/DBCCLuaUtils.cpp \
../../Classes/dragonbones/renderer/DBCCSlot.cpp \
../../Classes/dragonbones/renderer/DBCCUtils.cpp \
../../Classes/lua_dragonbones_auto.cpp \
../../Classes/MD5/luamd5.cpp \
../../Classes/MD5/MD5.cpp \
../../Classes/extend/Extend.cpp \
hellolua/main.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Classes/dragonbones \
$(LOCAL_PATH)/../../Classes 

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
