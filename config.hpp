#pragma once

#include <string_view>
#include <opencv2/opencv.hpp>
#include "json/single_include/nlohmann/json.hpp"

struct config
{
    private:
        nlohmann::json cfg_;
    
    public:
        explicit config( std::string_view cfg_file );

        const float INPUT_WIDTH;
        const float INPUT_HEIGHT;
        const float SCORE_THRESHOLD;
        const float NMS_THRESHOLD;
        const float CONFIDENCE_THRESHOLD;

        // Text parameters.
        const float FONT_SCALE;
        const int32_t FONT_FACE;
        const int32_t THICKNESS;

        // Colors.
        const cv::Scalar BLACK;
        const cv::Scalar BLUE;
        const cv::Scalar YELLOW;
        const cv::Scalar RED;
};