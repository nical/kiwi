
#echo "--test.kiwi.core"
#dmd -Iinclude/extern -debug -unittest -g -odbin/ -ofbin/core_test src/kiwi/core/*.d src/extern/*/*.d test/core.d
echo "--test.kiwi.text"
dmd -Iinclude/extern -debug -unittest -g -odbin/ -ofbin/text_test src/kiwi/*/*.d src/extern/*/*.d test/text.d
