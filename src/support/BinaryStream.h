/* BINARY STREAM.h
*    by Lut99
*
*  Header file for BinaryStream.cpp.
**/

#ifndef BINARYSTREAM_H
#define BINARYSTREAM_H

#include <cstddef>

namespace DataTypes {
    struct BinaryString {
        char *data;
        int size;

        /* Create a BinaryString object by ptr and size. Note: does nothing about allocation or deallocation. */
        BinaryString(char *data_string, int data_size);

        /* Create a BinaryString object by providing a null-terminated char*. Note: does nothing about allocation or deallocation. */
        BinaryString(char *null_terminated_string);
    };

    class BinaryStream {
        private:
            char *binary_string;
            std::size_t size;
            std::size_t real_size;

            /* Appends n characters to the internal array, which is resized automatically. To be dynamic, the actual size is often higher than the contents. */

        public:
            /* The BinaryStream class makes constructing BinaryStreams easier. Simply use the '<<' operator to add various types of data. You can also define such an operator yourself by using '<< BinaryString' to add binary data yourself. */
            BinaryStream(std::size_t initial_size=256);
            ~BinaryStream();
            
            /* Returns a copy of the contents of the BinaryStream. The size of this data is returned, and the data itself copied to given pointer. */
            const std::size_t read(char *result) const;
            /* Flushes the contents of the BinaryStream. The size of this data is returned, and the data itself copied to given pointer. */
            const std::size_t flush(char *result);

            /* Returns the length of the stream right now. */
            const std::size_t length() const;

            /* Clears the internal buffer and resets the stream to have no content. */
            void clear();

            /* Declares the necessary << operators as friends. */
            /* Appends unsigned chars to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const unsigned char& value);
            /* Appends chars to the stream */
            /* Appends unsigned shorts to the stream */
            /* Appends shorts to the stream */
            /* Appends unsigned integers to the stream */
            /* Appends integers to the stream */
            /* Appends unsigned longs to the stream */
            /* Appends longs to the stream */
            /* Appends strings to the stream */
            /* Appends BinaryStrings to the stream */
            /* Allows the binarystream to be appended to an ostream */
    };

    BinaryStream& operator<<(BinaryStream& bs, const unsigned char& value);
}

#endif