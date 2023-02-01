// #include <VertexBufferLayout.h>
#if defined _WINDOWS_x64 || _WINDOWS_x86
#include <VertexBufferLayout_WINDOWS.h>
typedef VertexBufferLayout_WINDOWS VertexBufferLayout;
#else
#include <VertexBufferLayout_LINUX.h>
typedef VertexBufferLayout_LINUX VertexBufferLayout;
#endif




