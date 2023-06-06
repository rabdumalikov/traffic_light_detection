// Include Libraries.
#include "config.hpp"
#include "data_provider.hpp"
#include "detector.hpp"
#include "visualizer.hpp"
#include <fstream>

// Namespaces.
using namespace cv;
using namespace std;
using namespace cv::dnn;

void detect_in_video() {
  const auto cfg = config{"/app/config.json"};

  data_provider dp("/app/traffic_light_hw.mp4");

  // Get the video's properties
  const int32_t frameWidth = dp.get<CAP_PROP_FRAME_WIDTH>();
  const int32_t frameHeight = dp.get<CAP_PROP_FRAME_HEIGHT>();
  const double fps = dp.get<CAP_PROP_FPS>();

  // Create a VideoWriter object to save the output video
  VideoWriter outputVideo("/app/output/output_video.mp4",
                          VideoWriter::fourcc('a', 'v', 'c', '1'), fps,
                          Size(frameWidth, frameHeight), true);
  if (!outputVideo.isOpened()) {
    std::cout << "Error opening output video file" << std::endl;
    return;
  }

  detector det("/app/models/yolov5s.onnx", cfg);
  visualizer vis("coco.names", cfg);

  // Loop through the video frames
  for (auto &frame : dp) {
    vector<Mat> detections = det(frame);

    Mat img = vis(frame, detections);

    // Save the processed frame to the output video
    outputVideo.write(img);
  }

  // Release the video capture, close the output video, and destroy the window
  outputVideo.release();
}

int main() {
  detect_in_video();
  return 1;
}