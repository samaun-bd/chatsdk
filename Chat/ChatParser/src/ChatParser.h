/* 
 * File:   chatparser.h
 * Author: dipal
 *
 * Created on July 12, 2015, 2:29 PM
 */

#ifndef CHATPARSER_H
#define	CHATPARSER_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "ByteArray.h"
#include "GroupActivityDTO.h"
#include "PacketDTO.h"


namespace imsdk {

class PacketDTO;
class PacketTemplate;


struct ParsedObject
{
    std::shared_ptr<PacketDTO> packet;
    int parsedLength;
};

class ChatParser
{
public:

  ChatParser ();

  virtual ~ChatParser ();

  /**
   * @return ParsedObject
   * @param  Bytes
   */
   ParsedObject parse (ByteArray &data, int startIndex = 0);
   
   ParsedObject parseHeader(ByteArray &byteArray);

  /**
   * @return Bytes
   * @param  PacketDTO
   */
  std::shared_ptr<ByteArray> parse (std::shared_ptr<PacketDTO> &packet);
  
  GroupActivityDTO parseGroupActivity(std::shared_ptr<PacketDTO> packet);
  
  std::unordered_map<std::string,std::string> jsonParser(std::string str);
  
  long long toStringToLong(std::string s);
  
  int toStringToInt(std::string s);
    
  static std::vector<std::string> getSplittedString(std::string originalString, char delim);
  
  /**
   * Returns the Chat Parser Version
   * @return string
   * @param  
   */
  std::string version()
  {
      return "Native Chat Parser 1.0 (compiled "+std::string(__TIME__)+", "+std::string(__DATE__)+")";
  }

private:

    std::shared_ptr<PacketTemplate> packetTemplate{nullptr};
};
}

#endif	/* CHATPARSER_H */

