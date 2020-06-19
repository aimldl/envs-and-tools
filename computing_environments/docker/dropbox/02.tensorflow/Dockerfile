FROM "tensorflow/tensorflow:latest-gpu"
RUN apt-get update && yes | apt-get upgrade

# Install some basic programs
RUN apt-get install -y tree 

# Install necessary Python packages with pip
RUN apt-get install -y python-pip
RUN pip install --upgrade pip
RUN pip install --user scikit-image

# Clone the TensorFlow models
RUN apt-get install -y git-all
RUN mkdir -p /tensorflow/models
#RUN git clone https://github.com/tensorflow/models.git /tensorflow/models


#RUN pip install tensorflow
#RUN apt-get install -y protobuf-compiler python-pil python-lxml
#RUN pip install jupyter
#RUN pip install matplotlib
#WORKDIR /tensorflow/models/research
#RUN protoc object_detection/protos/*.proto --python_out=.
#RUN export PYTHONPATH=$PYTHONPATH:`pwd`:`pwd`/slim
#RUN jupyter notebook --generate-config --allow-root
#RUN echo "c.NotebookApp.password = u'sha1:6a3f528eec40:6e896b6e4828f525a6e20e5411cd1c8075d68619'" >> /root/.jupyter/jupyter_notebook_config.py

EXPOSE 8888
CMD ["echo", "Hello"]

