#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio> // FILE, fwrite
#include <vector>

// Buffered write of uint64_t data to FILE stream (e.g. stdout/stderr)
class BufferedWriter {
public:
    BufferedWriter(size_t bufferSize, FILE* fout)
        : mData(bufferSize)
        , mFout(fout) {}

    // neither copy nor movable
    BufferedWriter(BufferedWriter const&) = delete;
    BufferedWriter& operator=(BufferedWriter const&) = delete;

    void operator()(uint64_t val) {
        mData[mIdx++] = val;
        if (mIdx == mData.size()) {
            mIdx = 0;
            fwrite(mData.data(), sizeof(uint64_t), mData.size(), mFout);
        }
    }

    void flush() {
        if (mIdx == 0) {
            return;
        }
        fwrite(mData.data(), sizeof(uint64_t), mIdx, mFout);
        mIdx = 0;
    }

    ~BufferedWriter() {
        flush();
    }

private:
    std::vector<uint64_t> mData{};
    size_t mIdx = 0;
    FILE* mFout = nullptr;
};