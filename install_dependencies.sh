#!/bin/bash

wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.61.tar.gz
tar bcm2835-1.61.tar.gz

cd bcm2835-1.61/
./configure
make
sudo make install
cd ../

echo "Installed bcm2835 library"
