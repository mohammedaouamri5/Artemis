-- WalnutExternal-Headless.lua

IncludeDir = {


}
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["glad"] = "../vendor/glad"
IncludeDir["cnpy"] = "../vendor/cnpy"
IncludeDir["spdlog"] = "../vendor/spdlog/include"
IncludeDir["vendor"] = "../vendor/"
IncludeDir["X11"] = "../vendor/X11"
IncludeDir["std_image"] = "../vendor/std_image"
IncludeDir["SOIL"] = "../vendor/SOIL"

 
 
group "Dependencies"
   include "vendor/STDIMAGE"
   include "vendor/SOIL"
   include "vendor/glad"
   include "vendor/cnpy"
   include "vendor/yaml-cpp"
   include "vendor/spdlog"
group ""

-- group "Core"
--     include "Walnut/Build-Headless.lua"

     
group ""
