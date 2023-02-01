#include <VertexBufferLayout.h>


class VertexBufferLayout_WINDOWS : public VertexBufferLayout
{
public:
  virtual const char* GetPlatform();

  VertexBufferLayout_WINDOWS();
  // { m_Stride = 0; }

};
