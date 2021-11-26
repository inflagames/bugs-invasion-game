# Bugs Invasion

Game to participate in the GameOff2021 contest.

This game is motivated by the movie "Love & Monsters". In an apocalyptic world dominated by giant insect, the user need to fight the monsters and survive as mush as possible.

[*Description of tanks used in the game*](./blender-projects/TANKS_DOCUMENTATION.md)

**Todo list**
- [x] Add movement to the tank (go forward/backward and rotate)
  - [ ] Integrate animations with app
  - [ ] Integrate mouse with tank cannon
    - [ ] Create a new cursor for the mouse
  - [ ] Create and integrate Bug (spider) to the game
    - [ ] Add animation to the spider
    - [ ] Automatic generation of bugs
  - [ ] Work in the textures
    - [ ] tank
    - [ ] terrain
    - [ ] spider
  - [ ] Create start menu
  - [ ] Add score to the game
  - [ ] Add collisions to the map

## Setup OGRE locally (UBUNTU)

Using the following script, the ogre project is automatically cloned, and installed in the target system.

```
./scripts/setup-ogre.sh
```

## Build project (UBUNTU)

```
./scripts/build.sh
```

**Build project inside docker**

```
docker run -it -v /home/guille/CLionProjects/template:/app ggjnez92/ogre-ubuntu21:13.1.1 bash -c "cd /app && ./scripts/build.sh"
```

## Start project

```
./build/template
```

> NOTE: First the build should be executed

## Project structure

```
|-- bin
|   |-- game
|       |-- assets              (app assets, textures, images, etc...)
|       |-- inc                 (app private headers)
|       |-- src                 (app sources)
|       |-- resources.cfg       (resources config file)
|       |-- main.cpp            (app main file)
|-- blender-projects            (blender 3d model projects)
|   |-- bluprints               (3d models blueprints)
|   |-- TANKS_DOCUMENTATION.md  (tanks documentation)
|-- doc                         (project documentation)
|-- include                     (public headers)
|-- lib                         (external libraries)
|-- scripts                     (helper scripts)
```

## License

[Apache 2.0](./LICENSE.md)

# Contributions

All contributions are welcome.
