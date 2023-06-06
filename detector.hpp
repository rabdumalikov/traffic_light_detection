#pragma once

#include <opencv2/opencv.hpp>
#include <string_view>
#include "config.hpp"

class detector
{
        // Load model.
        cv::dnn::Net net_;
        config config_;

    public:
        detector( std::string_view model_file_path, const config & cfg );

        // Run inference on input_image to detect traffic lights
        std::vector<cv::Mat> operator()( cv::Mat & input_image );
};