#### TODO:

## I hope first release will be in May (ABN ver. 1.0)

If you think you can help me with bellow issues - do not hesitate and write me please :)
If you think I could do something better let's discuss it :)
If you read this sentence... um...  I'm happy about it.

##### Engennering issues:
    1) Add tests (Python), (done)
    2) Static code analysing,
    3) Decumentation generating (Sphinx or something like that - Doxygen),
    4) Reverse engennering doing to check time and memmory occupancy. Generate raport if it will be satisfying, otherwise look at Feature issues (2),
    5) Release 0.1 version past all issues done,
    6) Fix make scripts (fix an output of 'make clean'- Now there is only make[1] entering and escaping), (done)
    7) Rename functions etc.,
    8) Split tests for suits (done),
    9) Refactoring of code and tests (++i instead i++)

##### Feature issues:
    1) Add to libabn
        void abn_adu(abn_t* result, abn_unit value) (addunit) (done)
        void abn_subunit(abn_t* result, abn_unit value)
        void abn_mulunit(abn_t* result, abn_unit value)
        void abn_smulunit(abn_t* result, abn_unit value)
    2) Add assembly support for few architectures (x86, x64, ARM, maybe more) for few functions (for those what time or memory occupation aren't satisfying for me.) (?), (for ver 2.0)
    3) Add Arduino support (maybe one-file-library?)
    4) Add complition codes
    5) Add create_from_string() function 
    6) Change create function. (Argument should be an amoud of bits - not a volume)
    7) Add define file for mnemonics