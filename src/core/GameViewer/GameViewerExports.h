#pragma once

#if defined(GameViewer_EXPORTS)
#	define GameViewerAPI __declspec(dllexport)
#else
#	define GameViewerAPI __declspec(dllimport)
#endif

#define GameViewerBegin extern "C++" { namespace GameViewer_space{
#define GameViewerEnd } }