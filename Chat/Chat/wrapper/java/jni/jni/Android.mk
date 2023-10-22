LOCAL_PATH := $(call my-dir)
DIRECTORY_ROOT := $(LOCAL_PATH)/../../../../../
PARSER_DIRECTORY := $(DIRECTORY_ROOT)/ChatParser/
SDK_DIRECTORY := $(DIRECTORY_ROOT)/Chat/
SDK_JNI_DIRECTORY := $(DIRECTORY_ROOT)/Chat/wrapper/java/jni
NDK_FLAGS := -DNDK_BUILD -pthread
IPVCORE_DIRECTORY := $(DIRECTORY_ROOT)/../../ipvcore/core
CURL_PATH        := $(DIRECTORY_ROOT)/../libs/curl

#LOCAL_CFLAGS += -DANDROID -D_LINUX -DDEBUGLOG -D_INDENT_DB_PRINT -fsigned-char -fno-inline -D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS -D_POSIX_PER_PROCESS_TIMER_SOURCE -D_PTHREADS -DUNICODE


################################# CHAT_PARSER #################################
include $(CLEAR_VARS)

LOCAL_PATH := $(PARSER_DIRECTORY)/src

LOCAL_C_INCLUDES := 	$(LOCAL_PATH)/ \
			$(IPVCORE_DIRECTORY) \
			$(CURL_PATH)/include/nix \

LOCAL_MODULE := chatparsercore

LOCAL_CFLAGS := -std=gnu++11 $(NDK_FLAGS) 

LOCAL_SRC_FILES := $(LOCAL_PATH)/ByteArray.cpp\
	$(LOCAL_PATH)/ChatParser.cpp\
	$(LOCAL_PATH)/PacketDTO.cpp\
	$(LOCAL_PATH)/MemberDTO.cpp\
	$(LOCAL_PATH)/PacketTemplate.cpp\
	$(LOCAL_PATH)/SeenPacketDTO.cpp\
	$(LOCAL_PATH)/FriendMessageStatusDTO.cpp\
	$(LOCAL_PATH)/GroupActivityDTO.cpp\
	$(LOCAL_PATH)/GroupDTO.cpp\
	$(LOCAL_PATH)/RoomDTO.cpp\
	$(LOCAL_PATH)/SDKMessageDTO.cpp\
	$(LOCAL_PATH)/ConversationDTO.cpp\
	$(LOCAL_PATH)/PublicChatMemberDTO.cpp\
        $(LOCAL_PATH)/DataCounter.cpp
		
LOCAL_XOM := false

include $(BUILD_STATIC_LIBRARY)

################################# CHAT_PARSER #################################


#################################   IPVCORE   #################################

include $(CLEAR_VARS)
LOCAL_MODULE     := libcurl

LOCAL_SRC_FILES  := $(CURL_PATH)/android/$(TARGET_ARCH_ABI)/libcurl.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
FILE_LIST := $(wildcard $(IPVCORE_DIRECTORY)/**/*.cpp)
FILE_LIST += $(wildcard $(IPVCORE_DIRECTORY)/**/**/*.cpp)

LOCAL_MODULE     := ipvcore
LOCAL_SRC_FILES  := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_C_INCLUDES := $(IPVCORE_DIRECTORY) $(CURL_PATH)/include/nix
LOCAL_CFLAGS     := -g -std=gnu++11 -D_PTHREADS
#LOCAL_LDLIBS     := -lz -llog

LOCAL_STATIC_LIBRARIES := libcurl

LOCAL_XOM := false

include $(BUILD_STATIC_LIBRARY)

#################################   IPVCORE   #################################



################################# SDK #################################
include $(CLEAR_VARS)

LOCAL_PATH := $(SDK_DIRECTORY)/src

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
	$(PARSER_DIRECTORY)/src \
	$(IPVCORE_DIRECTORY) \
	$(CURL_PATH)/include/nix \

LOCAL_MODULE := imsdkcore

LOCAL_CFLAGS := -std=gnu++11 $(NDK_FLAGS) 

LOCAL_SRC_FILES := $(LOCAL_PATH)/ApiStatus.cpp\
	$(LOCAL_PATH)/ChatPacketBuilder.cpp\
	$(LOCAL_PATH)/EventProcessor.cpp\
	$(LOCAL_PATH)/KeepaliveProcessor.cpp\
	$(LOCAL_PATH)/PacketReceiver.cpp\
	$(LOCAL_PATH)/Scheduler.cpp\
	$(LOCAL_PATH)/Thread.cpp\
	$(LOCAL_PATH)/Chat.cpp\
	$(LOCAL_PATH)/Connection.cpp\
	$(LOCAL_PATH)/IChatEventHandler.cpp\
	$(LOCAL_PATH)/Logger.cpp\
	$(LOCAL_PATH)/ResendProcessor.cpp\
	$(LOCAL_PATH)/ChatEvent.cpp\
	$(LOCAL_PATH)/Event.cpp\
	$(LOCAL_PATH)/KeepalivePacket.cpp\
	$(LOCAL_PATH)/PacketProcessor.cpp\
	$(LOCAL_PATH)/PacketTimeId.cpp\
	$(LOCAL_PATH)/ResourceManager.cpp\
	$(LOCAL_PATH)/Socket.cpp\
	$(LOCAL_PATH)/UnifiedProcessor.cpp\
	$(LOCAL_PATH)/FriendInformation.cpp\
	$(LOCAL_PATH)/DuplicateChecker.cpp\
	$(LOCAL_PATH)/GroupInformation.cpp\
	$(LOCAL_PATH)/CloudNotificationHandler.cpp\
	$(LOCAL_PATH)/InternetChecker.cpp\
	$(LOCAL_PATH)/sha1.cpp\
	$(LOCAL_PATH)/HashAlgorithm.cpp\
	$(LOCAL_PATH)/DataEncryption.cpp\

LOCAL_XOM := false

include $(BUILD_STATIC_LIBRARY)

################################# SDK #################################







include $(CLEAR_VARS)

LOCAL_PATH := $(SDK_JNI_DIRECTORY)/

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
	$(PARSER_DIRECTORY)/src \
	$(SDK_DIRECTORY)/src \
	$(IPVCORE_DIRECTORY) \
	$(CURL_PATH)/include/nix \

LOCAL_MODULE := imsdk



################################# SDK_JNI #################################
include $(CLEAR_VARS)

LOCAL_PATH := $(SDK_JNI_DIRECTORY)/

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
	$(PARSER_DIRECTORY)/src \
	$(SDK_DIRECTORY)/src \
	$(IPVCORE_DIRECTORY) \
	$(CURL_PATH)/include/nix \

LOCAL_MODULE := imsdk

LOCAL_CFLAGS := -std=gnu++11 $(NDK_FLAGS)

LOCAL_SRC_FILES := $(LOCAL_PATH)/com_ringid_imsdk_Chat.cpp\
	$(LOCAL_PATH)/ChatEventHandler.cpp\
	$(LOCAL_PATH)/MemberDTOConversion.cpp\
	$(LOCAL_PATH)/ArrayListManipulation.cpp\
	$(LOCAL_PATH)/SeenPacketDTOConversion.cpp\
	$(LOCAL_PATH)/FriendMessageStatusDTOConversion.cpp\
	$(LOCAL_PATH)/GroupActivityDTOConversion.cpp\
	$(LOCAL_PATH)/GroupDTOConversion.cpp\
	$(LOCAL_PATH)/RoomDTOConversion.cpp\
	$(LOCAL_PATH)/SDKMessageDTOConversion.cpp\
	$(LOCAL_PATH)/PublicChatMemberDTOConversion.cpp\
	$(LOCAL_PATH)/ConversationDTOConversion.cpp\
	$(LOCAL_PATH)/DataCounterConversion.cpp\
	$(LOCAL_PATH)/com_ringid_imsdk_InternetChecker.cpp\
	$(LOCAL_PATH)/com_ringid_imsdk_DataEncryption.cpp

LOCAL_LDLIBS = -llog -lz
	
LOCAL_STATIC_LIBRARIES := imsdkcore chatparsercore ipvcore

LOCAL_XOM := false

include $(BUILD_SHARED_LIBRARY)

################################# SDK_JNI #################################
