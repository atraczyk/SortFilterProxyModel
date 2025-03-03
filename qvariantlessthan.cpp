#include "qvariantlessthan.h"

namespace qqsfpm {

/*!
    \brief Less-than operator for generic QVariants

    For the pre Qt 6 versions the < operator is used, even though it's deprecated
    since 5.15, to avoid using complicated, potentially error-prone custom
    implementations and to keep consistency between 5.15 and earlier versions.
    Since Qt 6 QVariant::compare is used.
*/
bool lessThan(const QVariant &lhs, const QVariant &rhs)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return QPartialOrdering::Less == QVariant::compare(lhs, rhs);
#else
    return lhs < rhs;
#endif
}

} // namespace qqsfpm
