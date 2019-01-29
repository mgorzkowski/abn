# ABN

ABN - Arbitrary-Bit Number. This library allows simple mathematical operations (like addition, multiplication, bit operations etc) on big natural numbers. ABN library is designed with multiplatform in mind. ABN library can be used with architectures like: x86, ARM, AVR (Arduino) and more. (not been proven yet)

# Warning! this library works but it is under development

## How to use?

### Building library:
First of all, you need the build your instance of ABN library. It's static linked library (libabn.a)
>git clone https://github.com/mgorzkowski/abn.git  
>cd ./abn  
>make

Now, in the 'bin/' directory you can find the libabn.a file that contains all necessary functions.

### Example project:
In the 'example' directory there is a 'simple_c_example' example of ABN usage. This is a series of various operations. Firstly, make sure that your ABN library are built, which means 'libabn.a' file exists in 'bin/libabn.a' - see 'Building library' paragraph. To build and run example project type:
>cd examples/simple_c_example  
>make run

### Using ABN with own project:
If you already have project that can use ABN library compile source files with libabn.a library in this way:
>gcc program.c -I<_path/to/the/directory/containing/headers/_> -L<_path/to/the/directory/containing/libabn.a/_> -labn -o program

## Additional informations:

### How to make ABN library useful in your embedded project?
All you should to do is compile library with proper abn_unit and abn_halfunit type. They're defined in include/abn.h. Abn_unit type should be defined as the widest integer type your compiler knows and abn_halfunit should be defined as two times smaller
e.g.
>typedef uint32_t abn_unit;  
>typedef uint16_t abn_halfunit;

The widest type, the shortest execution time. :)

### Non portable header file:
ABN library contains non-portable functions also. (abn/nonportable.h) Functions from this header file are unnecessary to perform calculations. Non-portable header file contains functions that are specific only for part of systems (e.g. they allows file operations). This can help you read or write your number to the file. You can use non-portable header file functions when you use system that supports standard I/O. This kind of functions are used in example/simple too.

#### Have fun! :smile:
If you have noticed something inappropriate or something what I can improve please send to me a message. :mailbox: dhmaciek@gmail.com
