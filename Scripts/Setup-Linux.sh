#!/bin/bash

pushd 
../vendor/bin/premake/Linux/premake5 --cc=gcc --file=../Build-Project.lua gmake2
popd