#ifdef MYLIBAPI

#else

#define MYLIBAPI extern "C" __declspec(dllimport)

#endif

MYLIBAPI int g_nResult;

MYLIBAPI int Add(int nLeft, int nRight);