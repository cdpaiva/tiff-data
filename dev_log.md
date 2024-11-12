# Tiff Info

### Dev log

The idea of this project is to create a CLI tool that will inspect a TIFF file and print its metadata.
It's mostly an excuse to write some C code in a project of my own, but it can be useful to quickly inspect TIFF files.

### Goals

[x] Open a tiff file and inspect the image file header.

* Image File Header content:

Bytes 0-1: Byte order

"II" (Intel): little-endian
"MM" (Motorola): big endian

* Obs: I'm not really sure about how to handle opened files. 

At the moment, I am saving the fptr position with `ftell`, then I move the pointer to access the bytes I want. Before returning from the function I fseek() it back to the point it was before.
The only reason for this is to maintain the previous position in case some other function eventually relies on that.

Bytes 2-3: Magic number

For tiff files it's 42 (order given by endianess).
This means that if the image is "II", the magic number will be 42 00.
For "MM", it would be 00 42.

Bytes 4-7: Offset

Location of the first Image File Directory (IFD).
The offset is given in bytes from the beginning of the file.

[x] Functions to interpret the tiff header: 

get_offset

**My computer uses little-endian byte order, so at the moment I will write everything considering LE by default.**
Images in BE will be flipped to LE, to then be processed.
The conversion between BE and LE is pretty neat: for 16 bit values we flip the two bytes, and for 32 bits we mirror the values, by combining the bit shifts with corresponding & operations.

[x] Add unity for unit tests

Makefile for unity adapted from: https://www.throwtheswitch.org/build/make

-> It was actually a mix of different makefiles, which did not make sense in the end.

[x] Start processing IFDs

An IFD consists of a 2-byte count of the number of directory entries (number of fields).
After the number of directories, each entry is represented as 12-bytes, followed by an offset of 4 bytes or zero (last IFD needs to have a 4-byte offset).

[x] Print the number of IFDs

[x] Print all IFD entries as sequences of 12 bytes
[x] Print the number of entries in the first IFD

[x] Print the IFD tag names
[x] Print the IFD values that are outside the IFD range (offsets)
    [x] Read ASCII values
    [x] Read rational values

After reading the code again, I realized that most of what the code was doing is:
1. Read some amount of bytes, for example read 4 bytes after a 4 byte offset to get the IFD address
2. Parse the bytes as a different numeric type, ie uint32 or uint16, taking in account the byte order (LE or BE)
3. Use that value to something

Steps 1 and 2 were refactored to the function `read_chunks`.
