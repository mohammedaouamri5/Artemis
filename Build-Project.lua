-- premake5.lua
workspace "main"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "main"

 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Build-External.lua"
include "main/Build-main.lua"