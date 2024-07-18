# Application Binary Interface (ABI) for EnvoyX

This repository hosts the ABI for EnvoyX. The ABI is defined in a single header file, `abi.h`, which is will be used in the EnvoyX source code as well as SDKs. To build the ABI, run the following command:

```bash
zig cc -target x86_64-linux-gnu -c abi.h
```

