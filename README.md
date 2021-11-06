# Bugs Invasion

Game to participate in the GameOff2021 contest.

This game is motivated by the movie "Love & Monsters". In an apocalyptic world dominated by giant insect, the user need to fight the monsters and survive as mush as possible.

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

## License

[Apache 2.0](./LICENSE.md)

# Contributions

All contributions are welcome.
