#ifndef _LKENGINE_UUID_H
#define _LKENGINE_UUID_H

#include <stdint.h> // FIXME

namespace LukkelEngine {
	
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }

	private:
		uint64_t m_UUID;
	};
}


#endif
