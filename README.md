# Application Binary Interface (ABI) for EnvoyX

This repository hosts the ABI for EnvoyX. The ABI is defined in a single header file, `abi.h`, which is will be used in the EnvoyX source code as well as SDKs. To build the ABI, run the following commands:

```bash
clang -c abi.h
clang-format -i abi.h
```
