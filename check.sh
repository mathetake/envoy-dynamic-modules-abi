set -e

echo "Formatting C header..."
clang-format -i abi.h

echo "Building C header..."
clang abi.h && rm abi.h.pch

echo "Building C++ header..."
cp -f abi.h abi.hpp && clang++ abi.hpp && rm -f abi abi.hpp.pch abi.hpp

if [ ! -z "`git status -s`" ]; then \
    echo "The following differences will fail CI until committed:"; \
    git diff --exit-code; \
fi
