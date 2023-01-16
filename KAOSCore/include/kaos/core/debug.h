// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once

#ifdef _DEBUG
#include <assert.h>

#define KAOS_ENABLE_ITERATOR_VERIFY
#define KAOS_ENABLE_CONTAINER_VERIFY

#define KAOS_ASSERT(mesg)	assert(!mesg)
#else
#define KAOS_ASSERT(mesg)
#endif


#ifdef KAOS_ENABLE_ITERATOR_VERIFY
# define KAOS_ITERATOR_VERIFY(cond, mesg) if (!(cond)) { KAOS_ASSERT(mesg); }
#else
# define KAOS_ITERATOR_VERIFY(cond, mesg)
#endif

#ifdef KAOS_ENABLE_CONTAINER_VERIFY
# define KAOS_CONTAINER_VERIFY(cond, mesg) if (!(cond)) { KAOS_ASSERT(mesg); }
#else
# define KAOS_CONTAINER_VERIFY(cond, mesg)
#endif

