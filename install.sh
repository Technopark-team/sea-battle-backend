#!/bin/bash

# install cmake
sudo apt-get -y install cmake

# install compiler gcc
sudo apt-get install build-essential

# install boost
sudo apt-get install libboost-all-dev

# install gtest and gmock
cd ~/Downloads
wget https://github.com/google/googletest/archive/release-1.10.0.tar.gz
tar xf release-1.10.0.tar.gz
cd googletest-release-1.10.0
cmake -DBUILD_SHARED_LIBS=ON .
make
sudo cp -a googletest/include/gtest /usr/include
sudo cp -a lib/libgtest_main.so lib/libgtest.so lib/libgmock.so lib/libgmock_main.so /usr/lib/
sudo ldconfig -v | grep gtest

# install msgpack
cd ~/Downloads
git clone https://github.com/msgpack/msgpack-c.git
cd msgpack-c || exit
cmake -DMSGPACK_CXX17=ON .
sudo make -j 8
sudo make install

# install ncurses
sudo apt-get install libncurses5-dev libncursesw5-dev
