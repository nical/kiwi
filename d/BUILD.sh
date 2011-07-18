#! /bin/sh

time dmd -debug -unittest test/core.d src/extern/log/logstream.d src/kiwi/core/commons.d src/kiwi/core/data.d src/kiwi/core/dynamic.d src/kiwi/core/interfaces.d src/kiwi/core/port.d
