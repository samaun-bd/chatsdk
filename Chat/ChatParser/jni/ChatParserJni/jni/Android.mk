LOCAL_PATH := $(call my-dir)
MY_LOCAL_PATH := $(LOCAL_PATH)/../../..

#LOCAL_CFLAGS += -DANDROID -D_LINUX -DDEBUGLOG -D_INDENT_DB_PRINT -fsigned-char -fno-inline -D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS -D_POSIX_PER_PROCESS_TIMER_SOURCE -D_PTHREADS -DUNICODE

################################# CHAT_PARSER #################################
include $(CLEAR_VARS)
LOCAL_PATH := $(MY_LOCAL_PATH)/src

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_MODULE := chatparsercore

LOCAL_CFLAGS := -std=gnu++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/ByteArray.cpp\
	$(LOCAL_PATH)/ChatParser.cpp\
	$(LOCAL_PATH)/PacketDTO.cpp\
	$(LOCAL_PATH)/MemberDTO.cpp\
	$(LOCAL_PATH)/PacketTemplate.cpp

include $(BUILD_STATIC_LIBRARY)

################################# CHAT_PARSER #################################

################################# CHAT_PARSER_JNI #################################
include $(CLEAR_VARS)
LOCAL_PATH := $(MY_LOCAL_PATH)/jni/ChatParserJni

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
	$(MY_LOCAL_PATH)/src

LOCAL_MODULE := chatparser

LOCAL_CFLAGS := -std=gnu++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/com_ringid_imsdk_ChatParser.cpp

LOCAL_STATIC_LIBRARIES := chatparsercore

include $(BUILD_SHARED_LIBRARY)

################################# CHAT_PARSER_JNI #################################