/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

__attribute__((always_inline))
inline void scope_dtor(void **label)
{
    if (*label != 0)
        ((void(*)())*label)();
}

__attribute__((always_inline))
inline void going_back(void ***label)
{
    if (**label == 0)
        __asm__("retq");
}

#define scope__exit(line)                                               \
    void *__scope_exit_ ## line ## __ __attribute__((cleanup(scope_dtor))) = 0; \
    for (void **__scope_cleanup_ ## line ## __  __attribute__((cleanup(going_back))) = &__scope_exit_ ## line ## __; \
         __scope_setjmp(&__scope_exit_ ## line ## __) != 42; )

#define scope(name) scope__ ## name(__LINE__)

int __scope_setjmp(void **);
