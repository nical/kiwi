#! /bin/sh

dmd -unittest -debug src/kiwi/*/*.d src/kiwi/main.d -oftestSuite
