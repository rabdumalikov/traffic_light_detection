#include "data_provider.hpp"

data_provider::video_capture::video_capture(std::string_view video_file_path)
    : video_(video_file_path.data()),
      size_(static_cast<int>(video_.get(cv::CAP_PROP_FRAME_COUNT))) {
  if (!video_.isOpened()) {
    std::cout << "Error opening video file\n";
    throw std::runtime_error("Error opening video file");
  }
}

data_provider::video_capture::~video_capture() { video_.release(); }

data_provider::data_provider(std::string_view video_file_path)
    : video_cap_(video_file_path), frames_(video_cap_.size_) {
  for (int32_t i = 0; i < video_cap_.size_; ++i) {
    cv::Mat frame;
    video_cap_.video_ >> frame;

    frames_[i] = std::move(frame);
  }
}

data_provider::iterator data_provider::begin() { return &frames_[0]; }

data_provider::const_iterator data_provider::begin() const {
  return &frames_[0];
}

data_provider::iterator data_provider::end() {
  return &frames_[video_cap_.size_];
}

data_provider::const_iterator data_provider::end() const {
  return &frames_[video_cap_.size_];
}