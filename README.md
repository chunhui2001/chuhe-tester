# chuhe-tester


## Install Ulfius
#$ sudo apt install libulfius-dev
$ sudo apt-get install libmicrohttpd-dev libjansson-dev libcurl4-gnutls-dev libgnutls28-dev libgcrypt20-dev

$ git clone https://github.com/babelouest/ulfius.git
$ cd ulfius/
$ git submodule update --init
$ cd lib/orcania
$ make && sudo make install
$ cd ../yder
$ make && sudo make install
$ cd ../..
$ make
$ sudo make install


## Install cJSON
$ cd /tmp/ && git clone https://github.com/DaveGamble/cJSON.git
$ cd cJSON/
$ mkdir build
$ cd build/
$ cmake ../
$ make install
$ sudo make install