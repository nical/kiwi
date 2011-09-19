#! /bin/sh

echo "--Generating interface files" && ./INCLUDES.sh && echo "--Building external libs" && ./EXTERN.sh && echo "--Building kiwi.core" && ./CORE.sh && echo "--Building kiwi.image" && ./IMAGE.sh && echo "--building test suite" &&./TEST.sh && echo "--Done."
