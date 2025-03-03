#ifndef REGEXPFILTER_H
#define REGEXPFILTER_H

#include "rolefilter.h"

#include <QRegularExpression>

namespace qqsfpm {

class RegExpFilter : public RoleFilter {
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(PatternSyntax syntax READ syntax WRITE setSyntax NOTIFY syntaxChanged)
    Q_PROPERTY(Qt::CaseSensitivity caseSensitivity READ caseSensitivity WRITE setCaseSensitivity NOTIFY caseSensitivityChanged)

public:
    enum class PatternSyntax {
        RegExp,
        Wildcard,
        FixedString };
    Q_ENUM(PatternSyntax)

    explicit RegExpFilter(QObject *parent = nullptr);

    QString pattern() const;
    void setPattern(const QString& pattern);

    PatternSyntax syntax() const;
    void setSyntax(PatternSyntax syntax);

    Qt::CaseSensitivity caseSensitivity() const;
    void setCaseSensitivity(Qt::CaseSensitivity caseSensitivity);

protected:
    bool filterRow(const QModelIndex& sourceIndex, const QQmlSortFilterProxyModel& proxyModel) const override;

Q_SIGNALS:
    void patternChanged();
    void syntaxChanged();
    void caseSensitivityChanged();

private:
    void updatePattern();

    QRegularExpression m_regExp;
    Qt::CaseSensitivity m_caseSensitivity;
    PatternSyntax m_syntax = PatternSyntax::RegExp;
    QString m_pattern = m_regExp.pattern();
};

}

#endif // REGEXPFILTER_H
