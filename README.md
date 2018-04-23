# CGALForUE4.19

Thanks for armabon.

This plugin is based on https://github.com/armabon/UE4_CGAL.git 

CGAL for 4.11

boost for 1.66

perhaps there will be some mistakes when packaging the project

this plugin for CGAL in UE4.19


note:
if you use the cgal library in other modules , you need to add 
"  
   bEnableUndefinedIdentifierWarnings = false;
   bUseRTTI = true;
" to the modules' build.cs file to prevent from "rtti error"
