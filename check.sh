set -e

echo "Formatting C header..."
clang-format -i abi.h

echo "Building C header..."
clang abi.h

echo "Building C++ header..."
cp abi.h abi.hpp && clang++ abi.hpp

if [ ! -z "`git status -s`" ]; then \
    echo "The following differences will fail CI until committed:"; \
    git diff --exit-code; \
fi
