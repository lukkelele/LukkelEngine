#include <VertexBufferLayout_LINUX.h>

VertexBufferLayout_LINUX::VertexBufferLayout_LINUX()
{
  m_Stride = 0;
}

const char* VertexBufferLayout_LINUX::GetPlatform() { return "LINUX"; }
