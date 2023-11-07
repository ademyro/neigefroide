#ifndef nevec_mem_h
#define nevec_mem_h

#define INITIAL_CAP 4

#define ALLOC_ARR(type) \
    malloc(INITIAL_CAP * sizeof (type))
    
#define GROW_CAP(cap) \
    (cap) == 1 ? INITIAL_CAP : (cap) * 2

#define GROW_ARR(type, ptr, newSize) \
    realloc(ptr, (newSize) * sizeof (type))

#endif
