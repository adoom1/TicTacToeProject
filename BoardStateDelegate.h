// BoardStateDelegate.h
#ifndef BOARDSTATEDELEGATE_H
#define BOARDSTATEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QVariant>

class BoardStateDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BoardStateDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    // Helper function to draw a single cell (X, O, or empty)
    void drawCell(QPainter *painter, const QRect &rect, char value, const QPalette &palette) const;
};

#endif // BOARDSTATEDELEGATE_H
