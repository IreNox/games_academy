#include "hw/threading/read_write_lock.h"

namespace hw
{
	bool ReadWriteLock::create()
	{
		InitializeSRWLock( &m_lock );
		return true;
	}

	void ReadWriteLock::destroy()
	{
	}

	void ReadWriteLock::lockRead()
	{
		AcquireSRWLockShared( &m_lock );
	}

	void ReadWriteLock::unlockRead()
	{
		ReleaseSRWLockShared( &m_lock );
	}

	void ReadWriteLock::lockWrite()
	{
		AcquireSRWLockExclusive( &m_lock );
	}

	void ReadWriteLock::unlockWrite()
	{
		ReleaseSRWLockExclusive( &m_lock );
	}
}
