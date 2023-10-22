/* 
 * File:   packet_template.h
 * Author: dipal
 *
 * Created on July 22, 2015, 11:40 AM
 */

#ifndef PACKET_TEMPLATE_H
#define PACKET_TEMPLATE_H

#include <vector>
#include <string>
#include "global.h"


/**
 Packet Types
 */
//Client Registration Constants



#define FRIEND_REGISTER                                 1
#define FRIEND_UNREGISTER                               2
#define FRIEND_REGISTER_CONFIRMATION                    3
#define FRIEND_CHAT_IDEL                                4
#define FRIEND_CHAT_MESSAGE_TYPING                      5
#define FRIEND_CHAT_MESSAGE                             6
#define FRIEND_CHAT_MESSAGE_EDIT                        7
#define FRIEND_CHAT_MESSAGE_BROKEN                      8
#define FRIEND_CHAT_MESSAGE_BROKEN_EDIT                 9
#define FRIEND_CHAT_MULTIPLE_MESSAGE                    10
#define GENERAL_ENCRYPTED_PACKET						11
#define GENERAL_ENCRYPTED_CONFIRMATION					12
#define FRIEND_CHAT_MESSAGE_DELIVERED                   15
#define FRIEND_CHAT_MESSAGE_SENT                        16
#define FRIEND_CHAT_MESSAGE_SEEN                        17
#define FRIEND_CHAT_MESSAGE_SEEN_CONFIRMATION           18
#define FRIEND_CHAT_MULTIPLE_MESSAGE_DELETE             19
#define FRIEND_CHAT_MESSAGE_DELETE_CONFIRMATION         20
#define ANONYMOUS_REGISTER                              21
#define ANONYMOUS_REGISTER_CONFIRMATION                 22
#define ANONYMOUS_UNREGISTER                            23
#define FRIEND_BROKEN_PACKET                            24
#define FRIEND_BROKEN_PACKET_CONFIRMATION               25
#define FRIEND_CALL_BUSY_MESSAGE                        26
#define FRIEND_BLOCK                                    27
#define FRIEND_UNBLOCK                                  28
#define FRIEND_BLOCK_UNBLOCK_CONFIRMATION               29
#define FRIEND_INIT_CHUNK_FILE_DOWNLOAD                 30
#define FRIEND_FILE_CHUNK_UPLOADED                      31
#define FRIEND_FILE_CHUNK_CONFIRMATION                  32
#define FRIEND_CHAT_MEDIA_TRANSFER_CANCEL               14
#define FRIEND_GET_CHAT_MESSAGE                         33
#define FRIEND_GET_CHAT_MESSAGE_CONFIRMATION            34
#define FRIEND_FILE_STREAM_REQUEST                      35
#define FRIEND_FILE_STREAM_REQUEST_CONFIRMATION         36
#define FRIEND_FILE_SESSION_REQUEST                     37
#define FRIEND_FILE_SESSION_REQUEST_CONFIRMATION        38
#define FRIEND_FILE_IDEL                                39
//#define FRIEND_FILE_STREAM_REQUEST                      36
//#define FRIEND_FILE_STREAM_REQUEST_CONFIRMATION         37
//#define FRIEND_FILE_STREAM_SEND                         38
//#define FRIEND_FILE_STREAM_SEND_CONFIRMATION            39

#define GROUP_REGISTER                                  41
#define GROUP_UNREGISTER                                42
#define GROUP_REGISTER_CONFIRMATION                     43
#define GROUP_INFORMATION                               46
#define GROUP_INFORMATION_CONFIRMATION                  47
#define GROUP_MEMBER_ADD                                51
#define GROUP_MEMBER_ADD_CONFIRMATION                   52
#define GROUP_MEMBER_REMOVE_LEAVE                       53
#define GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION          54
#define GROUP_MEMBER_TYPE_CHANGE                        55
#define GROUP_MEMBER_TYPE_CHANGE_CONFIRMATION           56
#define GROUP_INIT_CHUNK_FILE_DOWNLOAD                  57
#define GROUP_FILE_CHUNK_UPLOADED                       58
#define GROUP_FILE_CHUNK_CONFIRMATION                   59
#define GROUP_CHAT_IDEL                                 61
#define GROUP_CHAT_MESSAGE_TYPING                       62
#define GROUP_CHAT_MESSAGE                              63
#define GROUP_CHAT_MESSAGE_EDIT                         64
#define GROUP_CHAT_MESSAGE_BROKEN                       65
#define GROUP_CHAT_MESSAGE_BROKEN_EDIT                  66
#define GROUP_CHAT_MULTIPLE_MESSAGE                     67
#define GROUP_CHAT_MESSAGE_DELIVERED                    68
#define GROUP_CHAT_MESSAGE_SENT                         69
#define GROUP_CHAT_MESSAGE_SEEN                         70
#define GROUP_CHAT_MESSAGE_SEEN_CONFIRMATION            71
#define GROUP_CHAT_MULTIPLE_MESSAGE_DELETE              72
#define GROUP_CHAT_MESSAGE_DELETE_CONFIRMATION          73
#define GROUP_BROKEN_PACKET                             74
#define GROUP_BROKEN_PACKET_CONFIRMATION                75
#define GROUP_CHAT_GET_MESSAGE_SEEN_LIST_REQUEST        76
#define GROUP_CHAT_MESSAGE_SEEN_LIST                    77
#define GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION       78
#define GROUP_CHAT_MEDIA_TRANSFER_CANCEL                79
#define GROUP_GET_CHAT_MESSAGE                          80
#define GROUP_GET_CHAT_MESSAGE_CONFIRMATION             81
#define GROUP_FILE_STREAM_REQUEST                       82
#define GROUP_FILE_STREAM_REQUEST_CONFIRMATION          83
#define GROUP_FILE_SESSION_REQUEST                      84
#define GROUP_FILE_SESSION_REQUEST_CONFIRMATION         85
#define GROUP_FILE_IDEL                                 86

#define OFFLINE_FRIEND_INFORMATION                      91
#define OFFLINE_FRIEND_INFORMATION_CONFIRMATION         92
#define OFFLINE_GET_REQUEST                             93
#define OFFLINE_GET_REQUEST_CONFIRMATION                94
#define OFFLINE_FRIEND_UNREAD_MESSAGE                   95
#define OFFLINE_FRIEND_UNREAD_MESSAGE_CONFIRMATION      96
#define OFFLINE_FRIEND_HISTORY_MESSAGE_REQUEST          97
#define OFFLINE_FRIEND_HISTORY_MESSAGE                  98
#define OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION     99
#define OFFLINE_GET_FRIEND_MESSGAE_STATUS               100
#define OFFLINE_GET_FRIEND_MESSGAE_STATUS_CONFIRMATION  101
#define OFFLINE_GET_CONVERSATION_REQUEST                102
#define OFFLINE_MESSAGE_CONVERSATION_LIST               103
#define OFFLINE_GROUP_IP_PORT                           104
#define OFFLINE_MY_GROUP_LIST                           105 
#define OFFLINE_GROUP_UNREAD_MESSAGE                    106
#define OFFLINE_GROUP_UNREAD_MESSAGE_CONFIRMATION       107
#define OFFLINE_CREATE_GROUP                            108
#define OFFLINE_CREATE_GROUP_CONFIRMATION               109
#define OFFLINE_GROUP_HISTORY_MESSAGE_REQUEST           110
#define OFFLINE_GROUP_HISTORY_MESSAGE                   111
#define OFFLINE_GET_INFORMATION_WITH_MEMBERS            112
#define OFFLINE_INFORMATION_WITH_MEMBERS                113
#define DELETE_CONVERSATION_REQUEST                     114
#define MARK_CONVERSATION_SEEN_REQUEST                  115
#define OFFLINE_GROUP_CONFIRMATION                      117
#define OFFLINE_BROKEN_HISTORY_PACKET                   118
#define OFFLINE_BROKEN_PACKET                           119
#define OFFLINE_BROKEN_PACKET_CONFIRMATION              120

#define FRIEND_CHAT_MULTIPLE_MESSAGE_INNER              130
#define OFFLINE_FRIEND_UNREAD_MESSAGE_INNER             131
#define OFFLINE_FRIEND_HISTORY_MESSAGE_INNER            132
#define OFFLINE_GROUP_UNREAD_MESSAGE_INNER              133
#define OFFLINE_GROUP_HISTORY_MESSAGE_INNER             134

#define OFFLINE_GROUP_UNREAD_MESSAGE_HEADER             135

#define ROOM_HISTORY_INNER                              136

#define FRIEND_CHAT_MESSAGE_ANONYMOUS                   137
#define FRIEND_CHAT_MESSAGE_EDIT_ANONYMOUS              138
#define FRIEND_CHAT_MESSAGE_BROKEN_ANONYMOUS            139
#define FRIEND_CHAT_MESSAGE_BROKEN_EDIT_ANONYMOUS       140

#define FRIEND_CHAT_MESSAGE_HEADER                      141
#define OFFLINE_MESSAGE_CONVERSATION_LIST_INNER         142
#define OFFLINE_CREATE_GROUP_HEADER                     143

#define PUBLIC_ROOM_REGISTER                            1001 
#define PUBLIC_ROOM_UNREGISTER                          1002 
#define PUBLIC_ROOM_REGISTER_CONFIRMATION               1003 
#define PUBLIC_ROOM_CHAT_IDEL                           1004 
#define PUBLIC_ROOM_CHAT_MESSAGE_TYPING                 1005
#define PUBLIC_ROOM_CHAT_MESSAGE                        1006 
#define PUBLIC_ROOM_CHAT_MESSAGE_EDIT                   1007 
#define PUBLIC_ROOM_CHAT_MESSAGE_BROKEN                 1008 
#define PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT            1009 
#define PUBLIC_ROOM_CHAT_MESSAGE_DELIVERED              1010 
#define PUBLIC_ROOM_CHAT_MESSAGE_SENT                   1011 
#define PUBLIC_CHAT_GET_MEMBER_LIST                     1012
#define PUBLIC_CHAT_GET_MEMBER_LIST_CONFIRMATION        1013
#define PUBLIC_CHAT_MEMBER_LIST                         1014
#define PUBLIC_CHAT_MEMBER_COUNT_CHANGE                 1015
#define PUBLIC_CHAT_MEMBER_COUNT_CHANGE_CONFIRMATION    1016

#define OFFLINE_PUBLIC_ROOM_LIST_REQUEST                1017 
#define OFFLINE_PUBLIC_ROOM_LIST_SEARCH_REQUEST         1018 
#define OFFLINE_PUBLIC_ROOM_LIST_REQUEST_CONFIRMATION   1019 
#define OFFLINE_PUBLIC_ROOM_LIST                        1020 
#define OFFLINE_PUBLIC_GET_ROOM_IPPORT                  1021 
#define OFFLINE_PUBLIC_ROOM_IPPORT_CONFIRMATION         1022
#define OFFLINE_ROOM_INFORMATION_REQUEST                1023
#define OFFLINE_ROOM_INFORMATION                        1024
#define OFFLINE_ROOM_GET_HISTORY                        1025
#define OFFLINE_ROOM_GET_HISTORY_CONFIRMATION           1026
#define OFFLINE_ROOM_HISTORY_MESSAGE_LIST               1027

#define OFFLINE_PUBLIC_ROOM_LIST_WITH_HISTORY_REQUEST   1028
#define OFFLINE_PUBLIC_ROOM_LIST_WITH_HISTORY           1029
#define OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST       1043
#define OFFLINE_PUBLIC_CHAT_CATEGORY_LIST               1044

#define ROOM_BROKEN_PACKET                              1030
#define ROOM_BROKEN_PACKET_CONFIRMATION                 1031
#define SHADOW_IDS_INFO_REQUEST                         1032
#define SHADOW_IDS_INFO_RESPONSE                        1033

#define PUBLIC_CHAT_DELETE_MESSAGE                      1034
#define PUBLIC_CHAT_DELETE_MESSAGE_CONFIRMATION         1035
#define PUBLIC_CHAT_LIKE_A_MESSAGE                      1036
#define PUBLIC_CHAT_UNLIKE_A_MESSAGE                    1037
#define PUBLIC_CHAT_LIKE_UNLIKE_CONFIRMATION            1038
#define PUBLIC_CHAT_REPORT_A_MESSAGE                    1039
#define PUBLIC_CHAT_REPORT_A_MESSAGE_CONFIRMATION       1040
#define PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST            1041
#define PUBLIC_CHAT_LIKE_MEMBER_LIST                    1042
#define OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST       1043
#define OFFLINE_PUBLIC_CHAT_CATEGORY_LIST               1044

//Chat on live stream packets
#define LIVE_STREAM_CHAT_REGISTER                       2001 
#define LIVE_STREAM_CHAT_UNREGISTER                     2002 
#define LIVE_STREAM_CHAT_REGISTER_CONFIRMATION          2003 
#define LIVE_STREAM_CHAT_IDEL                           2004 
#define LIVE_STREAM_CHAT_MESSAGE_TYPING                 2005
#define LIVE_STREAM_CHAT_MESSAGE                        2006 
#define LIVE_STREAM_CHAT_MESSAGE_DELIVERED              2007 
#define LIVE_STREAM_CHAT_MESSAGE_SENT                   2008 
#define LIVE_STREAM_CHAT_BLOCK_USER                     2020
#define LIVE_STREAM_CHAT_BLOCK_USER_CONFIRMATION        2021

#define USER_PASSWORD_UPDATE                            3001
#define USER_PASSWORD_UPDATE_CONFIRMATION               3002
#define ACTIVATE_DEACTIVATE_USER_ACCOUNT                3003
#define ACTIVATE_DEACTIVATE_USER_ACCOUNT_CONFIRMATION   3004
#define GET_USER_INFO                                   3005
#define USER_INFO_DETAILS                               3006


#define GET_SYNC_CONVERSATION_REQUEST                   4001
#define SYNC_CONVERSATION_LIST                          4002
#define SYNC_CONVERSATION_CONFIRMATION                  4003

#define SYNC_FRIEND_HISTORY_MESSAGE_REQUEST             4004
#define SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION        4005
#define SYNC_FRIEND_HISTORY_MESSAGE                     4006

#define SYNC_GROUP_HISTORY_MESSAGE_REQUEST              4007
#define SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION         4008
#define SYNC_GROUP_HISTORY_MESSAGE                      4009
#define GET_MY_GROUP_LIST_PAGING                        4010
#define ADD_NOTICE                                      4011
#define ADD_NOTICE_CONFIRMATION                         4012




//#define CHAT_REGISTER                                   1
//#define CHAT_FRIEND_UNREGISTERED                        2
//#define CHAT_REGISTER_CONFIRMATION                      3
//#define CHAT_GROUP_UNREGISTER                           4
////Friend to Friend Chat Constants
//#define CHAT_FRIEND                                     5
//#define CHAT_DELIVERED                                  6
//#define CHAT_SEEN                                       7
//#define CHAT_SENT                                       8
//#define CHAT_TYPING                                     9
//#define CHAT_IDEL                                       10
////Group Chat Constants
//#define CHAT_GROUP_REGISTER                             12
//#define CHAT_GROUP_REG_CONFIRMATION                     13
//#define CHAT_GROUP                                      14
//#define CHAT_GROUP_DELIVERED                            15
//#define CHAT_GROUP_SEEN                                 16
//#define CHAT_GROUP_SENT                                 17
//#define CHAT_GROUP_TYPING                               18
//#define CHAT_GROUP_IDEL                                 19
////Offline Message
//#define CHAT_FRIEND_OFFLINE                             20
//#define CHAT_GROUP_OFFLINE                              21
//#define CHAT_GET_OFFLINE                                22
//#define CHAT_OFFLINE_CONFIRMATION                       23
////Chat Delete Constants
//#define FRIEND_CHAT_DELETE                              24
//#define FRIEND_CHAT_DELETE_CONFIRMATION                 25
//#define GROUP_CHAT_DELETE                               26
//#define GROUP_CHAT_DELETE_CONFIRMATION                  27
//#define FRIEND_INFORMATION                              28
//#define FRIEND_INFORMATION_CONFIRMATION                 29
////File Stream
//#define FILE_TOTAL_SEQUENCE                             30
//#define FILE_TOTAL_SEQUENCE_CONFIRMATION                31
//#define FILE_STREAM_SEND                                32
//#define FILE_STREAM_SEND_CONFIRMATION                   33
////End File Stream
////Group Chat
//#define GROUP_MEMBERS                                   34
//#define GROUP_MEMBERS_CONFIRMATION                      35
//#define GET_GROUP_MEMBERS                               36
//#define GROUP_MEMBER_REMOVE_LEAVE                       37
//#define GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION          38
//#define GROUP_DELETE                                    39
//#define GROUP_DELETE_CONFIRMATION                       40
//#define MULTIPLE_FRIEND_CHAT_DELETE                     41
//#define MULTIPLE_GROUP_CHAT_DELETE                      42
//#define FRIEND_CHAT_EDIT                                43
//#define GROUP_CHAT_EDIT                                 44
//#define MULTIPLE_CHAT_FOR_FRIEND                        45
//#define BROCKEN_CHAT_FOR_FRIEND                         46
//#define BROCKEN_CHAT_FOR_GROUP                          47
//#define EDIT_BROCKEN_CHAT_FOR_FRIEND                    48
//#define EDIT_BROCKEN_CHAT_FOR_GROUP                     49
////File Transfering using UDP
//#define CHAT_FRIEND_FILE_SESSION_REQUEST                50
//#define CHAT_FRIEND_FILE_SESSION_REQUEST_CONFIRMATION   51
//#define CHAT_FRIEND_FILE_STREAM_REQUEST                 52
//#define CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION    53
//#define CHAT_FRIEND_FILE_STREAM                         54
//#define CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION     55
//#define CHAT_GROUP_FILE_STREAM_SEND                     56
//#define CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION        57
//
//#define CHAT_FRIEND_OFFLINE_CONFIRMATION                58
//#define CHAT_GROUP_OFFLINE_CONFIRMATION                 59
//
//#define CHAT_FRIEND_BLOCK                               60
//#define CHAT_FRIEND_UNBLOCK                             61
//#define CHAT_BLOCK_UNBLOCK_CONFIRMATION                 62
//
//#define GROUP_MEMBER_ADD                                63
//#define GROUP_MEMBER_ADD_CONFIRMATION                   64
//#define GROUP_INFORMATION                               65
//#define GET_GROUP_INFORMATION                           66
//#define GROUP_INFORMATION_CONFIRMATION                  67
//#define GROUP_MEMBER_STATUS_CHANGE                      68
//#define GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION         69
//#define FRIEND_CHAT_SEEN                                72
//#define FRIEND_CHAT_SEEN_CONFIRMATION                   73
////add new types above, and increase the value of types bellow. 
////also increase the value of NUM_PACKET_TYPE
//#define CHAT_FRIEND_OFFLINE_INNER                       74
//#define CHAT_GROUP_OFFLINE_INNER                        75
//#define MULTIPLE_CHAT_FOR_FRIEND_INNER                  76
//#define HEADER_ONLY                                     77
//#define FILE_TRANSFER_PORT                              78

#define NUM_PACKET_TYPES                                4500 // total types of packets.


/**
 * Field Lengths
 */

#define LEN_PACKET_TYPE                     1
#define LEN_USER_IDENTITY                   8
#define LEN_FRIEND_IDENTITY                 8
#define LEN_RING_ID                         8
#define LEN_PUBLISHER_ID                    8
#define LEN_FILE_ID                         8
#define LEN_PACKETID_LENGTH                 1
#define LEN_PIVOTID_LENGTH                  1
#define LEN_LEAVE_TYPE                      1
#define LEN_PLATFORM                        1
#define LEN_CHAT_BINDING_PORT               4
#define LEN_FILE_TRANSFER_PORT              4
#define LEN_SERVER_DATE                     8
#define LEN_GROUPID                         8
#define LEN_ONLINE_STATUS                   1
#define LEN_MESSAGE_TYPE                    1
#define LEN_TIMEOUT                         2
#define LEN_MESSAGE_LENGTH                  2
#define LEN_MESSAGE_DATE                    8
#define LEN_NUMBER_OF_MESSAGES              1
#define LEN_TOTAL_NUMBER_OF_PACKETS         1
#define LEN_SEQUENCE_NUMBER                 1
#define LEN_NUMBER_OF_PACKETS               1 
#define LEN_FULL_NAME_LENGTH                1
#define LEN_NUMBER_OF_MEMBERS_DTO           2
#define LEN_NUMBER_OF_MEMBERS_ID_N_S        2
#define LEN_NUMBER_OF_MEMBERS_ID            2
#define LEN_NUMBER_OF_MEMBERS_ID_S          2
#define LEN_NUMBER_OF_MEMBERS_ID_T          2
#define LEN_FRIEND_ONLINE_STATUS            1
#define LEN_FRIEND_APP_TYPE                 1
#define LEN_PAGE_OWNER_IDENTITY             8
#define LEN_FRIEND_DEVICE_TOKEN_LENGTH      2
#define LEN_FILE_TOTAL_CHUNK                4
#define LEN_FILE_CHUNK_LIST_LENGTH          1
#define LEN_FILE_CHUNK_TYPE                 1
#define LEN_FILE_CHUNK_CURRENT_INDEX        4
#define LEN_FILE_CONTENT_LENGTH             2
#define LEN_FILE_CONTENT                    -1
#define LEN_IS_ADD_TO_BLOCK                 1
#define LEN_ONLINE_MOOD                     1
#define LEN_GROUP_NAME_LENGTH               2
#define LEN_GROUP_URL_LENGTH                1
#define LEN_MEMBER_NAME_LENGTH              1
#define LEN_MEMBER_PROFILE_URL_LENGTH       1
#define LEN_MEMBER_ADDED_TIME               8
#define LEN_MEMBER_STATUS                   1
#define LEN_BLOCK_UNBLOCK_DATE              8
#define LEN_TOTAL_GROUP_MEMBERS             2
#define LEN_IS_UPDATE_GROUP_INFORMATION     1
#define LEN_NUMBER_OF_SEEN_PACKET           1
#define LEN_IS_SECRET_VISIBLE               1
#define LEN_MESSAGE_STATUS                  1
#define LEN_DIRECTION                       1
#define LEN_DATA_BYTES                      -1
#define LEN_GROUP_UPDATE_DATE               8
#define LEN_UP_DOWN                         1
#define LEN_LIMIT                           1
#define LEN_NUMBER_OF_ACTIVITY              1
#define LEN_ACTIVITY_TYPE                   1
#define LEN_GROUP_NAME_URL_LENGTH           2
#define LEN_NUMBER_OF_GROUPS                2
#define LEN_NUMBER_OF_MEMBERS               2
#define LEN_NUMBER_OF_PACKETS_D_S           1
#define LEN_APP_VERSION                     2
#define LEN_ROOM_IDENTITY_LENGTH            1
#define LEN_FULLNAME_LENGTH                 1
#define LEN_MEMBER_PROFILE_URL_LENGTH       1
#define LEN_START_INDEX                     1
#define LEN_SEARCH_NAMELENGTH               1
#define LEN_NUMBER_OF_ROOM                  2
#define LEN_ROOM_FULL_NAME_LENGTH           1
#define LEN_SERVER_IP_LENGTH                1
#define LEN_SERVER_REGISTER_PORT            4
#define LEN_MONTH                           1
#define LEN_YEAR                            2
#define LEN_PAGING_STATE_LENGHT             1
#define LEN_RECEPIENT_IDENTITY              8
#define LEN_NUMBER_OF_ROOM_MEMBER           2
#define LEN_ORIGINAL_USER_IDENTITY          8
#define LEN_NUMBER_OF_PUBLIC_CHAT_MEMBERS_C 2
#define LEN_FILE_ACCEPT_REJECT              1
#define LEN_FILE_OFFSET                     8
#define LEN_NUMBER_OF_SHADOW_ID             1
#define LEN_NUMBER_OF_SHADOW_INFO_ID        1
#define LEN_IOS_VOIP_PUSH                   1
#define LEN_ORIGINAL_PACKETID_LENGTH        1
#define LEN_PUBLIC_CHAT_LAST_LIKER_ID       8
#define LEN_NUMBER_OF_PUBLIC_CHAT_LIKERS_ID 1
#define LEN_NUMBER_OF_PUBLIC_ROOM_CATEGORY  1
#define LEN_PUBLIC_ROOM_CATEGORY_LENGHT     1
#define LEN_PUBLIC_CHAT_COUNTRY_LENGTH      1
#define LEN_PUBLIC_CHAT_LIKE_COUNT          2
#define LEN_PUBLIC_CHAT_REPORT_COUNT        2
#define LEN_PUBLIC_CHAT_ILIKE               1
#define LEN_PUBLIC_CHAT_IREPORT             1
#define LEN_CONVERSATION_TYPE               1
#define LEN_FRIEND_GROUP_ID                 8
#define LEN_NUMBER_OF_CONVERSATION          1
#define LEN_UNREAD_COUNT                    2
#define LEN_NUMBER_OF_MESSAGES_2B           2
#define LEN_FILE_DOWNLOAD_ID_LENGTH         1
#define LEN_FILE_CHUNK_COUNT                1
#define LEN_FILE_CHUNK_SIZE                 4
#define LEN_FILE_SIZE                       8
#define LEN_IS_FILE_MANIFEST                1
#define LEN_FILE_CHUNK_DOWNLOAD_KEY_LENGTH  1
#define LEN_FILE_DOMAIN_TYPE                1
#define LEN_FILE_WIDTH_OR_SIZE              4
#define LEN_FILE_HEIGHT_OR_DURATION         4
#define LEN_FILE_CAPTION_LENGTH             1
#define LEN_FRIEND_PLATFORM                 1
#define LEN_NUMBER_OF_PAGE                  1
#define LEN_PROFILE_TYPE                    1
#define LEN_FRIEND_PROFILE_TYPE             1
#define LEN_FRIEND_PROFILE_IAMGE_URL_LENGTH 1
#define LEN_ACCOUNT_ACTIVATION_STATUS       1
#define LEN_LAST_SYNC_TIME                  8
#define LEN_MESSAGE_DELETE_TYPE             1
#define LEN_AUTH_SESSION_ID_LENGTH          1
#define LEN_DISBURSE_TIME                   8
#define LEN_EXPIRE_TIME                     8
#define LEN_NOTICE_LENGTH                   2
#define LEN_ISO_COUNTRY_LENGTH              2
#define LEN_TYPE							1
#define LEN_INFORMATION_LENGTH				2
#define LEN_INFORMATION_TYPE				1



#define PACKET_TYPE                     1
#define USER_IDENTITY                   2
#define FRIEND_IDENTITY                 3
#define PACKETID_LENGTH                 4
#define PACKETID                        -1  
#define PIVOTID                         -1
#define AUTHSESSIONID                   -1
//keeping the order here, will be skipped while parsing
#define PLATFORM                        5
#define CHAT_BINDING_PORT               6
#define SERVER_DATE                     7
#define GROUPID                         8
#define ONLINE_STATUS                   9
#define MESSAGE_TYPE                    10
#define TIMEOUT                         11
#define MESSAGE_LENGTH                  14
#define MESSAGE                         -1
#define MESSAGE_DATE                    15
#define NUMBER_OF_MESSAGES              16
#define TOTAL_NUMBER_OF_PACKETS         17
#define SEQUENCE_NUMBER                 18
#define NUMBER_OF_PACKETS               19 
#define FULL_NAME_LENGTH                20
#define FULL_NAME                       -1
#define NUMBER_OF_MEMBERS_DTO           21          //full dto
#define NUMBER_OF_MEMBERS_ID_N_S        22          //idm, name, status
#define NUMBER_OF_MEMBERS_ID            23          //id
#define NUMBER_OF_MEMBERS_ID_S          24          //id, status
#define NUMBER_OF_MEMBERS_ID_T          25          //id, seenTime
#define FRIEND_ONLINE_STATUS            27
#define FRIEND_APP_TYPE                 28
#define FRIEND_DEVICE_TOKEN_LENGTH      29
#define FRIEND_DEVICE_TOKEN             -1
#define FILE_TOTAL_CHUNK                30
#define FILE_CHUNK_LIST_LENGTH          31
#define FILE_CHUNK_CURRENT_INDEX        32
#define FILE_CONTENT_LENGTH             33
#define FILE_CONTENT                    -1
#define IS_ADD_TO_BLOCK                 34
#define ONLINE_MOOD                     35
#define GROUP_NAME_LENGTH               36
#define GROUP_NAME                      -1
#define GROUP_URL_LENGTH                37
#define GROUP_URL                       -1
#define MEMBER_NAME_LENGTH              38
#define MEMBER_NAME                     -1
#define MEMBER_STATUS                   39
#define NUMBER_OF_SEEN_PACKET           43
#define FILE_ID                         44
#define IS_SECRET_VISIBLE               45
#define MESSAGE_STATUS                  46
#define BLOCK_UNBLOCK_DATE              47
#define DATA_BYTES                      48
#define GROUP_UPDATE_DATE               49
#define UP_DOWN                         50
#define LIMIT                           51
#define NUMBER_OF_ACTIVITY              52
#define ACTIVITY_TYPE                   53
#define GROUP_NAME_URL_LENGTH           54
#define GROUP_NAME_URL                  -1
#define NUMBER_OF_GROUPS                55
#define NUMBER_OF_MEMBERS               56
#define NUMBER_OF_PACKETS_D_S           59
#define FILE_TRANSFER_PORT              60
#define APP_VERSION                     61


#define ROOM_IDENTITY_LENGTH            62
#define ROOM_IDENTITY                   -1
#define ROOM_FULL_NAME_LENGTH           63
#define ROOM_FULL_NAME                  -1
#define MEMBER_PROFILE_URL_LENGTH       64
#define MEMBER_PROFILE_URL              -1
#define START_INDEX                     65
#define SEARCH_NAMELENGTH               66
#define SEARCHNAME                      -1
#define NUMBER_OF_ROOM                  67
#define NUMBER_OF_PUBLIC_CHAT_MEMBERS   68   
#define SERVER_IP_LENGTH                69
#define SERVER_IP                       -1
#define SERVER_REGISTER_PORT            70
#define MONTH                           71
#define YEAR                            72
#define NUMBER_OF_PUBLIC_CHAT_MESSAGES  73
#define NUMBER_OF_ROOM_WITH_HISTORY     74
#define PAGING_STATE_LENGTH             75
#define PAGING_STATE                    -1
#define RECEPIENT_IDENTITY              76
#define ORIGINAL_USER_IDENTITY          77
#define NUMBER_OF_PUBLIC_CHAT_MEMBERS_C 78   //only count
#define FILE_ACCEPT_REJECT              79
#define FILE_OFFSET                     80
#define NUMBER_OF_SHADOW_ID             81  //on id list
#define NUMBER_OF_SHADOW_INFO_ID        82  //dto list
#define IOS_VOIP_PUSH                   83
#define ORIGINAL_PACKET_TYPE            84
#define ORIGINAL_PACKETID_LENGTH        85
#define ORIGINAL_PACKETID               -1
#define NUMBER_OF_PUBLIC_CHAT_LIKERS_ID 86
#define NUMBER_OF_PUBLIC_ROOM_CATEGORY  87
#define PUBLIC_CHAT_LAST_LIKER_ID       88
#define PUBLIC_CHAT_COUNTRY_LENGTH      89
#define PUBLIC_CHAT_COUNTRY             -1
#define PUBLIC_CHAT_CATEGORY_LENGTH     90
#define PUBLIC_CHAT_CATEGORY            -1
#define PUBLIC_CHAT_LIKE_COUNT          91
#define PUBLIC_CHAT_ILIKE               92
#define PUBLIC_CHAT_IREPORT             93
#define CONVERSATION_TYPE               94
#define FRIEND_GROUP_ID                 95
#define NUMBER_OF_CONVERSATION          96
#define UNREAD_COUNT                    97
#define NUMBER_OF_MESSAGES_2B           98
#define RING_ID                         99

#define FILE_DOWNLOAD_ID_LENGTH         100
#define FILE_DOWNLOAD_ID                -1
#define FILE_CHUNK_COUNT                101
#define FILE_CHUNK_SIZE                 102
#define FILE_SIZE                       103
#define IS_FILE_MANIFEST                104
#define FILE_CHUNK_DOWNLOAD_KEY_LENGTH  105
#define FILE_CHUNK_DOWNLOAD_KEY         -1
#define FILE_DOMAIN_TYPE                106

#define PUBLISHER_ID                    107

#define FILE_CAPTION_LENGTH             108
#define FILE_CAPTION                    -1
#define FILE_WIDTH_OR_SIZE              109
#define FILE_HEIGHT_OR_DURATION         110
#define FRIEND_PLATFORM                 111
#define NUMBER_OF_PAGE                  112
#define PAGE_OWNER_IDENTITY             113
#define PROFILE_TYPE					114
#define FRIEND_PROFILE_IAMGE_URL_LENGTH 115
#define FRIEND_PROFILE_IAMGE_URL        116
#define ACCOUNT_ACTIVATION_STATUS       117
#define FRIEND_PROFILE_TYPE				118
#define LAST_SYNC_TIME                  119
#define MESSAGE_DELETE_TYPE             120
#define PIVOTID_LENGTH                  121
#define LEAVE_TYPE                      122

#define AUTH_SESSION_ID_LENGTH          123

#define DISBURSE_TIME                   124
#define EXPIRE_TIME                     125
#define NOTICE_LENGTH                   126
#define NOTICE                          -1
#define TYPE							130
#define INFORMATION						131
#define INFORMATION_LENGTH				132
#define INFORMATION_TYPE				133
#define ISO_COUNTRY_LENGTH              127
#define ISO_COUNTRY                     -1

#define GROUP_NAME_CHANGE               3
#define GROUP_URL_CHANGE                5

#define OPTIONAL_FIELD                  -1

namespace imsdk {

    class PacketTemplate {
    public:
        PacketTemplate();
        virtual ~PacketTemplate();

        std::vector<int> getFormat(size_t packetType);

    private:

        std::vector<std::vector<int> > format;
    };
}

#endif /* PACKET_TEMPLATE_H */

