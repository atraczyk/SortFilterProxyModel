#include "regexpfilter.h"
#include <QVariant>

namespace qqsfpm {

/*!
    \qmltype RegExpFilter
    \inherits RoleFilter
    \inqmlmodule SortFilterProxyModel
    \ingroup Filters
    \brief  Filters rows matching a regular expression.

    A RegExpFilter is a \l RoleFilter that accepts rows matching a regular rexpression.

    In the following example, only rows with their \c lastName role beggining with the content of textfield the will be accepted:
    \code
    TextField {
       id: nameTextField
    }

    SortFilterProxyModel {
       sourceModel: contactModel
       filters: RegExpFilter {
           roleName: "lastName"
           pattern: "^" + nameTextField.displayText
       }
    }
    \endcode
*/

/*!
    \qmlproperty bool RegExpFilter::pattern

    The pattern used to filter the contents of the source model.

    \sa syntax
*/
RegExpFilter::RegExpFilter(QObject *parent)
    : RoleFilter(parent), m_caseSensitivity(
          m_regExp.patternOptions().testFlag(
              QRegularExpression::CaseInsensitiveOption) ? Qt::CaseInsensitive : Qt::CaseSensitive)
{
}

QString RegExpFilter::pattern() const
{
    return m_pattern;
}

void RegExpFilter::setPattern(const QString& pattern)
{
    if (m_pattern == pattern)
        return;

    m_pattern = pattern;
    updatePattern();

    Q_EMIT patternChanged();
    invalidate();
}

/*!
    \qmlproperty enum RegExpFilter::syntax
    The pattern used to filter the contents of the source model.
    Only the source model's value having their \l RoleFilter::roleName data matching this \l pattern with the specified \l syntax will be kept.
    \value RegExpFilter.RegExp A rich Perl-like pattern matching syntax. This is the default.
    \value RegExpFilter.Wildcard This provides a simple pattern matching syntax similar to that used by shells (command interpreters) for "file globbing".
    \value RegExpFilter.FixedString The pattern is a fixed string. This is equivalent to using the RegExp pattern on a string in which all metacharacters are escaped.
    \sa pattern
*/
RegExpFilter::PatternSyntax RegExpFilter::syntax() const
{
    return m_syntax;
}

void RegExpFilter::setSyntax(RegExpFilter::PatternSyntax syntax)
{
    if (m_syntax == syntax)
        return;

    m_syntax = syntax;
    updatePattern();

    Q_EMIT syntaxChanged();
    invalidate();
}

/*!
    \qmlproperty Qt::CaseSensitivity RegExpFilter::caseSensitivity

    This property holds the caseSensitivity of the filter.
*/
Qt::CaseSensitivity RegExpFilter::caseSensitivity() const
{
    return m_caseSensitivity;
}

void RegExpFilter::setCaseSensitivity(Qt::CaseSensitivity caseSensitivity)
{
    if (m_caseSensitivity == caseSensitivity)
        return;

    m_caseSensitivity = caseSensitivity;
    QRegularExpression::PatternOptions patternOptions = m_regExp.patternOptions();
    if (caseSensitivity == Qt::CaseInsensitive)
        patternOptions.setFlag(QRegularExpression::CaseInsensitiveOption);
    m_regExp.setPatternOptions(patternOptions);
    Q_EMIT caseSensitivityChanged();
    invalidate();
}

bool RegExpFilter::filterRow(const QModelIndex& sourceIndex, const QQmlSortFilterProxyModel& proxyModel) const
{
    const QString string = sourceData(sourceIndex, proxyModel).toString();
    return m_regExp.match(string).hasMatch();
}

void RegExpFilter::updatePattern()
{
    if (m_syntax == PatternSyntax::FixedString)
        m_regExp.setPattern(QRegularExpression::escape(m_pattern));
    else if (m_syntax == PatternSyntax::Wildcard)
        m_regExp.setPattern(QRegularExpression::wildcardToRegularExpression(m_pattern));
    else
        m_regExp.setPattern(m_pattern);
}

}
