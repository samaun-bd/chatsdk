#!/bin/bash

set -e

declare -a javaFileNames=("ApiStatus.java" "FriendMessageStatusDTO.java" "Chat.java" "GroupActivityDTO.java" "PacketTimeId.java" "ChatSDKTypes.java" "GroupDTO.java" "PublicChatMemberDTO.java" "SDKMessageDTO.java" "IChatEventHandler.java" "RoomDTO.java" "FriendInformation.java" "MemberDTO.java" "SeenPacketDTO.java" "GroupInformation.java" "DataCounter.java" "ConversationDTO.java" "InternetChecker.java" "DataEncryption.java")

packageName='com/ringid/imsdk'
outputJarName='imsdk.jar'


################## do not modify below this line #####################


tempDirName='/tmp/imsdk_jar_temp'

rm -fr bin || true
mkdir bin

rm -fr $tempDirName || true
mkdir $tempDirName

cp -ar src $tempDirName || true
rm $tempDirName/src/$packageName/* || true

for i in "${javaFileNames[@]}"
do
	#echo "$i"
	copyingFromSrcToTmp=0
   	cp src/$packageName/$i $tempDirName/src/$packageName/ || copyingFromSrcToTmp=1
	if [ $copyingFromSrcToTmp -ne 0 ]
	then
   	echo "File do not exist : $i"
   	rm -rf $tempDirName
   	exit 1
	fi
done


compilingSrc=0
/usr/lib/jvm/java-6-oracle/bin/javac -d ./bin $tempDirName/src/$packageName/*.java || compilingSrc=1
if [ $compilingSrc -ne 0 ]
	then
   	rm -rf $tempDirName
    echo "Compile Error !"
    exit 1
fi

echo "Compile Successful !"

#cp $tempDirName/src/$packageName/* ./bin/$packageName/

cd bin

compilingJar=0
(/usr/lib/jvm/java-6-oracle/bin/jar -cvf0 $outputJarName $packageName/* > jarCommandLog) || compilingJar=1
if [ $compilingJar -ne 0 ]
	then
   	echo "Jar Failed to Create !"
   	rm jarCommandLog
   	rm -rf $tempDirName
   	exit 1
fi 

echo "Jar Created !"
mv $outputJarName ../
rm jarCommandLog
rm -rf $tempDirName

