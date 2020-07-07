@ECHO Off
SET PATH=..\Compiler\SH_COFF\Other Utilities;..\Compiler\SH_COFF\sh-coff\bin;..\Compiler\SN;..\Compiler\TOOLS;%PATH%
make re

ping 127.0.0.1 -n 20 > nul