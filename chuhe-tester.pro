TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    httpclient/get/httget.c \
    httpclient/post/httpost.c \
    httpclient/httpclient.c \
    httpclient/httpclienthelper.c \
    httpclient/jsonhelper.c \
    test_product/product.c \
    utils/prog.c \
    webclient/webclient_c.c \
    webserver/webserver_c.c

DISTFILES += \
    dist/libhttget.so \
    dist/libhttpclienthelper.so \
    dist/libhttpget.so \
    dist/libhttpost.so \
    dist/libjsonhelper.so \
    webserver/favicon.ico \
    utils/README.md \
    README.md \
    Makefile

HEADERS += \
    httpclient/get/httget.h \
    httpclient/post/httpost.h \
    httpclient/httpclienthelper.h \
    httpclient/jsonhelper.h \
    utils/colors.h \
    config.h
