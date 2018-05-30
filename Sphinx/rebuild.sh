rm -rf continuous.o
rm -rf pocketsphinx_continuous
gcc -DHAVE_CONFIG_H -I./include   -I./base_include -I./base_include/sphinxbase -I./include -I./libpocketsphinx -I./include -g -O2 -Wall -c -o continuous.o continuous.c
/bin/sh ./libtool  --tag=CC   --mode=link gcc -I./include -I./libpocketsphinx -I./include -g -O2 -Wall -L./libsphinxad -L./libsphinxbase -o pocketsphinx_continuous continuous.o ./libpocketsphinx.la -lsphinxad -lsphinxbase