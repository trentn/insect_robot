#!/bin/bash


####
# Helper Functions
####
function install_srcs {

SRC_LOCATIONS="$1"
CROSS_COMPILE="$2"
INSTALL_LOCATION="$3"

for src_location in $1
do
    filename=${src_location##*/}
    dir=${filename%%\.tar\.gz}

    if [ ! -d "$dir" ]; then
        echo "Retrieving and installing $dir"
        wget $src_location
        tar xzvf $filename

        cd $dir
        ./configure $CROSS_COMPILE $INSTALL_LOCATION
        make
        make install
        cd ..
    else
        echo "Already installed $dir"
    fi
done

}

####
# Main Script
####

echo "Creating and entering 'depends' directory"
mkdir -p depends
cd depends


BCMLIBRARY="bcm2835-1.60"
BUILD_APT_PACKAGES="cmake"
HOST_APT_PACKAGES="libncurses5 libncurses5-dev"

SRC_LOCATIONS="http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz"

XCOMP_SRC_LOCATIONS="ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.1.tar.gz"

CROSS_COMPILE=""
INSTALL_LOCATION=""
APT_PACKAGES="$MIN_APT_PACKAGES $HOST_APT_PACKAGES"


while (( "$#" )); do
    case "$1" in
        -x|--cross-compile)
            CROSS_COMPILE="--host $2 --disable-stripping"
            INSTALL_LOCATION="--prefix $PWD"
            APT_PACKAGES="$BUILD_APT_PACAKGES"
            shift 2
            ;;
        *)
            echo "Error: unsupported arguments"
            exit 1
            ;;
    esac
done


echo ""
echo "Installing apt packages $APT_PACKAGES..."
sudo apt-get install -y $APT_PACKAGES


mkdir -p src
cd src

if [ -z "$CROSS_COMPILE" ]; then

    echo "-------------------------------------------------------"
    echo "Installing dependecies requiring from source compiling"
    echo "-------------------------------------------------------"
    install_srcs "$SRC_LOCATIONS" "$CROSS_COMPILE" "$INSTALL_LOCATION"
else
    echo "-------------------------------------------------------"
    echo "Installing dependencies for cross compiling into 'depends' directory"
    echo "-------------------------------------------------------"
    SRC_LOCATIONS="$SRC_LOCATIONS $XCOMP_SRC_LOCATIONS"
    install_srcs "$SRC_LOCATIONS" "$CROSS_COMPILE" "$INSTALL_LOCATION"
fi