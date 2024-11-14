## TIFF DATA

A CLI tool to inspect a TIFF file and print its metadata.

The current version reads the Image File Header and all entries from the first Image File Directory (IFD).
The data is read as bytes and printed in the format described below.
Importantly, the image content is never read, to save memory and time.
Expects TIFF images that follow the TIFF 6.0 specification.
Images can be encoded in Big Endian or Little Endian order.

Every IFD entry is printed as:

> Tag_name (tag identifier) field_type Count Value

Example output:

```console
~$: build/tiff_data images/tire.tif
Image byte order: Little Endian
File has valid magic number (42)
IFD offset: b932.
File has 13 IFDs:
ImageWidth (256) SHORT 1 232
ImageLength (257) SHORT 1 205
BitsPerSample (258) SHORT 1 8
Compression (259) SHORT 1 32773
PhotometricInterpretation (262) SHORT 1 1
StripOffsets (273) LONG 6
Orientation (274) SHORT 1 1
SamplesPerPixel (277) SHORT 1 1
RowsPerStrip (278) SHORT 1 35
StripByteCounts (279) LONG 6
XResolution (282) RATIONAL 1 72.00
YResolution (283) RATIONAL 1 72.00
PlanarConfiguration (284) SHORT 1 1
```

Running the tests will require the Unity testing framework (I've used v 2.6.0).
Download or clone it and add to a `unity` folder under the project root.

### Project Structure

```
tiff-data
├──src: Source files.
├──test: Test files.
├──unity: Unity framework (v2.6.0) files used for unit testing.
├── build: Compiled executable and object files.
    
```

Makefile Commands

1. Building the Executable

To compile the main executable:

```
make build
```

This creates an executable called tiff_data in the build directory.

2. Running Tests

To compile and run the unit tests:

```
make test
```

This creates a test executable called test_runner in the build directory and then runs it to output the results of the unit tests.

3. Cleaning Up

To remove all compiled files and directories:

```
make clean
```

This deletes the build directory and all of its contents.

### Getting Started

Ensure you have `gcc` installed, then clone the repository and navigate to the project directory.
Download `unity` and place it the project root, in a directory named `unity`.
Use the commands above to build the project, run tests, and clean the build environment.
