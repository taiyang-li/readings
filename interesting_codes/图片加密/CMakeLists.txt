# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (image_codec)

# 库文件目录
link_directories(/usr/local/Cellar/opencv/3.3.1_1/lib)

# 添加头文件
include_directories(/usr/local/Cellar/opencv/3.3.1_1/include)

# 指定生成目标
add_executable(encoder encoder.cpp)
add_executable(decoder decoder.cpp)

# 添加链接库
target_link_libraries(encoder opencv_stitching opencv_superres opencv_videostab opencv_photo opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dpm opencv_face opencv_fuzzy opencv_img_hash opencv_line_descriptor opencv_optflow opencv_reg opencv_rgbd opencv_saliency opencv_stereo opencv_structured_light opencv_phase_unwrapping opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_dnn opencv_plot opencv_xfeatures2d opencv_shape opencv_video opencv_ml opencv_ximgproc opencv_calib3d opencv_features2d opencv_highgui opencv_videoio opencv_flann opencv_xobjdetect opencv_imgcodecs opencv_objdetect opencv_xphoto opencv_imgproc opencv_core)
target_link_libraries(decoder opencv_stitching opencv_superres opencv_videostab opencv_photo opencv_aruco opencv_bgsegm opencv_bioinspired opencv_ccalib opencv_dpm opencv_face opencv_fuzzy opencv_img_hash opencv_line_descriptor opencv_optflow opencv_reg opencv_rgbd opencv_saliency opencv_stereo opencv_structured_light opencv_phase_unwrapping opencv_surface_matching opencv_tracking opencv_datasets opencv_text opencv_dnn opencv_plot opencv_xfeatures2d opencv_shape opencv_video opencv_ml opencv_ximgproc opencv_calib3d opencv_features2d opencv_highgui opencv_videoio opencv_flann opencv_xobjdetect opencv_imgcodecs opencv_objdetect opencv_xphoto opencv_imgproc opencv_core)

# 调试选项
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall -std=c++11")
