#include <ConfigureVariant.h>

namespace xc{

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================

    configure_variant_buffer::configure_variant_buffer() :_capacity(8){
        _buf = new char[_capacity];
        memset(_buf, 0, _capacity);
        _wpos = 0;
        _rpos = 0;
        _size = 0;
    }

    configure_variant_buffer::configure_variant_buffer(const configure_variant_buffer& cvb){
        _buf = new char[cvb._size];
        memcpy(_buf, cvb._buf, cvb._size);
        _wpos = cvb._wpos;
        _rpos = cvb._rpos;
        _size = cvb._size;
        _capacity = cvb._capacity;
    }

    configure_variant_buffer& configure_variant_buffer::operator=(const configure_variant_buffer& cvb){
        clear();
        _buf = new char[cvb._size];
        memcpy(_buf, cvb._buf, cvb._size);
        _wpos = cvb._wpos;
        _rpos = cvb._rpos;
        _size = cvb._size;
        _capacity = cvb._capacity;
        return *this;
    }

    configure_variant_buffer::configure_variant_buffer(const char* addr, size_t size){
        _wpos = 0;
        _rpos = 0;
        _size = size;
        _capacity = size_t(log2(size)) + 1;
        _buf = new char[_capacity];
        memcpy(_buf, addr, size);
    }

    configure_variant_buffer::~configure_variant_buffer(){
        delete[]_buf;
        _buf = NULL;
    }

    size_t configure_variant_buffer::size()const{
        return _size;
    }

    size_t configure_variant_buffer::append_data(const char* data, size_t size){
        size_t newcapacity = _capacity;
        while (newcapacity < _size + size){
            newcapacity *= 2;
        }
        if (_capacity == newcapacity){
            memcpy(_buf + size, data, size);
        }
        else{
            _capacity = newcapacity;
            char* newbuf = new char[_capacity];
            memcpy(newbuf, _buf, _size);
            memcpy(newbuf + _size, data, size);
            delete[]_buf;
            _buf = newbuf;
        }
        _size += size;
        _wpos = _size;
        return _wpos;
    }

    size_t configure_variant_buffer::append_char(char c, size_t size){
        size_t newcapacity = _capacity;
        while (newcapacity < _size + size){
            newcapacity *= 2;
        }
        char* buf = new char[size];
        memset(buf, c, size);
        if (_capacity == newcapacity){
            memcpy(_buf + size, buf, size);
        }
        else{
            _capacity = newcapacity;
            char* newbuf = new char[_capacity];
            memcpy(newbuf, _buf, _size);
            memcpy(newbuf + _size, buf, size);
            delete[]_buf;
            _buf = newbuf;
        }
        delete[]buf;
        buf = NULL;
        _size += size;
        _wpos = _size;
        return _wpos;
    }

    size_t configure_variant_buffer::wseek(size_t pos){
        return _wpos = pos;
    }

    size_t configure_variant_buffer::rseek(size_t pos){
        return _rpos = pos;
    }

    size_t configure_variant_buffer::write(const char* data, size_t size){
        size_t newcapacity = _capacity;
        while (newcapacity < _wpos + size){
            newcapacity *= 2;
        }
        if (_capacity == newcapacity){
            memcpy(_buf + _wpos, data, size);
        }
        else{
            _capacity = newcapacity;
            char* buf = new char[_capacity];
            memcpy(buf, _buf, _wpos);
            memcpy(buf + _wpos, data, size);
            delete[]_buf;
            _buf = buf;
            buf = NULL;
        }
        _size = (_wpos + size)>_size ? (_wpos + size) : _size;
        _wpos = _wpos + size;
        return _wpos;
    }

    size_t configure_variant_buffer::write(size_t pos, const char* data, size_t size){
        wseek(pos);
        return write(data, size);
    }

    size_t configure_variant_buffer::insert(const char* data, size_t size){
        size_t newcapacity = _capacity;
        while (newcapacity < _size + size){
            newcapacity *= 2;
        }
        if (newcapacity == _capacity){
            memcpy(_buf + _wpos + size, _buf + _wpos, _size - _wpos);
            memcpy(_buf + _wpos, data, size);
        }
        else{
            _capacity = newcapacity;
            char* buf = new char[_capacity];
            memcpy(buf, _buf, _wpos);
            memcpy(buf + _wpos, data, size);
            memcpy(buf + _wpos + size, _buf + _wpos, _size - _wpos);
            delete[]_buf;
            _buf = buf;
            buf = NULL;
        }
        _size += size;
        _wpos += size;
        return _wpos;
    }

    size_t configure_variant_buffer::insert(size_t pos, const char* data, size_t size){
        wseek(pos);
        return insert(data, size);
    }

    size_t configure_variant_buffer::wpos()const{
        return _wpos;
    }

    size_t configure_variant_buffer::rpos()const{
        return _rpos;
    }

    size_t configure_variant_buffer::read(char* data, size_t length, size_t* size){
        size_t real_size = (_rpos + length) > _size ? (_size - _rpos) : length;
        memcpy(data, _buf + _rpos, real_size);
        if (NULL != size){
            *size = real_size;
        }
        return _rpos += real_size;
    }

    size_t configure_variant_buffer::read(size_t pos, char* data, size_t length, size_t* size){
        rseek(pos);
        return read(data, length, size);
    }

    bool configure_variant_buffer::isempty(){
        return _size == 0;
    }

    void configure_variant_buffer::shrink(){
        if (_capacity > _size){
            char* buf = new char[_size];
            memcpy(buf, _buf, _size);
            _capacity = _size;
            delete[]_buf;
            _buf = buf;
            buf = NULL;
        }
    }

    void configure_variant_buffer::clear(){
        delete[]_buf;
        _capacity = 8;
        _buf = new char[_capacity];
        memset(_buf, 0, _capacity);
        _size = 0;
        _wpos = 0;
        _rpos = 0;
    }

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================

    configure_variant_stream::configure_variant_stream(){
        _buffer = NULL;
    }

    configure_variant_stream::configure_variant_stream(configure_variant_buffer* cvb){
        _buffer = cvb;
    }

    configure_variant_stream::configure_variant_stream(const configure_variant_stream& cvs){
        _buffer = cvs._buffer;
    }

    configure_variant_stream::~configure_variant_stream(){
        _buffer = NULL;
    }

    void configure_variant_stream::attach_buffer(configure_variant_buffer* cvb){
        _buffer = cvb;
    }

    configure_variant_stream& configure_variant_stream::operator<<(int value){
        typedef union _int_convertor{
            int value;
            char data[sizeof(int)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(int));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(long value){
        typedef union _int_convertor{
            long value;
            char data[sizeof(long)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(long));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(float value){
        typedef union _int_convertor{
            float value;
            char data[sizeof(float)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(float));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(double value){
        typedef union _int_convertor{
            double value;
            char data[sizeof(double)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(double));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(bool value){
        char c = value ? '\0' : '\1';
        _buffer->append_data(&c, sizeof(bool));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(const std::string& value){
        _buffer->append_data(value.data(), value.size());
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(int& value){
        char data[sizeof(int)];
        _buffer->read(data, sizeof(int));
        typedef union _int_convertor{
            char data[sizeof(int)];
            int value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(int));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(long& value){
        char data[sizeof(long)];
        _buffer->read(data, sizeof(long));
        typedef union _int_convertor{
            char data[sizeof(long)];
            long value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(long));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(float& value){
        char data[sizeof(float)];
        _buffer->read(data, sizeof(float));
        typedef union _int_convertor{
            char data[sizeof(float)];
            float value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(float));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(double& value){
        char data[sizeof(double)];
        _buffer->read(data, sizeof(double));
        typedef union _int_convertor{
            char data[sizeof(double)];
            float value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(double));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(bool& value){
        char c;
        _buffer->read(&c, 1);
        value = c == '\0' ? false : true;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(std::string& value){
        size_t length = _buffer->size() - _buffer->rpos();
        char* data = new char[_buffer->size() - _buffer->rpos()];
        _buffer->read(data, length);
        value.assign(data);
        delete[]data;
        data = NULL;
        return *this;
    }

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================


    configure_variant::configure_variant(){
        _type = TYPE_UNKNOWN;
    }

    configure_variant::configure_variant(const configure_variant& cv){
        _buffer = cv._buffer;
        _type = cv._type;
    }

    configure_variant& configure_variant::operator=(const configure_variant& cv){
        _buffer = cv._buffer;
        _type = cv._type;
        return *this;
    }

    configure_variant::configure_variant(int value){
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(long value){
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(bool value){
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(double value){
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(float value){
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(const std::string& value){
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::~configure_variant(){

    }

    configure_variant& configure_variant::operator=(int value){
        _buffer.clear();
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(long value){
        _buffer.clear();
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(float value){
        _buffer.clear();
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(double value){
        _buffer.clear();
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(bool value){
        _buffer.clear();
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(const std::string& value){
        _buffer.clear();
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant::operator bool(){
        bool result;
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator int(){
        int result;
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator long(){
        long result;
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator float(){
        float result;
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator double(){
        double result;
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator std::string(){
        std::string result;
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

}