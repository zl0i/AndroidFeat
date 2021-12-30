!contains(QT.network_private.enabled_features, openssl-linked) {

    DISTFILES += \
        $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm/libcrypto_1_1.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm/libssl_1_1.so

    ANDROID_EXTRA_LIBS += \
        $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm/libcrypto_1_1.so \
        $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm/libssl_1_1.so

    contains(ANDROID_ABIS, arm64-v8a) {
        ANDROID_EXTRA_LIBS += \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm64/libcrypto_1_1.so \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm64/libssl_1_1.so

        DISTFILES += \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm64/libcrypto_1_1.so \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/arm64/libssl_1_1.so
    }

    contains(ANDROID_ABIS, x86) {
        ANDROID_EXTRA_LIBS += \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86/libcrypto_1_1.so \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86/libssl_1_1.so

        DISTFILES += \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86/libcrypto_1_1.so \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86/libssl_1_1.so
    }

    contains(ANDROID_ABIS, x86_64) {
        ANDROID_EXTRA_LIBS += \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86_64/libcrypto_1_1.so \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86_64/libssl_1_1.so

        DISTFILES += \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86_64/libcrypto_1_1.so \
            $$ANDROID_PACKAGE_SOURCE_DIR/ssl/x86_64/libssl_1_1.so
    }
}
