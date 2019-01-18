#### TODO:
##### Engennering issues: (to May)
    1) Tests adding (CUnit with C or unittest with Python), (done)
    2) Static code analysing,
    3) Decumentation generating (Sphinx or something like that - Doxygen),
    4) Reverse engennering doing to check time and memmory occupancy. Generate raport if it will be satisfying, otherwise look at Feature issues (2),
    5) Release 0.1 version past all issues done,
    6) Fix make scripts (fix an output of 'make clean'- Now there is only make[1] entering and escaping ) (done)

##### Feature issues:
    1) Add to libabn
        void abn_addunit(abn_t* result, abn_unit value)
        void abn_subunit(abn_t* result, abn_unit value)
        void abn_mulunit(abn_t* result, abn_unit value)
        void abn_smulunit(abn_t* result, abn_unit value)
        void abn_divunit(abn_t* result, abn_unit value)
        void abn_modunit(abn_t* result, abn_unit value)
    2) Add to wrapper
        abn.get_volume(_abn_t_p)    
    3) Add assembly support for few architectures (x86, x64, ARM, maybe more) for few functions (for those what time or memory occupation aren't satisfying for me.) (?),