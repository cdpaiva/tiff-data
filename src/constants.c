#include "constants.h"

// All tags names from TIFF 6.0 Specification Appendix A
IFD_Tag tag_names[] = {
    {254, "NewSubfileType"},
    {255, "SubfileType"},
    {256, "ImageWidth"},
    {257, "ImageLength"},
    {258, "BitsPerSample"},
    {259, "Compression"},
    {262, "PhotometricInterpretation"},
    {263, "Threshholding"},
    {264, "CellWidth"},
    {265, "CellLength"},
    {266, "FillOrder"},
    {269, "DocumentName"},
    {270, "ImageDescription"},
    {271, "Make"},
    {272, "Model"},
    {273, "StripOffsets"},
    {274, "Orientation"},
    {277, "SamplesPerPixel"},
    {278, "RowsPerStrip"},
    {279, "StripByteCounts"},
    {280, "MinSampleValue"},
    {281, "MaxSampleValue"},
    {282, "XResolution"},
    {283, "YResolution"},
    {284, "PlanarConfiguration"},
    {285, "PageName"},
    {286, "XPosition"},
    {287, "YPosition"},
    {288, "FreeOffsets"},
    {289, "FreeByteCounts"},
    {290, "GrayResponseUnit"},
    {291, "GrayResponseCurve"},
    {292, "T4Options"},
    {293, "T6Options"},
    {296, "ResolutionUnit"},
    {297, "PageNumber"},
    {301, "TransferFunction"},
    {305, "Software"},
    {306, "DateTime"},
    {315, "Artist"},
    {316, "HostComputer"},
    {317, "Predictor"},
    {318, "WhitePoint"},
    {319, "PrimaryChromaticities"},
    {320, "ColorMap"},
    {321, "HalftoneHints"},
    {322, "TileWidth"},
    {323, "TileLength"},
    {324, "TileOffsets"},
    {325, "TileByteCounts"},
    {332, "InkSet"},
    {333, "InkNames"},
    {334, "NumberOfInks"},
    {336, "DotRange"},
    {337, "TargetPrinter"},
    {338, "ExtraSamples"},
    {339, "SampleFormat"},
    {340, "SMinSampleValue"},
    {341, "SMaxSampleValue"},
    {342, "TransferRange"},
    {512, "JPEGProc"},
    {513, "JPEGInterchangeFormat"},
    {514, "JPEGInterchangeFormatLngth"},
    {515, "JPEGRestartInterval"},
    {517, "JPEGLosslessPredictors"},
    {518, "JPEGPointTransforms"},
    {519, "JPEGQTables"},
    {520, "JPEGDCTables"},
    {521, "JPEGACTables"},
    {529, "YCbCrCoefficients"},
    {530, "YCbCrSubSampling"},
    {531, "YCbCrPositioning"},
    {532, "ReferenceBlackWhite"},
    {33432, "Copyright"},
};

int get_type_byte_count(int type)
{
    int tag_types[5][2] = {{1, 1}, {2, 1}, {3, 2}, {4, 4}, {5, 8}};

    for (int i = 0; i < 5; i++) {\
        if (tag_types[i][0] == type) {
            return tag_types[i][1];
        }
    }
    return -1;
}

char* get_tag_name(int tag)
{
    int size = sizeof(tag_names) / sizeof(tag_names[0]);
    for (int i = 0; i < size; i++) {
        if (tag_names[i].tag_number == tag) {
            return tag_names[i].name;
        }
    }
    return "";
}

char* get_type_name(int type)
{
    if (type < 1 || type > 11) {
        return "";
    }
    char *type_names[11] = {"BYTE", "ASCII", "SHORT", "LONG", "RATIONAL", "SBYTE", "UNDEFINED", "SSHORT", "SRATIONAL", "FLOAT", "DOUBLE"};

    return type_names[type-1];
}
