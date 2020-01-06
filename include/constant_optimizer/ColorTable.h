#pragma once

#include <array>
#include <cstdint>
#include <iostream>

// see https://en.wikipedia.org/wiki/ANSI_escape_code#24-bit
class ColorTable {
public:
    ColorTable(std::array<uint8_t, 3 * 256> rgb)
        : mRgb(rgb) {}

    void bg(std::ostream& os, uint8_t colorIdx) const {
        write(os, 48, colorIdx);
    }

    void fg(std::ostream& os, uint8_t colorIdx) const {
        write(os, 38, colorIdx);
    }

    void ansiColors(std::ostream& os, uint8_t colorIdx) const {
        bg(os, colorIdx);
        fg(os, static_cast<uint8_t>(colorIdx + UINT8_C(127)));
    }

    // set background based on coloridx
private:
    void write(std::ostream& os, int what, uint8_t colorIdx) const {
        auto idx = static_cast<size_t>(colorIdx) * 3;
        os << "\x1b[" << what << ";2;" << static_cast<int>(mRgb[idx]) << ';'
           << static_cast<int>(mRgb[idx + 1]) << ';' << static_cast<int>(mRgb[idx + 2]) << 'm';
    }

    std::array<uint8_t, 3 * 256> mRgb;
};

ColorTable const& colorTableVic();
