void* esi
void* var_58 = esi;
void list
read_six_numbers(arg1, &list)

int32_t edi = 0

// verifie que les nombres ne sont pas egaux et inferieur a 6
do
    if (list[edi] > 6)
        explode_bomb()
        noreturn
    int32_t ebx_1 = edi + 1
    if (ebx_1 <= 5)
        int32_t eax_3 = edi << 2
        do
            if (list[eax] == list[ebx_1])
                explode_bomb()
                noreturn
            ebx_1++
        while (ebx_1 <= 5)
    edi++
while (edi <= 5)


int32_t y_1 = 0
int32_t* c2node1
do
    void* cnode1 = &node1 // node
    int32_t i_1 = 1
    //int32_t yy_1 = y_1 
    if (list[y_1] > 1) // les element[y_1] > 1
        int32_t list_1 = list[y_1] // recupere element[y_1];
        cnode1 = &node1 // copie de node
        do
            cnode1 = *(cnode1 + 8) // decale de 8
            i_1++
        while (i_1 < list_1) 
    c2node1[y_1] = cnode1
    y_1++
while (y_1 <= 5)


int32_t* c4node1 = c2node1
int32_t i_2 = 1
do
    int32_t* c5node1 = &(c2node1[i_2])
    c2node1[2] = c5node1
    c2node1 = c5node1
    i_2++
while (i_2 <= 5)


c2node1[2] = 0
int32_t i_3 = 0
int32_t* c6node1 = c4node1
int32_t c7node1
do
    c7node1 = *c2node1
    if (c7node1 < *c2node1[2])
        explode_bomb()
        noreturn
    c2node1 = c2node1[2]
    i_3++
while (i_3 <= 4)

return c7node1
