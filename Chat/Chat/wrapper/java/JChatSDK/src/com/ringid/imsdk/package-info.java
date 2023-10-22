
/**
 * The SDK that handles all communication with IM Server. There is a {@link Chat} class that contains all APIs
 * to communicate with SDK. SDK will communicate with SDK user (application developer) through an instance of {@link IChatEventHandler}
 * 
 * You should extend {@link IChatEventHandler} register the event handler instance 
 * using Chat::registerEventHandler() function. SDK will notify when there is an event
 * waiting for you. Here is a basic example about using the APIs.
 * <pre>
 * {@code 
        long myUserId = 20021256;
        
        //initate the Chat instance
        Chat chat = new Chat(myUserId);
        
        //register event handler. ChatEventHandler will extend IChatEventHandler
        chat.registerEventHandler(new ChatEventHandler()); 
        
        //get the SDK version
        System.out.println(chat.version());
        
        //start new chat session with a friend
        String registerServerAddress = "192.168.1.138";
        int registerS   erverPort = 1500;
        String offlineServerAddress = "192.168.1.138";
        int offlineServerPort = 1200;
        
        long friendId = 20021257;
        
        ApiStatus apiStatus= chat.registerFriendChat(friendId, registerServerAddress, registerServerPort, offlineServerAddress, offlineServerPort, ANDROID);
        
        apiStatus = chat.sendFriendChat(...);
 * }
 * </pre>
 * 
 * If any other friend sends chat to this user or any kind of communication to use will be notified using the {@link IChatEventHandler}
 * An example implementation is as follows
 * 
 * <pre>
 * <code>
 * class ChatEventHandler implements IChatEventHandler {

   {@literal @}Override
    public void onFriendChatRegisterSuccess(long friendId) {
        System.out.println("register success "+friendId);
    }

   {@literal @}Override
    public void onFriendChatRegisterFailure(long friendId) {
        System.out.println("register failure "+friendId);
    }
    
   {@literal @}Override
    public void onFriendChatReceived(long friendid, String packetId, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        System.out.println("message from "+friendid+" "+message);
        //myui.chatwindow(friendid).show(message, timeout, latitude, longitude);
    }

    ...
    other overwridden functions
 * }
 * </code>
 * </pre>
 * 
 * 
 * Note: You will be able to handle all chat sessions using one instance of Chat object.
 * @see <a href="{@docRoot}/downloads">Download library</a>
 */
package com.ringid.imsdk;
