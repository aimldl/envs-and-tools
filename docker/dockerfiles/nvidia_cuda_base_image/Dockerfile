# CUDA base image
#   https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu18.04-x86_64/devel/Dockerfile

FROM nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04
LABEL maintainer "NVIDIA CORPORATION <cudatools@nvidia.com>"
ENV NCCL_VERSION 2.8.3

RUN apt-get update
RUN apt-get install -y --no-install-recommends \
    cuda-cudart-dev-11-2=11.2.72-1 \
    cuda-command-line-tools-11-2=11.2.0-1 \
    cuda-minimal-build-11-2=11.2.0-1 \
    cuda-libraries-dev-11-2=11.2.0-1 \
    cuda-nvml-dev-11-2=11.2.67-1 \
    libnpp-dev-11-2=11.2.1.68-1 \
    libnccl-dev=2.8.3-1+cuda11.2 \
    libcublas-dev-11-2=11.3.1.68-1 \
    libcusparse-11-2=11.3.1.68-1 \
    libcusparse-dev-11-2=11.3.1.68-1
RUN rm -rf /var/lib/apt/lists/*

# apt from auto upgrading the cublas package. See https://gitlab.com/nvidia/container-images/cuda/-/issues/88
RUN apt-mark hold libcublas-dev-11-2 libnccl-dev
ENV LIBRARY_PATH /usr/local/cuda/lib64/stubs

# OpenCV
#   https://hub.docker.com/r/alemelis/darknet
#pip3 install opencv-python

RUN apt install -y \
    pkg-config \
    git \
    build-essential \
    libopencv-dev

# build darknet
WORKDIR /app
RUN git clone https://github.com/AlexeyAB/darknet.git
WORKDIR darknet
RUN make OPENCV=1 GPU=1 AVX=1 OPENMP=1 CUDNN=1 CUDNN_HALF=1 OPENMP=1 -j $(nproc)
RUN chmod +x darknet

ENTRYPOINT ["/app/darknet/darknet"]
