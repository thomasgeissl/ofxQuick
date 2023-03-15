#!/bin/sh
cd "$(dirname "$0")"
cd ..
make -j4
mkdir -p ../tmp
cd ../tmp
cp -R ../runtime runtime
# rm -rf ofPackageManager/frontend
zip -r runtime_osx_version.zip runtime
openssl dgst -sha256 runtime_osx_version.zip
