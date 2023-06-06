#include "visualizer.hpp"
#include <fstream>

// Draw the predicted bounding box.
void visualizer::draw_label(cv::Mat &input_image, std::string label, int left,
                            int top, const config &cfg) {
  // Display the label at the top of the bounding box.
  int baseLine;
  cv::Size label_size = cv::getTextSize(label, cfg.FONT_FACE, cfg.FONT_SCALE,
                                        cfg.THICKNESS, &baseLine);

  top = cv::max(top, label_size.height);
  // Top left corner.
  cv::Point tlc = cv::Point(left, top);
  // Bottom right corner.
  cv::Point brc =
      cv::Point(left + label_size.width, top + label_size.height + baseLine);
  // Draw black rectangle.
  cv::rectangle(input_image, tlc, brc, cfg.BLACK, cv::FILLED);
  // Put the label on the black rectangle.
  cv::putText(input_image, label, cv::Point(left, top + label_size.height),
              cfg.FONT_FACE, cfg.FONT_SCALE, cfg.YELLOW, cfg.THICKNESS);
}

std::vector<std::string>
visualizer::fetch_label(std::string_view label_file_path) {
  std::ifstream ifs(label_file_path.data());
  std::string line;

  std::vector<std::string> class_list;

  while (getline(ifs, line)) {
    class_list.push_back(line);
  }

  return class_list;
}

visualizer::visualizer(std::string_view label_file_path, const config &cfg)
    : class_list_(visualizer::fetch_label(label_file_path)), config_{cfg} {}

cv::Mat visualizer::operator()(cv::Mat input_image,
                               std::vector<cv::Mat> &predictions) {
  // Initialize vectors to hold respective predictions while unwrapping detections.
  std::vector<int32_t> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  // Resizing factor.
  float x_factor = input_image.cols / config_.INPUT_WIDTH;
  float y_factor = input_image.rows / config_.INPUT_HEIGHT;

  float *data = (float *)predictions[0].data;

  const int dimensions = 85;
  const int rows = 25200;
  // Iterate through 25200 detections.
  for (int i = 0; i < rows; ++i) {
    float confidence = data[4];
    // Discard bad detections and continue.
    if (confidence >= config_.CONFIDENCE_THRESHOLD) {
      float *classes_scores = data + 5;
      // Create a 1x85 Mat and store class scores of 80 classes.
      cv::Mat scores(1, class_list_.size(), CV_32FC1, classes_scores);
      // Perform minMaxLoc and acquire index of best class score.
      cv::Point class_id;
      double max_class_score;
      cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
      // Continue if the class score is above the threshold.
      if (max_class_score > config_.SCORE_THRESHOLD) {
        // Store class ID and confidence in the pre-defined respective vectors.

        confidences.push_back(confidence);
        class_ids.push_back(class_id.x);

        // Center.
        float cx = data[0];
        float cy = data[1];
        // Box dimension.
        float w = data[2];
        float h = data[3];

        // Bounding box coordinates.
        int left = int((cx - 0.5 * w) * x_factor);
        int top = int((cy - 0.5 * h) * y_factor);
        int width = int(w * x_factor);
        int height = int(h * y_factor);
        // Store good detections in the boxes vector.
        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }
    // Jump to the next column.
    data += 85;
  }

  // Perform Non Maximum Suppression and draw predictions.
  std::vector<int32_t> indices;
  cv::dnn::NMSBoxes(boxes, confidences, config_.SCORE_THRESHOLD,
                    config_.NMS_THRESHOLD, indices);
  for (int i = 0; i < indices.size(); i++) {
    int idx = indices[i];

    if (class_list_[class_ids[idx]] != "traffic light") {
      continue;
    }

    const auto [left, top, width, height] = boxes[idx];

    // Draw bounding box.
    cv::rectangle(input_image, cv::Point(left, top),
                  cv::Point(left + width, top + height), config_.BLUE,
                  config_.THICKNESS * 3);

    const std::string label = cv::format("%dx%d", width, height);
        //class_list_[class_ids[idx]] + ":" + cv::format("%dx%d", width, height);
    // Draw class labels.
    visualizer::draw_label(input_image, label, left, top, config_);
  }

  return input_image;
}
