# Download and prepare a Docker image

```
# Let's use a command line command to log into Docker Hub.
# The login credentials have already been set up in this example.
$ docker login
Authenticating with existing credentials...
WARNING! Your password will be stored unencrypted in /home/userid/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded

# My Docker Hub ID is aimldl. Search the uploaded Docker images by me.
$ docker search aimldl
NAME                      DESCRIPTION     STARS     OFFICIAL     AUTOMATED
aimldl/python3_base_image                 0                               
aimldl/keras_base_image                   0             
aimldl/tensorflow_base_image              0                 
aimldl/flask_was_base_image               0               
aimldl/flask_hello_world                  0         
aimldl/ubuntu_base_image                  0               
  ...
$

# List up the Docker images downloaded to my local machine.
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/tensorflow_base_image  latest  255f88e7c71f  18 months ago  1.55GB
  ...
$

# aimldl/keras_base_image doesn't exist on the local machine.
# So let's download the image from Docker Hub to the local machine.
$ docker pull aimldl/keras_base_image
Using default tag: latest
latest: Pulling from aimldl/keras_base_image
124c757242f8: Already exists 
9d866f8bde2a: Already exists 
  ...
f296ef3d9b89: Pull complete 
8c6adc173361: Pull complete 
  ...
Status: Downloaded newer image for aimldl/keras_base_image:latest
docker.io/aimldl/keras_base_image:latest
$

# Verify if the target Docker image "keras_base_image" is downloaded.
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
  ...
aimldl/keras_base_image       latest  3b9219a43e4d  18 months ago  1.56GB
  ...
$

# Check the OS in the downloaded image to see if I got the right one.
$ docker inspect --format="{{.Os}}" aimldl/keras_base_image
linux
$

# Rename the image for convenience. I know all images are from aimldl.
$ docker tag aimldl/keras_base_image keras_base_image

# Double-check the result. The same IMAGE ID 3b9219a43e4d has two names!
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
  ...
aimldl/keras_base_image       latest  3b9219a43e4d  18 months ago  1.56GB
keras_base_image              latest  3b9219a43e4d  18 months ago  1.56GB

  ...
$

# I could've logged out earlier right after downloading the Docker image.
# But I'm logging out after all the relevant tasks are finished.
# In case the Docker image must be downloaded again.
$ docker logout
Removing login credentials for https://index.docker.io/v1/
$
```

#### 
