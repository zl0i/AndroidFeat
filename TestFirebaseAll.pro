QT += quick svg
QT -= widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/appcore.cpp \
        src/chrometabs.cpp \
        src/deeplinkshandler.cpp \
        main.cpp \
        src/notificationworker.cpp \
        src/oauthflow.cpp

RESOURCES += qml.qrc \
        icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


android {

    QT += androidextras

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
    android/src/com/zloi/firebase/test/MainActivity.java \
        android/src/com/zloi/firebase/test/Notification.java

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    ANDROID_ABIS = arm64-v8a

    include(android/openssl.pri)

}

HEADERS += \
    src/appcore.h \
    src/chrometabs.h \
    src/deeplinkshandler.h \
    src/notificationworker.h \
    src/oauthflow.h
