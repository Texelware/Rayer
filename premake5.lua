workspace "Rayer"

    architecture "x64"
    configurations {

        "Debug",
        "Release",
        "Dist"
    }

    startproject "SandBox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"

    include "Rayer/vendor/GLFW"
    include "Rayer/vendor/GLAD"
    include "Rayer/vendor/ImGui"

group ""

group "Core"

    include "Rayer"
    
group ""

group "SandBox" 

    include "Sandbox"

group ""

