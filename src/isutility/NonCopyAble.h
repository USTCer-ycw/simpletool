#ifndef ISTOOL_ISUTILITY_NONCOPYABLE_H
#define ISTOOL_ISUTILITY_NONCOPYABLE_H

namespace istool
{
	namespace isutility
	{
		class NonCopyable
		{
		protected:
			NonCopyable() = default;
			~NonCopyable() = default;

			NonCopyable(const NonCopyable&) = delete;
			NonCopyable& operator=(const NonCopyable&) = delete;

		};
	}
}

#endif
