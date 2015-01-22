#pragma once

#if defined(ISE_EXPORTS)
#	define ISEAPI __declspec(dllexport)
#else
#	define ISEAPI __declspec(dllimport)
#endif

#define ISEBegin extern "C++" { namespace ISE_space{
#define ISEEnd } }