#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace cv;

static const int LETTER_WIDTH = 12; 
static const int LETTER_HEIGHT = 12; 

int rearrange_words(const std::string& words, int max_letter_in_row, std::vector<std::string>& lines)
{
    char* p = const_cast<char*>(words.c_str());
    char* start = p;
    char* last_space = NULL;
    
    lines.clear();
    while (*p != 0)
    {
        last_space = NULL;
        while (*p != 0 && p - start < max_letter_in_row)
        {
            if (*p == ' ')
                last_space = p;
            p++;
        }
        if (last_space == NULL && *p != 0)
        {
            std::cout << "a word is longer than max_letter_in_row" << std::endl;
            return -1;
        }

        if (last_space == NULL)
        {
            lines.push_back(std::string(start, p-start));
        }
        else
        {
            lines.push_back(std::string(start, last_space-start));
            start = last_space + 1;
            p = start;
        }
    }
    return 0;
}

int put_lines_into_image(std::vector<std::string>& lines, int max_letter_in_col, std::vector<Mat>& images)
{
    int font_face = FONT_HERSHEY_COMPLEX;
    double font_scale = 0.5;
    int thickness = 0;
    int line_idx = 0;
    bool finish = false;

    for (int channel=0; channel<3; ++channel)
    {
        for (int pos_in_col=0; pos_in_col<max_letter_in_col; ++pos_in_col)
        {
            Point origin;
            origin.x = 5;
            origin.y = (1+pos_in_col) * LETTER_HEIGHT - 1;
            putText(images[channel], lines[line_idx++], origin, font_face, font_scale, Scalar(255), thickness);
            if ((size_t)line_idx == lines.size())
            {
                finish = true;
                break;
            }
        }
        if (finish)
            break;
    }
    return 0;
}

int merge_images(const Mat& input_image, std::vector<Mat>& words_images, Mat& output_image)
{
    for (auto it=words_images.begin(); it!=words_images.end(); ++it)
    {
        assert(it->cols == input_image.cols && it->cols == output_image.cols);
        assert(it->rows == input_image.rows && it->rows == output_image.rows);
    }

    for (int x=0; x<input_image.cols; ++x)
    {
        for (int y=0; y<input_image.rows; ++y)
        {
            ::Vec3b base = input_image.at<Vec3b>(y, x);
            for (int channel=0; channel<3; ++channel)
            {
                if (words_images[channel].at<uint8_t>(y,x))
                    base[channel] |= (uint8_t)1;
                else
                    base[channel] &= ~((uint8_t)1);
            }
            output_image.at<Vec3b>(y, x) = base;
        }
    }
    return 0;
}

int encode_words_into_image(const std::string& input_image_path, const std::string& words_path,
        const std::string& output_image_path)
{
    // read content of words_path
    int ret = 0;
    std::fstream ifs(words_path);
    if (! ifs.good())
    {
        std::cout << "open words_path " << words_path << " failed" << std::endl;
        return -1;
    }
    std::string line;
    std::string words;
    bool first_line = true;
    while (getline(ifs, line))
    {
        if (line.empty())
            continue;
        if (first_line)
            first_line = false;
        else
            words.append(" ");
        words.append(line);
    }

    // check if image space is big enough to put all words
    Mat input_image = imread(input_image_path);
    size_t expect_capacity = words.size() * 1.5;
    size_t real_capacity = input_image.cols * input_image.rows * 3.0 / (LETTER_WIDTH * LETTER_HEIGHT);
    if (real_capacity < expect_capacity)
    {
        std::cout << "not enough space of image to encode words" << std::endl;
        return -2;
    }

    // rearrange_words to put in base_images
    std::vector<std::string> lines;
    int max_letter_in_row = (input_image.cols + LETTER_WIDTH - 1)/LETTER_WIDTH;
    int max_letter_in_col = (input_image.rows + LETTER_HEIGHT- 1)/LETTER_HEIGHT;
    ret = rearrange_words(words, max_letter_in_row, lines);
    if (ret != 0)
    {
        std::cout << "rearrange_words failed" << std::endl;
        return -3;
    }

    // put all words into another image
    std::vector<Mat> words_images(3, Mat::zeros(Size(input_image.cols, input_image.rows), CV_8U));
    ret = put_lines_into_image(lines, max_letter_in_col, words_images);
    if (ret != 0)
    {
        std::cout << "put_lines_into_image failed" << std::endl;
        return -4;
    }

    // for debug
    // imwrite("debug.jpg", words_images[0]);
    
    // merge input image and image with words
    Mat output_image = Mat::zeros(Size(input_image.cols, input_image.rows), CV_8UC3);
    ret = merge_images(input_image, words_images, output_image);
    if (ret != 0)
    {
        std::cout << "merge_images failed" << std::endl;
        return -5;
    }
    
    /*
    size_t dark_count = 0;
    size_t white_count = 0;
    for (int x=0; x<output_image.cols; ++x)
    {
        for (int y=0; y<output_image.rows; ++y)
        {
            ::Vec3b base = output_image.at<Vec3b>(y, x);
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
    */

    // save images
    if (! imwrite(output_image_path, output_image))
    {
        std::cout << "imwrite failed" << std::endl;
        return -6;
    }

    /*
    Mat output1_image = imread(output_image_path);
    dark_count = 0;
    white_count = 0;
    for (int x=0; x<output1_image.cols; ++x)
    {
        for (int y=0; y<output1_image.rows; ++y)
        {
            ::Vec3b base = output1_image.at<Vec3b>(y, x);
            for (int channel=0; channel<3; ++channel)
            {
                if (base[channel] & 1)
                    white_count++;
                else
                    dark_count++;
            }
        }
    }
    std::cout << "dark_count1: " << dark_count << ", white_count1: " << white_count << std::endl;
    */

    return 0;
}


int main()
{
    int ret = encode_words_into_image("input.jpg", "words.txt", "output.png");
    if (ret != 0)
    {
        std::cout << "encode_words_into_image failed" << std::endl;
        return -1;
    }
    return 0;
}
