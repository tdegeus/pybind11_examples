# pybind11_examples

Examples for the usage of `pybind11`

# Cloning the examples

The `pybind11` module (which is header only!) is included as a submodule of this repository. This asks for a little bit more attention when cloning this project. There are two options. The simplest one is

```bash
git clone --recursive https://github.com/tdegeus/pybind11_examples.git
```

This will download the submodule up to the version that is used in this project. To directly download the submodule from the source use


```bash
git clone https://github.com/tdegeus/pybind11_examples.git
cd pybind11_examples
git submodule init
git submodule update
```

