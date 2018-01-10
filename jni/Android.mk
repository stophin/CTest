LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := NanoJNI
LOCAL_CFLAGS := -O2
LOCAL_SRC_FILES := Unix_wrap.cxx
include $(BUILD_SHARED_LIBRARY)