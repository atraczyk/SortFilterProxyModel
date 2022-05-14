#include "utils.h"

namespace qqsfpm {

int compareVariants(const QVariant &lhs, const QVariant &rhs)
{
    if (lhs.typeId() == QMetaType::QString && rhs.typeId() == QMetaType::QString) {
        const auto lhsValue = lhs.toString();
        const auto rhsValue = rhs.toString();
        if (lhsValue == rhsValue)
            return 0;
        return lhsValue.compare(rhsValue, Qt::CaseInsensitive);
    } else if (lhs.canConvert<int>() && rhs.canConvert<int>()) {
        const auto lhsValue = lhs.toInt();
        const auto rhsValue = rhs.toInt();
        if (lhsValue == rhsValue)
            return 0;
        return lhsValue < rhsValue ? -1 : 1;
    } else if (lhs.canConvert<qreal>() && rhs.canConvert<qreal>()) {
        const auto lhsValue = lhs.toReal();
        const auto rhsValue = rhs.toReal();
        if (qFuzzyCompare(lhsValue, rhsValue))
            return 0;
        return lhsValue < rhsValue ? -1 : 1;
    }

    qWarning() << "Don't know how to compare" << lhs << "against" << rhs << "- returning 0";
    return 0;
}

}
