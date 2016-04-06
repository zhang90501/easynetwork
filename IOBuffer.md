# Introduction #

**IOBuffer缓冲区:** 提供读写数据的缓冲区功能


# Details #
  * **原理**
IOBuffer维护一个字符数组,提供数据的写入读出. IOBuffer类似于一个管道,从数组(有效数据)开头读数据,读出数据处理成功之后, 重新设置IOBuffer将读出的数据清掉; 从有效数据结尾写入数据,当结尾的空间不够时,可能移动有效数据到数组开头,以腾出更多的空间,如果空间还不够的话, 需要从新分配一块足够的内存空间(直到到了最大的数据大小MAX\_BUFFER\_SIZE,默认值为10M,或者没有内存可分配).

  * **创建IOBuffer**
```
//1. 创建一个指定初始大小的io buffer
IOBuffer io_buffer(512);
IOBuffer *p_io_buffer = &io_buffer;

//2. 创建一个默认大小BUFFER_SIZE(1024)的io buffer
//IOBuffer *p_io_buffer = new IOBuffer();
```

  * **获取读缓冲区**
```
unsigned int size;
const char *buffer = p_io_buffer->read_open(size); //返回可读数据的大小

if(buffer == NULL)
    return NO_DATA;
memcpy(data, buffer, size); //使用数据

p_io_buffer->read_close(size);
```

  * **获取大小为size的写缓冲区**
```
char *buffer = p_io_buffer->write_open(size);

if(buffer == NULL)
    return NO_MEMORY;
memcpy(buffer, data, size); //写入数据

p_io_buffer->write_close(size);  //设置写了多少数据
```

  * **截断尾部size字节的数据**
```
p_io_buffer->truncate(size);
//返回true的话, 数组最后的size大小的内容无效
```

  * **seek有效数据缓冲区(用于更改写入的数据)**
```
//seek到偏移为offset,大小为5的有效数据缓冲区
char* buffer = p_io_buffer->seek(offset,5);
memcpy(buffer, "hello", 5); //写入数据,必须保证写入的数据不超过剩余的空间!!!
```