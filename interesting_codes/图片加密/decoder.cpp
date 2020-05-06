#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
using namespace cv;

int extract_images(Mat& base_image, std::vector<Mat>& words_images)
{
    for (auto it=words_images.begin(); it!=words_images.end(); ++it)
    {
        assert(it->cols == base_image.cols);
        assert(it->rows == base_image.rows);
    }

    for (int x=0; x<base_image.cols; ++x)
    {
        for (int y=0; y<base_image.rows; ++y)
        {
            ::Vec3b base = base_image.at<Vec3b>(y, x);
            for (int channel=0; channel<3; ++channel)
            {
                if (base[channel] & (uint8_t)1)
                    words_images[channel].at<uint8_t>(y,x) = 255;
                else 
                    words_images[channel].at<uint8_t>(y,x) = 0;
            }
        }
    }
    return 0;
}

int decode_words_from_image(const std::string& input_image_path, const std::string output_words_path)
{
    int ret = 0;
    // Mat input_image = imread(input_image_path, CV_LOAD_IMAGE_UNCHANGED);
    Mat input_image = imread(input_image_path);
    if (input_image.empty())
    {
        std::cout << "imread failed" << std::endl;
        return -1;
    }

    size_t dark_count = 0;
    size_t white_count = 0;
    for (int x=0; x<input_image.cols; ++x)
    {
        for (int y=0; y<input_image.rows; ++y)
        {
            ::Vec3b base = input_image.at<Vec3b>(y, x);
            for (int channel=0; channel<3; ++channel)
            {
                if (base[channel] & 1)
                    white_count++;
                else
                    dark_count++;
            }
        }
    }
    std::cout << "dark_count: " << dark_count << ", white_count: " << white_count << std::endl;

    std::vector<Mat> words_images(3, Mat::zeros(Size(input_image.cols, input_image.rows), CV_8U));
    ret = extract_images(input_image, words_images);
    if (ret != 0)
    {
        std::cout << "extract_images failed" << std::endl;
        return -2;
    }
    
    // form 3 image path
    size_t last_slash_pos = output_words_path.find_last_of('/');
    size_t filename_pos = (last_slash_pos != std::string::npos) ? last_slash_pos+1 : 0;
    std::string filename = output_words_path.substr(filename_pos);
    std::string dirname = (last_slash_pos != std::string::npos) ? output_words_path.substr(0, last_slash_pos+1) : "";

    size_t last_dot_pos = filename.find_last_of('.');
    if (last_dot_pos == std::string::npos)
    {
        std::cout << "illegal output_words_path" << std::endl;
        return -3;
    }
    std::string filename_prefix = filename.substr(0, last_dot_pos);
    std::string filename_suffix = filename.substr(last_dot_pos+1);

    char buf[256];
    for (int channel=0; channel<3; ++channel)
    {
        ::sprintf(buf, "%s%s.%d.%s", dirname.c_str(), filename_prefix.c_str(), channel, filename_suffix.c_str());
        if (! imwrite(std::string(buf), words_images[channel]))
        {
            std::cout << "imwrite failed" << std::endl;
            return -6;
        }
    }
    return 0;
}


int main()
{
    decode_words_from_image("output.png", "words.png");
    return 0;
}
