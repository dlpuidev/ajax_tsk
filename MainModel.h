#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QAbstractListModel>
#include <QColor>

class MainModel : public QAbstractListModel
{
    Q_OBJECT

    enum ColorRoles
    {
        ColorRole = Qt::UserRole + 1,
        IndexRole,
    };

private:
    QList<QColor> _colors;

public:
    MainModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

    void updateColor(int index, const QString& color);

    Q_INVOKABLE void setColor(int index, const QString& color);
    Q_INVOKABLE void moveItem(int from, int to);

public slots:
   void updateGridModel(const QString& color);
};

#endif // MAINMODEL_H
