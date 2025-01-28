#pragma once

#include <vector>
#include <fstream>

namespace m3l::bmp
{
    struct Header
    {
        uint16_t Signature;
        uint32_t FileSize;
        uint32_t Reserved;
        uint32_t DataOffset;
    };

    struct InfoHeader
    {
        uint32_t Size;
        uint32_t Width;
        uint32_t Height;
        uint16_t Plaes;
        uint16_t BPP;
        uint32_t Compression;
        uint32_t ImageSize;
        uint32_t XpxPerM;
        uint32_t YpxPerM;
        uint32_t NbColor;
        uint32_t ImpColor;
    };

    struct ColorTable
    {
        uint8_t RedIntensity;
        uint8_t GreenIntensity;
        uint8_t BlueIntensity;
        uint8_t Reserved;
    };

    /*class File
    {
        public:
            File() = default;
            File(const std::string &_path);
            ~File() = default;

            void load(const std::string &_path);

            Header Header;
            InfoHeader HeaderInfo;
            std::vector<ColorTable> ClrTable;

    };*/
}