QT += quick androidextras

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        notificationworker.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = arm64-v8a
android: include(G:/Android_Studio_SDK/android_openssl/openssl.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/google-services.json \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/drawable-hdpi/firebase_lockup_400.png \
    android/res/drawable-hdpi/notificationicon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-ldpi/notificationicon.png \
    android/res/drawable-mdpi/firebase_lockup_400.png \
    android/res/drawable-mdpi/notificationicon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-xhdpi/firebase_lockup_400.png \
    android/res/drawable-xhdpi/notificationicon.png \
    android/res/drawable-xxhdpi/firebase_lockup_400.png \
    android/res/drawable-xxhdpi/notificationicon.png \
    android/res/values/color.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/src/com/zloi/firebase/test/Notification.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    notificationworker.h
