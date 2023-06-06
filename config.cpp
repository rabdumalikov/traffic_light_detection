#include "config.hpp"
#include <fstream>

static cv::Scalar create_color(const std::vector<int32_t> &color) {
  return cv::Scalar(color[0], color[1], color[2]);
}

static nlohmann::json parse_config_file(std::string_view config_file_path) {
  std::ifstream cfg(config_file_path.data());

  if (!cfg.is_open()) {
    std::cout << "Error opening config file\n" << config_file_path << "\n";
    throw std::runtime_error("Error opening config file");
  }

  // Read the file content into a string
  std::string file_content((std::istreambuf_iterator<char>(cfg)),
                           std::istreambuf_iterator<char>());

  cfg.close();

  // Parse the JSON string
  return nlohmann::json::parse(file_content);
}

config::config(std::string_view cfg_file)
    : cfg_(parse_config_file(cfg_file)),
      INPUT_WIDTH(cfg_["INPUT_WIDTH"].get<float>()),
      INPUT_HEIGHT(cfg_["INPUT_HEIGHT"].get<float>()),
      SCORE_THRESHOLD(cfg_["SCORE_THRESHOLD"].get<float>()),
      NMS_THRESHOLD(cfg_["NMS_THRESHOLD"].get<float>()),
      CONFIDENCE_THRESHOLD(cfg_["CONFIDENCE_THRESHOLD"].get<float>()),
      FONT_SCALE(cfg_["FONT_SCALE"].get<float>()),
      FONT_FACE(cfg_["FONT_FACE"].get<int32_t>()),
      THICKNESS(cfg_["THICKNESS"].get<int32_t>()),
      BLACK(create_color(cfg_["BLACK"].get<std::vector<int32_t>>())),
      BLUE(create_color(cfg_["BLUE"].get<std::vector<int32_t>>())),
      YELLOW(create_color(cfg_["YELLOW"].get<std::vector<int32_t>>())),
      RED(create_color(cfg_["RED"].get<std::vector<int32_t>>())) {}