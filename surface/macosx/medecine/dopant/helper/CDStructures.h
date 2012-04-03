#import <Foundation/Foundation.h>

/**
 * Types de données utilisés par Finder et dont on a besoin à un moment
 * ou à un autre...
 * Il y a beaucoup de void* car on cherche juste à avoir la taille de ces
 * structures.
 */
struct _NSSize {
    float width;
    float height;
};
struct _NSPoint {
    float x;
    float y;
};
struct _NSRect {
    struct _NSPoint origin;
    struct _NSSize size;
};
struct TUniString {
    void **_vptrTUniString;
    unsigned int fCapacity;
    unsigned int fLength;
    unsigned short *fBuffer;
};

typedef struct {
	void* fNodeRef;
	void* dummyValue1;
	void* dummyValue2;
	void* dummyValue3;
	void* dummyValue4;
} TFENode;

typedef struct {
	TFENode *_M_start;
	TFENode *_M_finish;
	TFENode *_M_end_of_storage;
} _Vector_impl;

typedef struct {
    _Vector_impl _M_impl;
} TFENodeVector;

typedef struct {
    struct OpaqueIconRef *fRef;
} TIconRef;