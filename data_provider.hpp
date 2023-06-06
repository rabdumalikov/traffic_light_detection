#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <string_view>


class data_provider
{
        // RAII wrapper for cv::VideoCapture.
        struct video_capture
        {
            video_capture( std::string_view video_file_path );
           ~video_capture();

            cv::VideoCapture video_;
            int32_t size_;
        };

        video_capture video_cap_;
        std::vector<cv::Mat> frames_;

    public:
        // Throw exception if video file cannot be opened.        
        explicit data_provider( std::string_view video_file_path );

        // For range-based for loop.
        using iterator = cv::Mat*;
        using const_iterator = const cv::Mat*;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        // Access to video capture properties.
        template< int32_t T >
        int32_t get() const
        {
            return static_cast<int32_t>( video_cap_.video_.get( T ) );
        }
};