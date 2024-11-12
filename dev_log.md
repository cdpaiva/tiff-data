# Tiff Info

### Dev log

* Day 1 (Aug 19)

The idea of this project is to create a CLI tool that will inspect a TIFF file and print its metadata.
Even though I can do this by opening the image somewhere else (like ImageJ), it would be cool to have an easy to use tool that did this right away.
This would also only read the bytes that are relevant to the metadata, in contrast with most tool, that actually read the entire file.
It's also an excuse to write some C code in a project of my own.

### Goals

[x] Open a tiff file and inspect the image file header.

* Image File Header content:

Bytes 0-1: Byte order

"II" (Intel): little-endian
"MM" (Motorola): big endian

* Obs: I'm not really sure about how to handle opened files. 

At the moment, I am saving the fptr previous position, with `ftell`, then I move the pointer to access the bytes I want and before returning from the function I fseek() it back to the point it was before.
The only idea behind this is to maintain the previous position in case some other function eventally relies on that.

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

-> Kind of works, but I use an exercism template, and that does not make sense because the only reason they compile the code is for testing.
In my case, I had to do a few work arounds (exclude main.c in the Makefile when I compile the tests) to make this work.
Surely there are much better solutions than this, I just need to learn how to do it.

Makefile for unity extracted from: https://www.throwtheswitch.org/build/make

-> It was actually a mix of different makefiles, which did not make sense in the end.

[ ] Start processing IFDs

An IFD consists of a 2-byte count of the number of directory entries (number of fields).
After the number of directories, each entry is represented as 12-bytes, followed by an offset of 4 bytes or zero (last IFD needs to have a 4-byte offset).

[x] Print the number of IFDs -> seems to be wrong!

It's not wrong.. during the conversion to BE images some extra tags were created, probably the tool I've used adds those tags to all images.

[x] Print all IFDs as sequences of 12 bytes
[x] Print the number of entries in the first IFD
[x] Jump to the second IFD

[x] Print the IFD tag names
[ ] Print the IFD values that are outside the IFD range (offsets)
    [ ] Read ASCII values
    [ ] Read rational values

After some refactoring, I realised that most of what the code was doing is:
1. Read some amount of bytes, for example read 4 bytes after a 4 byte offset to get the IFD address
2. Parse the bytes as a different numeric type, ie uint32 or uint16, taking in account the byte order (LE or BE)
3. Use that value to something

So I've extracted the read logic and the parsing into separate functions, the code is looking better now.
