SStory
====================

A very basic header library for the creations of Interactive CLI Text Adventure Games.

* Author: Santiago Quintero Pabón
* Realeased under the MIT License

## Building from source

In general just run the Makefile to compile the provided example

```
make
```

To clean the generated executable run

```
make clean
```

### Linux

Tested on Ubuntu 18.04

You will need OpenAL and Alut installed. In Ubuntu run:

```
sudo apt install libopenal-dev libalut-dev
```

Remember to pass the `-lalut` and `-lopenal` flags when linking.

With Clang:

```
clang++ -o ExGame -std=c++11 -Wall main.cpp -lalut -lopenal
```

### Mac OS

You may want to use Xcode and build from there.

If the Xcode console doesn't respond to the enter key, open the generated executable directly.

If there are linking errors, then the OpenAL.framework is not imported in the project. It must be added to the Link Binary with libraries Build Phase.

If there are _include_ errors about alut.h, try using the included alut.h by changing the include line in SSound.h. Or you can install freealut.

## Note

If there is no sound, remember to point the `base_path` of `SSoundMaster` (in ssound.h) to the appropiated path. This path is relative to the generated executable.
