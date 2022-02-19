# Merase

[![ci](https://github.com/ztnel/merase/actions/workflows/ci.yaml/badge.svg)](https://github.com/ztnel/merase/actions/workflows/ci.yaml) [![codecov](https://codecov.io/gh/ztnel/merase/branch/master/graph/badge.svg?token=6Q7DKCSAVU)](https://codecov.io/gh/ztnel/merase)

Modified: 2022-02

C logger for embedded systems. `Merase` is derived from [polymerase](https://en.wikipedia.org/wiki/Polymerase), an enzyme responsible for transcribing DNA or MRNA, in other words a genetic logger.

## Build
Build the static library:
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

## Tests
Clone the project: 
```bash
git clone https://github.com/ztnel/merase.git
```

Build static lib from source with debug flag set:
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j
```

Run the tests and coverage:
```bash
make cov
```

## Example
See [here](examples) for an example of using the static library in your project.

## License
This software is licensed under the terms of the [MIT License](LICENSE)
