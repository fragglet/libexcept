
/*

Copyright (C) 2006, Simon Howard 

Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions: 

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software. 

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE. 

*/

/* This is the "limitations" page for the documentation. */

/**
 
@page limits Limitations

Although it is possible to get a fairly functional exceptions framework
using standard ANSI C, there are limitations to the system. This page
documents things that cannot be done with libexcept.

@section breakout Breaking out of an exception block

It is not possible to break out of an exception block using continue,
break, return or goto. libexcept has built-in guards that detect when
this is done. The following example demonstrates illegal usage:

@code
    void illegal(void)
    {
        int i;

        for (i=0; i<10; ++i) {
            except_try {
                /* Illegal: cannot use break to exit out of an exception block */

                break;
            
                /* Illegal: cannot use continue to exit out of an exception block */

                continue;

                /* Illegal: cannot return from within an exception block */

                return;

                /* Illegal: do not use goto to break out of an exception block */

                goto label;
            } except_end

        label:
        }
    }
@endcode

However, the following is legal:

@code
    void legal(void)
    {
        int i;

        except_try {
            for (i=0; i<10; ++i) {
                /* Legal: Can use break to exit a loop within an exception block */

                break;
            
                /* Legal: Can use continue within an exception block */

                continue;

                /* Legal: Can use goto to jump within an exception block */

                goto label;
            }
            label:
        } except_end
    }
@endcode

Note: the same limitations also apply within catch and finally blocks.

@section nested Nested exception blocks

It is not possible to have an exception block within another exception block.
The following is illegal:

@code
    void illegal(void)
    {
        except_try {
            except_try {
                printf("hello, world\n");
            } except_catch (CircleException, e) {
                printf("Circle Exception caught!\n");
            }
        } except_catch (SquareException, e) {
            printf("Square Exception caught!\n");
        }
    }
@endcode

However, the following is legal:

@code
    void legal_2(void)
    {
        except_try {
            printf("hello, world\n");
        } except_catch (CircleException, e) {
            printf("Circle Exception caught!\n");
        }
    }

    void legal_1(void)
    {
        except_try {
            legal_2();
        } except_catch (SquareException, e) {
            printf("Square Exception caught!\n");
        }
    }
@endcode

 */

