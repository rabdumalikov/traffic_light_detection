#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <string_view>
#include "config.hpp"

class visualizer 
{
        std::vector<std::string> class_list_;
        config config_;
    public:

        visualizer( std::string_view label_file_path, const config & cfg );

        // Draw bounding boxes and labels on input_image.
        cv::Mat operator()(cv::Mat input_image, std::vector<cv::Mat> &predictions);

    private:
        static std::vector<std::string> fetch_label( std::string_view label_file_path );
        static void draw_label( cv::Mat& input_image, std::string label, 
            int left, int top, const config & cfg );

};