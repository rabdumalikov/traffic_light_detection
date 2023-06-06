

#include "detector.hpp"

detector::detector(std::string_view model_file_path, const config &cfg)
    : net_(cv::dnn::readNet(model_file_path.data())), config_{cfg} {}

std::vector<cv::Mat> detector::operator()(cv::Mat &input_image) {
  // Convert to blob.
  cv::Mat blob;
  cv::dnn::blobFromImage(input_image, blob, 1. / 255.,
                         cv::Size(config_.INPUT_WIDTH, config_.INPUT_HEIGHT),
                         cv::Scalar(), true, false);

  net_.setInput(blob);

  // Forward propagate.
  std::vector<cv::Mat> outputs;
  net_.forward(outputs, net_.getUnconnectedOutLayersNames());

  return outputs;
}