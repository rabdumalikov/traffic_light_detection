# Base image
FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive

# Update package lists
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang \
    clang-format \
    libopencv-dev \
    libclang-dev \
    git \
    doxygen

# Set the working directory
WORKDIR /app

# Copy source code files to the container
COPY . /app

# Clone the json library to parse the config file
RUN git clone https://github.com/nlohmann/json.git

# Set the PKG_CONFIG_PATH environment variable for opencv
ENV PKG_CONFIG_PATH=/usr/lib/x86_64-linux-gnu/pkgconfig/

# Compile and build code with cmake
RUN cmake . && make

# Set the entry point to predicting traffic lights
ENTRYPOINT ["/app/my_program"]