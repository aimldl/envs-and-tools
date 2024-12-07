



Google search: nvidia-docker darknet with opencv

* [Docker image for OpenCV + Python](https://forums.developer.nvidia.com/t/docker-image-for-opencv-python/77513)

> I would like to create an Ubuntu Docker container that uses the following packages:
>
> - Python 3.6 or above
> - OpenCV
> - Python PIL module
> - Keras for inference
> - PyQt5
> - YOLO V3 for inference (Darknet used through OpenCV)
>
> I would like the NVIDIA GPU to be used by these packages. So, I guess OpenCV must be compiled with the appropriate compile flags turned on.

> It is entirely possible for OpenCV itself to never need to use a GPU. But here are my suggestions for some great Base Images for your Docker file: