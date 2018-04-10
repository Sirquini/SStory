SStory
====================

A very basic Interactive CLI Text Adventure creation header library.

* Author: Santiago Quintero Pabón
* Realeased under the MIT License

## Building from source

### Linux

Tested on Ubuntu 16.04

You will need OpenAL and Alut installed. In ubuntu just run:

```
sudo apt-get install libopenal-dev libalut-dev
```

Remember to pass the `-lalut` and `-lopenal` flags for proper linking.

For example, with Clang:

```
clang++ -o ExGame -std=c++11 -Wall main.cpp main.cpp -lalut -lopenal
```

### Mac OS

It is a lot easier to just use Xcode and open the Xcode project file and build from there.

If the Xcode console doesn't respond to the enter key, open the generated executable directly.

If the are linking errors, then the OpenAL.framework is not imported in the project. It must be added to the Link Binary with libraries Build Phase.

If there are include errors about alut.h, try using the included alut.h, changing the include line in SSound.h. Or you can install freealut.

## Note

If there is no sound, remember to point the base_path of SSoundMaster (in ssound.h) to the appropiated absolute path.

