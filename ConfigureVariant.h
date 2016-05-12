#ifndef XML_CONFIGURE_VARIANT_HH
#define XML_CONFIGURE_VARIANT_HH

#include <Export.h>
#include <string>
#include <vector>
#include <sstream>
namespace xc{

    /**
     *
     */
    class configure_variant_buffer{

    public:
        /**
         *
         */
        configure_variant_buffer();

        /**
         *
         */
        configure_variant_buffer(const configure_variant_buffer& cvb);

        /**
         *
         */
        configure_variant_buffer& operator=(const configure_variant_buffer& cvb);

        /**
         *
         */
        configure_variant_buffer(const char* addr, size_t size);

        ~configure_variant_buffer();

    public:

        /**
         *
         */
        size_t size()const;

        /**
         *
         */
        size_t append_data(const char* data, size_t size);

        /**
         *
         */
        size_t append_char(char c, size_t size);

        /**
         *
         */
        size_t wseek(size_t pos);

        /**
         *
         */
        size_t rseek(size_t pos);

        /**
         *
         */
        size_t write(const char* data, size_t size);

        /**
         *
         */
        size_t write(size_t pos, const char* data, size_t size);

        /**
         *
         */
        size_t insert(const char* data, size_t size);

        /**
         *
         */
        size_t insert(size_t pos, const char* data, size_t size);

        /**
         *
         */
        size_t wpos()const;

        /**
         *
         */
        size_t rpos()const;

        /**
         *
         */
        size_t read(char*data, size_t length, size_t* size = NULL);

        /**
         *
         */
        size_t read(size_t pos, char* data, size_t length, size_t* size = NULL);

        /**
         *
         */
        size_t capacity()const;

        /**
         *
         */
        bool isempty();

        /**
         *
         */
        void shrink();

        /**
         *
         */
        void clear();

        /**
         *
         */
    protected:

        /**
         *
         */
        size_t _capacity;

        /**
         *
         */
        size_t _wpos;

        /**
         *
         */
        size_t _rpos;

        /**
         *
         */
        char* _buf;

        /**
         *
         */
        size_t _size;


    };

    /**
     *
     */
    class configure_variant_stream{

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant_stream();

        /**
         *
         */
        configure_variant_stream(configure_variant_buffer* cvb);

        /**
         *
         */
        configure_variant_stream(const configure_variant_stream& cvs);

        /**
         *
         */
        ~configure_variant_stream();
    public:
        /**
         *
         */

        void attach_buffer(configure_variant_buffer* cvb);
        /**
         *
         */

    public:
        /**
         *
         */

        configure_variant_stream& operator<<(int value);

        /**
         *
         */
        configure_variant_stream& operator<<(long value);

        /**
         *
         */
        configure_variant_stream& operator<<(float value);

        /**
         *
         */
        configure_variant_stream& operator<<(double value);

        /**
         *
         */
        configure_variant_stream& operator<<(bool value);

        /**
         *
         */
        configure_variant_stream& operator<<(const std::string& value);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant_stream& operator>>(int& value);

        /**
         *
         */
        configure_variant_stream& operator>>(long& value);

        /**
         *
         */
        configure_variant_stream& operator>>(float& value);

        /**
         *
         */
        configure_variant_stream& operator>>(double& value);

        /**
         *
         */
        configure_variant_stream& operator>>(bool& value);

        /**
         *
         */
        configure_variant_stream& operator>>(std::string& value);

        /**
         *
         */
    protected:

        /**
         *
         */
        configure_variant_buffer* _buffer;


    };

    /**
     *
     */
    class configure_variant{

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant();

        /**
         *
         */
        configure_variant(const configure_variant& cv);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant(int value);

        /**
         *
         */
        configure_variant(long value);

        /**
         *
         */
        configure_variant(bool value);

        /**
         *
         */
        configure_variant(double value);

        /**
         *
         */
        configure_variant(float value);

        /**
         *
         */
        configure_variant(const std::string& value);

        /**
         *
         */
    public:

        /**
         *
         */
        ~configure_variant();

        /**
         *
         */
    public:

        /**
         *
         */
        enum VAR_TYPE{
            TYPE_INT,
            TYPE_LONG,
            TYPE_BOOL,
            TYPE_DOUBLE,
            TYPE_FLOAT,
            TYPE_STRING,
            TYPE_UNKNOWN
        };

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant& operator=(const configure_variant& cv);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant& operator=(int value);

        /**
         *
         */
        configure_variant& operator=(long value);

        /**
         *
         */
        configure_variant& operator=(float value);

        /**
         *
         */
        configure_variant& operator=(double value);

        /**
         *
         */
        configure_variant& operator=(bool value);

        /**
         *
         */
        configure_variant& operator=(const std::string& value);

        /**
         *
         */
        operator int();

        /**
         *
         */
        operator long();

        /**
         *
         */
        operator float();

        /**
         *
         */
        operator double();

        /**
         *
         */
        operator bool();

        /**
         *
         */
        operator std::string();

        /**
         *
         */
    public:

        /**
         *
         */
        VAR_TYPE type()const;

        /**
         *
         */
    public:

        /**
         *
         */
        template<typename T>
        T value(){
            T t;
            t = *this;
            return t;
        }

        /**
         *
         */
        std::string to_string()const;

    protected:

        configure_variant_buffer _buffer;

        VAR_TYPE    _type;

    };
}

#endif//XML_CONFIGURE_VARIANT_HH
