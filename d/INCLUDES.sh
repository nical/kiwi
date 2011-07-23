dmd -o- -Hdinclude/kiwi/core/ -Isrc -Isrc/extern -Dddoc src/kiwi/core/commons.d src/kiwi/core/interfaces.d src/kiwi/core/dynamic.d src/kiwi/core/data.d
dmd -o- -Hdinclude/dtools/ src/extern/dtools/logstream.d  
