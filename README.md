# Merase

[![ci](https://github.com/ztnel/merase/actions/workflows/ci.yaml/badge.svg)](https://github.com/ztnel/merase/actions/workflows/ci.yaml)

Modified: 2022-02

Micro c logger for micro embedded systems. The name `merase` is derived from [polymerase](https://en.wikipedia.org/wiki/Polymerase), an enzyme responsible for transcribing DNA or MRNA, in other words a genetic logger.

## Build
Build the static library for merase
```bash
git clone https://github.com/ztnel/merase.git
cd merase
```

Build static lib from source:
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
```

## Example
See [here](examples/README.md) for an example of using the static library.

## License
This software is licensed under the terms of the [MIT License](LICENSE)