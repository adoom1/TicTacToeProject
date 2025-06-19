// BoardStateDelegate.cpp
#include "BoardStateDelegate.h"
#include <QDebug>
#include <QTextOption>

BoardStateDelegate::BoardStateDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void BoardStateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Get the raw board state string from the model using a custom role
    QString boardState = index.data(Qt::UserRole + 1).toString();

    // If it's not the board state column or invalid data, let the default delegate handle it
    if (index.column() != 3 || boardState.isEmpty() || boardState.length() != 9) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Draw background
    painter->fillRect(option.rect, option.palette.base());

    // Define colors for drawing
    QColor xColor = QColor("#00ffff"); // Neon blue for X
    QColor oColor = QColor("#ff00ff"); // Neon pink for O
    QColor gridColor = QColor("#8a2be2"); // Purple grid lines

    // Calculate cell size within the given option.rect
    qreal cellSize = qMin(option.rect.width() / 3.0, option.rect.height() / 3.0);
    qreal boardSize = cellSize * 3;

    // Center the board drawing within the cell
    qreal startX = option.rect.x() + (option.rect.width() - boardSize) / 2.0;
    qreal startY = option.rect.y() + (option.rect.height() - boardSize) / 2.0;

    // Draw the grid lines
    painter->setPen(QPen(gridColor, 1)); // Reduced grid line thickness for better readability (from 2 to 1)
    for (int i = 1; i < 3; ++i) {
        painter->drawLine(QPointF(startX + i * cellSize, startY), QPointF(startX + i * cellSize, startY + boardSize)); // Vertical lines
        painter->drawLine(QPointF(startX, startY + i * cellSize), QPointF(startX + boardSize, startY + i * cellSize)); // Horizontal lines
    }

    // Define padding for X and O symbols relative to cell size
    // Increased padding from 0.15 to 0.25 for more space, and I'll keep this value.
    qreal padding = cellSize * 0.25;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            QChar cellValue = boardState.at(r * 3 + c);
            QRectF cellRect(startX + c * cellSize, startY + r * cellSize, cellSize, cellSize);

            // Draw X
            if (cellValue == 'X') {
                painter->setPen(QPen(xColor, 2)); // Reduced X line thickness from 4 to 2
                // Draw X as two lines, adjusted by padding
                painter->drawLine(cellRect.topLeft() + QPointF(padding,padding), cellRect.bottomRight() - QPointF(padding,padding));
                painter->drawLine(cellRect.topRight() + QPointF(-padding,padding), cellRect.bottomLeft() - QPointF(-padding,padding));
            }
            // Draw O
            else if (cellValue == 'O') {
                painter->setPen(QPen(oColor, 2)); // Reduced O line thickness from 4 to 2
                // Draw ellipse, adjusted by padding
                painter->drawEllipse(cellRect.adjusted(padding, padding, -padding, -padding));
            }
        }
    }

    painter->restore();
}

QSize BoardStateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // A 3x3 grid needs a certain minimum width and height.
    // Let's assume a minimum cell size for drawing (e.g., 30 pixels per sub-cell).
    const int minSubCellSize = 40; // Increased minimum size for better visibility
    const int desiredWidth = minSubCellSize * 3;
    const int desiredHeight = minSubCellSize * 3;

    // Return a size hint that ensures the board is visible.
    // We also consider the original size hint for other columns,
    // but for column 3 we enforce a minimum size.
    if (index.column() == 3) {
        return QSize(desiredWidth, desiredHeight);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}
