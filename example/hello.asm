section .text
    _start:
        ; Get a value into al.
        push 0x10
        pop al

        ; We can use the stack to copy values.
        ; For example, to copy al into bl:
        push al
        pop bl

        ; However, `mov` is typically preferable, and faster.
        ; Let's copy bl into cl:
        mov cl, bl