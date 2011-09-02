
echo "--test.kiwi.core"
dmd -Iinclude/extern -debug -unittest -g -odbin/ -ofbin/core_test src/kiwi/core/*.d src/kiwi/dynamic/*.d src/kiwi/utils/*.d src/kiwi/graph/*.d src/kiwi/text/*.d src/extern/*/*.d test/core.d && echo "--done" && ./bin/core_test || echo "\033[1;31m\n--error\033[0m\n"
