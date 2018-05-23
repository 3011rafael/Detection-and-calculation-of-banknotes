QT       += core
QT       -= gui

TARGET = OpenCV-Ex1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32 {
    INCLUDEPATH += C:\\opencv-3.2.0\\build\\install\\include


    LIBS += -LC:/opencv-3.2.0/build/lib \
        -llibopencv_core320 \
        -lopencv_highgui320 \
        -llibopencv_imgproc320 \
        -llibopencv_features2d320 \
        -llibopencv_calib3d320 \
        -llibopencv_ml320 \
        -llibopencv_features2d320 \
        -llibopencv_imgcodecs320
}

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv

}
