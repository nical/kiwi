
echo "--test.kiwi.core"
dmd -Iinclude/extern -debug -unittest -g -odbin/ -ofbin/core_test src/kiwi/*.d src/kiwi/dynamic/*.d src/kiwi/text/*.d src/extern/*/*.d test/core.d && echo "--done" && ./bin/core_test || echo "--error"
