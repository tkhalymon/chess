# Chess

Working chess board game simulator. Game is for 2 players.<br />Now it hasn't got a computer player, but I'm working at this.
Also, it has some bugs. And actualy, it isn't finished yet.

# How to build project (Ubuntu 14.04)

Launch `bash install_dev_env.sh` to install nescessary libraries.

Use `cmake .` to generate Makefile in the root directory of project. Note that default Makefile will be owerwritten which is know issue (need to fix some configs).

Then use `make` to build project and `./chess` to run it
