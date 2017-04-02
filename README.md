PLS-Compression

Compressor without loss

School project of a compressor without loss. Extensions possibles
How to use it

In order to use the compressor, compile it with the make command on the root path of the project. All the binary files are in the /bin path.

To execute the binary, use ./main.exe. If not working (or an error appears in the huffman compression), try to set the environment variable DEBUG to 0, using export DEBUG=0.

Note that you can also set it to 1 for a debugging without showing the trees, and to 2 in order to only show the trees during the execution.
Another program is the ./test_hf.exe that compresses the file given in argument and decompresses it right away. And finally a program called comp.exe in the /src path allows us to give the compression rate between two files (given in parameter) with the first one being the compresses one.

Warnings

Do not try to compress a file smaller than 18 bytes using test_hf.exe or any huffman compression. That will lead to a segmentation fault. The decompression of a preprocessed file does not work. Compressed binary files do no shrink in size. Do not try to preprocess a file with RLE if they are more than 9 repetitions of a char.

About

We made this projet through a scholaristical programming week. We had, by group of 4 or 5, to produce a program at least able to compress and decompress files following the huffman encoding. Our workgroup was composed by

Abonnenc Alicia
Bonhoure Gilles
Fu Cecile
Siest Damien
Vegreville Thibaut
