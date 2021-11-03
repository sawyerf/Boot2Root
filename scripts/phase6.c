void* esi
void* var_58 = esi
void list
read_six_numbers(arg1, &list)
int32_t edi = 0
do
    if (*(&list + (edi << 2)) - 1 u> 5)
        explode_bomb()
        noreturn
    int32_t ebx_1 = edi + 1
    if (ebx_1 s<= 5)
        int32_t eax_3 = edi << 2
        do
            if (*(eax_3 + &list) == *(&list + (ebx_1 << 2)))
                explode_bomb()
                noreturn
            ebx_1 = ebx_1 + 1
        while (ebx_1 s<= 5)
    edi = edi + 1
while (edi s<= 5)



int32_t y_1 = 0
int32_t* c2node1
do
    void* cnode1 = &node1
    int32_t i_1 = 1
    int32_t yy_1 = y_1 << 2
    if (1 s< *(yy_1 + &list))
        int32_t list_1 = *(yy_1 + &list)
        cnode1 = &node1
        do
            cnode1 = *(cnode1 + 8)
            i_1 = i_1 + 1
        while (i_1 s< list_1)
    c2node1[y_1] = cnode1
    y_1 = y_1 + 1
while (y_1 s<= 5)



int32_t* c3node1 = c2node1
int32_t* c4node1 = c3node1
int32_t i_2 = 1
do
    int32_t* c5node1 = (&c2node1)[i_2]
    c3node1[2] = c5node1
    c3node1 = c5node1
    i_2 = i_2 + 1
while (i_2 s<= 5)



c3node1[2] = 0
int32_t i_3 = 0
int32_t* c6node1 = c4node1
int32_t c7node1
do
    c7node1 = *c6node1
    if (c7node1 s< *c6node1[2])
        explode_bomb()
        noreturn
    c6node1 = c6node1[2]
    i_3 = i_3 + 1
while (i_3 s<= 4)
return c7node1
