* Draft: 2021-01-28 (Thu)

# E: Unable to locate package libjasper-dev

## Problem



## Hint

Google search: ubuntu 18.04 "E: Unable to locate package libjasper-dev"



#RUN apt install -y  libjasper-dev
RUN apt-get install -y  libjasper-dev

sudo add-apt-repository “deb http://security.ubuntu.com/ubuntu xenial-security main”
sudo apt update
sudo apt install libjasper1 libjasper-dev