-- premake5.lua
workspace "Artemis"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "main"

 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


defines{"SPDLOG_COMPILED_LIB","SPDLOG_ACTIVE_LEVEL" , "SPDLOG_FMT_EXTERNAL"}

include "Build-External.lua"
include "main/Build-main.lua"
   

