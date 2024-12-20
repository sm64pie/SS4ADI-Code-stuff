#pragma once

/*
 These headers are necessary for SM64 'Object' struct to work
 */
extern "C"
{
    #include "types.h"
    #include "game/object_list_processor.h"
}
#include "object_fields.h"

/*
 I will be inheriting from 'Object' which is the normal sm64 object which has all the possible fields that could be accessed conveniently
 You must NOT add any more fields here or everything will break, you must use OBJECT_FIELD_S32(X), where [0x1b <= X <= 0x21]
 */
class DonutPlatform : Object
{
// Just a convenient alias
    using Type = DonutPlatform;

/*
 I defined some custom fields that sample object may use
 Notice that I added 'SampleObject' prefix, this is needed because defines are not a part of class
 If there is a better solution with 'using', tell me :3
 */
#define oSampleObjectFoo OBJECT_FIELD_OBJ(0x1b)
#define oSampleObjectBar OBJECT_FIELD_S32(0x1c)

/*
 'Proxied' functions use object at 0x80361160 to call class methods using casting.
 The behavior script will use proxied function to call it, check 'Behavior' in cpp file
 */
#define PROXIED_FUNCTION(x) void x(); static void s##x() { return reinterpret_cast<Type*>(gCurrentObject)->x(); }
    PROXIED_FUNCTION(Init)
    PROXIED_FUNCTION(Step)
#undef PROXIED_FUNCTION

public:
    static uintptr_t Behavior[];
};