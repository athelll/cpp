[COMPILATION]
Author: Felix,  Date: [19/08/23]

In Gcc/G++ compiler there are two compilation mode

1) '-ggdb' : This flag compiles with debugging making the file larger and removes
all optimizaion while compiling. the exec is larger in size and slower in execution.

2) '-O2 -DNDEBUG' : This flag compiles with full optimazations and the debug info stripped
from the executable. its exec is smaller in size, and faster in execution.
use for publice releases.

3) '-pedantic-errors': disables compiler extensions. makes code more portable and vanilla C++.

4) '-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion': this flags ensure that error checking and warning is at maximum
to prevent error-prone code and amiss syntaxes which might still run but in the grand scheme might become questionable.
