set -e
set -x

mkdir -p output/iphoneos/usr/local/include

mkdir -p output/iphonesimulator/usr/local/include

DIR="output/iphoneos/IMSDK.framework/Headers"


while true ; do

if [ "$(ls -A $DIR)" ]; then
     echo "$DIR is not Empty"
     break
else
    echo "$DIR is Empty"
    cd ./chat/Chat/wrapper/ios

    if $log_enable ; then
	xcodebuild -scheme 'IMSDK' -configuration 'Release' -sdk iphoneos CONFIGURATION_BUILD_DIR='../../../../output/iphoneos/' GCC_PREPROCESSOR_DEFINITIONS='$GCC_PREPROCESSOR_DEFINITIONS IMSDK_LOG'
    else
	xcodebuild -scheme 'IMSDK' -configuration 'Release' -sdk iphoneos CONFIGURATION_BUILD_DIR='../../../../output/iphoneos/'
    fi
fi

cd ../../../../
done

DIR="output/iphonesimulator/IMSDK.framework/Headers"

while true ; do

if [ "$(ls -A $DIR)" ]; then
     echo "$DIR is not Empty"
     break
else
    echo "$DIR is Empty"
    cd ./chat/Chat/wrapper/ios

    if $log_enable ; then
	xcodebuild -scheme 'IMSDK' -configuration 'Release' -sdk iphonesimulator CONFIGURATION_BUILD_DIR='../../../../output/iphonesimulator' GCC_PREPROCESSOR_DEFINITIONS='$GCC_PREPROCESSOR_DEFINITIONS IMSDK_LOG'
    else
	xcodebuild -scheme 'IMSDK' -configuration 'Release' -sdk iphonesimulator CONFIGURATION_BUILD_DIR='../../../../output/iphonesimulator'
    fi
fi

cd ../../../../
done

cd ./chat/Chat/wrapper/ios
xcodebuild -scheme 'IMSDKFramework' -configuration 'Release' -sdk iphoneos CONFIGURATION_BUILD_DIR='../../../../output/iphoneos/'
