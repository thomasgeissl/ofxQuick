#!/bin/sh
cd "$(dirname "$0")"
cd ..
make -j4
mkdir -p ../tmp
cd ../tmp
cp -R ../ofxQuickApp ofxQuickApp
# rm -rf ofPackageManager/frontend
zip -r ofxQuickApp_osx_version.zip ofxQuickApp
openssl dgst -sha256 ofxQuickApp_osx_version.zip
