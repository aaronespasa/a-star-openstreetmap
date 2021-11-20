<p align="center">
  <img width=200px src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b0/Openstreetmap_logo.svg/1200px-Openstreetmap_logo.svg.png">
</p>

<h1 align="center">Real-word route planning using C++ and OpenStreetMap </h1>

## Zurich Example

Let's assume that you have arrived in Zurich because you have to do an intership on Google (a hypothetical case, of course).

You have been eating in the center of Zurich, but you still don't know how to get to Google. Like any other person, you could open Google maps and search for it. However, you know a more interesting way to do it:

You declare that Google is at the coordinates (20, 35) of your map and you go from (200, 60). And, simply using a map that you downloaded from [OpenStreetMap](https://www.openstreetmap.org/search?query=zurich#map=15/47.3744/8.5435), you get to Google thanks to this A* search algorithm:

![Zurich Example of A* Search Algorithm](https://github.com/aaronespasa/a-star-openstreetmap/blob/main/images/zurich-a-search.png)

## Getting Started

> **I encourage you to use Ubuntu and it's crucial to follow the next steps as install the IO2D package can throw many errors!**

If you have a MacBook (ARM or x86), I recommend you to use an Ubuntu Virtual Machine (for example, by using [Parallels](https://www.parallels.com/en/)). I'm using an M1 Macbook Air with an Ubuntu VM and it works without any issue.

### 1. Clone the repository
Don't forget to use the flag `--recurse-submodules`. It'll allow you to install the necessary modules (you can view them in the file .gitmodules).

Using HTTPS:
```bash
git clone https://github.com/aaronespasa/a-star-openstreetmap.git --recurse-submodules
```
Or using SSH:
```bash
git clone git@github.com:aaronespasa/a-star-openstreetmap.git --recurse-submodules
```

And get into it: `cd a-star-openstreetmap`.

### 2. Install the IO2D package
Install all the necessary dependencies:

```bash
>>> sudo apt update
>>> sudo apt install build-essential
>>> sudo apt install cmake
>>> sudo apt install libcairo2-dev
>>> sudo apt install libgraphicsmagick1-dev
>>> sudo apt install libpng-dev
```

All the modules are install inside the folder `thirdparty/`, so go to that directory `cd thirdparty/`.

Clone the IO2D package:
```bash
>>> git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
>>> cd P0267_RefImpl
```

Create a folder called `Debug/` and install the IO2D package there using CMake:
```bash
>>> mkdir Debug && cd Debug
>>> cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
>>> cmake --build .
>>> sudo make install
```

### 3. Build the project

Go to the main folder `a-star-openstreetmap/` (be careful not to be in the folder `thirdparty/`).

Then, create the `build` directory and run `cmake` and `make`:

```bash
>>> mkdir build && cd build
>>> cmake ..
>>> make
```

You're all set! 🎉

## Run the program

Once you're in the `build/` directory, execute the following command:

```bash
>>> ./OSM_A_star_search
```

And to specify your own map file:

```bash
>>> ./OSM_A_star_search -f ../<your_osm_file.osm>
```

=======
```

All the modules are install inside the folder `thirdparty/`, so go to that directory `cd thirdparty/`.

Clone the IO2D package:
```bash
>>> git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
>>> cd P0267_RefImpl
```

Create a folder called `Debug/` and install the IO2D package there using CMake:
```bash
>>> mkdir Debug && cd Debug
>>> cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
>>> cmake --build .
>>> sudo make install
```

### 3. Build the project

Go to the main folder `a-star-openstreetmap/` (be careful not to be in the folder `thirdparty/`).

Then, create the `build` directory and run `cmake` and `make`:

```bash
>>> mkdir build && cd build
>>> cmake ..
>>> make
```

You're all set! 🎉

## Run the program

Once you're in the `build/` directory, execute the following command:

```bash
>>> ./OSM_A_star_search
```

And to specify your own map file:

```bash
>>> ./OSM_A_star_search -f ../<your_osm_file.osm>
```

The base files were provided by Udacity but all the A-Star implementation were made by my own.

## Made with ❤️ and ☕️ by Aarón

