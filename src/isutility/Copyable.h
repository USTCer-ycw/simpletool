#ifndef JET_BASE_COPYABLE_H
#define JET_BASE_COPYABLE_H

namespace istool
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class Copyable
{
};

};

#endif  // FTMD_BASE_COPYABLE_H
