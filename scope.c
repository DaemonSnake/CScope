int __scope_setjmp(void **label)
{
    *label = (*label == 0 ? __builtin_return_address(0) : 0);
    return 42;
}
