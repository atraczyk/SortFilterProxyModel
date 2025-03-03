#include "proxyrole.h"
#include "qqmlsortfilterproxymodel.h"

namespace qqsfpm {

/*!
    \qmltype ProxyRole
    \inqmlmodule SortFilterProxyModel
    \ingroup ProxyRoles
    \brief Base type for the \l SortFilterProxyModel proxy roles.

    The ProxyRole type cannot be used directly in a QML file.
    It exists to provide a set of common properties and methods,
    available across all the other proxy role types that inherit from it.
    Attempting to use the ProxyRole type directly will result in an error.
*/

QVariant ProxyRole::roleData(const QModelIndex& sourceIndex, const QQmlSortFilterProxyModel& proxyModel, const QString &name)
{
    if (m_mutex.tryLock()) {
        QVariant result = data(sourceIndex, proxyModel, name);
        m_mutex.unlock();
        return result;
    }
    return {};
}

void ProxyRole::proxyModelCompleted(const QQmlSortFilterProxyModel &proxyModel)
{
    Q_UNUSED(proxyModel)
}

void ProxyRole::invalidate()
{
    Q_EMIT invalidated();
}

}
