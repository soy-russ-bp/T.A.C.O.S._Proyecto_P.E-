#include "Flags.h"
#pragma once
#include <sal.h>

#define OnTrueReturn (return)
#define OnFalseReturn (!return)
#define SalExt_Ptr_InNull_OutMaybeNull_ _Deref_pre_null_ _Deref_post_maybenull_
#define SalExt_Str_In_NotNull_ _In_z_ _Notnull_ const
