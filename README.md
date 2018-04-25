## ABN
This library allows simple mathematical operations on big natural numbers like addition, multiplication, bit operations etc.

### How to use?
##### Compiling library:
First of all you need the compiled library.
>git clone https://github.com/mgorzkowski/abn.git  
cd ./abn  
make

Now, you can find the libabn.a file in the output directory. This is library that contains all necessary functions.

##### Using with own project:
If you have program.c source file using abn library, compile it with libabn.a library
>gcc program.c -I<_path/to/the/headers/_> -L<_path/to/the/directory/containing/libabn.a/_> -labn -o program

Have fun!
