The program has been tested on Ubuntu 16.04.

Install SDL library: sudo apt-get install libsdl1.2-dev

To compile the program from source, go into compile/ and use the Makefile.
Execute ./road-generation [-d <Density map>] [-h <Height map>]

If you get a blue background window it is probably because the heightmap
(hmap.png) and the density map (dmap.png) are not in the same folder as the binary.
