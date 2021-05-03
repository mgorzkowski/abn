# ABN

ABN - Arbitrary-Bit Number. This library allows simple mathematical operations like addition, multiplication, bit operations on big natural numbers. It's not a standard implementation of big number - numbers are not expansible, which mins that you have to define size first (eg. 256, 4096 or 4294967296 bit). This size cannot be changed in runtime.

ABN library is designed with multiplatform in mind. ABN library can be used with architectures like: x86, ARM (STM32, Raspberry Pi), AVR (Arduino) and more.

Proven architectures:
- x86
- x64
- AArch64 (64bit ARM)
- ARM

## How to use?

### Get abn library:
>git clone https://github.com/mgorzkowski/abn.git
>cd ./abn   

### Prepare environment variables:
>source ./env.sh

### Use ready to use container with prepared software (optional):
> docker_it.sh launch  
> docker_it.sh shell

### Building library:
>mkdir -p build & cd build  
>cmake -GNinja ..  
>ninja

Now, in 'build' directory you can find both libraries:
- libabn-static.a
- libabn-shared.so

You can use different dictionary but please use 'build' directory because this name is required by test runner.

## Example project:
In the 'example' directory there is a 'sample' example of ABN usage. This is a series of some operations.  
To build and run example project type:
>cd examples/sample
>setup.sh
>mkdir -p build && cd build
>cmake -GNinja ..
>ninja

## How to adjust abn library to your project
The ABN library works on abn_unit, which is the basic type the calculations are porformed on.
The abn_unit has ABN_UNIT_BITSIZE size (8, 16, 32, 64, 128 or 256). By default it is set to 32.
To change it modify the ABN_UNIT_BITSIZE definition.

The bigger size theoretically gives the shortest execution time.

## Extra header files limitations:
Some functions cannot be used on some platforms without porting some another functions. Examples of such functions may be file operations. On standard OS (like Windows or Linux) it works and doesn't require additional work. Look at src/extra/README.md

#### Have fun!
If you have noticed something inappropriate or something what can be improved please let me know.   :mailbox: dhmaciek@gmail.com
