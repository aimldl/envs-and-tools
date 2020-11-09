* Draft: 2020-10-08 (Thu)
Master node
* ID: h2o-docker, k1-4$, h2o_docker@h2o-Alienware-Aurora-R6:~$
Web browser에 떠있던 링크
* Linux Docker Images
  * http://docs.h2o.ai/driverless-ai/latest-stable/docs/userguide/install/linux-docker-images.html
* Docker-README
  * https://github.com/aimldl/technical_skills/blob/master/computing_environments/docker/README.md
* h2o-3/Dockerfile 
  https://github.com/h2oai/h2o-3/blob/master/Dockerfile
  
To remind where I stopped,
* No conda is installed.

```bash
h2o_docker@h2o-Alienware-Aurora-R6:~$ history
    1  sudo docker ps
    2  sudo docker attach fe51f813476b
    3  docker
    4  ls
    5  cd _k8s_kubeflow_installation/
    6  ls
    7  chmod +x install_ubuntu_packages 
    8  ./install_ubuntu_packages 
    9  ls
   10  ./install_ubuntu_packages 
   11  ls
   12  gedit install_ubuntu_packages &
   13  ls
   14  gedit install &
   15  ./install_ubuntu_packages 
   16  sudo apt-get remove docker docker-engine docker.io
   17  sudo apt install -y docker.io
   18  docker --version
   19  sudo docker run hello-world
   20  sudo groupadd docker
   21  sudo usermod -aG docker $USER
   22  sudo systemctl enable docker
   23  docker
   24  docker login
   25  sudo docker login
   26  docker pull aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4
   27  sudo docker pull aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4
   28  docker run -it -p 54321:54321 aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
   29  sudo docker run -it -p 54321:54321 aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
   30  docker images
   31  sudo docker images
   32  sudo docker run -it -p 54321:54321 aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
   33  sudo docker run -it -p 8080:8080 aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
   34  history
   35  docker images
   36  sudo docker ps
   37  sudo docker login
   38  sudo docker commit dcf0949f7ec7 aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4
   39  docker images
   40  sudo docker images
   41  docker push aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4
   42  sudo docker push aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4
   43  cd
   44  l
   45  ls
   46  docker ps
   47  sudo docker ps
   48  docker exec  dcf0949f7ec7
   49  sudo docker exec  dcf0949f7ec7
   50  sudo docker exec -it dcf0949f7ec7 bash
   51  ls
   52  sudo docker exec -it dcf0949f7ec7 bash
   53  sudo docker exec -it -m _h2o_installation: downloads dcf0949f7ec7 bash
   54  sudo docker exec -it --mount _h2o_installation: downloads dcf0949f7ec7 bash
   55  sudo docker exec -it -v _h2o_installation: downloads dcf0949f7ec7 bash
   56  sudo docker exec -it --volume _h2o_installation: downloads dcf0949f7ec7 bash
   57  sudo docker exec -it --volume _h2o_installation: downloads dcf0949f7ec7 bashdocker exec --help
   58  sudo docker exec --help
   59  docker ps
   60  sudo docker ps
   61  sudo docker stop xenodochial_poincare
   62  sudo docker ps
   63  ls
   64  cd _
   65  cd _h2o_installation/
   66  pwd
   67  docker run -it v /home/h2o_docker/_h2o_installation:/home/user/projects aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4 bash
   68  sudo docker run -it v /home/h2o_docker/_h2o_installation:/home/user/projects aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4 bash
   69  sudo docker run -it -v /home/h2o_docker/_h2o_installation:/home/user/projects aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4 bash
   70  ls
   71  history
   72  docker images
   73  sudo docker images
   74  sudo docker -it aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4 bash
   75  sudo docker run -it aimldl/baseimage_openjdk11.0.8_python3.7.6_conda4.8.2_ubuntu18.04.4 bash
   76  sudo docker images
   77  sudo docker ps
   78  sudo docker run -it aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
   79  ls
   80  sudo docker images
   81  sudo docker ps
   82  sudo docker attach fe51f813476b
   83  sudo docker ps
   84  sudo docker commit fe51f813476b aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
   85  sudo docker images
   86  sudo docker login
   87  sudo docker push aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
   88  ls
   89  docker ps
   90  dos2unix
   91  sudo apt install dos2unix
   92  unix2dox
   93  unix2dos
   94  which unix2dos
   95  ls
   96  docker
   97  ls
   98  docker ps
   99  sudo systemctl status docker
  100  groups
  101  groups $USER
  102  cd /opt
  103  ls
  104  tree
  105  tree -d
  106  cd
  107  l
  108  sudo docker ps
  109  sudo docker images
  110  sudo docker run -it -p 54321:54321 aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
  111  history
  112  docker ps
  113  docker attach f07c7b8d5897
  114  history
  115  sudo docker run -it -p 54321:54321 aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
  116  sudo docker ps
  117  sudo docker attach heuristic_black 
  118  ifconfig | grep "inet "
  119  LS
  120  ㅣㄴ
  121  ls
  122  pwd
  123  kubectl
  124  conda ino -e
  125  conda info -e
  126  which kubectl
  127  history
$
```
