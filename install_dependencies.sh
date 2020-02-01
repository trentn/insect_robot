#!/bin/bash

BCMLIBRARY="bcm2835-1.60"
APT_PACKAGES="cmake libncurses5 libncurses5-dev"

echo "Installing $BCMLIBRARY..."
if [ ! -d "$BCMLIBRARY" ]; then
wget http://www.airspayce.com/mikem/bcm2835/$BCMLIBRARY.tar.gz
tar xzvf $BCMLIBRARY.tar.gz

cd $BCMLIBRARY
./configure
make
sudo make check
sudo make install
cd ../

echo "Installed bcm2835 library"
else
    echo "$BCMLIBRARY is already installed"
    
fi

echo ""
echo "Installing apt packages $APT_PACKAGES..."
sudo apt-get install -y $APT_PACKAGES