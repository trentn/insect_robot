#!/bin/bash

BCMLIBRARY="bcm2835-1.60"
APT_PACKAGES="cmake libncurses5 libncurses5-dev"

CROSS_COMPILE=""
BCM_LOCATION=""

while (( "$#" )); do
    case "$1" in
        -x|--cross-compile)
            CROSS_COMPILE="--host $2"
            BCM_LOCATION="--prefix $PWD/extras"
            shift 2
            ;;
        *)
            echo "Error: unsupported arguments"
            exit 1
            ;;
    esac
done


echo "Installing $BCMLIBRARY..."
if [ ! -d "$BCMLIBRARY" ]; then
wget http://www.airspayce.com/mikem/bcm2835/$BCMLIBRARY.tar.gz
tar xzvf $BCMLIBRARY.tar.gz

cd $BCMLIBRARY
./configure $CROSS_COMPILE $BCM_LOCATION
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