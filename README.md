# wordle-bg

A [Wordle](https://www.powerlanguage.co.uk/wordle/) clone in Bulgarian

<img src="https://user-images.githubusercontent.com/1991296/149661731-0b545de4-bf1c-4f9c-bf17-28ca22013ad6.png" style="display: inline-block; overflow: hidden; width: 49%;"></img>
<img src="https://user-images.githubusercontent.com/1991296/149661701-62093ce4-c97a-43b9-b9bf-5641fd6a9474.png" style="display: inline-block; overflow: hidden; width: 49%;"></img>

Play online: https://wordle-bg.ggerganov.com

## Description

This clone is written in C++ and ported to the Web with Emscripten. The bulk of the implementation is in the file [src/main.cpp](src/main.cpp). The HTML/JS wrapper is in [src/index-tmpl.html](src/index-tmpl.html). The advantages of this programming stack is that you can run the game both as a native application and as a web-page. The main drawback is that you lose most of the HTML/JS/CSS goodies available when building a standard web application.

I've tried to keep the look and feel as close as possible to the original, although there are certain things that do not behave the same. For example, the smooth fade-in and fade-out of the window popups was too complicated to implement, so I opted out for a simpler approach.

The current [dictionary](words/words.txt) contains 6474 words. Derivative forms are not included (e.g. "бягам" is allowed, but not "бягал", "бягащ").

## Build as native app

```
# install dependencies
sudo apt-get install libsdl2-dev

# build from source
git clone --recursive https://github.com/ggerganov/wordle-bg
cd wordle-bg
mkdir build && cd build
cmake ..
make -j
ln -sfn ../fonts/* ./
ln -sfn ../words/* ./
./bin/wordle
```

## Build as web app

```
git clone --recursive https://github.com/ggerganov/wordle-bg
cd wordle-bg
mkdir build-em && cd build-em
emcmake cmake ..
make -j
cp ./bin/wordle-extra/* /var/www/html/
cp ./bin/* /var/www/html/
```

## Thanks

- [@rgerganov](https://github.com/rgerganov) for the idea
- [@ibob](https://github.com/ibob) for helping me find a dictionary with Bulgarian words
- Make sure to check out the original at: https://www.powerlanguage.co.uk/wordle/
