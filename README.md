## Traffic Light Detection

The system uses opencv and yolo-v5. yolo-v5's main purpose is to find traffic lights in an image using a deep learning model. opencv, on the other hand, is used to draw a box around the detected traffic lights. The system consists of three main parts: the Data Provider, the Detector, and the Visualizer. Each part is compiled into separate static libraries.

  

**Data Provided:**

  

The Data Provider is primarily responsible for retrieving images from a video stream. Since we are working with a video file, I have implemented support for a class that can be used in a range-based for loop. This allows for convenient iteration over frames. However, this approach would not be suitable if we were using a camera feed, as it would be unintuitive for other developers to understand the incorporated termination points inside the loop that stop the system.

  

Instead, a better approach would be to create the Data Provider as a separate process. This process would handle the task of sending frames and could also receive signals from other components indicating whether it should continue sending the camera feed. By decoupling the Data Provider from the main loop, we can easily introduce a termination mechanism without sacrificing clarity or comprehension.

  

**Detector:**

  

The Detector, utilizing yolo-v5, is responsible for detecting traffic lights within a frame and providing bounding boxes for the detected objects.

  

**Visualizer:**

  

The Visualizer takes in a frame and predicted bounding box information for traffic lights. It uses opencv to draw these bounding boxes on the frame and also displays the size of each box in pixels. This helps us visualize where the traffic lights are and how big they are in the image.

  

**Config:**

  

The Config module accepts a path to a configuration file in JSON format. It reads and analyzes the file using nlohmann library, then initializes variables within the structure to conveniently and easily access those values. This allows us to retrieve and utilize the configuration settings efficiently and effortlessly.

**Main:** 

The Main file serves as the central component that brings all the different parts together to create a cohesive system for detecting traffic lights.
  
  

# How to use:

  

1. Run the command `./builddocker.sh` to build a container named 'auvetech'. This step will create the necessary container environment.

2. Execute the command `./rundocker.sh` to start the created container. This will initiate the entry point, which involves detecting traffic lights within a video file named **traffic_light_hw.mp4**. The detection results will be outputted to a file named **output_video.mp4** located in the same folder as the script.

  
  

# Formatting:

I have used clang-format to format c++ code.

  

# Finished Tasks:

  

1. Usage of Docker is required. Your system must work inside a docker container based on public image with Ubuntu and OpenCV.

  

2. Your system must start automatically after starting the docker container.

  

3. Your system should contain several classes for specific functions (data provider, detector, visualizer, etc).

  

4. Readme with the description.

  

5. Splitting the provider, detector and visualizer to a separate libraries

(different CMake targets).

  

6. Using external yaml/json file with the parameters (not hardcode it).

  

7. Using OpenCV neural network detectors.