#include "MainModel.h"
#include <QDebug>

MainModel::MainModel(QObject *parent) : QAbstractListModel(parent)
{

}

int MainModel::rowCount(const QModelIndex &parent) const
{
    return _colors.count();
}

QVariant MainModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
        case ColorRole:
            return _colors[index.row()].name();

        case IndexRole:
            if (std::find(_colors.begin(), _colors.end(), _colors[index.row()]) != _colors.end()) {
              return std::distance(_colors.begin(), std::find(_colors.begin(), _colors.end(), _colors[index.row()]));
            } else {
              return -1;
            }

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> MainModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ColorRole] = "color";
    roles[IndexRole] = "index";
    return roles;
}

void MainModel::moveItem(int from, int to)
{
    if(from >= 0 && from < rowCount() && to >= 0 && to < rowCount() && from != to) {
        if(from == to - 1) {
            to = from++;
        }

        beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
        qInfo() << "model move from: " << from << " to: " << to;
        _colors.move(from, to);
        endMoveRows();
    }
}

void MainModel::updateGridModel(const QString& color)
{
    beginResetModel();
    _colors.push_back(color);
    endResetModel();
}

void MainModel::updateColor(int index, const QString& color)
{
    if (index >= 0 && index < rowCount()) {
        _colors[index] = color;
        emit layoutChanged();
    }
}

void MainModel::setColor(int index, const QString& color)
{
    updateColor(index, color);
}
