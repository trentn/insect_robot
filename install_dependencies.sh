#!/bin/bash

wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
tar xzvf bcm2835-1.60.tar.gz

cd bcm2835-1.60/
./configure
make
sudo make check
sudo make install
cd ../

echo "Installed bcm2835 library"
