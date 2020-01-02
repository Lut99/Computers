/* BINARY STREAM.h
*    by Lut99
*
*  Header file for BinaryStream.cpp.
**/

#ifndef BINARYSTREAM_H
#define BINARYSTREAM_H

#include <cstddef>
#include <iostream>

namespace DataTypes {
    struct BinaryString {
        private:
            char deallocate;
        public:
            char *data;
            std::size_t size;

            /* Create an empty BinaryString object. */
            BinaryString(bool deallocate = true);
            ~BinaryString();

            /* Create a BinaryString object by ptr and siz. If desired, the deallocation of the internat char array can be disabled. */
            BinaryString(char *data_string, std::size_t data_size, bool deallocate = true);

            /* Create a BinaryString object by void ptr and size. If desired, the deallocation of the internat char array can be disabled. */
            BinaryString(void *data_string, std::size_t data_size, bool deallocate = true);

            /* Create a BinaryString object by providing a null-terminated char*. If desired, the deallocation of the internat char array can be disabled. */
            BinaryString(char *null_terminated_string, bool deallocate = true);
    };

    class BinaryStream {
        private:
            char *binary_string;
            std::size_t size;
            std::size_t real_size;
            std::size_t init_size;

            /* Appends n characters to the internal array, which is resized automatically. To be dynamic, the actual size is often higher than the contents. */
            void append(const char *data, const std::size_t n);
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

            /* Returns a string representing the contents of the stream */
            std::string to_string();

            /* Declare the necessary << operators as friends. */
            
            /* Appends unsigned chars to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const unsigned char value);
            /* Appends chars to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const char value);
            /* Appends unsigned shorts to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const unsigned short value);
            /* Appends shorts to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const short value);
            /* Appends unsigned integers to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const unsigned int value);
            /* Appends integers to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const int value);
            /* Appends unsigned longs to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const unsigned long value);
            /* Appends longs to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const long value);
            /* Appends a zero-terminated string to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const char *value);
            /* Appends strings to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const std::string value);
            /* Appends BinaryStrings to the stream */
            friend BinaryStream& operator<<(BinaryStream& bs, const BinaryString value);
            /* Appends one binary stream to the other */
            friend BinaryStream& operator<<(BinaryStream& bs, const BinaryStream value);
            /* Appends this binarystream to an ostream */
            friend std::ostream& operator<<(std::ostream& os, const BinaryStream bs);
    };

    BinaryStream& operator<<(BinaryStream& bs, const unsigned char value);
    BinaryStream& operator<<(BinaryStream& bs, const char value);
    BinaryStream& operator<<(BinaryStream& bs, const unsigned short value);
    BinaryStream& operator<<(BinaryStream& bs, const short value);
    BinaryStream& operator<<(BinaryStream& bs, const unsigned int value);
    BinaryStream& operator<<(BinaryStream& bs, const int value);
    BinaryStream& operator<<(BinaryStream& bs, const unsigned long value);
    BinaryStream& operator<<(BinaryStream& bs, const long value);
    BinaryStream& operator<<(BinaryStream& bs, const char *value);
    BinaryStream& operator<<(BinaryStream& bs, const std::string value);
    BinaryStream& operator<<(BinaryStream& bs, const BinaryString value);
    BinaryStream& operator<<(BinaryStream& bs, const BinaryStream value);
    std::ostream& operator<<(std::ostream& os, const BinaryStream bs);
}

#endif