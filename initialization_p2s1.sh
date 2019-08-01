
#!/bin/bash
echo "Initialization is starting soon... "

apt-get --assume-yes install g++
apt-get --assume-yes install build-essential

echo "g++ is needed to compile your c/c++ codes in linux."
echo "Available g++ version:"
g++ --version

echo "Update and upgrade your system."
apt-get update
apt-get upgrade

apt-get --assume-yes install libx11-dev
apt-get --assume-yes install cimg-dev

apt-get --assume-yes install git

su -c "git clone https://AysegulDemirtas:stmassignment3107@github.com/AysegulDemirtas/3Kernel-Image-Filtering.git" -m "user"

echo "Be sure that you have CImg.h file in your current working directory."

echo "Be sure that you have source image file in your current working directory."

cd 3Kernel-Image-Filtering
su -c "make" -m user
su -c "./img_filter" -m user


