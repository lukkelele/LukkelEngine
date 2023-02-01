#include <VertexBufferLayout_WINDOWS.h>

VertexBufferLayout_WINDOWS::VertexBufferLayout_WINDOWS()
{
  m_Stride = 0;
}

const char* VertexBufferLayout_WINDOWS::GetPlatform() { return "WINDOWS"; }
