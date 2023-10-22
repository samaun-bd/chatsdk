/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package chatparserjavatester;

import com.ringid.imsdk.*;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author dipal
 */
public class ChatParserJavaTester {

    public static void run()
    {
        String message = "i got a jar of dart";
        byte[] data;
        data = ChatParser.getInstance().makeChatFriendPacket(3, 7, "21abcd", 3, 3600, (float) 21.1245, (float) 93.1545, message, 123455678);
        MessageDTO messageDTO = ChatParser.getInstance().parse(data);
    }
    
    public static void benchmark()
    {
        for (int i=0; i<10000; i++)
        {
            try {
                run();
                Thread.sleep(10);
            } catch (InterruptedException ex) {
                Logger.getLogger(ChatParserJavaTester.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println(System.getProperty("java.library.path"));
        ChatParser parser = ChatParser.getInstance();
        System.out.println(parser.version());
        
        benchmark();
        //run();
        
   }
    
}
